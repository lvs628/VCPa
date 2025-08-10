#pragma once
#include "Var.h"
#include "SetVar.h"
class CSetVarNetFsa :
	public CSetVar
{
public:
	CSetVarNetFsa(TAppCore *pC, string strNam);
	~CSetVarNetFsa(void);
	void SaveDat();
	void ReadDat(string& pszP, string& pszFile);
	void WriteDat(string& pszP, string& pszFile);
	bool Add(CVar &var);
	bool Replace(CVar &var);
	bool Delete(CVar &var);
	CVar* GetAddressVar(const char* nam);
	TArrayIVar *pArray;
};

