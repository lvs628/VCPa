// решить прблему- строки 230, 258
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "csetlocvar.h"

#include <algorithm>		// sort
#include "LConvStr.h"
#include <strstream>
#include "lfsaappl.h"
#include "VarFSA.h"
#include "TAppCore.h"
#include "SetVarFSA.h"
#include "clocvar.h"
#include "ArrayNetFsa.h"
#include <cstdlib>

CSetLocVar::CSetLocVar(void)
//	:CSetVar()
{
    pArray = nullptr;
    pArray = new TArrayLocVar();
    pLFsaAppl = nullptr;
}


CSetLocVar::~CSetLocVar(void)
{
 if (pArray)
     if (pArray->size() != 0)
         pArray->erase(pArray->begin(), pArray->end());
 delete pArray;
}

bool CSetLocVar::Add(CLocVar &var, bool bSave)
{
    if (var.pLFsaType->pCVarFSA) {
        TIteratorLocVar next=find(pArray->begin(), pArray->end(), var);
        if (next==pArray->end()) {
            pArray->push_back(var);
            var.pLFsaType->pCVarFSA->strListLocalVar = CreateStringVariables();
            var.pLFsaType->pTAppCore->pSetVarFSA->SetSaveSet(bSave);
            var.pLFsaAppl = var.pLFsaType; var.bIfInit = true;
            var.pLFsaAppl->pTAppCore->nSizeLocVars++;
            return true;
        }
        else {
            return false;
        }
    }
    else {
// нет автоматной переменной для процесса
// скорее всего, процесс создан программно,
// а локальные переменные для вложенных или программно созданных объектов [пока (на 16.10.2016)] не сохраняются)
        TIteratorLocVar next=find(pArray->begin(), pArray->end(), var);
        if (next==pArray->end()) {
            pArray->push_back(var);
            var.pLFsaAppl = var.pLFsaType;
            var.bIfInit = true;
            return true;
        }
//        int n = 0;
        return false;
    }

}

bool CSetLocVar::Replace(CLocVar &var, bool bSave)
{
    TIteratorLocVar next=find(pArray->begin(), pArray->end(), var);
    if (next!=pArray->end()) {
        if (!next->IfEqu(var) || bSave) {
            *next = var;
            var.pLFsaType->pCVarFSA->strListLocalVar = CreateStringVariables();
            var.pLFsaType->pTAppCore->pSetVarFSA->SetSaveSet(bSave);
            return true;
        }
        return false;
    }
    else return false;
}

bool CSetLocVar::Delete(CLocVar &var, bool bSave)
{
//    LFsaAppl *pL = var.pLFsaAppl;
    TIteratorLocVar next=find(pArray->begin(), pArray->end(), var);
    if (next!=pArray->end()) {
        pArray->erase(next);
        pLFsaAppl->pCVarFSA->strListLocalVar = CreateStringVariables();
        pLFsaAppl->pTAppCore->pSetVarFSA->SetSaveSet(bSave);
        pLFsaAppl->pTAppCore->nSizeLocVars--;
        // обновить связи процессов
        pLFsaAppl->pTAppCore->pCArrayNetFsa->ResetTasks();
        return true;
    }
    return false;
}

CLocVar* CSetLocVar::GetAddressVar(string nam)
{
    CLocVar vs(nullptr,nam);
    TIteratorLocVar bg=pArray->begin();
    while (bg != pArray->end()) {
        if (bg->strName == "") {
        }
        bg++;
    }
    TIteratorLocVar next=find(pArray->begin(), pArray->end(), vs);
    if (next!=pArray->end())
        return &*next;
    else
        return nullptr;
}


string CSetLocVar::SaveListVariables(string& pstrOutput)
{
    string str="";
    TIteratorLocVar next= pArray->begin();
    while (next!= pArray->end()) {
        str +=next->strName + ";";
        str +=next->strComment + ";";
        string ch;
        ch = itoa(int(next->unTypeVar));
        str +=next->unTypeVar + ";" + ch + ";";
        next++;
    }
    return str;
}

string CSetLocVar::CreateStringVariables()
{
    char ach[2048];
    memset(ach,0,sizeof(ach));
    string str="";
    ostrstream o(ach, sizeof(ach));
    TIteratorLocVar next= pArray->begin();
    while (next!= pArray->end()) {
        o<<"<"<<next->strName<<","
        <<next->strComment<<","
        <<next->unTypeVar<<","
        <<next->bIfInit<<","
        <<next->strInitValue<<","
        <<next->bSerial<<","
        <<next->bOnlyChanges<<","
        <<next->bConstant<<","
        <<">";
        next++;
    }
    return string(ach);
};

