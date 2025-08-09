#ifndef CSETLOCVAR_H
#define CSETLOCVAR_H

#include "clocvar.h"

class CSetLocVar
{
public:
    CSetLocVar(void);
    ~CSetLocVar(void);
    void CreateArrayVariables(LFsaAppl *pL, string& pstrInput);
    string SaveListVariables(string& pstrOutput);
    string CreateStringVariables();
    bool Add(CLocVar &var, bool bSave = true);
    bool Replace(CLocVar &var, bool bSave = true);
    bool Delete(CLocVar &var, bool bSave = true);
    CLocVar* GetAddressVar(string nam);
    TArrayLocVar *pArray;
    LFsaAppl	*pLFsaAppl;
};

#endif // CSETLOCVAR_H
