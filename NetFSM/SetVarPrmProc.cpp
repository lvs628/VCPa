#include "stdafx.h"
#include "SetVarPrmProc.h"
#include <fstream>
#include <algorithm>
using namespace std;
#include "TAppCore.h"

CSetVarPrmProc::CSetVarPrmProc(TAppCore *pInfo, string strNam)
{
	pTAppCore = pInfo;
	bSaveSet = false;
	nIndexVar = 0;
	strPath = "";
	strFileName = "";
	pArray = new TArrayVarPrmProc();
}

CSetVarPrmProc::~CSetVarPrmProc(void)
{
	if (pArray) {
        if (bSaveSet) {
			bSaveSet = false;
			}
		if (pArray->size() != 0)
			 pArray->erase(pArray->begin(), pArray->end());
		delete pArray;
	}
}

CVarPrmProc* CSetVarPrmProc::GetAddressVar(string nam)
{
	CVarPrmProc vn;
	CVarPrmProc *pVn;
    vn.strName=nam;
	TIteratorVarPrmProc next=find(pArray->begin(), pArray->end(), vn);
	if (next!=pArray->end()) {
		pVn = &(*next);
		return pVn;
	}
	else
 		return nullptr;
}

bool CSetVarPrmProc::Add(CVarPrmProc &var)
{
	TIteratorVarPrmProc next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) return false;
	else {
		pArray->push_back(var);
		SetSaveSet(true);
		return true;
	}
}

bool CSetVarPrmProc::Replace(CVarPrmProc &var)
{
	TIteratorVarPrmProc next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		if (!next->IfEqu(var)) {
			*next = var; 
			SetSaveSet(true);
			return true;
		}
		return false;
	}
	else { 
		return false;
	}
}

bool CSetVarPrmProc::Delete(CVarPrmProc &var)
{
//	unsigned int n = pArray->size();
	TIteratorVarPrmProc next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		pArray->erase(next); 
		SetSaveSet(true);
		return true;
		}
	else return false;
}

void CSetVarPrmProc::SetSaveSet(bool b) 
{
	if (b) {
		string str = strFileName;
	}
	bSaveSet = b;
}

