#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <string>
using namespace std;
#include "VarFsaObject.h"


class TAppCore;
class CSetVarFsaObject
{
public:
	CSetVarFsaObject(TAppCore *pInfo);
	~CSetVarFsaObject(void);

	int Size() { return ArrayVarFsaObject.size(); }
	void Add(string nam, LFsaAppl *pFsa, bool bW);
	void CreateLink();
	CVarFsaObject* GetAddressVar(string nam);
	bool Erase(string nam);
	TArrayVarFsaObject	ArrayVarFsaObject;// ������ �������� ��������
private:
	TAppCore*	pInfoAppl;
};
