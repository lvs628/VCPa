#include <stdlib.h>
#include "TAppProcesses.h"
#include "tappdrv.h"
#include "TDataDrv.h"
#include "netfsa.h"
#include "SetVarNetFsa.h"
#include "VarSetting.h"
#include "SetVarSetting.h"
#include "SetVarCircuit.h"
#include "TSetVarRead.h"
#include "SetVarPrmProc.h"
#include "SetVarCircuit.h"
#include "TAppCore.h"
#include "SetVarFSA.h"
#include "csetlocvar.h"
#include "ArrayNetFsa.h"
#include "TAppCore.h"

TAppProcesses::TAppProcesses(void)
    :TAppVar()
{
    pTAppDrv = nullptr;
    for (int i=0; i<10; i++ ) {
        arLibraryFsa[i] = nullptr;
    }
    ReloadVCPa();
}


TAppProcesses::~TAppProcesses(void)
{
    if (pTAppDrv)
        delete pTAppDrv;
}

bool TAppProcesses::LoadConfiguration(void)
{
    pTAppDrv	= new TAppDrv(this);
    /*
        MaxSpeed;1;6;MaxSpeed;1;0;1;0;1;0;1;0;;0;1000;0;0;0;1;1;
        Setting1;1;1;1;10;нет;0;InitFsaWorld;1;0;1;not(var);1;0;1;1;InitFsaWorld;0;1000;1;0;0;1;1;
        Sensors;1;1;1;10;нет;0;Sensors;1;0;0;0;1;0;0;0;;0;1000;0;0;0;1;1;
        Models;1;1;0;20;нет;0;Models;1;0;0;0;1;0;0;0;;0;1000;0;0;0;1;1;
    */
//    string strV= "Setting1;1;2;InitFsaWorld;1;0;InitFsaWorld;1;1;"; // 2msec
    string strV= "Setting1;1;1;InitFsaWorld;1;0;InitFsaWorld;1;1;"; // 1msec
//    string strV= "Setting1;1;10;InitFsaWorld;1;0;InitFsaWorld;1;1;";    // 10msec
    CVarSetting var(this, strV);
    pSetVarSetting->Add(var);
    string str = "Setting1";
    pCVarSetting = pSetVarSetting->GetAddressVar(str);

    bIfStopAllTasks = pCVarSetting->bIfStopAllTasks;
    strCurrentWorldFSA = pCVarSetting->strName;
//	загрузка базовой конфигурации (если указано в последнем параметре переменной конфигурации (указано в <>):
//	--- vSetting: Setting1;1;1;1;6;Пресс ТИСНУМ;0;InitFsaWorld;0;0;1;0;<0>;
// загрузка доп. конфигурации из той библиотеки в кот. стоит соответствующий параметр
// например, для библиотеки vLibrary.txt: 8;;1;1;<1>;Press10
    LoadConfig(); // коммент 26.06.2024 - фактически пустой вызов, т.к. будет выполнен выход сразу см. строку 324 ниже
    pTAppDrv->pSetVarRead->CreateLink();
    StopAllTasks("");
    return true;
}

void TAppProcesses(void)
{
}

bool TAppProcesses::LinkVar()
{
/*
    TAppVar::LinkVar();
    pSetVarCircuit->CreateLink();
    pTAppDrv->pSetVarRead->CreateLink();

    TIIteratorNetFsa IIteratorNetFsa;
    IIteratorNetFsa = pCArrayNetFsa->IArrayNetFsa.begin();
// загрузить список типов переменных для каждого автоматного пространства
    TIteratorCVarSetting nextSet = pSetVarSetting->pArray->begin();
    while (nextSet != pSetVarSetting->pArray->end()) {
//        CVarSetting *pCV = &(*nextSet);
        if (nextSet->pTNetFsa) {
            nextSet->pTNetFsa->strListTypeVar.clear();		// ???????? ?????? ????? ??????????
            nextSet->pTNetFsa->LoadingTypesVar();
            nextSet->pTNetFsa->pCSetVar->pArray->clear();	// ???????? ?????? ?????? ??????????
        }
        nextSet++;
    }
    // создать списки переменных (ссылок на массив из глобальных переменных) автоматных пространств
    TIteratorVarRead next= pTAppDrv->pSetVarRead->pArray->begin();
    while (next!=pTAppDrv->pSetVarRead->pArray->end()) {
//		TVarRead var= *next;
        TNetFsa *pNet = nullptr;
        pNet = pCArrayNetFsa->GetAdressNetFsa(next->strNameNetFsa);
        TVarRead *pvar= &(*next);
        if (pNet) {
            pvar->pTNetFsa = pNet;
            pNet->pCSetVar->Add(*next);
        }
        else {
            pNet = pCArrayNetFsa->GetAdressNetFsa(pCVarSetting->strNetFsaDefault);
            pvar->pTNetFsa = pNet;
            if (pNet) {
                pNet->pCSetVar->Add(*next);
                pvar->strNameNetFsa = pCVarSetting->strNetFsaDefault;
                pSetVarSetting->SetSaveSet(true);
            }
        }
        next++;
    }
*/        
    return true;
}

