#ifndef __CVARSETTING_H
#define __CVARSETTING_H

#include <string>
#include <list>
using namespace std;

class TNetFsa;
class CVar;
class TAppCore;
class CVarSetting
{
public:
    enum {cvarAdmin, cvarAnalyst, cvarExpert, cvarUser, cvarBeginner, cvarDemo, cvarPress831=831};
	void SetConfig(bool b);
	bool GetConfig();
	CVarSetting(void);
	CVarSetting(const CVarSetting& var);
	CVarSetting(TAppCore *pPr);
	CVarSetting(TAppCore *pPr, string &nam);
    ~CVarSetting(void) {};
	virtual bool IfEqu(CVarSetting& var);
	void MoveToVar(string &strS);
	int operator==(const CVarSetting &var) const;
	int operator<(const CVarSetting &var) const;

public:
    string	strName;				// Имя переменной
    string	strNameNetFsa;			// имя автоматного пространства
    int		bIfSynchronousOperation;// =1, ���� ������ ���������� ����� ����������� �������
    double	dDeltaTime;				// ������������ � ������������ "��������" ����������� ����� �������
	bool	bIfStopAllTasks;		// ������� �������� ���� ����� "����������� ������������"
// �������� ������������
    bool	bIfShadowVariable;		// "�������" ����� ������ ������
// ��������
    double	dTimeTick;				// �������� ������������ ����������� �����
// ��� ���?
    string	strNetFsaDefault;		// ��� ���������� ������������ �� ���������

    TAppCore *pTAppCore;			// ��������� �� �������� ������
    TNetFsa	*pTNetFsa;				//	����� ������������
    int     idTimer{0};
};
typedef list<CVarSetting> TArrayCVarSetting;
typedef list<CVarSetting>::iterator TIteratorCVarSetting;
#endif //__CVARPRMPROC_H
