// TVarBase.cpp: implementation of the TVarBase class.
//
//////////////////////////////////////////////////////////////////////

#include "TVarBase.h"
#include "LConvStr.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TVarBase::TVarBase():TDataDrv()
{
}

TVarBase::~TVarBase()
{

}

bool TVarBase::IfEqu(TVarBase& var)
{
	if (!TDataDrv::IfEqu(var)) return false;
	return true; 
}

TVarBase::TVarBase(const TVarBase & var):TDataDrv(var)
{
	strInitValue		=var.strInitValue; 
}

TVarBase::TVarBase(TAppDrv * pInf, string & nam):TDataDrv(pInf,nam)
{ 
	MoveToVar(nam); 
}

void TVarBase::MoveToVar(string & Str)
{
	LConvStr CS(Str);
// ��� ��������
//	strDriver= CS;
    strInitValue= string(CS);
// ��� �������
    int strDevice= CS;
// ��������� ������
    string strCommand= CS;
// ��������� ������������
    int nPriority= CS;
// ����� ���������
    int nNumOfMsr= CS;
// ������� ������� ���������� ��������
    string strCurCommand=strCommand;
    string strNewCommand=strCommand;
}

istream& operator>>(istream& is, TVarBase &dat)
{
	string Str; is>>Str;
	if (Str.empty()) { dat=TVarBase(); return is; }
	dat.MoveToVar(Str);
	return is;
}

// ������������� ��������� (pKamakDrv) �� ���������� ������� 
// ������������� ��������� (pDevice) �� �������� ������� 1-�� ������
void TVarBase::SetAddr()
{
	if (!pTAppCore) return;
// TDataDrv
//	������������� ����� ����� ������� ���������� �:
// 1 - ����������� ���������� (� ������ ������� ����������)
// 2 - �������� ������������� � ������ strNameModelData
// 3 - "�������� �����" � ������� nNumView
	TDataDrv::SetAddr();
//	���������� ����� ��������-�����������, ��� ��������� � ����������-��������
}

double TVarBase::SetDataDrvSrc(double d)
{
	double dTmp;
	dTmp=dDataSrc;
	dDataSrc = d;
	return dTmp;
}
