//#include "stdafx.h"
#include "LConvStr.h"
#include "Var.h"
#include "TAppVar.h"
#include "varcircuit.h"

CVarCircuit::CVarCircuit(void)
{
	strName = "";
	strNameInp = "";
	strNameOut = "";
	pDataDrvInp = NULL;
	pDataDrvOut = NULL;
	pInfoAppl	= NULL;
	bRelcase	= false;
	strComment	= "";
}
CVarCircuit::CVarCircuit(const CVarCircuit& var)
{
	strName		= var.strName;
	strNameInp	= var.strNameInp;
	strNameOut	= var.strNameOut;
	pDataDrvInp = var.pDataDrvInp;
	pDataDrvOut = var.pDataDrvOut;
	pInfoAppl	= var.pInfoAppl;
	bRelcase	= var.bRelcase;
	strComment	= var.strComment;
}

CVarCircuit::CVarCircuit(TAppVar* pInfo, string& nam)
{
	MoveToVar(nam); 
	pInfoAppl = pInfo;
}

CVarCircuit::CVarCircuit(TAppVar* pInfo, CVar* pDatInp,  CVar* pDatOut)
{
	pDataDrvInp = pDatInp;
	pDataDrvOut = pDatOut;
	strName = "";
	strNameInp = pDatInp->strName;
	strNameOut = pDatOut->strName;
	pInfoAppl = pInfo;
	bRelcase	= false;
	strComment = "";
}

CVarCircuit::~CVarCircuit(void)
{
}

bool CVarCircuit::IfEqu(CVarCircuit& var)
{
	if (strName != var.strName) return false;
	if (strNameInp != var.strNameInp) return false;
	if (strNameOut != var.strNameOut) return false;
	if (bRelcase != var.bRelcase) return false;
	if (strComment != var.strComment) return false;
	return true;

}
void CVarCircuit::MoveToVar(string & Str)
{
	LConvStr Cmnd(Str);
    strName		= (string)Cmnd;
    strNameInp	= (string)Cmnd;
    strNameOut	= (string)Cmnd;
    strComment  = (string)Cmnd;
	bRelcase	= Cmnd;
	pDataDrvInp = NULL;
	pDataDrvOut = NULL;
}

int CVarCircuit::operator==(const CVarCircuit &var) const	
{ 
	return strName==var.strName; 
}

int CVarCircuit::operator<(const CVarCircuit &var) const 	
{ 
	return strName<var.strName; 
}

ostream& operator<<(ostream& os, CVarCircuit &dat)
{
	return os<<dat.strName<<';'
	<<dat.strNameInp<<';'
	<<dat.strNameOut<<';' 
	<<dat.strComment<<';'
	<<dat.bRelcase<<';'
	<<endl;
}

/*
istream& operator>>(istream& is, CVarCircuit &dat)
{
	string Str; is>>Str;
	if (Str.empty()) { dat=CVarCircuit(); return is; }
	dat.MoveToVar(Str);
	return is;
}
*/
void CVarCircuit::CreateLink()
{
// ��������� pDataDrv �������� ����� ������������ ����������, ��� ������� strName
// ���� ������� �� ������ � ������ �������� , � ����� � ������ ����������� ����������
// ����������. ������ ��������������� ����� ����� ������ ����.���������� (��)
// ��. CSetVarCircuit::CreateLink(CVarCircuit* var) ��� ��������� ���������� �
// ����� CSetVarCircuit::CreateLink() ���� ���� "�����������" �� ���� ��
//		����������� ����� �������� (��������������) ����������
	pDataDrvInp = NULL;
	pDataDrvOut = NULL;
	CVar *sens;
	sens= pInfoAppl->GetAddressVar(strNameInp.c_str(), NULL);
	if (sens) {
		pDataDrvInp = sens;
	}
	sens= pInfoAppl->GetAddressVar(strNameOut.c_str(), NULL);
	if (sens) {
		pDataDrvOut = sens;
	}
//		����������� ����� ������������ (���������� ��� �����������) ����������
	sens= pInfoAppl->GetAddressVar(strNameInp.c_str(), NULL);
	if (sens&&pDataDrvOut!=NULL) {
		pDataDrvInp = sens;
	}
	sens= pInfoAppl->GetAddressVar(strNameOut.c_str(), NULL);
	if (sens&&pDataDrvInp!=NULL) {
		pDataDrvOut = sens;
	}
}