CLocVar* TAppProcesses::InsertVar(CVar* pVar, LFsaAppl *pL) {

    CLocVar* pV = GetAddressVar(pVar->strName.c_str(), pL);

    if (pTAppDrv->pSetVarRead->Add(*static_cast<TVarRead*>(pVar))) {
        pTAppDrv->LinkVar();
        pTAppDrv->pTAppCore->pSetVarFSA->UpdateLinks("",0);		// ???????? ????? ??? ????????? ? ?????? FTrends2D (????? 2D-???????)
    }
    return pV;
}

CLocVar* TAppProcesses::ReplaceVar(CVar* pVar, LFsaAppl *pL) {
    TVarRead *p = (TVarRead*)GetAddressVar(pVar->strName.c_str(), pL);

    if (p->IfEqu(*static_cast<TVarRead*>(pVar)))
        return nullptr;

    pTAppDrv->pSetVarRead->Replace(*static_cast<TVarRead*>(pVar));
    pTAppDrv->pTAppCore->LinkVar();
    return static_cast<CLocVar*>(pVar);
}

CLocVar* TAppProcesses::DeleteVar(const char* nam, LFsaAppl *pL) {
    CLocVar* pV = GetAddressVar(nam, pL);
    if (pV) {
        TVarRead* p = pTAppDrv->pSetVarRead->GetAddressVar(nam);
        if (p) {
            pTAppDrv->pSetVarRead->Delete(*p);
            pTAppDrv->pTAppCore->pSetVarFSA->UpdateLinks("",0);		// ???????? ????? ??? ????????? ? ?????? FTrends2D (????? 2D-???????)
            pTAppDrv->pTAppCore->LinkVar();
            }
        return pV;
    }
    return nullptr;
}
CLocVar* TAppProcesses::GetAddressVar(const char* nam, LFsaAppl *pLFs)
{
//	TVarBase* pv = nullptr;
    CVar* pv = nullptr;
//    CVar *pCVar=nullptr;
    CLocVar *pCLocVar;
    string strNameVar = string(nam);
    unsigned int nPosPoint=0;
    nPosPoint=strNameVar.find_first_of(".");
//    pCVar = nullptr;
    pCLocVar = nullptr;
    if (int(nPosPoint)<0) {
//		pCVar	= GetAddressVar(strNameVar.c_str());
        pv = pTAppDrv->pSetVarRead->GetAddressVar(nam);
    }
    else {
        if (nPosPoint) {
            char ach[255];
            memset(ach,'\0',sizeof(ach));
            strNameVar.copy(ach,nPosPoint,0);
            string strNameVarFSA = string(ach);
            LFsaAppl *pL=nullptr;
            CVarFSA *pV = GetAddressVarFSA(strNameVarFSA);
            if (pV) {
//				if (pLFs && (pLFs != pV->pLFsaAppl))
//					return nullptr;				// ??????????? ???. ????? ?? ??? ???? ??????? (??? ???????, ??? ??, ???????, ??????!)
                memset(ach,'\0',sizeof(ach));
                unsigned int n = strNameVar.length() - nPosPoint;
                strNameVar.copy(ach,n,nPosPoint+1);
                string strNameVar = string(ach);
                pL = pV->pLFsaAppl;
                if (pL) {
                    pCLocVar = pL->pCSetLocVar->GetAddressVar(strNameVar);
                    if (pCLocVar) {
                        if (!pCLocVar->pLFsaAppl) {
                            pCLocVar->pLFsaAppl = pL;
//                            TNetFsa *pNet = pCArrayNetFsa->GetNetFsa(pV->strNameNetFsa, "");
//                            pCLocVar->pTNetFsa = pNet;
                            pCLocVar->pTNetFsa = pL->GetPointerToNet();
                        }
                        else {
                            if (!pCLocVar->pTNetFsa) {
                                pCLocVar->pTNetFsa = pCLocVar->pLFsaAppl->GetPointerToNet();
                            }

                        }
                    }
                    return pCLocVar;
                }
            }
        }
        else {
            if (pLFs) {
                char ach[255];
                memset(ach,'\0',sizeof(ach));
                unsigned int n = strNameVar.length();
                strNameVar.copy(ach,n,1);
                string strNameVar = string(ach);
                pCLocVar = pLFs->pCSetLocVar->GetAddressVar(strNameVar);
                return pCLocVar;
            }
            else {
                return nullptr;
            }
        }
    }
    return static_cast<CLocVar*>(pv);
}

