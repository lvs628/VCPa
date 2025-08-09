#include "VarFsaObject.h"

CVarFsaObject::CVarFsaObject(void)
{
	strName = "";
	bIfWnd = false;
	pLFsaHdr = nullptr;
	pCVarFSA = nullptr;

}

CVarFsaObject::~CVarFsaObject(void)
{
	strName = "";
	bIfWnd = false;
	pLFsaHdr = nullptr;
	pCVarFSA = nullptr;
}

bool CVarFsaObject::operator< (const CVarFsaObject& var)  const
{
	return strName<var.strName;
}

bool CVarFsaObject::operator== (const CVarFsaObject &var)  const
{
	return strName==var.strName;
}

bool CVarFsaObject::operator> (const CVarFsaObject& var)  const
{
	return strName>var.strName;
}

bool CVarFsaObject::operator!= (const CVarFsaObject &var)  const
{
	return strName!=var.strName; 
}

CVarFsaObject::CVarFsaObject (string name, LFsaHdr* pAddr, bool bW, CVarFSA *pVF)
{
	strName=name; pLFsaHdr=pAddr; bIfWnd = bW; pCVarFSA = pVF; 
}

void CVarFsaObject::SetAddress (LFsaHdr* pAddr)
{
	pLFsaHdr=pAddr;
}
CVarFsaObject::CVarFsaObject(const CVarFsaObject& var)
{
	strName=var.strName; 
	pLFsaHdr=var.pLFsaHdr; 
	bIfWnd = var.bIfWnd;
	pCVarFSA = var.pCVarFSA;
}
