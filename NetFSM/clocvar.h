#ifndef CLOCVAR_H
#define CLOCVAR_H

#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;
#include "Var.h"

class CLocVar: public CVar
{
//*
public:
    CLocVar(LFsaAppl* pF, string &nam);
    CLocVar(const CLocVar& var);
    CLocVar(void);
    ~CLocVar(void);
//////////////////////////////////////////////////////////////////////
    operator double();
    void CreateLink();
//
    void UpdateVariable();
    double SetDataSrc(LFsaAppl *pLFA, double d, LFsaAppl *pWr = nullptr);		// жесткая запись данных
    string SetDataSrc(LFsaAppl *pLFA, string strS, LFsaAppl *pWr);		// всегда, кроме, как из файла
    virtual void MoveToVar(string &strS);
    virtual bool IfEqu(CLocVar& var);
};
ostream& operator<<(ostream& os, CLocVar &dat);
istream& operator>>(istream& is, CLocVar &dat);
typedef list<CLocVar> TArrayLocVar;
typedef list<CLocVar>::iterator TIteratorLocVar;
typedef list<CLocVar*> TArrayILocVar;
typedef list<CLocVar*>::iterator TIteratorILocVar;

#endif // CLOCVAR_H
