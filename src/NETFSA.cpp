#include "stdafx.h"
//=========================================================  DISPC.CPP ====
#include "fsacore.h"
#include "TAppCore.h"
#include "netfsa.h"
#include "Wsp.h"
#include "StackWsp.h"
#include "StackTsk.h"
#include "Sttbl.h"
#include "Var.h"
#include "VarSetting.h"
#include "SetVarNetFsa.h"
#include "TAppProcesses.h"
#include "ArrayNetFsa.h"
#include "SetVarFSA.h"
#include "csetlocvar.h"
#include "esp_timer.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				                   TNetFsa
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TNetFsa::TNetFsa(CArrayNetFsa *pCArray, string str)
{
    IfStopTask(nullptr);
    pTAppCore = pCArray->pTAppCore;
    pCVarSetting = nullptr;
    pCArrayNetFsa = pCArray;
    strName = str;
    lCountTime	= 0;
    lNumberOfTasks =0;
//	len_pid		= 1000100;
//	len_pid		= 5100;
//	len_pid		= 25000;
//	len_pid		= 2000000;	//	тестирование Фибоначчи
//	len_pid		= 100;		//	для пресса
//    len_pid		= 1000;		//	для скринсайвера Kinks
//    len_pid		= 300;		//	26.10.2013 с тысячью - сбой при удалении процесса в закладке Базовые...
//    len_pid		= 100000;		//	для скринсайвера Akerm
    len_pid		= 100;		//
    bStopAllTask=false;
    pStackWsp	= nullptr;
    pStackWsp	= new CStackWsp(len_pid);
    pStackTsk	= nullptr;
    pStackTsk	= new CStackTsk(len_pid);
//  len_pid = 100;
    list_0task.SetPointers(&list_0task, &list_0task);
    stop_0task.SetPointers(&stop_0task, &stop_0task);
    list_1task.SetPointers(&list_1task, &list_1task);
    stop_1task.SetPointers(&stop_1task, &stop_1task);
    list_2task.SetPointers(&list_2task, &list_2task);
    stop_2task.SetPointers(&stop_2task, &stop_2task);
    wait_task.SetPointers(&wait_task, &wait_task);
    Init(&lCountTime);
    dCountDeltaTime = 0;
//    tickT0.restart();       // = LTime();
//    tbb_tickT0 = tick_count::now();
    // создать массив для списка указателей на переменные автоманого пространства
    pCSetVar	= new CSetVarNetFsa(pCArrayNetFsa->pTAppCore, "NetFsa_"+strName);
    dAmbiguity = 0;
}

TNetFsa::~TNetFsa()
{
/*
    if (pid_task)
        delete[] pid_task;
    if (pStackWsp) {
        int n = pStackWsp->GetRest();
        n = len_pid - n;
        delete pStackWsp;
    }
    if (pStackTsk) {
        int n = pStackTsk->GetRest();
        n = len_pid - n;
//        delete pStackTsk;
    }
    if (pCSetVar) {
        delete pCSetVar;
    }
    strListTypeVar.clear();
*/
}

//===================================================================
//                                                           OnIdle
//===================================================================
void TNetFsa::OnIdle(CVarSetting *pCV) {
    OnIdleSYS(pCV);
}

