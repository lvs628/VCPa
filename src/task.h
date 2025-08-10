#ifndef __task_h
#define __task_h
#include "Deffsa.h"
#include <string>
using namespace std;
//================================================       AUTOMCUR.H
class WSP;
class LFsaAppl;
class TNetFsa;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             PID
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TASK;
class PID {
 public:
	 TASK *task; int stop;
 public:
	 PID();
	 ~PID();
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             TASK
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TASK {
public:
	TASK();
	~TASK();
	void TSetSleep(long lS); 
	long TGetSleep();
	void Clear();
	TASK* remque();
	TASK* GetNextTask();
	void insque (TASK*);
	void SetPointers(TASK *t1, TASK *t2);
    const char* fsa_state () {return state;}
	string fsa_name ()  {return name;}
 public:
	TASK *flink, *blink;    //
	bool	bHead;
	TASK* pList;	 			// ������ ��������� ������ �����
	WSP *w_fl, *w_bl;
	TNetFsa *pNetFsa;
	LFsaAppl *pFsaAppl;
	PID *pid;
    const char *state;
	void *param;
	string name;
	int pri;
	bool bCancel;
    long lSleep;
    long lCountSleep;
friend class TNetFsa;
};
#endif
