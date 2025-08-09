#pragma once
#include "fsacore.h"

#include "SetLFsaHdr.h"

typedef vector<TNetFsa*> TPArrayNetFsa;
typedef vector<TNetFsa*>::iterator TPIteratorNetFsa;
typedef vector<TNetFsa> TArrayNetFsa;
typedef vector<TNetFsa>::iterator TIteratorNetFsa;

class TAppCore;
class CArrayNetFsa  
{
public:
    void    ResetTasks();
    long	GetNumberOfTasks(long *lAct);
	TNetFsa* GetAdressNetFsa(string strName);
	LFsaAppl* GetAdressFsaAppl(string str, int *pr, TNetFsa **pNet);
    bool InitNetFsa();
    TNetFsa* GetNetFsa(string str, string strConfig);
	CArrayNetFsa(TAppCore *pCore);
	virtual ~CArrayNetFsa();
	virtual bool OnIdleFsa(long lCount);

	TNetFsa* pNetFsa;

    TPArrayNetFsa PArrayNetFsa;
    TPIteratorNetFsa PIteratorNetFsa;

	CSetLFsaHdr	*pSetLFsaHdr;
	long	lNumberOfTasks;
	long	lNumberOfActiveTasks;
	TAppCore	*pTAppCore;
};
