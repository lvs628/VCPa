#ifndef __CVARPRMPROC_H
#define __CVARPRMPROC_H

#include <string>
#include <list>
using namespace std;
#include "defvsavar.h"

class TAppVar;
class TAppCore;
class CVarPrmProc
{
public:
    string		strName;			// ��� ����������-��������
    string		strComment;			// ��������/����������� � ���������� ��������
    string		strParam1;			// 1-� �������� ��������
    string		strParam2;			// 2-� �������� ��������
    string		strParam3;			// 3-� �������� ��������
    string		strParam4;			// 4-� �������� ��������
    string		strParam5;			// 5-� �������� ��������
    string		strParam6;			// 6-� �������� ��������
    string		strParam7;			// 7-� �������� ��������
    string		strParam8;			// 8-� �������� ��������
    string		strParam9;			// 9-� �������� ��������
    string		strParam10;			// 10-� �������� ��������
    string		strParam11;			// 11-� �������� ��������
    string		strParam12;			// 12-� �������� ��������
    string		strParam13;			// 13-� �������� ��������
    string		strParam14;			// 14-� �������� ��������
    string		strParam15;			// 15-� �������� ��������
    string		strParam16;			// 16-� �������� ��������
    string		strParam17;			// 17-� �������� ��������
    string		strParam18;			// 18-� �������� ��������
    string		strParam19;			// 19-� �������� ��������
    string		strParam20;			// 20-� �������� ��������
    string		strParam21;			// 21-� �������� ��������
    string		strParam22;			// 22-� �������� ��������
    string		strParam23;			// 23-� �������� ��������
    string		strParam24;			// 24-� �������� ��������
    string		strParam25;			// 25-� �������� ��������
    string		strParam26;			// 26-� �������� ��������
    string		strParam27;			// 27-� �������� ��������
    string		strParam28;			// 28-� �������� ��������
    string		strParam29;			// 29-� �������� ��������
    string		strParam30;			// 30-� �������� ��������
    CVarPrmProc(TAppVar* pInfo, string nam);
    CVarPrmProc(const CVarPrmProc &var);
    CVarPrmProc(void);
    ~CVarPrmProc(void);
    void MoveToVar(string& Str);
    virtual bool IfEqu(CVarPrmProc& var);
    int operator==(const CVarPrmProc &var) const;
    int operator<(const CVarPrmProc &var) const;
    TAppCore*	pTAppVar;
};
ostream& operator<<(ostream& os, CVarPrmProc &dat);
typedef list<CVarPrmProc> TArrayVarPrmProc;
typedef list<CVarPrmProc>::iterator TIteratorVarPrmProc;

#endif //__CVARPRMPROC_H
