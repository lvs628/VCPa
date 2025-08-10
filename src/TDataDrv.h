// TDataDrv.h: interface for the TDataDrv class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TDATADRV_H
#define AFX_TDATADRV_H

#include <iostream>
#include <list>
#include <string>
using namespace std;
#include "Var.h"

class TAppDrv;
class TDataDrv: public CVar
{
public:
 	enum {cvarNone, cvarAbstract, cvarRead, cvarWrite};
	TDataDrv();
	TDataDrv(const TDataDrv& var);
	TDataDrv(TAppDrv	*pInf, string &nam);
	TDataDrv(TAppDrv	*pInf, double d);
	virtual ~TDataDrv();
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
	TAppDrv		*pTAppDrv;
//	
	bool		bDebug;			// ����� �������
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
	void MoveToVar(string &strS);
	int	GetType() {return nType; }
//
	operator double();
	virtual bool IfEqu(TDataDrv& var);
	void SetAddr();
};
ostream& operator<<(ostream& os, TDataDrv &dat);
istream& operator>>(istream& is, TDataDrv &dat);
typedef list<TDataDrv> TArrayDataDrv;
typedef list<TDataDrv>::iterator TIteratorDataDrv;

#endif // !defined(AFX_TDATADRV_H