void TNetFsa::OnIdleSYS(CVarSetting *pCV)
{
    if (dDeltaTime != pCV->dDeltaTime) {
        dDeltaTime = pCV->dDeltaTime;
        dCountDeltaTime = 0;
    }
    if (pCV->bIfSynchronousOperation) {
//        double dT0 = tickT0.elapsed();              // ����� � ��������
        double dDDt = esp_timer_get_time()/1000;    // 1 - секунды; 1e3 - миллисекунды; 1e6 - микросекунды
//        double dDDt = dT0*pCV->dCoefficientTime;    // 1 - секунды; 1e3 - миллисекунды; 1e6 - микросекунды
        double dt = dCountDeltaTime * dDeltaTime;
        if (dDDt>=dt) {
            dAmbiguity = dDDt-dt;		// ��� ����������� ����������� ����������� ����������� �������

            if (dAmbiguity>0) {
                Serial.print(pCV->strName.c_str()); Serial.print(":"); Serial.print(dAmbiguity);Serial.print(" ");
            }
//            double dTimeTick = tickPrevTime.elapsed()*pCV->dCoefficientTime;
            double dTimeTick = 0;
            if (pCV->pTAppCore->pVarDeltaTimeSystem)
                pCV->pTAppCore->pVarDeltaTimeSystem->SetDataSrc(nullptr, dTimeTick);

//            tickPrevTime.restart(); // = LTime();

            PerformanceQuantum();
            pCV->pTAppCore->lTimeDeltaFSA = dTimeTick;
            ArithmeticMeanTime.Put(dTimeTick, 20, true);
            dCountDeltaTime++;
            UpdateVariable();
        }
    }
    else {
//        t1.restart();   // = LTime();
//        double d = tickPrevTime.elapsed()*pCV->dCoefficientTime;
        double d = tickPrevTime;
        if (pCV->pTAppCore->pVarDeltaTimeSystem)
            pCV->pTAppCore->pVarDeltaTimeSystem->SetDataSrc(nullptr, d);

//        tickPrevTime.restart(); // = LTime();
        PerformanceQuantum();
        UpdateVariable();
        ArithmeticMeanTime.Put(d, 20, true);
    }
}

//===================================================================
//                                                           DispInit
//===================================================================
void TNetFsa::Init(long *idleCount)
{
 SaveCountDispMain= idleCount;
 CountDispMain = *idleCount;
 pid_task = new PID[len_pid];
}
//===================================================================
//                                                           DispMain
//===================================================================
void TNetFsa::PerformanceQuantum()
{
    if (!pCVarSetting) return;
    if (bStopAllTask) return;
    if (CountDispMain>0) {
        CountDispMain--; return;
    }
    while (CountDispMain<=0) {
    //	x_y_state(list_0task);
    //	x_y_state(list_1task);
    //	x_y_state(list_2task);
//        qDebug()<<this->strName.c_str();
        dispcX(list_0task);
        dispcY(list_0task);
        dispcNewSt(list_0task);

//        dispcX(list_1task);
//        dispcY(list_1task);
//        dispcNewSt(list_1task);

//        dispcX(list_2task);
//        dispcY(list_2task);
//        dispcNewSt(list_2task);
        CountDispMain++;
    }
    CountDispMain= *SaveCountDispMain;
}
//===================================================================
//        							SetQuantum, GetQuantum
//===================================================================
void TNetFsa::SetQuantum(long *idleQuantum)
{
    SaveCountDispMain= idleQuantum;
    CountDispMain=*idleQuantum;
}

