#include "stdafx.h"
#include "SetVarSetting.h"
#include <fstream>
#include <algorithm>
using namespace std;
#include "VarSetting.h"
#include "TAppCore.h"

CSetVarSetting::CSetVarSetting(TAppCore *pPr, string strNam)
	:CSetVar(pPr, strNam)
{
	pArray = new TArrayCVarSetting();
}

CSetVarSetting::~CSetVarSetting()
{
    if (bSaveSet) {
		SaveDat();
		bSaveSet = false;
		}
	if (pArray)
		if (pArray->size() != 0)
				pArray->erase(pArray->begin(), pArray->end());
	delete pArray;
	pArray = nullptr;
}

void CSetVarSetting::SetSaveSet(bool b) {
    CSetVar::SetSaveSet(b);
}

bool CSetVarSetting::Add(CVarSetting &var)
{
	TIteratorCVarSetting next=find(pArray->begin(), pArray->end(), var);
	if (next==pArray->end()) {
		pArray->push_back(var); 
		return true;
		}
	else return false;
}

//===================================================================
//											Delete
//===================================================================
bool CSetVarSetting::Delete(CVarSetting &var)
{
	TIteratorCVarSetting next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		pArray->erase(next);
		SetSaveSet(true);
		return true;
		}
	else return false;
}
//===================================================================
//											Replace
//===================================================================
bool CSetVarSetting::Replace(CVarSetting &var)
{
	TIteratorCVarSetting next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		if (!next->IfEqu(var)) {
			*next = var; 
			SetSaveSet(true);
			return true;
		}
		return false;
	}
	else return false;
}

CVarSetting* CSetVarSetting::GetAddressVar(string &nam)
{
    string strNam = string(nam);
    CVarSetting vn(pTAppCore, strNam);
	TIteratorCVarSetting next=find(pArray->begin(), pArray->end(), vn);
	if (next!=pArray->end())
		return &(*next);
	else {
 		TIteratorCVarSetting next=pArray->begin();
		while (next!=pArray->end()) {
			if (next->strNameNetFsa == string(nam))
				return &(*next);
			next++;
		}
		return nullptr;
	}
}
