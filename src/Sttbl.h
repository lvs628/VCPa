#ifndef __STTBL
#define __STTBL

#include <string.h>
#include "Deffsa.h"
#include "task.h"
#include "larc.h"
//*******************************************************************
// STTBL.HPP
// State Table - (S.304 ���.455) ������� ���������
// ����������� ������� ��� �������� ������� ���������
//		 Sequential Machine - �������������������� ������
//			���
//		 Sequencer - ����������� �������
// ������:
//    1995 �. 6 ������� 1995 �.
//            9 ������� - ������������ ������� ��������� � ����������
//			  ��������� ������� ��������
//*******************************************************************
//				����������� �������� ������� ����
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                         LJumpState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LJumpState {
 public:
    LJumpState(LArc *pArc);
	~LJumpState();
 private:
	int ifJump(unsigned long);
	int GetMaskX();
	int GetMaskY();

 public:
    LArc *pArcSource{nullptr};
};

//	���� � ������� �������� � ���������� ��������� ������,
//	������ � ��������� ����������, ������ ��������
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            LFsaArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LAtomState; class LAtomArc;
//				������� ������� �����	�
class LFsaArc:public LJumpState {
 public:
	LFsaArc();
	LFsaArc(LArc&);
	~LFsaArc();
 public:
	LAtomState  *pNextState{nullptr};	//  ��������� ��������� �������� ������
	LAtomArc  *pNextAtomArc{nullptr};	//  ����� ����� ������ ���� ���������
    const char* szSt1{nullptr};				//	������� ���������
    const char* szSt2{nullptr};				//	��������� ���������
    const char* szPredicate{nullptr};			//	���������
    const char* szAction{nullptr};				//	���������
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            LAtomArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	       �������(�������/����/����) ������ ��������� ���������
class LAtomArc {
 public:
	LAtomArc(LArc& Arc);
	LAtomArc& Insert(LArc& Arc);
	~LAtomArc();

 public:
	LFsaArc FsaArc;
 private:
	LAtomArc *pNext{nullptr};
    friend class TNetFsa;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             LListArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				������ ��������� (���) ���������
class LListArc {
 public:
	LListArc();
	~LListArc();
	LAtomArc& Insert(LArc&);
	LAtomArc* pRoot{nullptr};
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            LAtomState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//				�������(����) ������ ���������
class LAtomState {
 public:
    LAtomState(const char*);
	~LAtomState();
	LAtomArc& Insert(LArc&);
    LAtomState& Insert(const char*);
 private:
    int ifState(const char*);
 public:
	LListArc ListArc;	// ������ ��������� ��������� ������
	char* szName{nullptr};        // ��� ���������
 private:
	LAtomState* pNext{nullptr};        // ��������� ������� ������ ��������� ������
	LAtomState* pLast{nullptr};	// ���������� ������� ������ ��������� ������
    friend class LFsaAppl;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     LListState
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 				������ ��������� ������
class LAtomState;
class _FSACLASS LListState
{
 public:
	LListState(LArc*);
	LListState();
	~LListState();
	void Create(LArc*);
 private:
	void Insert(LArc&);
    LAtomState& Insert(const char*);
	void ReadListArc(LArc*);
 public:
	LAtomState* pRoot{nullptr};
};

#endif
