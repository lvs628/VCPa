#ifndef TAPPVAR_H
#define TAPPVAR_H

#include <string>
using namespace std;

#include "fsacore.h"
#include "defvsavar.h"
#include "TAppCore.h"
#include "lfsaappl.h"

class CSetVarView;
class TSetVarPosWnd;
class CVarSetting;
class CSetVarSetting;
class CSetVarCircuit;
class CSetVarFsaNew;
class CSetVarFSA;
class CSetVarFsaObject;	// ������ ��������-���������
class CSetVarPrmProc;
class CVar;
class	TAppDrv;

class TAppVar: public TAppCore
{
public:

	TAppVar(void);
    virtual ~TAppVar(void);
	CVarPrmProc* DeleteParameters(LFsaAppl *pL);
	CVarPrmProc* GreateParameters(LFsaAppl *pL);
	CVarPrmProc* GetPtrParameters(LFsaAppl *pL);
	virtual bool	LinkVar();
    virtual void ReloadVCPa(void);

    CSetVarPrmProc	*pSetVarPrmProc;	// ������ ���������� ���������
	CSetVarCircuit	*pSetVarCircuit;	// ������ ����������-�����

	TAppDrv	*pTAppDrv;
};

#endif // TAPPVAR_H
