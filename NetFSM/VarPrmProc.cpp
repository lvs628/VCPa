#include "stdafx.h"
#include <sstream>
#include "VarPrmProc.h"
#include "LConvStr.h"

CVarPrmProc::CVarPrmProc(void)
{
	strName = "";
	strComment	= "";
	strParam1	= "";			// 1-� �������� ��������
	strParam2	= "";			// 2-� �������� ��������
	strParam3	= "";			// 3-� �������� ��������
	strParam4	= "";			// 4-� �������� ��������
	strParam5	= "";			// 5-� �������� ��������
	strParam6	= "";			// 6-� �������� ��������
	strParam7	= "";			// 7-� �������� ��������
	strParam8	= "";			// 8-� �������� ��������
	strParam9	= "";			// 9-� �������� ��������
	strParam10	= "";			// 10-� �������� ��������
	strParam11	= "";			// 10-� �������� ��������
	strParam12	= "";			// 10-� �������� ��������
	strParam13	= "";			// 10-� �������� ��������
	strParam14	= "";			// 10-� �������� ��������
	strParam15	= "";			// 10-� �������� ��������
	strParam16	= "";			// 10-� �������� ��������
	strParam17	= "";			// 10-� �������� ��������
	strParam18	= "";			// 10-� �������� ��������
	strParam19	= "";			// 10-� �������� ��������
	strParam20	= "";			// 10-� �������� ��������
	strParam21	= "";			// 10-� �������� ��������
	strParam22	= "";			// 10-� �������� ��������
	strParam23	= "";			// 10-� �������� ��������
	strParam24	= "";			// 10-� �������� ��������
	strParam25	= "";			// 10-� �������� ��������
	strParam26	= "";			// 10-� �������� ��������
	strParam27	= "";			// 10-� �������� ��������
	strParam28	= "";			// 10-� �������� ��������
	strParam29	= "";			// 10-� �������� ��������
	strParam30	= "";			// 10-� �������� ��������
}

CVarPrmProc::CVarPrmProc(const CVarPrmProc& var)
{
	pTAppVar	= var.pTAppVar;
	strName		= var.strName;
	strComment	= var.strComment;
	strParam1	= var.strParam1;			// 1-� �������� ��������
	strParam2	= var.strParam2;			// 2-� �������� ��������
	strParam3	= var.strParam3;			// 3-� �������� ��������
	strParam4	= var.strParam4;			// 4-� �������� ��������
	strParam5	= var.strParam5;			// 5-� �������� ��������
	strParam6	= var.strParam6;			// 6-� �������� ��������
	strParam7	= var.strParam7;			// 7-� �������� ��������
	strParam8	= var.strParam8;			// 8-� �������� ��������
	strParam9	= var.strParam9;			// 9-� �������� ��������
	strParam10	= var.strParam10;			// 10-� �������� ��������
	strParam11	= var.strParam11;			// 10-� �������� ��������
	strParam12	= var.strParam12;			// 10-� �������� ��������
	strParam13	= var.strParam13;			// 10-� �������� ��������
	strParam14	= var.strParam14;			// 10-� �������� ��������
	strParam15	= var.strParam15;			// 10-� �������� ��������
	strParam16	= var.strParam16;			// 10-� �������� ��������
	strParam17	= var.strParam17;			// 10-� �������� ��������
	strParam18	= var.strParam18;			// 10-� �������� ��������
	strParam19	= var.strParam19;			// 10-� �������� ��������
	strParam20	= var.strParam20;			// 10-� �������� ��������
	strParam21	= var.strParam11;			// 10-� �������� ��������
	strParam22	= var.strParam22;			// 10-� �������� ��������
	strParam23	= var.strParam23;			// 10-� �������� ��������
	strParam24	= var.strParam24;			// 10-� �������� ��������
	strParam25	= var.strParam25;			// 10-� �������� ��������
	strParam26	= var.strParam26;			// 10-� �������� ��������
	strParam27	= var.strParam27;			// 10-� �������� ��������
	strParam28	= var.strParam28;			// 10-� �������� ��������
	strParam29	= var.strParam29;			// 10-� �������� ��������
	strParam30	= var.strParam30;			// 10-� �������� ��������
}

CVarPrmProc::CVarPrmProc(TAppVar* pInfo, string nam)
{
    pTAppVar = (TAppCore*)pInfo;
	MoveToVar(nam); 
}

CVarPrmProc::~CVarPrmProc(void)
{
}

