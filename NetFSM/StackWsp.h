// StackWsp.h: interface for the CStackWsp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACKWSP_H)
#define AFX_STACKWSP_H

class WSP;
class CStackWsp
{
public:
	int GetRest();
	void Delete(WSP* pW);
	WSP* New();
	CStackWsp(int len);
	virtual ~CStackWsp();

private:
	WSP* pArrayWSP;
	WSP* pEnd;
	WSP* pBegin;
	int nNumberWsp;
	int nRestOfMembers;
};

#endif // !defined(AFX_STACKWSP_H)
