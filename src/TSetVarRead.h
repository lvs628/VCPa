// TSetVarRead.h: interface for the TSetVarRead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSETVARREAD_H)
#define AFX_TSETVARREAD_H

#pragma once
#include <string>
using namespace std;

#include "TVarRead.h"
#include "SetVar.h"
#include "deffsadrv.h"

class _FSADRVCLASS TSetVarRead: public CSetVar
{
public:
	void UpdateVariable();
	TSetVarRead(TAppDrv *pInfo, string strNam);
	virtual ~TSetVarRead();
	void CreateLink();
	void CreateLink(TVarRead* var);
	bool Add(TVarRead &var);
    bool Replace(TVarRead &var, bool bApply=false);
	bool Delete(TVarRead &var);
	TVarRead* GetAddressVar(const char* nam);
	TArrayVarRead *pArray;
private:
	TAppDrv	*pTAppDrv;

};

#endif // !defined(AFX_TSETVARREAD_H
