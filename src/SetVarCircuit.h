#ifndef __CSETVARCIRCUIT_H
#define __CSETVARCIRCUIT_H

#pragma once
#include <string>
using namespace std;
#include "SetVar.h"
#include "varcircuit.h"

class CSetVarCircuit :
	public CSetVar
{
public:
    CSetVarCircuit(TAppCore *pInfo, string strNam);
	~CSetVarCircuit(void);
	void CreateLink();
	void CreateLink(CVarCircuit* var);
    bool Add(CVarCircuit &var);
	bool Replace(CVarCircuit &var);
	bool Delete(CVarCircuit &var);
	CVarCircuit* GetAddressVar(const char* nam);
	CArrayVarCircuit *pArray;
private:
	TAppVar*	pInfoAppl;
};

#endif // __CSETVARCIRCUIT_H