static TIteratorVarRead nextVar;
CVar* TAppProcesses::IterAddressVar(bool begin)
{
    if (begin) {
        nextVar= pTAppDrv->pSetVarRead->pArray->begin();
        if (nextVar == pTAppDrv->pSetVarRead->pArray->end())
            return nullptr;
        TVarBase* pv = &(*nextVar);
        nextVar++;
        return pv;
    }
    else {
        if (nextVar == pTAppDrv->pSetVarRead->pArray->end())
            return nullptr;
        else {
            TVarBase* pv = &(*nextVar);
            nextVar++;
            return pv;
        }
    }
}

#include <fstream>

static string strSavePathConfig;
static string strFil = "";
//*
int TAppProcesses::LoadConfig()
{
//	настройки
//1)	формирование массива параметров процессов
//    string strFil  = vParameterProcesses;
//    pSetVarPrmProc->ReadDat(strPath,strFil);

// создание массива ссылок на заголовки процессов
//2) Создание переменных автоматов-процессов
// Circuit;FCircuit;Circuit;paired relationships of variables;0;0;0;0;SysPrc;1;CDlgCircuit;1;Circuit;692;1212;555;255;0;0;0;fsaprc10;0;<.,current state,7,1,,0,0,0,0,0,0,0,0,>
    string vFSA= "Circuit;FCircuit;Circuit;0;0;0;0;SysPrc;1;1;<.,current state,7,1,,0,0,0,0,0,0,0,0,>";
    CVarFSA var((TAppCore*)this,vFSA);
    pSetVarFSA->Add(var);
//    strFil  = vFSA;
//    pSetVarFSA->ReadDat(strPath, strFil);

    pTAppDrv->pSetVarRead->CreateLink();

//    strFil  = string("vColorSensor.txt");
//    pTAppDrv->pSetColorSensor->ReadDat(strPath,strFil);

//    strFil  = vCircuit;
//    pSetVarCircuit->ReadDat(strPath, strFil);
    pSetVarCircuit->CreateLink();
    pVarDeltaTimeSystem = nullptr;
    pVarDeltaTimeSystem = nullptr;
//===========================================================================================
//=============    создаем масссив автоматов        ===========================================
//=============  запуская функции инициализации библиотек   =================================
//===========================================================================================
// грузим автоматные объекты библиотек
//    int n = pSetVarFsaLibrary->ArrayI.size();
//    TIteratorICVarFsaLibrary itr= pSetVarFsaLibrary->ArrayI.begin();
//    while (itr!=pSetVarFsaLibrary->ArrayI.end()) {
//        CVarFsaLibrary *var=*itr;
//        var->LoadClass();
//        itr++;
//    }
// грузим индивидуальные конфигурации библиотек
//    itr= pSetVarFsaLibrary->ArrayI.begin();
//    while (itr!=pSetVarFsaLibrary->ArrayI.end()) {
//        CVarFsaLibrary *var=*itr;
//        var->LoadConfig();
//        itr++;
//    }
// проверить в автоматных связь автоматов с библиотеками
//    n = pSetVarFSA->pArray->size();
//    CIteratorVarFSA next=pSetVarFSA->pArray->begin();
//    while (next != pSetVarFSA->pArray->end()) {
//        string str = next->strNameFsaLibrary;
//        if (str==""||str=="нет такой библиотеки для автомата") {
//            CVarFsaLibrary *pLib = GetAddrLibForFsa(next->strNameFsa, &*next);
//            if (pLib)
//                next->strNameFsaLibrary = pLib->strNameLib;
//            else
//                next->strNameFsaLibrary = "нет такой библиотеки для автомата";
//        }
//        next++;
//    }


//=====================================================================
//========    создаем процессы                =========================
//=====================================================================
    // загрудить автомат функцией загрузки переменной
    // создание процесса произойдет, если имя автомата совпадает с именем
    // автомата, указанным в переменной
    pSetVarFSA->CreateProcesses();
//=====================================================================

    LinkVar();
    // вставлено, т.к. могут быть переменные автоматных процессов
    // выше вставлено на тот случай, если не будет создан процесс инициализации, а файл (vVarInit) с переменными будет
//    pSetVarInit->CreateLink();
//    pSetVarInit->ApplyAny(nullptr);			// ???????????? ?????????? ?????????? ????????? ??????
    return true;
}
