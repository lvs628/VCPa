#ifndef CSetVarPrmProc_H
#define CSetVarPrmProc_H
#include "VarPrmProc.h"

class _FSAVARCLASS CSetVarPrmProc
{
public:
	void SetSaveSet(bool b);
	bool	IfSave() {return bSaveSet;}
	CSetVarPrmProc(TAppCore *pInfo, string strNam);
	~CSetVarPrmProc(void);
	bool Add(CVarPrmProc &var);
	bool Replace(CVarPrmProc &var);
	bool Delete(CVarPrmProc &var);
	CVarPrmProc* GetAddressVar(string nam);
	TArrayVarPrmProc *pArray;

	TAppCore *pTAppCore;
	bool	bSaveSet;		//	������� ������������� ���������� ��������� ����������
	string	strPath;		//	���� � �������� ��������
	string 	strFileName;	//	��� �����
	int nIndexVar;			// ������ �������� �������� ��� ���� �����������
};

#endif // CSetVarPrmProc_H
