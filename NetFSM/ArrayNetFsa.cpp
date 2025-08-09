#include "stdafx.h"
#include "ArrayNetFsa.h"
#include "netfsa.h"
#include "ArithmeticMean.h"
#include "TAppCore.h"

CArrayNetFsa::CArrayNetFsa(TAppCore *pCore)
{
    pTAppCore = pCore;
    pNetFsa=nullptr;
//    InitNetFsa();
    pSetLFsaHdr = new CSetLFsaHdr();
}

CArrayNetFsa::~CArrayNetFsa()
{
//    TPIteratorNetFsa PIteratorNetFsa;
    PIteratorNetFsa = PArrayNetFsa.begin();

    while (PIteratorNetFsa != PArrayNetFsa.end()) {
        TNetFsa* pNet = *PIteratorNetFsa++;
        string strName = pNet->strName;
        delete pNet;
        }

    if (pSetLFsaHdr) delete pSetLFsaHdr;
}

void CArrayNetFsa::ResetTasks() {
    pTAppCore->llVCPaSystemTime = 0;
//$    pTAppCore->tk0.restart();
//    TPIteratorNetFsa PIteratorNetFsa;
    PIteratorNetFsa = PArrayNetFsa.begin();

    while (PIteratorNetFsa != PArrayNetFsa.end()) {
        TNetFsa* pNet = *PIteratorNetFsa++;
        pNet->ResetTasks();
    }

}

// ������� ������-���������� �����, �������� �� � ������ "���������� ����"
// � ���������� ���������� ��������� �� ��������� ������
TNetFsa* CArrayNetFsa::GetNetFsa(string strName, string strConfig)
{
    TNetFsa* pNet;
    pNet = GetAdressNetFsa(strName);
    if (!pNet) {
        pNet = new TNetFsa(this, strName);
        PArrayNetFsa.push_back(pNet);
    }
    return pNet;
}
// ��������� � ����� �� ���������� ���������� ���� ������� ������ ���������� ����� ��
// ������� ����. ���� - 50 ������ (����� �������� lMaxCountDisp)
//static long lCountDisp=0;
//static long lCountStep=0;
//static long lMaxCountDisp=50;
//long lMaxCountDisp=1;
bool CArrayNetFsa::OnIdleFsa(long lCount)
{
/*    
    IIteratorNetFsa = IArrayNetFsa.begin();

    while (IIteratorNetFsa != IArrayNetFsa.end()) {
        TNetFsa* pNet = *IIteratorNetFsa++;
        pNet->PerformanceQuantum();
    }
*/        
    return true;
}
// �������������� ������ ���������� ����, �������� ����� ���� �����.
bool CArrayNetFsa::InitNetFsa()
{
    if (!pNetFsa) {
        pNetFsa=nullptr;
        pNetFsa= GetNetFsa("InitFsaWorld", "");
        return true;
    }
    return false;
}
// ����� ������������ ������ (str)
TNetFsa* CArrayNetFsa::GetAdressNetFsa(string str)
{
/*
    int n = PArrayNetFsa.size();
    if (n) {
        for (int i=0; i<n; i++) {
            TNetFsa* pNet = PIteratorNetFsa[i];
            if (pNet) {
                if(pNet->strName == str)
                    return pNet;
            }
        }
        return nullptr;
    }
    return nullptr;
*/
//*
    PIteratorNetFsa = PArrayNetFsa.begin();

    while (PIteratorNetFsa != PArrayNetFsa.end()) {
        TNetFsa* pNet = *PIteratorNetFsa++;
        if (pNet->strName==str)
            return pNet;
    }
    return nullptr;
//*/
}
// ����� ����������� �������� ������ (str)
LFsaAppl* CArrayNetFsa::GetAdressFsaAppl(string str, int *pr, TNetFsa **pN)
{
    PIteratorNetFsa = PArrayNetFsa.begin();
    LFsaAppl *pAppl;

    while (PIteratorNetFsa != PArrayNetFsa.end()) {
        TNetFsa* pNet = *PIteratorNetFsa++;
        int pri;
        pAppl = pNet->TGetPointerProcess(str, &pri);
        if (pAppl) {
            if (pr) *pr = pri;
            if (pN) *pN = pNet;
            return pAppl;
        }
    }
    return nullptr;
}

long CArrayNetFsa::GetNumberOfTasks(long *lAct)
{
    PIteratorNetFsa = PArrayNetFsa.begin();
    lNumberOfTasks = 0;
    lNumberOfActiveTasks = 0;
    while (PIteratorNetFsa != PArrayNetFsa.end()) {
        TNetFsa* pNet = *PIteratorNetFsa++;
        long l;
        lNumberOfTasks += pNet->GetNumberOfTasks(&l);
        lNumberOfActiveTasks +=l;
    }
    *lAct = lNumberOfActiveTasks;
    return lNumberOfTasks;
}