void CSetLocVar::CreateArrayVariables(LFsaAppl *pL, string& pstr)
{
    pLFsaAppl = pL;
    string pstrInput = pstr;
    char ach[2048];
    memset(ach,'\0',sizeof(ach));
    while (!pstrInput.empty()) {
        string strList;
        int nStart = pstrInput.find_first_of("<");
        if (nStart<0) return;
        int nEnd = pstrInput.find_first_of(">");
        if (nEnd<0) return;
        int n = nEnd-(nStart+1);
        memset(ach,'\0',sizeof(ach));
        pstrInput.copy(ach,n,nStart+1);
        pstrInput.erase(nStart, nEnd+1);
        strList = string(ach);
        LConvStr CS(strList);
        CS.SetSeparator(",");
        while (!strList.empty()) {
            string strName		= CS;
            string strComment	= CS;
            int unTypeVar		= CS;
            bool bIfInit		= CS;
            string strInitValue	= CS;
            bool bIfMin			= CS;
            bool bIfMax			= CS;
            double dValueMin	= CS;
            double dValueMax	= CS;
            bool bSerial		= CS;
            bool bDrawTrend		= CS;
            bool bOnlyChanges	= CS;
            bool bConstant		= CS;
            CLocVar var;
            var.strName = strName;
            var.strComment = strComment;
            var.unTypeVar = unTypeVar;
            var.bIfInit = bIfInit;
            var.strInitValue = strInitValue;
            var.pLFsaAppl = pL;
            var.strng = "";
            var.bIfLocal = true;
            var.bSerial = bSerial;
            var.bOnlyChanges = bOnlyChanges;
            var.bConstant = bConstant;
            if (var.unTypeVar==CVar::vtFsastate) {
                string strng = strName;
                LConvStr CS(strng);
                CS.SetSeparator("(");
                string strNameFsa = CS;
                CS.SetSeparator(")");
                string strState = CS;
                var.strng = strState;
            }
            var.pLFsaType = pL;													// двигатель
            var.pTAppCore = pL->pTAppCore;										// двигатель
            double d=0;
            if (bIfInit) {
                if (unTypeVar == CVar::vtString) {
                    var.SetDataSrc(nullptr, strInitValue, nullptr);
                    var.UpdateVariable();
                }
                else {
                    string sss;
                    if (unTypeVar == CVar::vtFsastate) {
                        sss = var.strng;
                    }
                    try {
                        d = stod(strInitValue); // Преобразование строки в double
                    } catch (const std::exception& e) {
//                        Serial.printf("err CSetLocVar:232: %s\n", e.what());
                    }                        
                var.SetDataSrc(nullptr, d, pL);
                    var.UpdateVariable();
                    if (unTypeVar == CVar::vtFsastate) {
                        var.strng = sss;
                    }
                }
            }
            // необходимо, т.к. UpdateVariable обнуляет данное свойство
            var.pLFsaAppl = pL;
            var.pLFsaType = pL;		// заполняем ссылку на процесс, которому принадлежит локальная переменная
            CLocVar *pV = nullptr;
            if (!var.strName.empty()) {
                pArray->push_back(var);
                pLFsaAppl->pTAppCore->nSizeLocVars++;
                pV = GetAddressVar(var.strName);
                pV->pLFsaAppl = pL;		// необходимо, т.к. после помещения данное свойство очищается (?)
                pV->pLFsaType = pL;		// необходимо, т.к. после помещения данное свойство очищается (?)
                pV->dDataSrc = d;
                if (bIfInit) {
                    if (unTypeVar == CVar::vtString) {
                        pV->SetDataSrc(nullptr, strInitValue, nullptr);
                        pV->UpdateVariable();
                        string str = pV->strGetDataSrc();

                    }
                    else {
                        try {
                            d = stod(strInitValue); // Преобразование строки в double
                        } catch (const std::exception& e) {
//                            Serial.printf("err CSetLocVar:263: %s\n", e.what());
                        }                        
                        pV->CVar::SetDataSrc(nullptr, d, pL);
                        pV->CVar::UpdateVariable();
                    }
                }
            }

        }
    }
    pArray->sort();
}
