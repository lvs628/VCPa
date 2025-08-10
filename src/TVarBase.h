// TVarBase.h: interface for the TVarBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVARBASE_H)
#define AFX_TVARBASE_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

#include "TDataDrv.h"


class TVarBase : public TDataDrv
{
public:
	double SetDataDrvSrc(double d);
	TVarBase(TAppDrv* pInf, string &nam);
	TVarBase(const TVarBase& var);
	TVarBase();
	virtual ~TVarBase();
//
	void MoveToVar(string& strS);
	virtual bool IfEqu(TVarBase& var);
	void SetAddr();
};

typedef list<TVarBase> TArrayVarBase;
typedef list<TVarBase>::iterator TIteratorVarBase;
typedef list<TVarBase*> TArrayIVarBase;
typedef list<TVarBase*>::iterator TIteratorIVarBase;
#endif // !defined(AFX_TVARBASE_H
