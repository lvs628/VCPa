#include "stdafx.h"
#include "TAppCore.h"
#include "SetVar.h"
#include "setvarfsaobject.h"
#include "SetVarFSA.h"
#include "TAppVar.h"
#include "ArrayNetFsa.h"
#include "SetVarCircuit.h"
#include "SetVarSetting.h"

#include "netfsa.h"

TAppCore::TAppCore(void)
{
    pCArrayNetFsa = nullptr;
    pSetVarSetting = nullptr;
    pSetVarFsaObject = nullptr;
    pSetVarFSA = nullptr;

    ReloadVCPa();

    nSizeGlbVars	= 0;
    nSizeLocVars	= 0;
    strCurrentWorldFSA = "";
    bIfDesigning	= true;
    bIfStopAllTasks	= false;
    bSaveSensors	= false;
    bSaveConf	= false;		// ���������� ������ ������� ������������
    bNotRealTime = false;
    llVCPaSystemTime = 0;
}

TAppCore::~TAppCore(void)
{
    if (pSetVarSetting)	delete pSetVarSetting;
    pSetVarSetting = nullptr;
	if (pSetVarFsaObject) delete pSetVarFsaObject;
    pSetVarFsaObject = nullptr;
    if (pCArrayNetFsa)  delete pCArrayNetFsa;
    pCArrayNetFsa = nullptr;

	ArrayISetVar.clear();
}
void TAppCore::SetSaveSet(void)
{
    if (pSetVarFSA) pSetVarFSA->SetSaveSet(true);
	if (pSetVarSetting) pSetVarSetting->SetSaveSet(true);
}

extern TAppVar	*pGlbTAppVar;
CLocVar* TAppCore::GetAddressVar(const char* nam, LFsaAppl *pL) {
    return nullptr;
}

CLocVar* TAppCore::InsertVar(CVar* pVar, LFsaAppl *pL) {
    return nullptr;
}

CLocVar* TAppCore::ReplaceVar(CVar* pVar, LFsaAppl *pL) {
    return nullptr;
}

CLocVar* TAppCore::DeleteVar(const char* nam, LFsaAppl *pL) {
    return nullptr;
}

CVar* TAppCore::IterAddressVar(bool begin)
{
	if (begin) {
//		next = 
	}
    return nullptr;
}

bool TAppCore::LinkVar()
{
	return true;
}
// ���������� ��� ������ ����������� "����������� ������������" ��� ������ ���� ����������� (��� ��������� == "")
bool TAppCore::StopAllTasks(string strNameTNetFsa)
{
	if (strNameTNetFsa != "") {
		TNetFsa *pTNetFsa = pCArrayNetFsa->GetAdressNetFsa(strNameTNetFsa);
		if (pTNetFsa) {
			pTNetFsa->StopTask();
			return true;
		}
		return false;
	}
	else {
		TIteratorCVarSetting nextSet = pSetVarSetting->pArray->begin();
		while (nextSet != pSetVarSetting->pArray->end()) {
//			CVarSetting *pCV = &(*nextSet);
			if (nextSet->pTNetFsa) {
				nextSet->pTNetFsa->StopTask();
			}
			nextSet++;
		}
	}
	return true;
}
// ��������� ��� ������ ����������� "����������� ������������" ��� ������ ���� ����������� (��� ��������� == "")
bool TAppCore::StartAllTasks(string strNameTNetFsa)
{
	if (strNameTNetFsa != "") {
		TNetFsa *pTNetFsa = pCArrayNetFsa->GetAdressNetFsa(strNameTNetFsa);
		if (pTNetFsa) {
			pTNetFsa->StartTask();
			return true;
		}
		return false;
	}
	else {
		TIteratorCVarSetting nextSet = pSetVarSetting->pArray->begin();
		while (nextSet != pSetVarSetting->pArray->end()) {
//			CVarSetting *pCV = &(*nextSet);
			if (nextSet->pTNetFsa) {
				nextSet->pTNetFsa->StartTask();
			}
			nextSet++;
		}
	}
	return true;
}
// ���������� ������ �� ����� "���������� ����������"
bool TAppCore::StopTask(string strNameCVarFSA)
{
	LFsaAppl *pLFsaAppl	= pSetVarFSA->GetAddressFsa(strNameCVarFSA);
	if (pLFsaAppl) {
		if (!pLFsaAppl->FIfStop()) 
			pLFsaAppl->FStop();
		return true;
	}
	return false;
}
// ��������� ������ �� ����� "���������� ����������"
bool TAppCore::StartTask(string strNameCVarFSA)
{
	LFsaAppl *pLFsaAppl	= pSetVarFSA->GetAddressFsa(strNameCVarFSA);
	if (pLFsaAppl) {
		if (pLFsaAppl->FIfStop()) 
			pLFsaAppl->FStart();
		return true;
	}
	return false;
}

