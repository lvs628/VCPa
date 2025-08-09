//=========================================================  TASK.CPP ====
//#include <fsa\fsalws.h>
#include "task.h"
#include "Wsp.h"
#include "Sttbl.h"
#include "lfsaappl.h"

PID::PID()
{
	task=0; stop=0;
}
PID::~PID() {}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				                   TASK
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TASK::TASK()
{	
    flink=blink=pList= nullptr;
	bHead = true;
    w_fl=w_bl=nullptr;
    pid=nullptr; state=nullptr; param=nullptr;
	name="";
	pri=0;
	bCancel= false;
    pNetFsa=nullptr; pFsaAppl=nullptr;
	lSleep = lCountSleep = 0;
}

void TASK::SetPointers(TASK *t1, TASK *t2)
{
	flink=t1;blink=t2; 
}

TASK::~TASK()
{
}
void TASK::Clear()
{
	if (pid)
        pid->task = nullptr;
	remque();       // ������ TSK  �� ������
}
//===================================================================
//                                                             remque
//===================================================================
TASK* TASK::remque()
{
	blink->flink= flink;			// ���. ��뫪� ���। � �।. ��-�
	flink->blink= blink;			// ���. ��뫪� � � � � ᫥�. ��-�
    blink = nullptr;
    flink = nullptr;
	return this;
}
//===================================================================
//                                                             insque
//===================================================================
void TASK::insque (TASK* b)
{
	TASK *bx; 
	bx= b->flink; flink= b->flink; blink= b;
	b->flink= this; bx->blink = this;
}
//===================================================================
//                                                        GetNextTask
//===================================================================
TASK* TASK::GetNextTask() { return flink; }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------- INSQTSK --------
void TASK::TSetSleep(long lS) {
	lSleep = lS;
	lCountSleep = 0;
} 

long TASK::TGetSleep() { return lSleep; } 
