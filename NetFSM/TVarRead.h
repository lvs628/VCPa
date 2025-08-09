// TVarRead.h: interface for the TVarRead class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TVARREAD_H
#define AFX_TVARREAD_H

#include <list>
using namespace std;

#include "deffsadrv.h"
#include "TVarBase.h"

class TVarRead : public TVarBase
{
public:
	TVarRead(const TVarRead& var);
	TVarRead(TAppDrv *pInf, string &nam);
	TVarRead();
	virtual ~TVarRead();
	virtual bool IfEqu(TVarRead& var);
	void MoveToVar(string &strS);
	void SetAddr();
};
typedef list<TVarRead> TArrayVarRead;
typedef list<TVarRead>::iterator TIteratorVarRead;
typedef list<TVarRead*> TArrayIVarRead;
typedef list<TVarRead*>::iterator TIteratorIVarRead;

#endif // !defined(AFX_TVARREAD_H
