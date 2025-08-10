#include "stdafx.h"
#include "Sttbl.h"
#include "lfsaappl.h"
#include <string>
using namespace std;
#include "Wsp.h"
#include "netfsa.h"
#include "csetlocvar.h"
#include "StackTsk.h"
#include "StackWsp.h"
#include "TAppCore.h"
#include "FDelay.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             fs_tbl
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
fs_tbl::fs_tbl(LListState *pAdt, FncClassX *pAdx, FncClassY *pAdy)
{
    adt= pAdt;
    adx=pAdx;
    ady=pAdy;
}

fs_tbl::~fs_tbl(){}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             fs_dbg
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
fs_dbg::fs_dbg(string szName)
{
 nameFsa = szName;
}
fs_dbg::~fs_dbg() { }

LFsaAppl::LFsaAppl()
     :fs_tbl(nullptr,nullptr,nullptr),fs_dbg("NONAME")
{
    p2pck       = 0;
    pTAppCore	= nullptr;
    pCVarFSA	= nullptr;
    adt=nullptr; adx= nullptr; ady= nullptr;
    ADT = nullptr; ARC_T = ADT; ARC_B= ARC_T; M_X= 0;
    pWSP=nullptr; nOkProcess=true; nErrorProcess=0;
    SqmTable = new LListState();
    strError	= "";
    strOk		= "";
    FClearOk();
    FClearError();
//	bIfLFsaHdr = false;
    pLFsaHdr = nullptr;
    strNameVarFsaNew = nameFsa;
    pTAppCore	= nullptr;
    pCVarFSA	= nullptr;
    pVarPrmProc = nullptr;
    pTNetFsa	= nullptr;
    pCSetLocVar = nullptr;
    bIfViewArc	= false;
    pParFDelay = nullptr;
    pCFDelay	= nullptr;
    bIfCall = false;
    nModeVar = 0;
    bIfLoad = false;
}

