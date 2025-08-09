// StackTsk.h: interface for the CStackTsk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKTSK_H)
#define AFX_STACKTSK_H

#include "Deffsa.h"

class TASK;
class CStackTsk
{
public:
	int GetRest();
	void Delete(TASK* pT);
	TASK* New();
	CStackTsk(int len);
	virtual ~CStackTsk();

private:
	TASK* pArrayTsk;
	TASK* pEnd;
	TASK* pBegin;
	int nNumberTsk;
	int nRestOfMembers;		//	���������� ��������� ���������
};

#endif // !defined(AFX_STACKTSK_H)
