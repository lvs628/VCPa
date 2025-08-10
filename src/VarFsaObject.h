#ifndef CVARFSAOBJECT_H
#define CVARFSAOBJECT_H

#include "LFsaHdr.h"

class CVarFSA;
class CVarFsaObject
{
public:
	LFsaHdr* pLFsaHdr;					// ��������� �� �������� ������
	bool	bIfWnd;						// �������, ���� ������ - ���� Windows
	CVarFSA	*pCVarFSA;					// ��������� �� ����������-�������
	CVarFsaObject(void);
	CVarFsaObject(string name, LFsaHdr* pAddr, bool bW, CVarFSA *pVF);
	CVarFsaObject(const CVarFsaObject& var);
	~CVarFsaObject(void);
	LFsaAppl* GetAddress() {
		if (pLFsaHdr)
			return pLFsaHdr->pLFsaAppl; 
		else return NULL;
	}
	LFsaHdr* GetHdr() { return pLFsaHdr;	}
	LFsaHdr** GetHdrHdr() { return &pLFsaHdr;	}
	void SetAddress(LFsaHdr* pAddr);
	bool operator==(const CVarFsaObject &var)  const;
	bool operator<(const CVarFsaObject& var)  const;
	bool operator!=(const CVarFsaObject &var)  const;
	bool operator>(const CVarFsaObject& var)  const;
	string GetName() {	return strName; }
	void SetName(string str) { strName = str; }
private :
	string strName;									// ��� ����������
};
typedef list<CVarFsaObject> TArrayVarFsaObject;
typedef list<CVarFsaObject>::iterator TItrVarFsaObject;
typedef list<CVarFsaObject>::pointer TPointerVarFsaObject;

#endif // __CVARFSAOBJECT_H
