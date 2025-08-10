#ifndef CVARFSA_H
#define CVARFSA_H

#include <string>
#include <list>
using namespace std;

class LFsaAppl;
class CVarFsaNew;
class CVarFsaObject;
class TAppCore;
class CVarFSA
{
public:
    //***************************
    string		strName;				// имя переменной-процесса
    string		strNameFsa;				// имя автомата
    string		strNameFsaProcess;		// модификатор процесса - суффикс процесса
    int			nPriority;				// приоритет задачи
    bool		bStop;					// признак остановки процесса
    long		lSleep;					// время засыпания
    bool		bViewFSA;				// признак отображения текущей информации о процессе
    string		strNameNetFsa;			// имя пространства автоматных процессов
    bool		bIfLoad;				// загрузить автомат в пространство
    bool		bIfCreateProcess;		// создать автоматный процесс
    string		strListLocalVar;		// список локальных переменных
    //***************************
    bool		bIfCreate;                      // признак создания автомата методом Create();
    LFsaAppl	*pLFsaAppl{nullptr};			// указатель на заголовок класса автомата
    LFsaAppl	*pCurLFsaAppl{nullptr};			// указатель на текущий заголовок класса автомата
//
//
    CVarFsaObject *itrCVarFsaObject;	// указатель на объект, который будет иметь связь с заголовком
    bool		bRemoteVariable;		// признак удаленной переменной
public:
    void SetPtrToSrcClass(LFsaAppl *pL);
    bool CreateProcessFSA();
    bool	LoadFsa(LFsaAppl *pLFsa);
    LFsaAppl* GetAddress();
    void CreateLink();
    CVarFSA(void);
    CVarFSA(TAppCore* pInfo, string& nam);
    CVarFSA(const CVarFSA& var);
    virtual ~CVarFSA(void);
    string GetNameProcess();
    void MoveToVar(string& Str);
    virtual bool IfEqu(CVarFSA& var);
    int operator==(const CVarFSA &var) const;
    int operator<(const CVarFSA &var) const;
    CVarFSA& operator=(const CVarFSA& var);
//    CSetVDialog *pCSetVDialog;
protected:
    TAppCore*	pTAppCore;
    friend ostream& operator<<(ostream& os, CVarFSA &dat);
    LFsaAppl	*pLFsaSrcClass{nullptr};		// указатель на заголовок класса автомата
};
typedef list<CVarFSA> CArrayVarFSA;
typedef list<CVarFSA>::iterator CIteratorVarFSA;

#endif // CVARFSA_H
