#include "stdafx.h"
#include <fstream>
#include <algorithm>
using namespace std;
#include "SetVarCircuit.h"
#include "TAppCore.h"

CSetVarCircuit::CSetVarCircuit(TAppCore *pInfo, string strNam):
	CSetVar(pInfo, strNam)
{
	pArray = new CArrayVarCircuit();
}

CSetVarCircuit::~CSetVarCircuit(void)
{
	if (bSaveSet) {
		SaveDat();
		bSaveSet = false;
		}
 if (pArray)
	 if (pArray->size() != 0)
		 pArray->erase(pArray->begin(), pArray->end());
 delete pArray;
}

void CSetVarCircuit::CreateLink()
{
	CIteratorVarCircuit next=pArray->begin();
	while (next!=pArray->end()) {
		next->CreateLink();
		next++;
		}
}
void CSetVarCircuit::CreateLink(CVarCircuit* var)
{
	var->CreateLink();
}
//===================================================================
//											Add
//===================================================================
bool CSetVarCircuit::Add(CVarCircuit &var)
{
	CIteratorVarCircuit next=find(pArray->begin(), pArray->end(), var);
	if (next==pArray->end()) {
		pArray->push_back(var);
		next=find(pArray->begin(), pArray->end(), var);
		next->CreateLink();
		SetSaveSet(true);
		return true;
		}
	else return false;
}
//===================================================================
//											Delete
//===================================================================
bool CSetVarCircuit::Delete(CVarCircuit &var)
{
	CIteratorVarCircuit next=find(pArray->begin(), pArray->end(), var);
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
bool CSetVarCircuit::Replace(CVarCircuit &var)
{
	CIteratorVarCircuit next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		if (!next->IfEqu(var)) {
			*next = var; 
			CreateLink(&(*next));
			SetSaveSet(true);
			return true;
		}
		return false;
		}
	else return false;
}

CVarCircuit* CSetVarCircuit::GetAddressVar(const char* nam)
{
	CVarCircuit vn;
	vn.strName=nam;
	CIteratorVarCircuit next=find(pArray->begin(), pArray->end(), vn);
	if (next!=pArray->end())
		return &(*next);
	else
 		return nullptr;
}


