// SetVar.h: interface for the CSetVar class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SETVAR)
#define AFX_SETVAR

#include <string>
#include <list>
using namespace std;
//#include "TAppCore.h"

class CSetVar ;
typedef void(CSetVar::*pFnc)();

class TAppCore;
class CSetVar
{
public:
	string strName;
	CSetVar();
	CSetVar(TAppCore *pCore, string strNam);
	virtual ~CSetVar();
	string GetFileName() {return strFileName;}
	string GetPath() {return strPath;}
	void SetFileName(string& File) {strFileName=File;}
	void SetPath(string Path) {strPath=Path;}
	bool	IfSave() {return bSaveSet;}
	virtual void SetSaveSet(bool b);

	int nIndexVar;			// ������ �������� �������� ��� ���� �����������
	TAppCore *pTAppCore;
    bool    bIfAdd{false};  // ���� ���������� � ������

	virtual void  SaveDat();
	bool operator==(const CSetVar &var) const;
	bool operator<(const CSetVar &var) const;
	bool operator!=(const CSetVar &var) const;
	bool operator>(const CSetVar &var) const;

protected:
	string 	strFileName;	//	��� �����
	string	strPath;		//	���� � �������� ��������
    bool	bSaveSet{false};		//	������� ������������� ���������� ��������� ����������
//	pFnc	pFuncSave;		// ������ �� ����� ���������� ������ (������ ���������� ������� ��� CSetVar)

};
typedef list<CSetVar*> TArrayISetVar;
typedef list<CSetVar*>::iterator TIteratorISetVar;
#endif // !defined(AFX_SETVAR)
