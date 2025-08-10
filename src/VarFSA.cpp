#include "stdafx.h"
#include "VarFSA.h"
#include "LConvStr.h"
#include "VarFsaObject.h"
#include "setvarfsaobject.h"
#include "lfsaappl.h"
#include "TAppCore.h"
#include "netfsa.h"
#include "ArrayNetFsa.h"
#include "csetlocvar.h"

CVarFSA::CVarFSA(void)
{
    strName = "";
    strNameFsa = "";
    strNameFsaProcess = "";
    nPriority	= 0;
    bStop		= false;		// ������� ��������� ��������
    lSleep		= 0;			// ����� ���������
    bViewFSA	= 0;
    strNameNetFsa = "";
    bIfLoad		= false;
    pTAppCore	= nullptr;
    itrCVarFsaObject = nullptr;
    bIfCreateProcess = false;
    pLFsaAppl = nullptr;
    bIfCreate	= false;
    bRemoteVariable = false;
    strListLocalVar = "";
    pCurLFsaAppl	= nullptr;
}

CVarFSA::CVarFSA(const CVarFSA& var)
{
//    if (var.strName=="CycleNorm")
//        int n=1;
    pTAppCore	= var.pTAppCore;
    strName		= var.strName;
    strNameFsa	= var.strNameFsa;
    strNameFsaProcess	= var.strNameFsaProcess;
    nPriority	= var.nPriority;
    bStop		= var.bStop;
    lSleep		= var.lSleep;
    bViewFSA	= var.bViewFSA;
    strNameNetFsa = var.strNameNetFsa;
    bIfLoad		= var.bIfLoad;
    bIfCreateProcess = var.bIfCreateProcess;
    bIfCreate	= var.bIfCreate;
    bRemoteVariable = var.bRemoteVariable;
    pLFsaAppl	= nullptr;
    itrCVarFsaObject = nullptr;
    strListLocalVar = var.strListLocalVar;
    pCurLFsaAppl	= var.pCurLFsaAppl;
//    pCSetVDialog = new CSetVDialog();
}

CVarFSA::CVarFSA(TAppCore* pInfo, string& nam)
{
    pTAppCore = pInfo;
    MoveToVar(nam);
    itrCVarFsaObject = nullptr;
    pLFsaAppl = nullptr;
    bIfCreate	= false;
    bRemoteVariable = false;
    pCurLFsaAppl	= nullptr;
}

CVarFSA::~CVarFSA(void)
{
    string str = strName;
    if (pLFsaAppl) {
        string str = strName;
        if (itrCVarFsaObject) {
            if (!itrCVarFsaObject->bIfWnd) {
                delete pLFsaAppl;
                pLFsaAppl = nullptr;
            }
        }
        // ���� ���� �� ������� ���� (��� �������, ����������� ��� �������-����), ��
        // ����� ������� � ������� ��������
        //
        if (bIfCreate&&pLFsaAppl)
            delete pLFsaAppl;
        pLFsaAppl = nullptr;
    }
}

// ������� ����� � ���������� ������
void CVarFSA::CreateLink() 
{
//	if (strName=="CycleNorm")
//		int n=6;
	return;
}
// ��������� ������, ������� ���������
bool CVarFSA::LoadFsa(LFsaAppl*pLFsa)
{
//    if (strName=="���-maxim")
//        int n=3;
	if (pLFsa) {
		string str = pLFsa->FGetNameFsa();
		// ��� �������� � ���������� ��������� � ������ ��������, ������� �����������?
		if (str == strNameFsa) {
			// �������� �������� ����������, ���� ��� �������� ��������� � ������
			// ��������, ��������� � ����������
			TNetFsa *pTNetFsa = pTAppCore->pCArrayNetFsa->GetAdressNetFsa(strNameNetFsa);
			if (pTNetFsa&&bIfLoad) {
//				pLFsa->FSetNameFsa(strNameFsa);	// �������, �.�. ���� �������� �� ���������� ����
                pLFsa->FLoad(pTNetFsa, strNameFsaProcess, nPriority, true, this);
                pLFsa->pTAppCore = pTAppCore;
				pLFsa->FSetSleep(lSleep);
				if (bStop) pLFsa->FStop();
				pTNetFsa->go_task();
				if (pLFsa->pLFsaHdr) {
					// ������� ��� ���������� ���������� � ���������� �������� � ������� � � ���������
					pLFsa->pLFsaHdr->strNameCVarFSA = strName;
					pLFsa->var.strNameCVarFSA = strName;
				}
				// ���������� ��������� �� ��������� �������� � ���������� ����������
				pLFsaAppl = pLFsa;
				return true;
			}
			else return false;
		}
		else return false;
	}
	return false;
}

