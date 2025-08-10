// TVarRead.cpp: implementation of the TVarRead class.
//
//////////////////////////////////////////////////////////////////////

#include "TVarRead.h"
#include "tappdrv.h"
#include <algorithm>
#include "LConvStr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TVarRead::TVarRead():
	TVarBase()
{
}

TVarRead::~TVarRead()
{

}

bool TVarRead::IfEqu(TVarRead& var)
{
	if (!TVarBase::IfEqu(var)) return false;
	return true; 

}

TVarRead::TVarRead(const TVarRead& var):
	TVarBase(var)
{
}
TVarRead::TVarRead(TAppDrv *pInf, string &nam)
	:TVarBase(pInf, nam)
{ 
	MoveToVar(nam); 
	dDataSrc = 0;

	if (unTypeVar==CVar::vtFsastate) {

	}

}

void TVarRead::MoveToVar(string &Str)
{
	LConvStr CS(Str);
// ��� ����������� ������������
    strNameNetFsa= string(CS);
// ��� ����������
	unTypeVar= CS;
// ��� ������ 
	bSerial= CS;
// ������ ���������
	bOnlyChanges= CS;
// ���������
    bConstant = CS;
}
//	���������� ��������� �� ������ ��������������� � ����.���������
void TVarRead::SetAddr()
{
	TVarBase::SetAddr();
	if (!pTAppCore) return;
//	pAlgScale =	pTAppDrv->pSetArrayScale->GetAddressVar(strNamScaleAlg.c_str()); 
}
