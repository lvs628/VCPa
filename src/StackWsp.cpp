// StackWsp.cpp: implementation of the CStackWsp class.
//
//////////////////////////////////////////////////////////////////////

#include "StackWsp.h"
#include "Wsp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStackWsp::CStackWsp(int len)
{
//	nRestOfMembers = nNumberWsp= 1000100;
//	nRestOfMembers = nNumberWsp= 5100;		//	������� �����
//	nRestOfMembers = nNumberWsp= 25000;		//	������������ ����������
//	nRestOfMembers = nNumberWsp= 2000000;	//	������������ ���������
	nRestOfMembers = nNumberWsp= len;		//	��� ������
    pArrayWSP = nullptr;
//    pArrayWSP = new WSP[static_cast<unsigned int>(nNumberWsp)];
    pArrayWSP = new WSP[nNumberWsp];
	WSP* bl = pArrayWSP;
	for (int i=0; i<nNumberWsp; i++) {
        pArrayWSP[i].flink = nullptr;
		if (i)
			pArrayWSP[i].blink = bl;
		bl->flink = &pArrayWSP[i];
		bl = &pArrayWSP[i];
	}
	pBegin = pArrayWSP;
	pArrayWSP[0].blink = &pArrayWSP[nNumberWsp-1];
	pArrayWSP[nNumberWsp-1].flink = &pArrayWSP[0];

}

CStackWsp::~CStackWsp()
{
//	if (nRestOfMembers == nNumberWsp) {
//		if (pArrayWSP) delete[] pArrayWSP;
//	}
	if (pArrayWSP) delete[] pArrayWSP;

}

int CStackWsp::GetRest() { return nRestOfMembers; }
//	�������� ������� �� ������
//	������� ������ ������ ������� (�� ���� ��������� pBegin)
WSP* CStackWsp::New()
{
	if (nRestOfMembers) {
		WSP* pTopWsp;
		pTopWsp = pBegin;
		pBegin = pBegin->flink;
		pBegin->blink = pTopWsp->blink;
		nRestOfMembers--;
		return pTopWsp;
	}
	else {
        return nullptr;
	}

}
//	���������� ������� � ������
//	����������� ������ � ������ ������ (�� ���� ��������� pBegin)
void CStackWsp::Delete(WSP * pW)
{
	*pW = WSP();
	pW->flink = pBegin;
	pW->blink = pBegin->blink;
	pW->bHead = true;
	pBegin->blink = pW;
	pBegin = pW;
	nRestOfMembers++;
}
