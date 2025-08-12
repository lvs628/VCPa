#pragma once
#include "SetVarSetting.h"
#include "netfsa.h"
#include "TAppVar.h"
#include "deffsaprc.h"

class TAppProcesses :
	public TAppVar
{
public:
	CVar* IterAddressVar(bool begin=true);
	CLocVar* InsertVar(CVar* pVar, LFsaAppl *pL=NULL);
	CLocVar* ReplaceVar(CVar* pVar, LFsaAppl *pL=NULL);
	CLocVar* DeleteVar(const char* nam, LFsaAppl *pL=NULL);
	CLocVar* GetAddressVar(const char* nam, LFsaAppl *pL=NULL);
	bool LinkVar();
	TAppProcesses(void);
	~TAppProcesses(void);
    int LoadConfig();
    virtual bool LoadConfiguration(void);
};

union ucrc {
    _int16 uiValue;
    unsigned char ucCRC[2];
};

union fl {
    unsigned char ach[4];
    float d;
};

union fshort {
    unsigned char ach[2];
    unsigned short ud;
    short d;
};

union fint {
    unsigned char ach[2];
    int d;
};
extern TAppProcesses *pTAppProcesses;
TAppProcesses* VCPaCore_init();
void VCPaCore_TimerEvent(int nId);
void LoadingFsaProsesses();
