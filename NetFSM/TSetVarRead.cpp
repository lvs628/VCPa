// TSetVarRead.cpp: implementation of the TSetVarRead class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include <algorithm>
using namespace std;
#include "TSetVarRead.h"
#include "LConvStr.h"
#include "netfsa.h"
#include "tappdrv.h"
#include "TAppCore.h"
#include "ArrayNetFsa.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSetVarRead::TSetVarRead(TAppDrv *pInfo, string strNam)
    :CSetVar(nullptr, strNam)
{
	pTAppDrv=pInfo;
	pTAppCore = pTAppDrv->pTAppCore;
	pArray = new TArrayVarRead();
//	pFuncSave = (pFnc)&TSetVarRead::SaveDat;

}

TSetVarRead::~TSetVarRead()
{
	if (pArray)
	 if (pArray->size() != 0)
		 pArray->erase(pArray->begin(), pArray->end());
	delete pArray;
}
//===================================================================
//											Add
//===================================================================
bool TSetVarRead::Add(TVarRead &var)
{
	TIteratorVarRead next=find(pArray->begin(), pArray->end(), var);
	if (next==pArray->end()) {
		pArray->push_back(var); 
		CreateLink();
		SetSaveSet(true);
		pTAppDrv->pTAppCore->nSizeGlbVars++;
		return true;
		}
	else return false;
}
//===================================================================
//											Delete
//===================================================================
bool TSetVarRead::Delete(TVarRead &var)
{
	TIteratorVarRead next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		TNetFsa *pNet = next->pTNetFsa;
		pArray->erase(next);
		CreateLink();
		SetSaveSet(true);
		pTAppDrv->pTAppCore->nSizeGlbVars--;
		if (pNet)
			pNet->TCreationOfLinksForVariables();
		else {
			pTAppDrv->pTAppCore->TCreationOfLinksForVariables();
		}
		return true;
		}
	else return false;
}
//===================================================================
//											Replace
//===================================================================
bool TSetVarRead::Replace(TVarRead &var, bool bApply)
{
	TIteratorVarRead next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
        if (bApply || !next->IfEqu(var)) {
			*next = var; 
			CreateLink(&(*next));
			SetSaveSet(true);
			return true;
		}
		return false;
		}
	else return false;
}

TVarRead* TSetVarRead::GetAddressVar(const char* nam)
{
    if (!pTAppDrv) return nullptr;
	TIteratorVarRead next=pArray->begin();
	while (next!=pArray->end()) {
//		TVarRead vr = *next;
		string strNameVar = nam; 
		if (next->strName == string(nam)) {
			return &(*next);
		}
		next++;
	}
    return nullptr;
/*
	TVarRead vs(pTAppDrv,string(nam));
	TIteratorVarRead next=find(pArray->begin(), pArray->end(), vs);
	if (next!=pArray->end())
		return &(*next);
	else
        return nullptr;
*/
}

void TSetVarRead::CreateLink()
{
	if (!pTAppDrv) return;
	TIteratorVarRead next=pArray->begin();
	while (next!=pArray->end()) {
//		TVarRead vr = *next;
//		vr.CreateLink();
		next->CreateLink();
		CreateLink(&(*next));
		next++;
		}
}
// ���������� ������ ������� �������. � ����. ��� ����������
void TSetVarRead::CreateLink(TVarRead *sens)
{
	if (!pTAppDrv) return;
//	if (sens->strName == "Delta") {
//		int n=1;
//	}
	sens->SetAddr();
}

void TSetVarRead::UpdateVariable()
{
	if (!pTAppDrv) return;
	TIteratorVarRead next=pArray->begin();
	while (next!=pArray->end()) {
		next->UpdateVariable();
		next++;
		}
}