LFsaAppl::LFsaAppl(LArc* aT, string name, CVarFSA *pCVF)
     :fs_tbl(nullptr,nullptr,nullptr),fs_dbg(name)
{
    p2pck       = 0;
    pTBL		= aT;
    pTAppCore	= nullptr;
    pCVarFSA	= pCVF;
    strError	= "";
    strOk		= "";
    FClearOk();
    FClearError();
    SqmTable = new LListState;
    if (aT) {
        SqmTable->Create(aT); 
        adt=SqmTable;
        X[0]=&LFsaAppl::X1;   X[1]=&LFsaAppl::X2;    X[2]=&LFsaAppl::X3;
        X[3]=&LFsaAppl::X4;   X[4]=&LFsaAppl::X5;    X[5]=&LFsaAppl::X6;
        X[6]=&LFsaAppl::X7;   X[7]=&LFsaAppl::X8;    X[8]=&LFsaAppl::X9;
        X[9]=&LFsaAppl::X10;  X[10]=&LFsaAppl::X11;  X[11]=&LFsaAppl::X12;
        X[12]=&LFsaAppl::X13; X[13]=&LFsaAppl::X14;  X[14]=&LFsaAppl::X15;
        X[15]=&LFsaAppl::X16;
        X[16]=&LFsaAppl::X17; X[17]=&LFsaAppl::X18;  X[18]=&LFsaAppl::X19;
        X[19]=&LFsaAppl::X20; X[20]=&LFsaAppl::X21;  X[21]=&LFsaAppl::X22;
        X[22]=&LFsaAppl::X23; X[23]=&LFsaAppl::X24;  X[24]=&LFsaAppl::X25;
        X[25]=&LFsaAppl::X26; X[26]=&LFsaAppl::X27;  X[27]=&LFsaAppl::X28;
        X[28]=&LFsaAppl::X29; X[29]=&LFsaAppl::X30;  X[30]=&LFsaAppl::X31;
        X[31]=&LFsaAppl::X32;
        Y[0]=&LFsaAppl::y1;   Y[1]=&LFsaAppl::y2;    Y[2]=&LFsaAppl::y3;
        Y[3]=&LFsaAppl::y4;   Y[4]=&LFsaAppl::y5;    Y[5]=&LFsaAppl::y6;
        Y[6]=&LFsaAppl::y7;   Y[7]=&LFsaAppl::y8;    Y[8]=&LFsaAppl::y9;
        Y[9]=&LFsaAppl::y10;  Y[10]=&LFsaAppl::y11;  Y[11]=&LFsaAppl::y12;
        Y[12]=&LFsaAppl::y13; Y[13]=&LFsaAppl::y14;  Y[14]=&LFsaAppl::y15;
        Y[15]=&LFsaAppl::y16;
        Y[16]=&LFsaAppl::y17; Y[17]=&LFsaAppl::y18;  Y[18]=&LFsaAppl::y19;
        Y[19]=&LFsaAppl::y20; Y[20]=&LFsaAppl::y21;  Y[21]=&LFsaAppl::y22;
        Y[22]=&LFsaAppl::y23; Y[23]=&LFsaAppl::y24;  Y[24]=&LFsaAppl::y25;
        Y[25]=&LFsaAppl::y26; Y[26]=&LFsaAppl::y27;  Y[27]=&LFsaAppl::y28;
        Y[28]=&LFsaAppl::y29; Y[29]=&LFsaAppl::y30;  Y[30]=&LFsaAppl::y31;
        Y[31]=&LFsaAppl::y32;
        adx= X; ady= Y;
        if (adt->pRoot) {
            if (adt->pRoot->ListArc.pRoot) {
                ADT=&adt->pRoot->ListArc.pRoot->FsaArc;
            }
        }
    }

        /*        
        try {
            ADT = &adt->pRoot->ListArc.pRoot->FsaArc;
        } catch (const std::exception& e) {
            Serial.printf("Ошибка: %s\n", e.what());
        }
    }
*/        
    ARC_T = ADT; ARC_B= ARC_T; M_X= 0;
    pWSP=nullptr;
//	bIfLFsaHdr = false;
    pLFsaHdr = nullptr;
    strNameVarFsaNew = nameFsa;
    pVarPrmProc = nullptr;
    pCSetLocVar = new CSetLocVar();
    pTNetFsa	= nullptr;
    bIfViewArc	= false;
    nModeVar	= 0;			// режим выбора переменных (см. диалог Глобальные+локальные)
    pParFDelay = nullptr;
    pCFDelay	= nullptr;
    bIfCall = false;
    bIfLoad = false;

}
LFsaAppl::~LFsaAppl() {
    delete SqmTable;
    if (pCSetLocVar) { delete pCSetLocVar; pCSetLocVar = nullptr; }
}

void LFsaAppl::run() {}

bool LFsaAppl::FInit()
{
    FCreationOfLinksForVariables();
    if (pCVarFSA) {
//        string *pStr = &pCVarFSA->strListLocalVar;
        return true;
    }
    else {
        return false;
    }
}
// создание ссылок для переменных процесса
// возвращает true, если установлена/обновлена хотя бы одна новая ссылка на любую из переменных процесса
bool LFsaAppl::FCreationOfLinksForVariables()
{
    CreateLocVar(".",	CLocVar::vtFsa, "current state");
//	создавать только там, где это необходимо (см. например блоки FControl, FMotor библиотеки fsagdip
//	pVarIfLButtonDown = CreateLocVar("bIfLButtonDown",	CLocVar::vtBool, "реакция на лев.кнопку мышки");
//	pVarIfRButtonDown = CreateLocVar("bIfRButtonDown",	CLocVar::vtBool, "реакция на прав.кнопку мышки");
    return true;				//
}

string  LFsaAppl::FGetNameFsa() const {return nameFsa;}