void CVarPrmProc::MoveToVar(string& Str)
{
	LConvStr Cmnd(Str);
    strName		= string(Cmnd);
    strComment  = string(Cmnd);
    strParam1	= string(Cmnd);
    strParam2	= string(Cmnd);
    strParam3	= string(Cmnd);
    strParam4	= string(Cmnd);
    strParam5	= string(Cmnd);
    strParam6	= string(Cmnd);
    strParam7	= string(Cmnd);
    strParam8	= string(Cmnd);
    strParam9	= string(Cmnd);
    strParam10	= string(Cmnd);
    strParam11	= string(Cmnd);
    strParam12	= string(Cmnd);
    strParam13	= string(Cmnd);
    strParam14	= string(Cmnd);
    strParam15	= string(Cmnd);
    strParam16	= string(Cmnd);
    strParam17	= string(Cmnd);
    strParam18	= string(Cmnd);
    strParam19	= string(Cmnd);
    strParam20	= string(Cmnd);
    strParam21	= string(Cmnd);
    strParam22	= string(Cmnd);
    strParam23	= string(Cmnd);
    strParam24	= string(Cmnd);
    strParam25	= string(Cmnd);
    strParam26	= string(Cmnd);
    strParam27	= string(Cmnd);
    strParam28	= string(Cmnd);
    strParam29	= string(Cmnd);
    strParam30	= string(Cmnd);
}

bool CVarPrmProc::IfEqu(CVarPrmProc& var) {
	if (strName != var.strName) return false;
	if (strComment != var.strComment) return false;
	if (strParam1 != var.strParam1) return false;
	if (strParam2 != var.strParam2) return false;
	if (strParam3 != var.strParam3) return false;
	if (strParam4 != var.strParam4) return false;
	if (strParam5 != var.strParam5) return false;
	if (strParam6 != var.strParam6) return false;
	if (strParam8 != var.strParam7) return false;
	if (strParam8 != var.strParam8) return false;
	if (strParam9 != var.strParam9) return false;
	if (strParam10 != var.strParam10) return false;
	if (strParam11 != var.strParam11) return false;
	if (strParam12 != var.strParam12) return false;
	if (strParam13 != var.strParam13) return false;
	if (strParam14 != var.strParam14) return false;
	if (strParam15 != var.strParam15) return false;
	if (strParam16 != var.strParam16) return false;
	if (strParam17 != var.strParam17) return false;
	if (strParam18 != var.strParam18) return false;
	if (strParam19 != var.strParam19) return false;
	if (strParam20 != var.strParam20) return false;
	if (strParam21 != var.strParam21) return false;
	if (strParam22 != var.strParam22) return false;
	if (strParam23 != var.strParam23) return false;
	if (strParam24 != var.strParam24) return false;
	if (strParam25 != var.strParam25) return false;
	if (strParam26 != var.strParam26) return false;
	if (strParam27 != var.strParam27) return false;
	if (strParam28 != var.strParam28) return false;
	if (strParam29 != var.strParam29) return false;
	if (strParam30 != var.strParam30) return false;
	return true;
}

int CVarPrmProc::operator==(const CVarPrmProc &var) const
{ 
	return strName==var.strName; 
}

int CVarPrmProc::operator<(const CVarPrmProc &var) const
{ 
	return strName<var.strName; 
}

ostream& operator<<(ostream& os, CVarPrmProc &dat)
{
//	if (dat.strName=="CycleNorm")
//		int n=1;
    return os<<dat.strName<<';'
    <<dat.strComment<<';'
    <<dat.strParam1<<';'
    <<dat.strParam2<<';'
    <<dat.strParam3<<';'
    <<dat.strParam4<<';'
    <<dat.strParam5<<';'
    <<dat.strParam6<<';'
    <<dat.strParam7<<';'
    <<dat.strParam8<<';'
    <<dat.strParam9<<';'
    <<dat.strParam10<<';'
    <<dat.strParam11<<';'
    <<dat.strParam12<<';'
    <<dat.strParam13<<';'
    <<dat.strParam14<<';'
    <<dat.strParam15<<';'
    <<dat.strParam16<<';'
    <<dat.strParam17<<';'
    <<dat.strParam18<<';'
    <<dat.strParam19<<';'
    <<dat.strParam20<<';'
    <<dat.strParam21<<';'
    <<dat.strParam22<<';'
    <<dat.strParam23<<';'
    <<dat.strParam24<<';'
    <<dat.strParam25<<';'
    <<dat.strParam26<<';'
    <<dat.strParam27<<';'
    <<dat.strParam28<<';'
    <<dat.strParam29<<';'
    <<dat.strParam30<<';'
	<<endl;
}
