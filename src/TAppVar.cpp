#include "stdafx.h"
#include "TAppCore.h"
#include "TAppVar.h"
#include "SetVarPrmProc.h"
#include "SetVarCircuit.h"
#include "SetVarFSA.h"

TAppVar::TAppVar(void)
	:TAppCore()
{
    pTAppDrv		= nullptr;
    pSetVarPrmProc  = nullptr;
    pSetVarCircuit  = nullptr;
    ReloadVCPa();
}

TAppVar::~TAppVar(void)
{
	if (pSetVarFSA)	delete pSetVarFSA;
    pSetVarFSA = nullptr;
    if (pSetVarPrmProc) delete pSetVarPrmProc;
    pSetVarPrmProc = nullptr;
	if (pSetVarCircuit)	delete pSetVarCircuit;
    pSetVarCircuit = nullptr;
    pTAppDrv = nullptr;
}

void TAppVar::ReloadVCPa(void)
{
//	TAppCore::���������������();
    if (pSetVarPrmProc) delete pSetVarPrmProc;
	if (pSetVarCircuit) delete pSetVarCircuit;
	
	pSetVarPrmProc	= new CSetVarPrmProc(this, "PrmProc");
    pSetVarCircuit = new CSetVarCircuit(this, "Circuit");
}

void TAppVar(void)
{
}

bool TAppVar::LinkVar()
{
	TAppCore::LinkVar();
	return true;
}
// ������� ����� ������� (����������) ������� ���������� ��� ��������
CVarPrmProc* TAppVar::GetPtrParameters(LFsaAppl *pL)
{
	return ((TAppVar*)pL->pTAppCore)->pSetVarPrmProc->GetAddressVar(pL->pCVarFSA->strName);
}
// ������� ������ ������� ���������� ��� ��������
CVarPrmProc* TAppVar::GreateParameters(LFsaAppl *pL)
{
		CVarPrmProc var;
//		string str = pL->pLFsaHdr->strNameCVarFSA;
		string str = pL->pCVarFSA->strName;
		var.strName = str;
		var.pTAppVar = this;
		((TAppVar*)pL->pTAppCore)->pSetVarPrmProc->Add(var);
		pL->pVarPrmProc = ((TAppVar*)pL->pTAppCore)->pSetVarPrmProc->GetAddressVar(str);
		return pL->pVarPrmProc;
}

CVarPrmProc* TAppVar::DeleteParameters(LFsaAppl *pL)
{
	CVarPrmProc var;
	if (pL->pCVarFSA) {
		string str = pL->pCVarFSA->strName;
		var.strName = str;
		((TAppVar*)pL->pTAppCore)->pSetVarPrmProc->Delete(var);
		pL->pVarPrmProc = ((TAppVar*)pL->pTAppCore)->pSetVarPrmProc->GetAddressVar(str);
		return pL->pVarPrmProc;
	}
    return nullptr;
}
