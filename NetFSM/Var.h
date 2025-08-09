// Var.h: interface for the CVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VAR_H)
#define AFX_VAR_H

#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;
#include "DefineTypes.h"

class TAppCore;
class LFsaAppl;
class TNetFsa;
class CVar
{
public:
    // ������������, ������������, ��������� (�� �������)
    enum {cvarNone, cvarAbstract, cvarRead, cvarWrite, cvarConstant, cvarEvent};
    enum type {vtUnknown, vtBool, vtInteger, vtDouble, vtString, vtGraph1D, vtGraph2D, vtFsa, vtFsastate, vtArrayDouble};

/////////////////////////////////////////////////////////////////////
    string		strName;			//	��� ����������
    string		strComment;			// ����������� � ����������
    int			m_nCountUse;		// ������� �������������
    string		strNameNetFsa;		// ��� ����������� ������������
//
    string		strng;
    bool		bLocking;
    int			nType;				// ��� ����������
    bool		bUsed;				// used - ��������������, ������� ����, ��� ���������� ���� ������������ ��� ����-����
    bool		bIfLocal;			// ������� ���������� ���������� ���� (�� ��������� = false, �.�. ����������)
    bool		bSerial;			// ��� ������ - ����������������
    bool		bOnlyChanges;		// ���������� ������ ���������
    bool		bConstant;			// ���������
    bool		bEvent;             // ���������
    int         nError;             // ������ ��� ������ � ����������
//////////////////////////////////////////////////////////////////////
    bool	bIfInit;				// ���������������� ��� ��������
    string	strInitValue;			// �������� ������������� � ��������� �����
    unsigned int unTypeVar;
    TAppCore	*pTAppCore;
    LFsaAppl	*pLFsaType{nullptr};			// ��������� �� �������, ��������� �������
    LFsaAppl	*pLFsaOwner{nullptr};		// �������� ������� ��� ���������� ����������������� ����
    LFsaAppl	*pLFsaAppl{nullptr};			// ��������� �� �������, ������� �������� ������ �� ��������� ������ (�� ������� �����!)
                                    // ��������! - � ����� ����� - ���������� (� ������ UpdateVariable)
    TNetFsa		*pTNetFsa;			// ��������� �� "���������� ������������", � �������� "���������" ����������

    CVar();
    CVar(string strNm, string strCm);
    CVar(const CVar& var);
    virtual		~CVar();
//
    bool IfLocking(LFsaAppl *pFOwner, bool *bLoc);					//	������� ��������� ���������� ����������
    bool SetLocking(bool bSet, LFsaAppl *pOwner);		//	���������/����� ���������� ������������ ���������
    operator double();
    void CreateLink();
    void UpdateVariable();
    int	GetType() {return nType; }
    double InitVariable(double d);
    string InitVariable(string d);
//
    double SetData(LFsaAppl *pLFA, double d);			// ������� ������ ������
    double SetDataSrc(LFsaAppl *pLFA, double d, LFsaAppl *pLWriter = nullptr);		// ������, �����, ��� �� �����
    double GetDataSrc(LFsaAppl *pLFA = nullptr);
//
    string SetDataSrc(LFsaAppl *pLFA, string strS, LFsaAppl *pLWriter);		// ������, �����, ��� �� �����
    string strGetDataSrc(LFsaAppl *pLFA = nullptr);
    double* GetArrayDataSrc();
//
    bool operator==(const CVar &var) const;
    bool operator<(const CVar &var) const;
    bool operator!=(const CVar &var) const;
    bool operator>(const CVar &var) const;
    CVar& operator=(const CVar& var);
//
    virtual void MoveToVar(string &strS);
    virtual bool IfEqu(CVar& var);
protected:
    double		dDataSrc;			// данные от/к драйвера , в чистом виде
    double		*pArraydDataSrc;	// данные (массив) от/к драйвера , в чистом виде
private:
    double		dShadowDataSrc;		// данные от/к драйвера , в чистом виде
    double		*pArraydShadowDataSrc;		// данные(массив) от/к драйвера , в чистом виде
    string		strShadowData;
    bool		bIfCopyFromShadow;		// признак выполнения копироваяния из теневой памяти
    bool		bIfSetNewData;			// признак установки нового значения данных
    bool		bIfReadEvent;		// признак чтения события
    int			nAcntWriters;
    string		strErr;
    friend class CSetLocVar;

};
typedef list<CVar> TArrayVar;
typedef list<CVar>::iterator TIteratorVar;
typedef list<CVar*> TArrayIVar;
typedef list<CVar*>::iterator TIteratorIVar;

#endif // !defined(AFX_VAR_H)
