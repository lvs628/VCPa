// SetVar.cpp: implementation of the CSetVar class.
//
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include "SetVar.h"
#include "LConvStr.h"
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <string>
using namespace std;
#include "TAppCore.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSetVar::CSetVar()
{
	strName = "";		// ��������� ��� ������ ��������
	string strPath("");
	strFileName=string("");
	nIndexVar=0;
	bSaveSet = false;
//	pFuncSave = NULL;
    bIfAdd = false;
}

CSetVar::CSetVar(TAppCore *pCore, string strNam)
{
// ����� �� 1) ������� ��������� ��� ����� �������� ��������. 2) �������� ������ �� ���� � ������ ������ �� ����������� �������
// ����������. ���������� � ������ ������ �� ��� ����������� �� ������ (��. 1)�������� - strName, 2) ���� ������ ���� 52).
	strName = strNam;		// ��������� ��� ������ ��������
	string strPath("");
	strFileName=string("");
	nIndexVar=0;
	bSaveSet = false;
//	pFuncSave = &CSetVar::SaveDat;
	pTAppCore = pCore;
	if (pTAppCore) {
		if (strName != "") {
			TIteratorISetVar itr = find(pTAppCore->ArrayISetVar.begin(), pTAppCore->ArrayISetVar.end(), this);
			if (itr == pTAppCore->ArrayISetVar.end()) 
				pTAppCore->ArrayISetVar.push_back(this);
		}
//		else
//			int n =0;
	}
//	else {
//			int n =0;
//	}
    bIfAdd = false;
}

CSetVar::~CSetVar()
{
}

void CSetVar::SetSaveSet(bool b) 
{
	if (b) {
		string str = strFileName;
	}
	bSaveSet = b;
}

bool CSetVar::operator==(const CSetVar &var) const	
{ 
	if (strName==var.strName) return true;
	else return false;
}

bool CSetVar::operator<(const CSetVar &var) const 	
{ return strName<var.strName; }

bool CSetVar::operator!=(const CSetVar &var) const	
{ return strName!=var.strName; }

bool CSetVar::operator>(const CSetVar &var) const 	
{ return strName>var.strName; }

void  CSetVar::SaveDat() {}