CVarFsaNew* TAppCore::GetAddressVarFsaNew(string strNameFsa, string strNameLib)
{
    CVarFsaNew *pFsaNew = nullptr;	// ����� ������� �������
	return pFsaNew;
}

CVarPrmProc* TAppCore::GetPtrParameters(LFsaAppl *pL)
{
    return nullptr;
}

CVarPrmProc* TAppCore::GreateParameters(LFsaAppl *pL)
{
    return nullptr;
}

CVarPrmProc* TAppCore::DeleteParameters(LFsaAppl *pL)
{
    return nullptr;
}

CVarFSA* TAppCore::GetAddressVarFSA(string strNameVar)
{
	return pSetVarFSA->GetAddressVar(strNameVar);
}
// 0 - ��� ����������, 1- ����������, 2 - ���������, 3 - �����������
int	TAppCore::SizeAllVars(int nMode) { 
	if (nMode==0) return nSizeGlbVars+nSizeLocVars; 
	if (nMode==1) return nSizeGlbVars; 
	if (nMode==2) return nSizeLocVars; 
	return -1;
}

bool TAppCore::TCreationOfLinksForVariables(string strNameFsaWorld)
{
// ���������/������� ������ ��� ���������� ��������� ���� ���������� �����������
    TPIteratorNetFsa IIteratorNF = pCArrayNetFsa->PArrayNetFsa.begin();
    while (IIteratorNF!=pCArrayNetFsa->PArrayNetFsa.end()) {
        TNetFsa* pNet = *IIteratorNF++;
		if (strNameFsaWorld=="")
			pNet->TCreationOfLinksForVariables();
		else {
			if (pNet->strName == strNameFsaWorld)
				pNet->TCreationOfLinksForVariables();
		}
	}
	return true;
}

TNetFsa* TAppCore::GetAdressNetFsa(string str) { return pCArrayNetFsa->GetAdressNetFsa(str); }
// ���������� ����� ��������� ������������ ����. ����� ��������� ����������� ����� ���������.
int TAppCore::GetNumbersOfProcessesForNameFsa(string strNameFsa, string &strListOfProcesses)
{
	string strProc = "";
	int n = pCArrayNetFsa->pSetLFsaHdr->Size();
	int nNumbers=0;
	for (int i=0; i<n; i++) {
		LFsaHdr var = (*pCArrayNetFsa->pSetLFsaHdr)[i];
		if (var.Num() >= 0) {
			if (var.pLFsaAppl) {
				if (var.pLFsaAppl->FGetNameFsa() == strNameFsa) { 
					nNumbers++;
					if (nNumbers>1) { strProc +=";"; }
					strProc += var.pLFsaAppl->FGetNameProcess(); 
				}
			}
		}
	}
	strListOfProcesses = strProc;
	return nNumbers;
}
// ���������� ����� ������������ �� ����� ��������.
LFsaAppl *TAppCore::TPtrForNameProcess(string strNameProcess, int *pr, TNetFsa **pNet) {
	int nPriority;
	return pCArrayNetFsa->GetAdressFsaAppl(strNameProcess, &nPriority, pNet);
}

bool	TAppCore::InitAllTasks(string strNameTNetFsa) {
    StopAllTasks("");
    CIteratorVarFSA next=pSetVarFSA->pArray->begin();
    while (next != pSetVarFSA->pArray->end()) {
        string str = next->strName;
        LFsaAppl *pL = next->pLFsaAppl;
        if (pL) {
            next->pLFsaAppl->FInit();
            next->pLFsaAppl->FResetActions();
        }
        next++;
    }
    StartAllTasks("");
    return true;
}

void        TAppCore::SetRealTime(bool bValue) { bNotRealTime = !bValue; }
bool        TAppCore::GetRealTime() { return !bNotRealTime; }
void TAppCore::ReloadVCPa(void)
{
    if (pSetVarFSA) delete pSetVarFSA;
    if (pSetVarFsaObject) delete pSetVarFsaObject;
    if (pSetVarSetting) delete pSetVarSetting;
    if (pCArrayNetFsa) delete pCArrayNetFsa;

    bSaveConf	= false;		// сохранение файлов текущей конфигурации

    bSaveConf	= false;		// сохранение файлов текущей конфигурации

    pCArrayNetFsa = new CArrayNetFsa(this);
    pCArrayNetFsa->InitNetFsa();


    pSetVarSetting = nullptr;
    pSetVarSetting = new CSetVarSetting(this, "Setting");

    pSetVarFsaObject = nullptr;
    pSetVarFsaObject= new CSetVarFsaObject(this);

    pSetVarFSA = nullptr;
    pSetVarFSA = new CSetVarFSA(this, "FSA");

    lTimeDeltaFSA = 0;

    pVarDeltaTimeSystem = nullptr;
    pCVarSetting = nullptr;
}
