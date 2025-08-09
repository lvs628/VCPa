#ifndef __CSETVARSETTING_H
#define __CSETVARSETTING_H

#pragma once

#include "SetVar.h"
#include "VarSetting.h"	// Added by ClassView

class CSetVarSetting : public CSetVar
{
public:
	CSetVarSetting(TAppCore *pPr, string strNam);
	~CSetVarSetting(void);
    void SetSaveSet(bool b);
	bool Add(CVarSetting &var);
	bool Replace(CVarSetting &var);
	bool Delete(CVarSetting &var);
    CVarSetting* GetAddressVar(string &nam);
	TArrayCVarSetting *pArray;
};

#endif //__CSETVARSETTING_H