CLocVar* LFsaAppl::CreateLocVar(string namVar, unsigned int unType, string strComment, bool bSave, string strInit, string strNameNetFsa)
{
    CLocVar *pCLocVar;	CLocVar var; var.unTypeVar = unType;
    var.pLFsaAppl = this; var.pLFsaType = this; var.bIfInit = true;	var.bIfLocal = true;
    var.strName = namVar;	var.strComment = strComment;
    var.strNameNetFsa = strNameNetFsa;
    var.pTNetFsa = pTAppCore->GetAdressNetFsa(strNameNetFsa);
    pCLocVar = pCSetLocVar->GetAddressVar(namVar);
    if (pCLocVar) {
    }
    else {
         var.strInitValue = strInit;
        if (!var.bIfInit) {
            var.SetDataSrc(this,0.0);
            var.SetDataSrc(this,"", this);
        }
        else {
            var.strInitValue = strInit;
        }
        bool bAdd = pCSetLocVar->Add(var, bSave);
        if (bAdd) {
            pCLocVar = pCSetLocVar->GetAddressVar(namVar);
            if (pCLocVar->bIfInit) {
                if (pCLocVar->unTypeVar == CVar::vtString) {
                    pCLocVar->SetDataSrc(nullptr, var.strInitValue, nullptr);
                    pCLocVar->UpdateVariable();
                }
                else {
                    string sss;
                    if (pCLocVar->unTypeVar == CVar::vtFsastate) {
                        sss = pCLocVar->strng;
                    }
                    double d=0;
                    if (pCLocVar->strInitValue!="")
                        d = stod(pCLocVar->strInitValue);
                    pCLocVar->SetDataSrc(nullptr, d);
                    pCLocVar->UpdateVariable();
                    if (pCLocVar->unTypeVar == CVar::vtFsastate) {
                        pCLocVar->strng = sss;
                    }
                }
            }
        }
    }
    return pCLocVar;
}
//	установка/сброс блокировки определенным процессом
bool	LFsaAppl::FSetLocking(bool bSet, LFsaAppl *pOwner, string strNameVar)
{
    return false;
}

string	LFsaAppl::FGetNameVarFSA() const
{
    if (pCVarFSA != nullptr) {
        return pCVarFSA->strName;
    }
    return "";
}

int  LFsaAppl::FIsActiveTask()
{
    if (pCVarFSA == (CVarFSA*)0xfeeefeee)
        return false;
    bool b = FIfStop();
    if (b) return !b;
// анализ указателя this на nullptr (4 - это смещение в сегменте?)
    if (pCVarFSA == (CVarFSA*)0xfeeefeee) {
//        printf("FIsActiveTask-1(false)\n");
        return false;
    }
    if (pCVarFSA == (CVarFSA*)0x0000000f) {
//        printf("FIsActiveTask-2(false)\n");
        return false;
    }
    LFsaAppl* l= (LFsaAppl*)04;
    if (!pCVarFSA&&this ==l) {
//        printf("FIsActiveTask-3(false)\n");
        return 0;
    }
    if (!pCVarFSA&&!pWSP) {
//        printf("FIsActiveTask-4(false)\n");
        return 0;
    }
    else {
//        printf("FIsActiveTask-5(true)\n");
        return true;
    }
}

bool LFsaAppl::FIfStop()
{
    TASK *pTask = FGetTask();
    static TNetFsa Net = *GetPointerToNet();
    bool bSt = pNet->IfStopTask(pTask);
    if (bSt) return bSt;

    if (pWSP) {
        return pWSP->pTask->pNetFsa->IfStopTask(pWSP->pTask);
    }
    else
        return false;
//    return false;
}

string LFsaAppl::FGetState(int nNum)
{
    if (!this->pWSP) return "";
    if (!this->pWSP->pTask) return "";
    WSP *pWSPF,*pWSPB, *pWSP;
//#include <strstream>
//    int nRangeCall=0;
    pWSP = this->pWSP;	// указатель на след элемент
    pWSPF = this->pWSP->pTask->w_fl;	// указатель на след элемент
    pWSPB = this->pWSP->pTask->w_bl;	// на предыдущий элемент
    string sss = "";
    if (!pWSP) return sss;
    if (pWSP->arc_t) {
        if (!pWSP->arc_t->pNextState)
    //		return "00";
            return pWSP->arc_t->szSt1;	// исправлено 2015_05_28_07_39
        sss = string(pWSP->arc_t->pNextState->szName);
    }
    else {
        return "00";	// исправлено 2016_05_30_07_39
    }

    if (pWSPF == pWSPB) {
    }
    else {
    }
    if (!FIsActiveTask()) return "not active";

    if (pWSPF->flink==pWSPF->blink) {
        if (pWSPF->arc_t) return pWSPF->arc_t->szSt1;	// исправлено 07.10.2005
        return "00";
    }
    else {
        if (nNum==0) {
            return pWSPF->arc_t->szSt1;
        }
        else if (nNum<0) {
            if (pWSPB->arc_t) {
                return pWSPB->arc_t->szSt1;
            }
            else {
                if (pWSPB->nNumCall != 0) {
                    const char *pch = pWSPB->blink->arc_t->pNextState->ListArc.pRoot->FsaArc.szSt1;
                    return pch;
                }
                else {
                    return "00";
                }
            }
        }

    }
    return "";
}
//===================================================================
//									                       GetTask
//===================================================================
TASK* LFsaAppl::FGetTask()
{
/*    
    if (!pWSP)
        return nullptr;
    return pWSP->pTask;
*/    
    return nullptr;
}