long TNetFsa::GetQuantum() {
    return CountDispMain;
}
//===================================================================
//                                                              dispc
//===================================================================
void TNetFsa::dispc (TASK &lst_tsk)
{
    dispcX (lst_tsk);
    dispcY (lst_tsk);
    dispcNewSt (lst_tsk);
}
void TNetFsa::dispcX (TASK &lst_tsk)
{
    cur_task = lst_tsk.flink;
    while (cur_task != &lst_tsk ) {
        if (!cur_task->bCancel&&!cur_task->pid->stop) {
            if (cur_task->lSleep == cur_task->lCountSleep) {
                cur_wsp = cur_task->w_bl;
                if (cur_wsp->arc_t) {
                    cur_wsp->x();
                }
            }
        }
        else {
            if (cur_task->pid->stop) {
            }

        }
        cur_task = cur_task->flink;
    }

}
void TNetFsa::dispcY (TASK &lst_tsk)
{
    cur_task= lst_tsk.flink;
    while (cur_task != &lst_tsk) {
        cur_wsp = cur_task->w_bl;
        if (!cur_task->bCancel&&!cur_task->pid->stop) {
            if (cur_task->lSleep == cur_task->lCountSleep) {
                if ( cur_wsp->arc_t&&cur_wsp->arc_b) {
                    cur_wsp->y();
                    cur_wsp->pFsaAppl->ExecuteThreadStep();
                    cur_wsp->pFsaAppl->bIfReset = false;
                }
                else {
                    cur_wsp->pFsaAppl->ELSE();
                }
                cur_task->lCountSleep = 0;
                if (cur_wsp->pFsaAppl->bIfMoore)
                    cur_wsp->pFsaAppl->MealyLoop();
            }
            else {
                cur_task->lCountSleep++;
            }
        }
        cur_task= cur_task->flink;
    }

}
void TNetFsa::dispcNewSt (TASK &lst_tsk)
{
    // ���������� ����� ������� ���������
    //	cur_task= cur_task->flink;
        cur_task= lst_tsk.flink;
        while (cur_task != &lst_tsk) {
            cur_wsp = cur_task->w_bl;
            if (!cur_task->bCancel&&!cur_task->pid->stop) {
    //			if ( cur_wsp->arc_t&&cur_wsp->arc_b) {
                if ( (cur_wsp->arc_t&&cur_wsp->arc_b)||cur_wsp->bCall) {
                    /*
                    //10/10/05 (��. WSP::y())
                        if (cur_wsp->arc_t->pNextState) {
                            if (!cur_wsp->bCall) {
                                cur_wsp->arc_t= &cur_wsp->arc_t->pNextState->ListArc.pRoot->FsaArc;
                            }
                            else {
                    //			LFsaArc *arc = &arc_t->pNextState->ListArc.pRoot->FsaArc;
                            }
                        }
                        else {
                            cur_wsp->arc_t= 0;
                        }
                    */
                    if (cur_wsp->bCall) {
    //					cur_task->w_bl->arc_t = &cur_task->w_bl->arc_t->pNextState->ListArc.pRoot->FsaArc;
    //					cur_wsp->bCall = false;
                        cur_wsp->bCall = cur_wsp->bCall;
                    }
    //				cur_task->w_bl->arc_t = &cur_task->w_bl->arc_t->pNextState->ListArc.pRoot->FsaArc;
                    if (cur_task->w_bl->arc_t) {
                        // �������� ��������� ���� 10/10/05 (��. ����)
                        cur_task->state = cur_task->w_bl->arc_t->szSt1;
                        if (cur_wsp->pFsaAppl->bIfMoore)
                            cur_wsp->pFsaAppl->MooreAction();
    /*
                        if (cur_wsp->pFsaAppl->bIfReset) {
                            cur_task->w_bl->arc_t = cur_task->w_bl->pFsaAppl->ADT;
                            cur_task->state = cur_task->w_bl->arc_t->szSt1;
                            cur_wsp->pFsaAppl->bIfReset = false;
                            cur_wsp->pFsaAppl->FResetActions();
                        }
    */
                    }
                }
            }
            // ������� "���������" ������
            if (cur_task->bCancel) {
                while ( static_cast<void*>(cur_task->w_fl) != &cur_task->w_fl) {
                    if (cur_wsp->pFsaAppl) {
                        cur_wsp->pFsaAppl->pWSP=nullptr;
                    }
                    cur_wsp->Clear();
                    pStackWsp->Delete(cur_wsp);
                    cur_wsp= cur_task->w_bl;
                }
                TASK* del_tsk = cur_task;

                if (cur_task->pFsaAppl->pLFsaHdr) {
    //			if (cur_task->pFsaAppl->bIfLFsaHdr) {
    //				cur_task->pFsaAppl->bIfLFsaHdr = false;
                    LFsaHdr var;
                    var.pLFsaAppl = cur_task->pFsaAppl;
    //                cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Size();
                    cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Clear(var);
    //                cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Size();
    //				cur_task->pFsaAppl->bIfLFsaHdr = false;
                }

                cur_task= cur_task->GetNextTask();
                del_tsk->Clear();
                pStackTsk->Delete(del_tsk);
    //			lNumberOfTasks--;								//2007/09/24	��������� ������� ����� �����
            }
            else {
                string strRet;
                // ������� "�����������" ������
                if (!cur_wsp->arc_t) {
    //				string strARC;
                    strRet = cur_wsp->arc_b->szSt2;		// 2016_05_30_10_54
    //				strARC = cur_wsp->pFsaAppl->strGetCurrentArc(cur_wsp);
                    if (strRet == "XX") {
    //                    int n=0;
                    }
                    else if (strRet == "00") {
    //                    int n = 1;
                        string strARC;
    //                    strARC = cur_wsp->pFsaAppl->strGetCurrentArc(cur_wsp);
    //                    printf ("%s\n", strARC.c_str());
                    }

                    cur_wsp->Clear();
                    cur_wsp->pFsaAppl->pWSP=nullptr;

                    if (cur_wsp->pFsaAppl->pCVarFSA) {
                        if (cur_wsp->pFsaAppl->pCVarFSA->pCurLFsaAppl) {
                //	!! 2015.05.27  ����� �������� �������� � ���������� ����������
                            cur_wsp->pFsaAppl->pCVarFSA->pCurLFsaAppl = nullptr;
                        }
                    }
    /*
                    if (cur_wsp->pFsaAppl->pMainAutomaton->pCVarFSA) {
                        if (cur_wsp->pFsaAppl->pMainAutomaton->pCVarFSA->pCurLFsaAppl) {
                //	!! 2015.05.27  ����� �������� �������� � ���������� ����������
                            cur_wsp->pFsaAppl->pMainAutomaton->pCVarFSA->pCurLFsaAppl = nullptr;
                        }
                        if (cur_wsp->pFsaAppl->pMainAutomaton) {
                //	!! 2015.06.04  ��� ���������� �������� ����� ��������� � ������������ �������� �� ��������� �������
                            cur_wsp->pFsaAppl->pMainAutomaton->pNestedAutomaton = nullptr;
                        }
                    }
    */
                    pStackWsp->Delete(cur_wsp);
                    //		��������� WSP ?
                    if (static_cast<void*>(cur_task->w_fl) == &cur_task->w_fl ) {
                        TASK* del_tsk = cur_task;
    //*
                        if (cur_task->pFsaAppl->pLFsaHdr) {
    //					if (cur_task->pFsaAppl->bIfLFsaHdr) {
                            LFsaHdr var;
                            var.pLFsaAppl = cur_task->pFsaAppl;
    //                        int n = cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Size();
                            cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Clear(var);
    //                        n = cur_task->pNetFsa->pCArrayNetFsa->pSetLFsaHdr->Size();
    //						cur_task->pFsaAppl->bIfLFsaHdr = false;
                        }
    //*/
                        cur_task= cur_task->GetNextTask();
                        del_tsk->Clear();
                        pStackTsk->Delete(del_tsk);
    //					lNumberOfTasks--;						//2007/09/24	��������� ������� ����� �����
                    }
                    else {
                        // "����������� �����" �������� ������� �������� �������� ������, ��� ������ �����
                        // 1)������� � ��������� ������ ���������� �������� � 2) ������ �������� ����, ��� � ��� ������� �������� � ����
                        if (strRet=="XX") {
                            cur_task->w_bl->arc_b = nullptr;
    //						cur_task->w_bl->arc_t = cur_task->w_bl->arc_b; cur_task->w_bl->arc_b= 0;
                            if (cur_wsp->pFsaAppl) {
                                if (cur_wsp->pFsaAppl->bIfMoore)
                                    cur_task->pFsaAppl->MooreAction();		// ������� �� "������������" ��������� �������� ����� ������������� "�������� ����"
                            }
                        }
                        if (strRet=="00") {
    //                        int n =1;
    //						cur_task->w_bl->arc_b = nullptr;
    //						cur_task->w_bl->arc_t = cur_task->w_bl->arc_b; cur_task->w_bl->arc_b= 0;
                            cur_task->w_bl->arc_t = &cur_task->w_bl->arc_t->pNextState->ListArc.pRoot->FsaArc;
                        }
                        cur_task->w_bl->bCall=false;
                    }
                }
                else {
                    cur_task= cur_task->flink;
                }
            }
        }

}
long TNetFsa::GetNumberOfTasks(long *lActive)
{
    long nAllTask=0;
    long nActiveTask=0;
    TASK *cur_t = list_0task.flink;
    while (cur_t != &list_0task ) {
        if (!cur_t->pid->stop) {
            nAllTask++;
            if (cur_t->lSleep==cur_t->lCountSleep) {
                nActiveTask++;
            }
        }
        cur_t = cur_t->flink;
    }
    cur_t = list_1task.flink;
    while (cur_t != &list_1task ) {
        if (!cur_t->pid->stop) {
            nAllTask++;
            if (cur_t->lSleep==cur_t->lCountSleep) {
                nActiveTask++;
            }
        }
        cur_t = cur_t->flink;
    }
    cur_t = list_2task.flink;
    while (cur_t != &list_2task ) {
        if (!cur_t->pid->stop) {
            nAllTask++;
            if (cur_t->lSleep==cur_t->lCountSleep) {
                nActiveTask++;
            }
        }
        cur_t = cur_t->flink;
    }
    lNumberOfTasks = nAllTask;
    lNumberOfActiveTasks = nActiveTask;
    *lActive = nActiveTask;
    return nAllTask;
}
//===================================================================
//                                                          stop_task
//===================================================================
void TNetFsa::StopTask(TASK* task)
{
    if (!task->pid->stop) {
//		task->remque();
        task->pid->stop= 1;
//		task->insque (wait_task.blink);
//		task->pNetFsa->lNumberOfTasks--;
    }
}
//===================================================================
//                                                         start_task
//===================================================================
void TNetFsa::StartTask(TASK* task)
{
//    TASK *p_Nlist;
 if (task->pid->stop) {
//	 task->remque();
//    if (task->pri==0) p_Nlist= &list_0task;
//    if (task->pri==1) p_Nlist= &list_1task;
//    if (task->pri==2) p_Nlist= &list_2task;
//	task->insque(p_Nlist->blink);
    task->pid->stop= 0;
//	task->pNetFsa->lNumberOfTasks++;
 }
}

