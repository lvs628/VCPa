#ifndef __CVARCIRCUIT_H
#define __CVARCIRCUIT_H

#pragma once
#include <string>
#include <list>
using namespace std;

#include "Deffsa.h"

class CVar;
class TAppVar;
class CVarCircuit
{
public:
	string strName;					// ��� ����������-����
	string strNameInp;				// ��� ������� ����������-����
	string strNameOut;				// ��� �������� ����������-����
	CVar* pDataDrvInp;			// ����� ������� ��������� ����
	CVar* pDataDrvOut;			// ����� �������� ��������� ����
	bool	bRelcase;				// ������ �����
	string	strComment;				// ����������� � ����������
public:
	void CreateLink();
	CVarCircuit(void);
	CVarCircuit(TAppVar* pInfo, string& nam);
	CVarCircuit(const CVarCircuit& var);
	CVarCircuit(TAppVar* pInfo, CVar* pDatInp,  CVar* pDatOut);
	~CVarCircuit(void);
	void MoveToVar(string& Str);
	virtual bool IfEqu(CVarCircuit& var);
	int operator==(const CVarCircuit &var) const;
	int operator<(const CVarCircuit &var) const;
protected:
	TAppVar*	pInfoAppl;
};
ostream& operator<<(ostream& os, CVarCircuit &dat);
//istream& operator>>(istream& is, CVarCircuit &dat);
typedef list<CVarCircuit> CArrayVarCircuit;
typedef list<CVarCircuit>::iterator CIteratorVarCircuit;

#endif // CVARCIRCUIT_H