TNetFsa* LFsaAppl::GetPointerToNet()
{
    return pTNetFsa;
}

bool LFsaAppl::FUpdateLinks(string name, int nT) {
    if (name == "") return true;
    if (name == nameFsa) return true;
    return false;
};

LFsaAppl* LFsaAppl::Create(CVarFSA *pCVF) { return new LFsaAppl(pTBL, nameFsa, pCVarFSA); };

void LFsaAppl::FResetActions() {
    bIfLoad = false;
    if (pWSP->bCall)
        return;
    if (pCFDelay) {
        delete pCFDelay;
        pCFDelay = nullptr;
    }
//    bIfReset = false;
}

void  LFsaAppl::FStop()
{
    TASK *pTask = FGetTask();
    TNetFsa* pNet = GetPointerToNet();
    pNet->StopTask(pTask);
    return;

    if (pWSP) {
        pWSP->pTask->pNetFsa->StopTask(pWSP->pTask);
////		if (!pWSP->pTask->pNetFsa->bStopAllTask) {
////			 pWSP->pTask->pNetFsa->bStopAllTask=true;
        //	 pWSP->pTask->pid->stop= 1;
        //	 pWSP->pTask->remque();
        //	 pWSP->pTask->insque(pWSP->pTask->pNetFsa->wait_task.blink);
//		}
    }
}


void  LFsaAppl::FStart()
{
    TASK *pTask = FGetTask();
    TNetFsa* pNet = GetPointerToNet();
    pNet->StartTask(pTask);
    return;

    if (pWSP) {
        pWSP->pTask->pNetFsa->StartTask(pWSP->pTask);
//		if (pWSP->pTask->pNetFsa->bStopAllTask) {
//			 pWSP->pTask->pNetFsa->bStopAllTask=false;
//		}
    }
}

string  LFsaAppl::FGetNameProcess() const {
    string str = nameFsa + "." + nameFsaProcess;
    return str;
//	return pWSP->pTask->name;
}

void  LFsaAppl::ExecuteThreadStep()
{
    bIfRunThread = true;
}

string LFsaAppl::FDbgViewState(UINT id)
{
    string strSt="";
    strSt = FGetState();
    if (bIfViewArc) {
    }
    return strSt;
}

void LFsaAppl::ELSE() { }

void LFsaAppl::MealyLoop() { }

void LFsaAppl::FResetAppl() {
//    if (pWSP->bCall) {
//        int n = 0;
//    }
    string str = FGetNameVarFSA();
    bIfReset = true;
    pWSP->arc_t = ADT;  // переход в начало таблицы переходов автомата
    FInit();
    FResetActions();
}

int LFsaAppl::FGetRange()
{
    if (this->pWSP) {
        return this->pWSP->nNumCall;
    }
    else
        return -1;
}
void LFsaAppl::FClearOk()
{
    pFsaApplError = nullptr;
//*
    nOkProcess = 0;
    if (!strOk.empty()) {
        int nsize = int(strOk.size());
        if (nsize) {
            int nStart= int(strOk.find_first_of(":"));
            if (nStart>0)
                strOk.erase(uint(nStart+1),uint(nsize));
            else
                strOk.erase(strOk.begin(),strOk.end());
        }
    }
//*/
}