bool TNetFsa::IfStopTask(TASK* task) {
    if (!task)
        return false;
    return bool(task->pid->stop);
}

void TNetFsa::StopTask()
{
    if (!pCVarSetting) return;
    bStopAllTask=true;
}
//===================================================================
//                                                         start_task
//===================================================================
void TNetFsa::StartTask()
{
    if (!pCVarSetting)
        return;
//	bool bIfAnalist = pCVarSetting->nDegree==CVarSetting::cvarAnalyst;
//	if (bIfAnalist)
        bStopAllTask=false;
}
//===================================================================
//                                                            go_task
//===================================================================
void TNetFsa::go_task()
{
    mov_tsk(&stop_0task,&list_0task);
    mov_tsk(&stop_1task,&list_1task);
//    mov_tsk(&stop_2task,&list_2task);
}
//===================================================================
//                                                            mov_tsk
//===================================================================
// ����������� ������ �����
void TNetFsa::mov_tsk (TASK *st_tsk, TASK *lst_tsk)
{TASK *bs, *es, *et;
 TASK* cur;
 cur= st_tsk->flink;
 while (cur != st_tsk) {
     cur->pList=lst_tsk; cur= cur->flink;
    }
 if (st_tsk != st_tsk->flink) {
     bs= st_tsk->flink; es= st_tsk->blink; et= lst_tsk->blink;
     et->flink=bs; bs->blink=et; es->flink=lst_tsk; lst_tsk->blink=es;
     st_tsk->flink= st_tsk; st_tsk->blink= st_tsk;
//	 lNumberOfTasks++;
 }
}

