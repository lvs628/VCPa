#include "SetVarNetFsa.h"
#include <algorithm>		// sort
#include "Var.h"


CSetVarNetFsa::CSetVarNetFsa(TAppCore *pC, string strNam):
	CSetVar(pC, strNam)
{
	pArray	= new TArrayIVar();
}


CSetVarNetFsa::~CSetVarNetFsa(void)
{
	if (pArray) delete pArray;
}

void CSetVarNetFsa::SaveDat() 
{
}

void CSetVarNetFsa::ReadDat(string& pszP, string& pszFile)
{
}
void CSetVarNetFsa::WriteDat(string& pszP, string& pszFile)
{
}
bool CSetVarNetFsa::Add(CVar &var)
{
	TIteratorIVar next=find(pArray->begin(), pArray->end(), &var);
	if (next==pArray->end()) 
	{
		// ���� ��� � ������� ������ �� �������, ������� ��������� � dll-�����������
		pArray->push_back(&var);		// ��������� � ������� ������ 
		return true;
	}
	else { 
		return false;
	}
}
bool CSetVarNetFsa::Replace(CVar &var)
{
	return false;
}
bool CSetVarNetFsa::Delete(CVar &var)
{
	return false;
}
