#ifndef TAPPCORE_H
#define TAPPCORE_H

#include <string>
using namespace std;

#include "Var.h"
#include "SetVar.h"

class CVarFsaNew;
class CVarPrmProc;
class CVarFSA;
class CLocVar;
class TNetFsa;
class LFsaAppl;
class CVarSetting;
class CSetVarSetting;
class CSetVarFsaNew;
class CSetVarFSA;
class CSetVarFsaObject;	// ������ ��������-���������
class CArrayNetFsa;
class TAppCore
{
public:
    CArrayNetFsa	*pCArrayNetFsa;

    LFsaAppl *TPtrForNameProcess(string strNameProcess, int *pr, TNetFsa **pNet);
    int GetNumbersOfProcessesForNameFsa(string strNameFsa, string &strListProcesses);
    TNetFsa* GetAdressNetFsa(string str);
    bool	TCreationOfLinksForVariables(string strNameFsaWorld="");
    virtual CLocVar* InsertVar(CVar* pVar, LFsaAppl *pL=nullptr);
    virtual CLocVar* ReplaceVar(CVar* pVar, LFsaAppl *pL=nullptr);
    virtual CLocVar* DeleteVar(const char* nam, LFsaAppl *pL=nullptr);
    virtual CLocVar* GetAddressVar(const char* nam, LFsaAppl *pL=nullptr);		// �������� ������ �� ���������� nam
    virtual int		SizeAllVars(int nMode=0);											//
    CVarFSA* GetAddressVarFSA(string strNameVar);
    virtual CVarPrmProc* DeleteParameters(LFsaAppl *pL);
    virtual CVarPrmProc* GreateParameters(LFsaAppl *pL);
    virtual CVarPrmProc* GetPtrParameters(LFsaAppl *pL);
    CVarFsaNew* GetAddressVarFsaNew(string strNameFsa, string strNameLib);
    bool	StopAllTasks(string strNameTNetFsa);
    bool	StartAllTasks(string strNameTNetFsa);
    bool	InitAllTasks(string strNameTNetFsa);
    bool	StopTask(string strNameCVarFSA);
    bool	StartTask(string strNameCVarFSA);
    virtual bool	LinkVar();
    virtual CVar* IterAddressVar(bool begin=true);
    virtual void SetSaveSet(void);
    virtual void ReloadVCPa(void);
    long         TheTimeReference(void);
    void        SetRealTime(bool bValue);
    bool        GetRealTime();
    TAppCore(void);
    virtual ~TAppCore(void);
    CVar			*pVarDeltaTimeSystem;//	���������� ����� �������
    double			lTimeDeltaFSA;		//	������������ ������� ������� (����������� ����)

    CSetVarSetting	*pSetVarSetting;
    CSetVarFsaObject *pSetVarFsaObject;	// ������ ��������-���������
    CSetVarFSA		*pSetVarFSA;		// ������ ����������-���������

    CVarSetting		*pCVarSetting;
    string			strCurrentWorldFSA;
    TArrayISetVar	ArrayISetVar;
    int				nSizeGlbVars;
    int				nSizeLocVars;
    bool			bIfDesigning;
    bool			bIfStopAllTasks;
    bool            bNotRealTime{false};
    bool			bSaveSensors;
    TNetFsa*        pCurrentNetFsa{nullptr};
    int             nIdTimerVCPa{0};
    long long       llVCPaSystemTime{0};
    long            tk0;

private:
    TIteratorIVar	next;
    bool			bSaveConf;          // ���� ���������� ������ ������� ������������
};

#endif // TAPPCORE_H
