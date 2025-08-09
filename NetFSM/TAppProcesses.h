#pragma once
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
	CLocVar* GetAddressVar(const char* nam, LFsaAppl *pL=NULL);		// �������� ������ �� ���������� nam
	bool LinkVar();
	TAppProcesses(void);
	~TAppProcesses(void);
    int LoadConfig();
    virtual bool LoadConfiguration(void);
    LFsaAppl* arLibraryFsa[10];
};

union ucrc {
    _int16 uiValue;
    unsigned char ucCRC[2];				// ����� CRC 0,1
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
