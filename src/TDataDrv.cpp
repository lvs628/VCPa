// TDataDrv.cpp: implementation of the TDataDrv class.
//
//////////////////////////////////////////////////////////////////////

#include "tappdrv.h"
#include "TDataDrv.h"
#include <sstream>
#include <iomanip>
#include "LConvStr.h"
#include <algorithm>
#include "Var.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TDataDrv::TDataDrv()
    :CVar()
{
    dDataSrc=0;
    pTAppCore=nullptr;
    bDebug = false;
    pTAppDrv = nullptr;
}

TDataDrv::~TDataDrv()
{

}

TDataDrv::TDataDrv(const TDataDrv& var)
    :CVar(var)
{
    dDataSrc=var.dDataSrc;
    pTAppCore=var.pTAppCore;
    bDebug = var.bDebug;
    pTAppDrv = var.pTAppDrv;
}

TDataDrv::TDataDrv(TAppDrv *pInf, string &nam)
    :CVar()
{
    pTAppCore=pInf->pTAppCore; MoveToVar(nam);
    pTAppDrv = pInf;
}

TDataDrv::TDataDrv(TAppDrv *pInf, double d)
    :CVar()
{
    pTAppDrv = pInf;
    pTAppCore=pInf->pTAppCore;
    dDataSrc= d;
    bDebug = false;
}

TDataDrv::operator double()
{
    return dDataSrc;
}

bool TDataDrv::IfEqu(TDataDrv& var)
{
    if (!CVar::IfEqu(var)) return false;
    if (strComment != var.strComment) return false;
    if (bDebug != var.bDebug) return false;
    return true;
}

void TDataDrv::MoveToVar(string &Str)
{
    CVar::MoveToVar(Str);
    LConvStr CS(Str);
// ����� �������
    bDebug = CS;
    // ��� �������-������ ������
        string strNameModelData = CS;
    //	��� ������
        string strNameTrend = CS;
}

ostream& operator<<(ostream& os, TDataDrv &dat)
{
 CVar V;
 V = (CVar)dat;
 os<<V;
// os<<(CVar)dat;
 return os;
//	 setprecision(4)<<setw(15)<<dat.dData<<';'
// os<<setprecision(4)<<setw(15)<<dat.dData<<';'
// 	<<setw(20)/*<<dat.ExactTime*/<<';'<<endl;
 return os;
}

// ������������� ����� ����� ������� ���������� �:
// 1 - ����������� ���������� (� ������ ������� ����������)
// 2 - �������� ������������� � ������ strNameModelData
// 3 - "��������� �����" � ������� nNumView
void TDataDrv::SetAddr()
{
// ���������� � ����.���������� (���� ���� ��������������� (� ������ ������� ����������))
// ������ �� ������� ����������
//	if (GetRef()<=1)  {
//		if (m_nUse==cvarVacant) {

// nNumView - ����� ���� ����������� � ��������, ��� ������������ �������� ����������

}
