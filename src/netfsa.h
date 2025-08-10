#ifndef __netfsa_h
#define __netfsa_h
#include "ArithmeticMean.h"
#include "task.h"
#include "lfsaappl.h"
//#include <ctime.h>
#include <list>
#include <string>
using namespace std;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                         NetFsa
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSetVarNetFsa;
class CVarSetting;
class TAppCore;
class CArrayNetFsa;
class CStackWsp;
class CStackTsk;
class WSP;
class TNetFsa
{
 public:
	CArithmeticMean	ArithmeticMeanTime;
    bool bSynch{false};
    long tickT0{0};
    long t1{0};
    long tickPrevTime{0};
    double	dDeltaTime{0};
    double	dAmbiguity{0};							// погрешность
    double	dCountDeltaTime{0};
double SetDeltaTime(double d);
double GetDeltaTime();
TAppCore* GetPtrAppCore() { return pTAppCore; }
void 	OnIdle(CVarSetting *pCV);
void 	UpdateVariable();
bool	TCreationOfLinksForVariables();
long	GetNumberOfTasks(long *lAct);
LFsaAppl *TGetPointerProcess(string strName, int *pri);
	TNetFsa(CArrayNetFsa *pCArray, string str="");
	virtual ~TNetFsa();
public:
	bool	operator==(const TNetFsa& fsa) const;
	bool 	operator<(const TNetFsa& fsa) const;
	bool 	operator>(const TNetFsa& fsa) const;
	void	ClearNumberOfTasks();
	bool 	IfStopTask(TASK* task);
	void	Init(long *idleQuantum);
	void 	go_task();
	long	GetQuantum();
	int		GetRestWsp();
	int		GetRestTsk();
	void 	PerformanceQuantum();
	void	SetQuantum(long *idleQuantum);
	void	StartTask();
	void	StartTask(TASK* task);
	void 	StopTask();
	void 	StopTask(TASK* task);
	LFsaAppl *TGetPointerFsa(string strName, int *pri);
	WSP	*GetPointerToCurWSP();
    void    ResetTasks();
    CVarSetting	*pCVarSetting{nullptr};
 private:
    void OnIdleSYS(CVarSetting *pCV);
    void dispc (TASK&);
	void dispcX (TASK&);
	void dispcY (TASK&);
	void dispcNewSt (TASK&);
	int 	insqtsk(LFsaAppl*, TASK*);
	void  mov_tsk(TASK *st_tsk, TASK *lst_tsk);
 public:
	 string strName;
     long lCountTime{0};
     TASK 	*cur_task{nullptr};
	PID 	*pid_task;
    int 	len_pid{0};
	TASK 	list_0task;
	TASK 	list_1task;
	TASK 	list_2task;
	TASK 	stop_0task;
	TASK 	stop_1task;
	TASK 	stop_2task;
	TASK 	wait_task;
    bool 	bStopAllTask{false};
    CStackWsp*	pStackWsp{nullptr};
    CStackTsk*	pStackTsk{nullptr};
    long	lNumberOfTasks{0};
    long	lNumberOfActiveTasks{0};
    CArrayNetFsa	*pCArrayNetFsa{nullptr};
    CSetVarNetFsa   *pCSetVar{nullptr};
	list<string>	strListTypeVar;
	CArrayILFsaAppl	ArrayILFsaAppl;
 private:
    TASK 	*del_tsk{nullptr};
    WSP 	*OldWsp{nullptr}, *cur_wsp{nullptr};
    long 	CountDispMain{0};
    long 	MyCount{0};
	long* 	SaveCountDispMain;
    TAppCore	*pTAppCore{nullptr};
};
#endif
