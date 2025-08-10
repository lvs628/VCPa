#pragma once
#include "deffsadrv.h"

class	TSetVarRead;
class TAppCore;
class _FSADRVCLASS TAppDrv
{
public:

	virtual bool	LinkVar();
	void SetSaveSet(void);
    virtual void SaveConfiguration(void);
    virtual void ReloadVCPa(void);
	TAppDrv(TAppCore *pT);
    virtual ~TAppDrv(void);

	TAppCore		*pTAppCore;

	TSetVarRead		*pSetVarRead;		// массив читаемых переменных
};
