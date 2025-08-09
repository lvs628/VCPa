// StackTsk.cpp: implementation of the CStackTsk class.
//
//////////////////////////////////////////////////////////////////////

#include "StackTsk.h"
#include "task.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStackTsk::CStackTsk(int len)
{
//	nRestOfMembers = nNumberTsk= 1000100;
//	nRestOfMembers = nNumberTsk= 5100;		//	������� �����
//	nRestOfMembers = nNumberTsk= 25000;		//	������������ ����������
//	nRestOfMembers = nNumberTsk= 2000000;	//	������������ ���������
	nRestOfMembers = nNumberTsk= len;		//	��� ������
	pArrayTsk = 0;
	pArrayTsk = new TASK[nNumberTsk];
	TASK* bl = pArrayTsk;
	for (int i=0; i<nNumberTsk; i++) {
		pArrayTsk[i].flink = 0;
		if (i)
			pArrayTsk[i].blink = bl;
		bl->flink = &pArrayTsk[i];
		bl = &pArrayTsk[i];
	}
	pBegin = pArrayTsk;
	pArrayTsk[0].blink = &pArrayTsk[nNumberTsk-1];
	pArrayTsk[nNumberTsk-1].flink = &pArrayTsk[0];

}

CStackTsk::~CStackTsk()
{
//	if (nRestOfMembers == nNumberTsk) {
//		if (pArrayTsk) delete[] pArrayTsk;
//	}
	if (pArrayTsk) delete[] pArrayTsk;
}

int CStackTsk::GetRest() { return nRestOfMembers; }
//	�������� ������� �� ������
//	������� ������ ������ ������� (�� ���� ��������� pBegin)
TASK* CStackTsk::New()
{
	if (nRestOfMembers) {
		TASK* pTopTASK;
		pTopTASK = pBegin;
		pBegin = pBegin->flink;
		pBegin->blink = pTopTASK->blink;
		nRestOfMembers--;
		return pTopTASK;
	}
	else {
		return 0;
	}

}
//	���������� ������� � ������
//	����������� ������ � ������ ������ (�� ���� ��������� pBegin)
void CStackTsk::Delete(TASK * pW)
{
	*pW = TASK();
	pW->flink = pBegin;
	pW->blink = pBegin->blink;
	pW->bHead = true;
	pBegin->blink = pW;
	pBegin = pW;
	nRestOfMembers++;
}