void LFsaAppl::FClearError()
{
    pFsaApplError = nullptr;
    nErrorProcess = 0;
    if (!strError.empty()) {
        int nsize = int(strError.size());
        if (nsize) {
            int nStart=int(strError.find_first_of(":"));
            if (nStart>0)
                strError.erase(uint(nStart+1), uint(nsize));
            else
                strError.erase(strOk.begin(),strOk.end());
        }
    }
}

//===================================================================
//                   x1 --- x16
//===================================================================
int LFsaAppl::x1(){return 0;}   int LFsaAppl::x2(){return 0;}
int LFsaAppl::x3(){return 0;}   int LFsaAppl::x4(){return 0;}
int LFsaAppl::x5(){return 0;}   int LFsaAppl::x6(){return 0;}
int LFsaAppl::x7(){return 0;}   int LFsaAppl::x8(){return 0;}
int LFsaAppl::x9(){return 0;}   int LFsaAppl::x10(){return 0;}
int LFsaAppl::x11(){return 0;}  int LFsaAppl::x12(){return 0;}
int LFsaAppl::x13(){return 0;}  int LFsaAppl::x14(){return 0;}
int LFsaAppl::x15(){return 0;}  int LFsaAppl::x16(){return 0;}
int LFsaAppl::x17(){return 0;}  int LFsaAppl::x18(){return 0;}
int LFsaAppl::x19(){return 0;}  int LFsaAppl::x20(){return 0;}
int LFsaAppl::x21(){return 0;}  int LFsaAppl::x22(){return 0;}
int LFsaAppl::x23(){return 0;}  int LFsaAppl::x24(){return 0;}
int LFsaAppl::x25(){return 0;}  int LFsaAppl::x26(){return 0;}
int LFsaAppl::x27(){return 0;}  int LFsaAppl::x28(){return 0;}
int LFsaAppl::x29(){return 0;}  int LFsaAppl::x30(){return 0;}
int LFsaAppl::x31(){return 0;}  int LFsaAppl::x32(){return 0;}
inline int LFsaAppl::X1() { if (x1()) { p2pck|=bit0; return 1; } else { p2pck&=~bit0; return 0; } }
inline int LFsaAppl::X2() { if (x2()) { p2pck|=bit1; return 1; } else { p2pck&=~bit1; return 0; } }
inline int LFsaAppl::X3() { if (x3()) { p2pck|=bit2; return 1; } else { p2pck&=~bit2; return 0; } }
inline int LFsaAppl::X4() { if (x4()) { p2pck|=bit3; return 1; } else { p2pck&=~bit3; return 0; } }
inline int LFsaAppl::X5() { if (x5()) { p2pck|=bit4; return 1; } else { p2pck&=~bit4; return 0; } }
inline int LFsaAppl::X6() { if (x6()) { p2pck|=bit5; return 1; } else { p2pck&=~bit5; return 0; } }
inline int LFsaAppl::X7() { if (x7()) { p2pck|=bit6; return 1; } else { p2pck&=~bit6; return 0; } }
inline int LFsaAppl::X8() { if (x8()) { p2pck|=bit7; return 1; } else { p2pck&=~bit7; return 0; } }
inline int LFsaAppl::X9() { if (x9()) { p2pck|=bit8; return 1; } else { p2pck&=~bit8; return 0; } }
inline int LFsaAppl::X10() { if (x10()) { p2pck|=bit9; return 1; } else { p2pck&=~bit9; return 0; } }
inline int LFsaAppl::X11() { if (x11()) { p2pck|=bit10; return 1; } else { p2pck&=~bit10; return 0; } }
inline int LFsaAppl::X12() { if (x12()) { p2pck|=bit11; return 1; } else { p2pck&=~bit11; return 0; } }
inline int LFsaAppl::X13() { if (x13()) { p2pck|=bit12; return 1; } else { p2pck&=~bit12; return 0; } }
inline int LFsaAppl::X14() { if (x14()) { p2pck|=bit13; return 1; } else { p2pck&=~bit13; return 0; } }
inline int LFsaAppl::X15() { if (x15()) { p2pck|=bit14; return 1; } else { p2pck&=~bit14; return 0; } }
inline int LFsaAppl::X16() { if (x16()) { p2pck|=bit15; return 1; } else { p2pck&=~bit15; return 0; } }
inline int LFsaAppl::X17() { if (x17()) { p2pck|=bit16; return 1; } else { p2pck&=~bit16; return 0; } }
inline int LFsaAppl::X18() { if (x18()) { p2pck|=bit17; return 1; } else { p2pck&=~bit17; return 0; } }
inline int LFsaAppl::X19() { if (x19()) { p2pck|=bit18; return 1; } else { p2pck&=~bit18; return 0; } }
inline int LFsaAppl::X20() { if (x20()) { p2pck|=bit19; return 1; } else { p2pck&=~bit19; return 0; } }
inline int LFsaAppl::X21() { if (x21()) { p2pck|=bit20; return 1; } else { p2pck&=~bit20; return 0; } }
inline int LFsaAppl::X22() { if (x22()) { p2pck|=bit21; return 1; } else { p2pck&=~bit21; return 0; } }
inline int LFsaAppl::X23() { if (x23()) { p2pck|=bit22; return 1; } else { p2pck&=~bit22; return 0; } }
inline int LFsaAppl::X24() { if (x24()) { p2pck|=bit23; return 1; } else { p2pck&=~bit23; return 0; } }
inline int LFsaAppl::X25() { if (x25()) { p2pck|=bit24; return 1; } else { p2pck&=~bit24; return 0; } }
inline int LFsaAppl::X26() { if (x26()) { p2pck|=bit25; return 1; } else { p2pck&=~bit25; return 0; } }
inline int LFsaAppl::X27() { if (x27()) { p2pck|=bit26; return 1; } else { p2pck&=~bit26; return 0; } }
inline int LFsaAppl::X28() { if (x28()) { p2pck|=bit27; return 1; } else { p2pck&=~bit27; return 0; } }
inline int LFsaAppl::X29() { if (x29()) { p2pck|=bit28; return 1; } else { p2pck&=~bit28; return 0; } }
inline int LFsaAppl::X30() { if (x30()) { p2pck|=bit29; return 1; } else { p2pck&=~bit29; return 0; } }
inline int LFsaAppl::X31() { if (x31()) { p2pck|=bit30; return 1; } else { p2pck&=~bit30; return 0; } }
inline int LFsaAppl::X32() { if (x32()) { p2pck|=bit31; return 1; } else { p2pck&=~bit31; return 0; } }
//===================================================================
//                                                          CALTSK
//===================================================================
TASK*  LFsaAppl::CALTSK (TNetFsa *NetFsa, int pri)
{
    WSP *r5; TASK *r6=nullptr; PID *r0;
    r0 = NetFsa->pid_task;
    int i= 0;
    // ищем свободныю ячейку для ID процесса (по ID затем можно будет получить указатель на TASK)
    while ((r0->task) && (i<NetFsa->len_pid)) {r0++; i++;}
//    qDebug()<<"CALTSK: "+ QString(FGetNameFsa().c_str());
    if (i == NetFsa->len_pid) {
//        Serial.println("Message->CALTSK: ");

        return nullptr;
    }	// все занято
    r6 = NetFsa->pStackTsk->New();				// в r6 описатель задачи
    if (!r6) {
        return nullptr;
    }					// в стеке задач уже нет места
    r6->name = "";
    r5 = NetFsa->pStackWsp->New();				//	в r5 описатель автомата
    r5->pTask=r6;
    pWSP=r5;
    r5->pFsaAppl= this;	// в WSP указатель на объект
    r6->pFsaAppl= this;  // в TASK указатель на оюъект
    r5->pTask->pNetFsa= NetFsa;

    if (pri == 0) r6->pList = &NetFsa->stop_0task;
    if (pri == 1) r6->pList = &NetFsa->stop_1task;
    if (pri == 2) r6->pList = &NetFsa->stop_2task;
    if (!r6->pList) {
        pri = 0; r6->pList = &NetFsa->stop_0task;
    }
    r6->insque(r6->pList->blink);		// подключить к списку процессов
    r6->w_fl= r6->w_bl= (WSP*)&r6->w_fl;
    r5->insque(r6->w_fl );
    r6->pid = r0; r6->pri = pri;
    r0->task = r6;
    r0->stop = 0;
    r5->adt = &adt->pRoot->ListArc.pRoot->FsaArc;
    r5->adx = adx; r5->ady = ady; r5->arc_t = r5->adt; r5->arc_b = nullptr;
//	r5->upr = trace;
    r5->name = nameFsa;
//	r6->state = adt->pRoot->szName;
    r6->state = r5->arc_t->szSt1;
    r6->name = nameFsa + "." + nameFsaProcess;
//	r5->pTask->pNetFsa->lNumberOfTasks++;
//    qDebug()<<QString("CALTSK: ") + QString(FGetNameFsa().c_str()) + QString::number(int(r6));
    return ( r6 );
 }
