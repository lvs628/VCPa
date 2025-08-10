#ifndef LFSAAPPL_H
#define LFSAAPPL_H
#include <Arduino.h>
#include <string>
#include <list>
using namespace std;

#include "task.h"
#include "LFsaHdr.h"
class TAppProcesses;
#include "clocvar.h"
#include "VarFSA.h"

class CVarPrmProc;
class LFsaAppl;
typedef int(LFsaAppl::*FncClassX)();
typedef void(LFsaAppl::*FncClassY)();
class LListState;
class LFsaHdr;
class CSetLocVar;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             fs_tbl
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class fs_tbl {
    public:
        LListState* adt; FncClassX* adx; FncClassY* ady;
    public:
        fs_tbl(LListState *pAdt, FncClassX *pAdx, FncClassY *pAdy);
        ~fs_tbl();
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             fs_dbg
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class fs_dbg {
public:
    string nameFsa;
    string nameFsaProcess;
    fs_dbg(string szName);
    ~fs_dbg();
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             LFsaAppl
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CFDelay;
class LListState;
class WSP;
class LFsaArc;
class LArc;
class LFsaAppl:public fs_tbl, public fs_dbg  
{
public:
    bool			FDbgSetViewArc(bool b);
    virtual string	FDbgViewArc(UINT id = 29003);
    bool			FIsActiveParDelay();
    void			FCreateDelay(int nDelay);
    void			FCreateParDelay(int nDelay);
    CVarPrmProc* GreateParameters();
    CVarPrmProc* GetPtrParameters();
    LFsaAppl*   FCall(LFsaAppl*);
    int				FGetRange();
    virtual string	FDbgViewState(UINT id = 29003);
    void			FUpdateVariable();                                      // обновить локальные переменные
    virtual bool	FUpdateLinks(string name, int nT);				// отредактировать связи процесса (имя процесса, тип редакции)
    virtual bool	FSetLocking(bool bSet, LFsaAppl *pOwner, string strNameVar);			//	установка/сброс блокировки определенным процессом
    virtual bool	FCreationOfLinksForVariables();					// создание ссылок для переменных процесса
    virtual bool	FInit();
    virtual LFsaAppl* Create(CVarFSA *pCVF);
    LFsaAppl();
    LFsaAppl(LArc* aT, string name, CVarFSA *pCVF=nullptr);
    ~LFsaAppl();
    int virtual x1();   int virtual x2();   int virtual x3();
    int virtual x4();   int virtual x5();   int virtual x6();
    int virtual x7();   int virtual x8();   int virtual x9();
    int virtual x10();  int virtual x11();  int virtual x12();
    int virtual x13();  int virtual x14();  int virtual x15();
    int virtual x16();
    int virtual x17();  int virtual x18();  int virtual x19();
    int virtual x20();  int virtual x21();  int virtual x22();
    int virtual x23();  int virtual x24();  int virtual x25();
    int virtual x26();  int virtual x27();  int virtual x28();
    int virtual x29();  int virtual x30();  int virtual x31();
    int virtual x32();
    void virtual y1(){}   void virtual y2(){}   void virtual y3(){}
    void virtual y4(){}   void virtual y5(){}   void virtual y6(){}
    void virtual y7(){}   void virtual y8(){}   void virtual y9(){}
    void virtual y10(){}  void virtual y11(){}  void virtual y12(){}
    void virtual y13(){}  void virtual y14(){}  void virtual y15(){}
    void virtual y16(){}
    void virtual y17(){}  void virtual y18(){}  void virtual y19(){}
    void virtual y20(){}  void virtual y21(){}  void virtual y22(){}
    void virtual y23(){}  void virtual y24(){}  void virtual y25(){}
    void virtual y26(){}  void virtual y27(){}  void virtual y28(){}
    void virtual y29(){}  void virtual y30(){}  void virtual y31(){}
    void virtual y32(){}

    CLocVar*    CreateLocVar(string namVar, unsigned int unType, string strComment, bool bSave=true, string strInit="", string strNameNetFsa="");
    void virtual run();
    void    FSetMoore(bool b=true);
    string	FGetNameFsa() const;
    string	FGetNameVarFSA() const;
    int		FIsActiveTask();
    void	FStart();
    void	FStop();
    bool	FIfStop();
    TASK*	FLoad(TNetFsa *NetFsa, string strProc, int pri=1, bool bNot=false, CVarFSA *pVar=nullptr);
    TASK*	FGetTask();
    TNetFsa*	GetPointerToNet();
    virtual string	FGetState(int nNum=-1);
    void virtual FResetActions();
    string	FGetNameProcess() const;
    virtual void ExecuteThreadStep();
    void virtual MooreAction(){}
    void virtual ELSE();
    void virtual MealyLoop();
    void FResetAppl();
    void 	FClearOk();
    void 	FClearError();
    void 	FSetOk(int nOk=1, const char* pch=nullptr);
    void	FSetSleep(long lS);
    long	FGetSleep();
    string	FGetStateUp();

    string      strCurrentArc;
    int nState{0}, nTmpState{0};
    bool    FGoToState(string nam);
    string      strGetCurrentArc(WSP *p=nullptr);
private:
    inline int X1();	inline int X2();	inline int X3();  inline int X4();
    inline int X5();	inline int X6();	inline int X7();  inline int X8();
    inline int X9();	inline int X10();	inline int X11(); inline int X12();
    inline int X13();inline int X14(); inline int X15(); inline int X16();
    inline int X17();inline int X18(); inline int X19(); inline int X20();
    inline int X21();inline int X22(); inline int X23(); inline int X24();
    inline int X25();inline int X26(); inline int X27(); inline int X28();
    inline int X29();inline int X30(); inline int X31(); inline int X32();

public:
    TASK*		CALTSK(TNetFsa *NetFsa, int pri);
    LFsaHdr		var;
    LFsaHdr		*pLFsaHdr;
    LFsaAppl	*pFsaApplError;
    int			nFsaPriority;
    string		strNameVarFsaNew;
    TAppCore	*pTAppCore;
    CVarFSA		*pCVarFSA{nullptr};
    CVarPrmProc *pVarPrmProc;
    CSetLocVar	*pCSetLocVar;
    int	nModeVar;
    LArc		*pTBL;
    LFsaAppl	*pNestedAutomaton{nullptr};
    LFsaAppl	*pMainAutomaton{nullptr};
    bool bIfLoad{false};            // флаг загрузки процесса (2024.08.20)

//protected:
    LFsaArc		*ADT, *ARC_T, *ARC_B;
    unsigned long M_X, M_XY, BAZ_XY;
    LListState* SqmTable;
    FncClassX	X[32];
    FncClassY	Y[32];
    WSP*		pWSP;
    bool		bIfViewArc;
    CFDelay		*pParFDelay;
    CFDelay		*pCFDelay;
    bool        bIfRunThread{false};
    bool bIfReset{false};
    unsigned long p2pck;
    string		strOk;
    string		strError;
    int			nOkProcess;
    int			nErrorProcess;
    TNetFsa		*pTNetFsa;
    bool		bIfCall;
    bool        bIfMoore{false};
    friend class WSP;
    friend class TNetFsa;

private:    
    TNetFsa* pNet;
};
typedef std::list<LFsaAppl> CArrayLFsaAppl;
typedef std::list<LFsaAppl>::iterator CIteratorLFsaAppl;
typedef std::list<LFsaAppl*> CArrayILFsaAppl;
typedef std::list<LFsaAppl*>::iterator CIteratorILFsaAppl;
#endif // LFSAAPPL_H