bool TNetFsa::operator==(const TNetFsa& fsa) const
{
    return *SaveCountDispMain == *fsa.SaveCountDispMain;
}

bool TNetFsa::operator<(const TNetFsa& fsa) const
{
    return *SaveCountDispMain < *fsa.SaveCountDispMain;
}

bool TNetFsa::operator>(const TNetFsa& fsa) const
{
    return *SaveCountDispMain > *fsa.SaveCountDispMain;
}

int TNetFsa::GetRestWsp()
{
    return pStackWsp->GetRest();
}

int TNetFsa::GetRestTsk()
{
    return pStackTsk->GetRest();
}
void TNetFsa::ClearNumberOfTasks()
{
    lNumberOfTasks =0;
}

//===================================================================
//                                                        TGetPointer
//===================================================================
LFsaAppl* TNetFsa::TGetPointerFsa(string strName, int *pri)
{
    TASK *cur_task = list_0task.flink;
    while (cur_task != &list_0task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->nameFsa == strName) {
                *pri = 0;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_1task.flink;
    while (cur_task != &list_1task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->nameFsa == strName) {
                *pri = 1;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_2task.flink;
    while (cur_task != &list_2task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->nameFsa == strName) {
                *pri = 2;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    *pri = 777;
    return nullptr;
}

void TNetFsa::ResetTasks() {
// ������������� ���������� ����������
    CVar* nextVar= pTAppCore->IterAddressVar(true);
    while (nextVar !=nullptr) {
        string str = nextVar->strName;
        if (nextVar->bIfInit) {
            if (nextVar->unTypeVar == CVar::vtString) {
                nextVar->SetDataSrc(nullptr, nextVar->strInitValue, nullptr);
                nextVar->UpdateVariable();
            }
            else {
                string sss;
                if (nextVar->unTypeVar == CVar::vtFsastate) {
                    sss = nextVar->strng;
                }
                double d = stod(nextVar->strInitValue);
                nextVar->SetDataSrc(nullptr, d);
                nextVar->UpdateVariable();
                if (nextVar->unTypeVar == CVar::vtFsastate) {
                    nextVar->strng = sss;
                }
            }
        }
        nextVar= pTAppCore->IterAddressVar(false);
    }
//*
// ������������� ��������� ����������
    CIteratorVarFSA nextVarFsa= pTAppCore->pSetVarFSA->pArray->begin();
    for (int i=0; i<int(pTAppCore->pSetVarFSA->pArray->size()); i++) {
        // ����� �� ���������� ����������, � ������� ���� ��������� �� �������
        if (nextVarFsa->pLFsaAppl) {
            if (nextVarFsa->pLFsaAppl->pCVarFSA) {
                // ���� ����� "����" ��� ������ �� ��������� ������������
                if (nextVarFsa->pLFsaAppl->pCSetLocVar->pArray->size()) {
                    TIteratorLocVar TIteratorIVar = nextVarFsa->pLFsaAppl->pCSetLocVar->pArray->begin();
                    while (TIteratorIVar != nextVarFsa->pLFsaAppl->pCSetLocVar->pArray->end()) {
                        string str;
                        str = nextVarFsa->strName +"." + TIteratorIVar->strName;
                        if (TIteratorIVar->bIfInit) {
                            if (TIteratorIVar->unTypeVar == CVar::vtDouble ||
                                TIteratorIVar->unTypeVar == CVar::vtInteger ) {
                                double d = stod(TIteratorIVar->strInitValue);
                                TIteratorIVar->SetDataSrc(nullptr, d);
                                TIteratorIVar->UpdateVariable();
                            }
                        }
                        TIteratorIVar++;
                    }
                }
            }
        }
        nextVarFsa++;
    }
// ����� ���������
    TASK *cur_task = list_0task.flink;
    while (cur_task != &list_0task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            cur_task->pFsaAppl->FResetAppl();
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_1task.flink;
    while (cur_task != &list_1task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            cur_task->pFsaAppl->FResetAppl();
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_2task.flink;
    while (cur_task != &list_2task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            cur_task->pFsaAppl->FResetAppl();
        }
        cur_task = cur_task->flink;
    }

}

LFsaAppl* TNetFsa::TGetPointerProcess(string strName, int *pri)
{
    TASK *cur_task = list_0task.flink;
    while (cur_task != &list_0task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->pWSP->pTask->name == strName) {
                *pri = 0;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_1task.flink;
    while (cur_task != &list_1task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->pWSP->pTask->name == strName) {
                *pri = 1;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    cur_task = list_2task.flink;
    while (cur_task != &list_2task ) {
        if (cur_task->pFsaAppl&&!cur_task->bCancel) {
            if (cur_task->pFsaAppl->pWSP->pTask->name == strName) {
                *pri = 2;
                return cur_task->pFsaAppl;
            }
        }
        cur_task = cur_task->flink;
    }
    *pri = 777;
    return nullptr;
}

void TNetFsa::UpdateVariable()
{
// �������� ���������� ���������� ����������� ������������
    TIteratorIVar next= pCSetVar->pArray->begin();
//    int ns = 0;
//    if (strName == "InitFsaWorld") {
//        ns = pCSetVar->pArray->size();
//    }
    while (next!=pCSetVar->pArray->end()) {
        CVar *pv = *next;
//		��� [����������] ���������� �� ������������
//		if (pv->strName== "U") {
//			int n = 0;
//		}

// if (strName == pv->strNameNetFsa)     // �������� �� �����, �.�. ���������� � ������ ���������� ������������
// ����� 202409200045 - �� �����, �.�. ���������� ���������� ��� ���������� ���������� �������� ������������
            pv->UpdateVariable();
        next++;
    }
// �������� ��������� ���������� ���������
    CIteratorILFsaAppl nextL=ArrayILFsaAppl.begin();
    while (nextL!=ArrayILFsaAppl.end()) {
        string str = (*nextL)->FGetNameProcess();	// ��� ����������� �������� �������� ������������
//        (*nextL)->FUpdateVariable();				// ���������� ��������� ���������� ��������
        LFsaAppl *pNestedPrev = nullptr;
        int n=0;
        if (pNestedPrev) {
//            str = pNestedPrev->FGetState();
            n = pNestedPrev->FGetRange();
            if (n>0) {
                pNestedPrev->FUpdateVariable();
                // ���������� ���������� �������� �������� ������
                (*nextL)->FUpdateVariable();    // ��������� 06.07.2020 19:22
            }
            else {
                (*nextL)->FUpdateVariable();				// ���������� ��������� ���������� ��������
            }
        }
        else {
            (*nextL)->FUpdateVariable();				// ���������� ��������� ���������� ��������
        }
        nextL++;
    }
    next= pCSetVar->pArray->begin();
    while (next!=pCSetVar->pArray->end()) {
        CVar *pv = *next;
        string strName = pv->strName;
//        if (pv->unTypeVar == CVar::vtGraph1D || pv->unTypeVar == CVar::vtGraph2D) {
//        }
        next++;
    }
    nextL=ArrayILFsaAppl.begin();
    while (nextL!=ArrayILFsaAppl.end()) {

        string strFsa = (*nextL)->FGetNameFsa();
//        if (strFsa == "FTrends") {
//            (*nextL)->y4();
//        }
        nextL++;
    }
//    ((TAppProcesses*)pTAppCore)->pTAppDrv->pSetVarRead->;
}
// ��������/���������� ������ ��� ���������� ��������� ����������� ������������
bool TNetFsa::TCreationOfLinksForVariables()
{
    bool bRet=false;
    CIteratorILFsaAppl nextL=ArrayILFsaAppl.begin();
//    int n = ArrayILFsaAppl.size();
    while (nextL!=ArrayILFsaAppl.end()) {
        bRet |= (*nextL)->FCreationOfLinksForVariables();
        nextL++;
    }
    return bRet;
}

WSP* TNetFsa::GetPointerToCurWSP()
{
    return cur_wsp;
}

double TNetFsa::SetDeltaTime(double d) {
    double dSav = dDeltaTime;
    dCountDeltaTime		= 0;
    dDeltaTime = d;
    return dSav;
}

double TNetFsa::GetDeltaTime() { return dDeltaTime; }

void LFsaAppl::FUpdateVariable()
{
    TIteratorLocVar next= pCSetLocVar->pArray->begin();
    while (next!=pCSetLocVar->pArray->end()) {
        CVar* pVar = &(*next);
        pVar->UpdateVariable();
        next++;
    }
}
