//-------------------------------------------------------------------
// MFSTTBL.CPP
//-------------------------------------------------------------------
#include <stdlib.h>
#include "larc.h"
#include "Sttbl.h"
#include <stdio.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LArc::LArc() { }

LArc::LArc(const char* ST1, const char* ST2, const char* MX, const char* MY)
{
unsigned long BitN[]= {
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 
	0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800,
	0x00001000, 0x00002000, 0x00004000, 0x00008000,

	0x00010000, 0x00020000, 0x00040000, 0x00080000, 
	0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,
};
	szSt1= ST1; szSt2= ST2;
	szMX = MX; szMY = MY;
    const char *nextX= MX;
	nextX=strchr(nextX, 'E');
	if (nextX) {
		ulMx = 0;
		ulMx |=BitN[31]; ulRx |=BitN[31];
	}
	else {
		nextX= MX; 
		nextX=strchr(nextX, 'x');
		while (nextX) { 
			int i= atoi(nextX+1);
			if (i>0&&i<=31) {
				i--;
				ulMx |=BitN[i]; ulRx |=BitN[i];
                if (nextX != MX) {
                    if (*(nextX-1)=='^')
                        ulRx &=~BitN[i];
                }
			}
			nextX++; nextX=strchr(nextX, 'x');
		}
	}
	nextX= MY; nextX=strchr(nextX, 'y');
	while (nextX) {
		int i= atoi(nextX+1);
		if (i>0&&i<=32) {
			i--; ulMy |=BitN[i]; 
		}
		nextX++; nextX=strchr(nextX, 'y');
	}
//    printf("LArc: %s %s %s %s\n", ST1, ST2, MX, MY);
//    printf("LArc: %s %s %o %o %o\n", ST1, ST2, ulMx, ulRx, ulMy);
}
LArc::~LArc()
{}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LJumpState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LJumpState::LJumpState(LArc *pArc)
{
    pArcSource = pArc;
}

int LJumpState::ifJump(unsigned long ulKey) 
{
    return ((ulKey&pArcSource->ulMx)== pArcSource->ulRx);
}

int LJumpState::GetMaskX() 
{
    return(int(pArcSource->ulMx));
}

int LJumpState::GetMaskY() 
{
    return(int(pArcSource->ulMy));
}

LJumpState::~LJumpState()
{}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LFsaArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LFsaArc::LFsaArc()
    :LJumpState(nullptr)
{
    pNextAtomArc=nullptr; pNextState=nullptr;
    szSt1 = nullptr;
    szSt2 = nullptr;
    szPredicate = nullptr;
    szAction = nullptr;
}

LFsaArc::LFsaArc(LArc& ARC)
    :LJumpState(&ARC)
{
    pNextAtomArc=nullptr; pNextState=nullptr;
	szSt1 = ARC.szSt1;
	szSt2 = ARC.szSt2;
	szPredicate = ARC.szMX;
	szAction = ARC.szMY;
}

LFsaArc::~LFsaArc()	
{}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LAtomArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline LAtomArc::LAtomArc(LArc& Arc)
{
	FsaArc = LFsaArc(Arc); 
    FsaArc.pNextAtomArc=nullptr; pNext= nullptr;
}

LAtomArc::~LAtomArc()
{
	if (pNext)	delete pNext; 
}
//===================================================================
//                                               Insert
//===================================================================
LAtomArc& LAtomArc::Insert(LArc& Arc)
{
	if (pNext) 
		return(pNext->Insert(Arc));
	else { pNext = new LAtomArc(Arc);
		FsaArc.pNextAtomArc= pNext;
		return *pNext;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LListArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LListArc::LListArc() 
{
    pRoot=nullptr;
}

LListArc::~LListArc()
{ 
	if (pRoot)	
		delete pRoot; 
}
//===================================================================
//                                               Insert
//===================================================================
LAtomArc& LListArc::
Insert(LArc& Arc)
{
	if (pRoot) 
		return pRoot->Insert(Arc);
	else {
		pRoot= new LAtomArc(Arc);
		return *pRoot;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                 LAtomState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LAtomState::LAtomState(const char* szNameState)
{
	szName = new char[strlen(szNameState)+1]; 
//	strcpy_s(szName, strlen(szNameState), szNameState);
	strcpy(szName, szNameState);
    pLast=pNext=nullptr;
}

LAtomState::~LAtomState()
{
	if (szName) 	
		delete[] szName;
	if (pNext) 	
		delete pNext;
}
//===================================================================
//                                               Insert
//===================================================================
LAtomState& LAtomState::Insert(const char* szNameState)
{
	LAtomState* pHead=nullptr;
	pHead= this;
	while (pHead->pLast) 
		pHead= pHead->pLast;	// � ������ ������
	while (pHead->pNext&&!pHead->ifState(szNameState))
		pHead= pHead->pNext;			// ����� ���������
	if (!pHead->pNext&&!pHead->ifState(szNameState)) {
		pHead->pNext = new LAtomState(szNameState);
		pHead->pNext->pLast = pHead;
		return *pHead->pNext;
	}
	else 
		return *pHead;
}
//===================================================================
//                                               ifState
//===================================================================
int LAtomState::ifState(const char* St)
{
	return !strcmp(szName,St);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                      LListState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LListState::LListState(LArc* aT) 
{ 
	ReadListArc(aT);
}

LListState::LListState() 
{ 
    pRoot=nullptr;
}

LListState::~LListState()
{ 
	if (pRoot) 
		delete pRoot; 
}
//===================================================================
//                                               Create
//===================================================================
void LListState::Create(LArc* aT) 
{ 
	ReadListArc(aT);
}
//===================================================================
//                                               Insert
//===================================================================
void LListState::Insert(LArc& Arc)
{
	LAtomState* CurState= &Insert(Arc.szSt1);
	LAtomArc* CurArc = &CurState->ListArc.Insert(Arc);
    if (strcmp(Arc.szSt2,"00")) {
//    if (string(Arc.szSt2) == "00") {
        LAtomState* NextState = &Insert(Arc.szSt2);
		CurArc->FsaArc.pNextState = NextState;
	}
}
//===================================================================
//                                               Insert
//===================================================================
LAtomState& LListState::Insert(const char* szNameState)
{	
	if (!pRoot) {
		pRoot = new LAtomState(szNameState);   // ������������� �
		return *pRoot;			// ������� ������ ���������
	}
	else 
		return pRoot->Insert(szNameState);
}
//===================================================================
//                                               ReadListArc
//===================================================================
void LListState::ReadListArc(LArc* aArc)
{
	int i= 0; LArc* Arc; Arc= &aArc[i];
	while (Arc->szSt1) {
		Insert(*Arc); 
		i++; 
		Arc = &aArc[i];
	}
}