void CVarFSA::MoveToVar(string& Str)
{
    LConvStr Cmnd(Str);
    strName		= string(Cmnd);
    strNameFsa	= strName;
    strNameFsaProcess	= strName;
    nPriority	= Cmnd;
    bStop		= Cmnd;
    lSleep		= Cmnd;
    bViewFSA	= Cmnd;
    strNameNetFsa = string(Cmnd);
    bIfLoad		= Cmnd;				// загрузка
    bIfCreateProcess= Cmnd;         // создать процесс
    strListLocalVar = string(Cmnd);	// список локальных переменных (с инициализацией нач. значений)
}

bool CVarFSA::IfEqu(CVarFSA& var) {
    string strLocVar = strListLocalVar;
    string varstrLocVarr = var.strListLocalVar;
    if (strName != var.strName) return false;
	if (strNameFsa != var.strNameFsa) return false;
	if (strNameFsaProcess != var.strNameFsaProcess) return false;
    if (nPriority != var.nPriority) return false;
	if (bStop != var.bStop) return false;
	if (lSleep != var.lSleep) return false;
	if (bViewFSA != var.bViewFSA) return false;
	if (strNameNetFsa != var.strNameNetFsa) return false;
	if (bIfLoad != var.bIfLoad) return false;
    if (bIfCreateProcess != var.bIfCreateProcess) return false;
    if (bRemoteVariable != var.bRemoteVariable) return false;
    if (strLocVar != varstrLocVarr) return false;
    return true;
}

int CVarFSA::operator==(const CVarFSA &var) const
{ 
//    if (var.strName=="CycleNorm"||strName=="CycleNorm")
//        int n=1;
	return strName==var.strName; 
}

int CVarFSA::operator<(const CVarFSA &var) const
{ 
	return strName<var.strName; 
}

CVarFSA&  CVarFSA::operator=(const CVarFSA &var)
{
	if (this != &var) {
		strName = var.strName.c_str();
		strNameFsa = var.strNameFsa;
		strNameFsaProcess = var.strNameFsaProcess;
		nPriority = var.nPriority;
		bStop = var.bStop;
		lSleep = var.lSleep;
		bViewFSA = var.bViewFSA;
		strNameNetFsa = var.strNameNetFsa;
		bIfLoad = var.bIfLoad;
		bIfCreateProcess = var.bIfCreateProcess;
        bRemoteVariable = var.bRemoteVariable;
		strListLocalVar	= var.strListLocalVar;
    }
	return *this;
}

string CVarFSA::GetNameProcess()
{
	return strNameFsa + "." + strNameFsaProcess;

}

bool CVarFSA::CreateProcessFSA()
{
    LFsaAppl *pFsa = nullptr;
	if (!pLFsaAppl) {
		LFsaAppl *p = GetAddress();
		if (!p&&bIfCreateProcess) {
                pFsa = pLFsaSrcClass;
                if (!pFsa) {
                    // еще нет автоматного объекта с запрошенным именем
                    bIfCreate = false;
                    return false;
                }
                else {
                    // адрес получен с помощью определенного метода Create
                    bIfCreate = true;
                }
                if (pFsa) {
                    LoadFsa(pFsa);
                    if (pFsa->pLFsaHdr) {
                        if (!strListLocalVar.empty()) {
                            pFsa->pCSetLocVar->CreateArrayVariables(pFsa, strListLocalVar);
                            pFsa->LFsaAppl::FCreationOfLinksForVariables();
                        }
                        else {
                            pFsa->pCSetLocVar->CreateArrayVariables(pFsa, strListLocalVar);
                            pFsa->LFsaAppl::FCreationOfLinksForVariables();
                        }
                        pFsa->pVarPrmProc = pFsa->GetPtrParameters();
                        if (!pFsa->pVarPrmProc) {
                            pFsa->pVarPrmProc =  pFsa->GreateParameters();
                        }
                        pFsa->FInit();
                    }
                    pFsa->pCVarFSA = this;
                    pFsa->pTAppCore = this->pTAppCore;
                    if (!(bIfCreateProcess && bIfLoad)) {
                        if (!strListLocalVar.empty()) {
                            pFsa->pCSetLocVar->CreateArrayVariables(pFsa, strListLocalVar);
                            pFsa->LFsaAppl::FCreationOfLinksForVariables();
                        }
                        pFsa->pVarPrmProc = pFsa->GetPtrParameters();
                        if (!pFsa->pVarPrmProc) {
                            pFsa->pVarPrmProc =  pFsa->GreateParameters();
                        }
                        pFsa->FInit();
                    }
                    pLFsaAppl = pFsa;
                    return true;
            }
            return false;
        }
        return false;
    }
    return true;
}

void CVarFSA::SetPtrToSrcClass(LFsaAppl *pL)
{
    pLFsaSrcClass = pL;
}

LFsaAppl* CVarFSA::GetAddress() {
    if (itrCVarFsaObject) {
        if (itrCVarFsaObject->GetHdr()) {
            return itrCVarFsaObject->GetHdr()->pLFsaAppl;
        }
        else return nullptr;
    }
    else return nullptr;
}