//===================================================================
//                                                         FLoad
//===================================================================
TASK*  LFsaAppl::FLoad (TNetFsa *NetFsa, string strProc, int pri, bool bYes, CVarFSA *pVar)
{
    pTNetFsa = NetFsa;
    pCVarFSA  = pVar;
    pTAppCore = NetFsa->GetPtrAppCore();
    LFsaAppl* l= (LFsaAppl*)04;
    if (this !=l) {
        nameFsaProcess = strProc;
        if (bYes) {
            //	создать заголовок задачи в массиве заголовков
            var.pLFsaAppl = this;
            var.pNetFsa = NetFsa;
            var.strNameLFsaAppl = nameFsa + "." + nameFsaProcess;
            NetFsa->pCArrayNetFsa->pSetLFsaHdr->Add(var);
            pLFsaHdr = NetFsa->pCArrayNetFsa->pSetLFsaHdr->GetAdressHdrFsa(this);
        }
        else {
//			bIfLFsaHdr = false;
            pLFsaHdr = nullptr; // а это означает, что заголовка для автомата нет!!!
        }
        FSetOk();
        nFsaPriority = pri;
        TASK *pT = CALTSK (NetFsa, pri);
//        int n;
        if (pT) {
//            qDebug()<<"FLoad: "+ QString(FGetNameFsa().c_str());
            if (pTNetFsa) {
                pTNetFsa->ArrayILFsaAppl.push_back(this);
//                n = NetFsa->ArrayILFsaAppl.size();
            }
        }
        return pT;
    }
    else return nullptr;
}

