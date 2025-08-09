#include "stdafx.h"
#include <algorithm>
#include "LFsaHdr.h"
#include "TAppCore.h"
#include "setvarfsaobject.h"
#include "SetVarFSA.h"

CSetVarFsaObject::CSetVarFsaObject(TAppCore *pInfo)
{
	pInfoAppl	= pInfo;
}

CSetVarFsaObject::~CSetVarFsaObject(void)
{
//	TItrVarFsaObject itrFsa= ArrayVarFsaObject.begin();
//	int n = ArrayVarFsaObject.size();

	ArrayVarFsaObject.clear();
}

void CSetVarFsaObject::Add(string name, LFsaAppl *pFsa, bool bW)
{
	CVarFSA *pVarFsa= pInfoAppl->pSetVarFSA->GetAddressVar(name);
	CVarFsaObject var = CVarFsaObject(name, pFsa->pLFsaHdr, bW, pVarFsa);
//	ArrayVarFsaObject.push_back(CVarFsaObject(name, pHdr, bW, pVarFsa));
	ArrayVarFsaObject.push_back(var);
//	int n = ArrayVarFsaObject.size();
	CVarFsaObject *pVarFsaObj = GetAddressVar(name);
	if (pVarFsa) {
		pVarFsa->itrCVarFsaObject = pVarFsaObj;
	}
}
CVarFsaObject* CSetVarFsaObject::GetAddressVar(string nam)
{
	TItrVarFsaObject itrFsa= ArrayVarFsaObject.begin();
	while (itrFsa!=ArrayVarFsaObject.end()) {
		CVarFsaObject p = *itrFsa;
		if (nam == itrFsa->GetName()) {
			return &*itrFsa;
		}
		itrFsa++;
	}
	return nullptr;
}
bool CSetVarFsaObject::Erase(string nam)
{
	TItrVarFsaObject itrFsa= ArrayVarFsaObject.begin();
	while (itrFsa!=ArrayVarFsaObject.end()) {
		if (nam == itrFsa->GetName()) {
			ArrayVarFsaObject.erase(itrFsa);
			return true;
		}
		itrFsa++;
	}
	return false;
}

