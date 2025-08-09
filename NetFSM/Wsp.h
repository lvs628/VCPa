#ifndef wsp_h
#define wsp_h

#include <string>
using namespace std;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             WSP
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TASK;
class LFsaArc;
class LFsaAppl;
typedef int(LFsaAppl::*FncClassX)();
typedef void(LFsaAppl::*FncClassY)();
class WSP {
 public:
 	WSP *flink, *blink;
	bool	bHead;
	TASK* pTask;	 // ��������� ������ ��� �������� WSP
	LFsaAppl *pFsaAppl; // ����� �������, ���������� WSP
	LFsaArc *adt; 
    FncClassX *adx; FncClassY *ady;
	LFsaArc *arc_b; LFsaArc *arc_t;
	string name;
   unsigned long mask;
   unsigned long m_x;
   unsigned long baza;
   bool	bCall;
   int	nNumCall;	//	������� ����������� �������� (0,1, ...)
public:
	WSP();
	~WSP();
	void Clear();
	WSP* remque();
	void insque (WSP*);
	void x();
	void y();
};

#endif