void LFsaAppl::FSetOk(int nOk, const char* pch)
{
    nOkProcess=nOk;

    if (pch!=nullptr)	strOk +=pch;
}

CVarPrmProc* LFsaAppl::GreateParameters()
{
    return pTAppCore->GreateParameters(this);
}

CVarPrmProc* LFsaAppl::GetPtrParameters()
{
    return pTAppCore->GetPtrParameters(this);
}

void LFsaAppl::FSetSleep(long lS) {
    if (pWSP) {
        pWSP->pTask->TSetSleep(lS);
    }
}

long LFsaAppl::FGetSleep() {
    if (pWSP) {
        return pWSP->pTask->TGetSleep();
    }
    return -1;
}

// задержка параллельного типа
void LFsaAppl::FCreateParDelay(int nDelay)
{
    if (nDelay>0) {
        TNetFsa *pNet = GetPointerToNet();
        if (pParFDelay) { delete pParFDelay; pParFDelay = nullptr; }
        pParFDelay = new CFDelay(long(nDelay), this);
        if (pCVarFSA)
            pParFDelay->FLoad(pNet, "", pCVarFSA->nPriority, false, nullptr);
        else
            pParFDelay->FLoad(pNet, "", 1, false, nullptr);
        pNet->go_task();	// пуск задачи (будет работать сразу, если не установлен признак останова)
    }
}
// проверка активности задержки параллельного типа ( 1 - активна (т.е. еще не истекла);  0 - не активна (завершила свою работу, т.е. истекла))
bool LFsaAppl::FIsActiveParDelay()
{
    if (!pParFDelay)
        return false;
    if (pParFDelay->FIsActiveTask())
        return true;
    else
        return false;
}
// задержка последовательного (по типу вложенного автомата) типа (только по ее завершении автомат переходит в следующее состояние)
void LFsaAppl::FCreateDelay(int nDelay)
{
    if (nDelay>0) {
        if (pCFDelay)
            delete pCFDelay;
        pCFDelay = new CFDelay(nDelay, this);
        pCFDelay->FCall(this);
    }
}
//===================================================================
//                                                         FCall
//===================================================================
// main - указатель на объект к которому подключается подавтомат
LFsaAppl* LFsaAppl::FCall(LFsaAppl *main)
{
    bIfCall = true;
    int nCl = main->pWSP->nNumCall;	//	текущий уровень вложенности
    main->pWSP->bCall = true;
    pFsaApplError = this;
    WSP *r5;
    pWSP = main->pWSP->pTask->pNetFsa->pStackWsp->New();
    pWSP->bHead = false;
//	pWSP = new WSP();
    r5 = pWSP;
    r5->pFsaAppl= this;
    r5->pTask = main->pWSP->pTask;
    r5->insque(pWSP->pTask->pNetFsa->cur_task->w_bl );
    r5->adt = &adt->pRoot->ListArc.pRoot->FsaArc;
    r5->adx = adx; r5->ady = ady;
    r5->arc_t = r5->adt; r5->arc_b = nullptr;
    r5->nNumCall = nCl+1;			//	уровень вложенности автомата
//	r5->upr = trace;
    r5->name = nameFsa;
    FSetOk(true);
    FClearOk();
    FClearError();
    if (main->pCVarFSA) {
//	!! 2015.05.27  установка текущего процесса в автоматной переменной
        main->pCVarFSA->pCurLFsaAppl = this;
    }
    main->pNestedAutomaton = this;
    pMainAutomaton = main;
    if (bIfMoore)
        this->MooreAction();
    return this;
}

void LFsaAppl::FSetMoore(bool b) { bIfMoore = b; };

bool LFsaAppl::FGoToState(string nam) {
    LFsaArc *arc_t;
    LAtomState *pState = ADT->pNextState;
    while (pState != nullptr) {
        if (pState->szName == nam) {
            arc_t = &pState->ListArc.pRoot->FsaArc; // адрес нового состояния
            pWSP->arc_t = arc_t;                    // установить новое состояние
            pWSP->arc_b = arc_t;                    // установить новое состояние
            return true;
        }
        pState = pState->pNext;
    }
    return false;
}

bool LFsaAppl::FDbgSetViewArc(bool b)
{
    bool bRet = bIfViewArc;
    bIfViewArc = b;
    return bRet;
}

string LFsaAppl::FDbgViewArc(UINT id)
{
    string strArc="";
    if (bIfViewArc) {
        strArc=LFsaAppl::strGetCurrentArc();
    }
    return strArc;
}

string	LFsaAppl::strGetCurrentArc(WSP *p)
{
    string strArc="";
    TNetFsa *pNet = GetPointerToNet();
    WSP *pWSP=nullptr;
    LFsaArc *pArc = nullptr;
    if (!p) {
        if (pNet)
            pWSP = pNet->GetPointerToCurWSP();
    }
    else
        pWSP = p;
    pArc = pWSP->arc_b;
    pArc = ARC_B;
    if (pArc) {
        string str = FGetNameProcess() +"(";
        str += FGetState();
        strArc +=str + ")";
        if (pWSP->arc_b) {
            strArc +=string(pWSP->arc_b->szSt1) + ",";
            strArc +=string(pWSP->arc_b->szSt2) + ",";
            strArc +=string(pWSP->arc_b->szPredicate) + ",";
            strArc +=string(pWSP->arc_b->szAction) + ",";
        }
    }
    return strArc;
}

string	LFsaAppl::FGetStateUp()
{

    if (pMainAutomaton) {
        WSP *pWSP0;
        pWSP0 = this->pWSP->pTask->w_fl;
        if (pWSP0->arc_t) {
            return pWSP0->arc_t->szSt1;
        }
        return "";
    }
    else
        return "";
}

