// Var.cpp: implementation of the CVar class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Var.h"
#include "LConvStr.h"
#include <sstream>
#include <iomanip>
#include "VarSetting.h"
#include "lfsaappl.h"
#include "TAppCore.h"
#include "VarFSA.h"
#include "SetVarFSA.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static string strVarControl_0 = "Out";
static string strVarControl_1 = "Out";
CVar::CVar()
{
    nType=cvarNone;
    strName=strComment="";
    m_nCountUse = 0;
    bLocking = false;
    pTAppCore = nullptr;
    dShadowDataSrc = 0;			// ������ ��/� �������� , � ������ ����
    pTNetFsa = nullptr;
    strNameNetFsa	= "";
    unTypeVar	= 0;
    pLFsaAppl = nullptr;
    pLFsaType = nullptr;
    strng	= "";
    strShadowData = "";
    bIfInit	= false;
    strInitValue = "";
    pArraydDataSrc = nullptr;			// ������ (������) ��/� �������� , � ������ ����
    pArraydShadowDataSrc = nullptr;	// ������(������) ��/� �������� , � ������ ����
    bUsed	= false;
    bIfLocal = false;
    bSerial	= false;
    pLFsaOwner	= nullptr;
    bIfCopyFromShadow = false;
    dDataSrc = 0;			// ������ ��/� �������� , � ������ ����
    bOnlyChanges	= false;	// ���������� ������ ���������
    bIfSetNewData	= false;	// ������� ��������� ������ �������� ������
    bConstant		= false;
    bEvent			= false;
    bIfReadEvent	= false;
    nError          = 0;
}

CVar::CVar(string strNm, string strCm)
{
    strName=strNm; strComment=strCm;
    m_nCountUse = 0;
    bLocking = false;
    nType=cvarNone;
    pTAppCore = nullptr;
    dShadowDataSrc = 0;			// ������ ��/� �������� , � ������ ����
    pTNetFsa = nullptr;
    strNameNetFsa	= "";
    unTypeVar	= 0;
    pLFsaAppl = nullptr;
    strng	= "";
    strShadowData = "";
    pLFsaType = nullptr;
    bIfInit	= false;
    strInitValue = "";
    pArraydDataSrc = nullptr;			// ������ (������) ��/� �������� , � ������ ����
    pArraydShadowDataSrc = nullptr;	// ������(������) ��/� �������� , � ������ ����
    bUsed	= false;
    bIfLocal = false;
    bSerial = false;
    pLFsaOwner	= nullptr;
    bIfCopyFromShadow = false;
    dDataSrc = 0;			// ������ ��/� �������� , � ������ ����
    bOnlyChanges	= false;	// ���������� ������ ���������
    bIfSetNewData	= false;	// ������� ��������� ������ �������� ������
    bConstant		= false;
    bEvent			= false;
    bIfReadEvent	= false;
    nError          = 0;
}

CVar::~CVar()
{

}

CVar::CVar(const CVar& var)
{
    pLFsaType = var.pLFsaType;
    bIfInit = var.bIfInit;
    strInitValue = var.strInitValue;
//
    nType=var.nType;
    strName=var.strName; strComment=var.strComment;
    strng		= var.strng;
    strShadowData		= var.strShadowData;
    pTAppCore = var.pTAppCore;
    m_nCountUse = 0;
    bLocking = false;
    dShadowDataSrc = var.dShadowDataSrc;			// ������ ��/� �������� , � ������ ����
    pTNetFsa = var.pTNetFsa;
    strNameNetFsa	= var.strNameNetFsa;
    unTypeVar	= var.unTypeVar;
//	pLFsaAppl = nullptr;
    pLFsaAppl = var.pLFsaAppl;
    pArraydDataSrc = nullptr;			// ������ (������) ��/� �������� , � ������ ����
    pArraydShadowDataSrc = nullptr;	// ������(������) ��/� �������� , � ������ ����
    bUsed	= var.bUsed;
    bIfLocal = var.bIfLocal;
    bSerial	= var.bSerial;
    pLFsaOwner = var.pLFsaOwner;
    bIfCopyFromShadow = var.bIfCopyFromShadow;
    dDataSrc = 0;			// ������ ��/� �������� , � ������ ����
    bOnlyChanges	= var.bOnlyChanges;		// ���������� ������ ���������
    bIfSetNewData	= var.bIfSetNewData;	// ������� ��������� ������ �������� ������
    bConstant		= var.bConstant;
    bEvent			= var.bEvent;
    bIfReadEvent	= var.bIfReadEvent;
    nError      	= var.nError;
}

bool CVar::operator==(const CVar &var) const
{
    if (strName==var.strName) return true;
    else return false;
}

bool CVar::operator<(const CVar &var) const
{ return strName<var.strName; }

bool CVar::operator!=(const CVar &var) const
{ return strName!=var.strName; }

bool CVar::operator>(const CVar &var) const
{ return strName>var.strName; }

bool CVar::IfEqu(CVar& var)
{
    if (strName!=var.strName) return false;
    if (strComment != var.strComment) return false;
    if (nType!= var.nType) return false;
    if (strNameNetFsa != var.strNameNetFsa) return false;
    if (unTypeVar != var.unTypeVar) return false;
    if (bSerial != var.bSerial) return false;
    if (bIfInit != var.bIfInit) return false;
    if (strInitValue != var.strInitValue) return false;
    if (bOnlyChanges != var.bOnlyChanges) return false;
    if (bConstant != var.bConstant) return false;
    if (bEvent != var.bEvent) return false;
    return true;
}

void CVar::MoveToVar(string &Str)
{
    if (Str!="") {
    LConvStr CS(Str);
// ��� ����������
        strName		= string(CS);
// �����������
        strComment	= string(CS);
// ��� ����������
        nType		= CS;
// ����� ���� �����������
        bIfInit		= CS;
    }

}
// ���������� ������, ���� ����� nullptr � ����� ������ ���������, false - �����
// ��� ���� ��������������� ������� ������ ��������� �������� ����������
bool CVar::IfLocking(LFsaAppl *pFOwner, bool *bLoc) {
    *bLoc = bLocking;
    if (pLFsaOwner==nullptr||pFOwner==pLFsaOwner) {
        // ���� ���������� �������� ��� �������� - pFOwner
        return true;
    }
    else
        return false;
}
// ���������� true, ����� ������ � ����� ����������� ��� ��� ���������� ���������� � ������ ����������
// false, ����� ������ ������� �������� ���������� ����������
bool CVar::SetLocking(bool bSet, LFsaAppl *pOwner) {
    if (!pLFsaOwner || pLFsaOwner == pOwner) {
        // ���� ���������� �������� ��� ������������ � ������ ���������� ������� (pOwner) �����������
        bLocking = bSet;
        if (bSet) {
            // ���� ����� �����������, �� ������������� ������������ ����������
            pLFsaOwner = pOwner;
        }
        else {
            // ���� ��������������, �� ���������� ������������
            pLFsaOwner = nullptr;
        }
        // ���� ������� ������� ������������ ����������, �� ����������� �����, ��������������� ���� ��������� (������ �� ���������� ����������)
        if (pOwner&&!bSet)
            pOwner->FSetLocking(bSet, pOwner, strName);
        return true;
    }
    else {
        // ������ ������� ���������� ������ ����������
        return false;
    }
}

double CVar::InitVariable(double d)
{
    if (bConstant) return dDataSrc;
/*
    if (strName == strVarControl_0||strName == strVarControl_1) {
        double dd = d;
        if (d==0)
            int n = 1;
    }
*/
    double dTmp;
    dTmp=dDataSrc;
    dDataSrc = d;
    dShadowDataSrc = d;
    pLFsaAppl = nullptr;
    pArraydDataSrc = nullptr;			// ������ (������) ��/� �������� , � ������ ����
    pArraydShadowDataSrc = nullptr;	// ������(������) ��/� �������� , � ������ ����
    return dTmp;
}

string CVar::InitVariable(string d)
{
    if (bConstant) return strng;
/*
    if (strName == strVarControl_0||strName == strVarControl_1) {
        int n = 1;
    }
*/
    string strTmp;
    strTmp=strng;
    strng = d;
    strShadowData = d;
    pLFsaAppl = nullptr;
    pArraydDataSrc = nullptr;			// ������ (������) ��/� �������� , � ������ ����
    pArraydShadowDataSrc = nullptr;	// ������(������) ��/� �������� , � ������ ����
    return strTmp;
}

double CVar::SetData(LFsaAppl *pLFA, double d)
{
    if (bConstant) return dDataSrc;
    bUsed	|= true;
/*
    if (strName == strVarControl_0||strName == strVarControl_1) {
        double dd = d;
        if (d==0)
            int n = 1;
    }
*/
    if (pTAppCore) {
        if (!bSerial) {
            if (!pLFsaAppl)
                pLFsaAppl = pLFA;
            else {
                string str;
                if (pLFA) {
                }
                else {
                }
                return dDataSrc;
            }
        }
    }
    double dTmp = 0;
    if (unTypeVar>=1||unTypeVar<=3) {
        dTmp=dDataSrc;
        dShadowDataSrc = d;
        bIfCopyFromShadow = true;
        if (pTAppCore) {
            if (!pTAppCore->pCVarSetting->bIfShadowVariable || bSerial)
                UpdateVariable();
        }
    }

    return dTmp;
}

double CVar::SetDataSrc(LFsaAppl *pLFA, double d, LFsaAppl *pLWriter)
{
//  ��� ���������� �����������
//    if (strName == "bIfHide") {
//        int n = 0;
//    }
    if (pLFsaType) {
    }
        bUsed	|= true;
        if (bLocking && pLFA != nullptr) {
            if (pLFsaOwner != pLFA) return d;
        }
        if (pLFA) {
            if (pTAppCore) {
                if (!bSerial) {
                    if (!pLFsaAppl) {
                        // ������ ��� ��������� ����������
                        if (this->bIfLocal) {
                            pLFsaAppl = pLFA;
                        }
                    }
                    else {
                        if (pLFsaType != pLFA) {
                            string str;
                            if (pLFA) {
            //					str = "������ ������: �������� ��������� - " + pLFsaAppl->nameFsa + "," + pLFA->nameFsa;
                                string strName2;
                                if (pLFA->pCVarFSA)
                                    strName2 = pLFA->pCVarFSA->strName;
                                else
                                    strName2 = pLFA->FGetNameFsa();
                                if (pLFsaAppl->pCVarFSA) {
                                    str = "������ ������: �������� ��������� - " + strName + ":" +pLFsaAppl->pCVarFSA->strName +  "," + strName2;
//                                    str = QString::fromLocal8Bit(str.c_str()).toStdString();
                                }
                                else {
                                    str = "������ ������: �������� ��������� - " + strName + ":" +pLFsaAppl->nameFsa +  "," + strName2;
                                }
                            }
                            else {
                                str = "������ ������: �������� ��������� - " + strName + ":" +pLFsaAppl->pCVarFSA->strName + ", nullptr";
            //					str = "������ ������: �������� ��������� - " + pLFsaAppl->nameFsa + ", nullptr";
            //					MessageBox(nullptr, str.c_str(), _T("CVar:Error"), MB_ICONEXCLAMATION | MB_OK);
                            }
            //				pTAppCore->StopAllTasks("");
                            return dDataSrc;
                        }
                    }
                }
    //	�������� �� ��������� ������ � ������� �����
                if (nAcntWriters) {
                    if (dShadowDataSrc != d) {
                        string strN = "";
                        if (this->bIfLocal) {
                            if (this->pLFsaType) {
                                if (this->pLFsaType->pCVarFSA) {
                                    strN = this->pLFsaType->pCVarFSA->strName +".";
                                }
                            }
                        }
                        string str = "��-� ������ > 1: "  + strN+strName + "<- ";
                        if (pLWriter) {
                            str += strErr + "," +pLWriter->FGetNameVarFSA();
                        }
                        nAcntWriters++;
                    }
                }
                else {
                    nAcntWriters++;
                    if (pLWriter)
                        strErr += pLWriter->FGetNameVarFSA();
                }
    //
            }
        }
    //next:
        double dTmp;
        dTmp=dDataSrc;
        dShadowDataSrc = d;
        bIfCopyFromShadow = true;
        if (bSerial) {
            UpdateVariable();
        }
        if (pTAppCore) {
            if (pTAppCore->pCVarSetting) {
                if(!pTAppCore->pCVarSetting->bIfShadowVariable)
                    UpdateVariable();
            }
        }
        if (nType == cvarWrite) {
//            ExactTime = LTime();
        }
        return dTmp;
}

double CVar::GetDataSrc(LFsaAppl *pLFA)
{
    bUsed	|= true;
    if (unTypeVar==vtFsastate) {
        if (!pLFsaType) {
            string strNameFsa = "";
            string strState = "";
            string str = strName;
            LConvStr CS(str);
            CS.SetSeparator("(");
            strNameFsa = string(CS);
            CS.SetSeparator(")");
            strState = string(CS);
            strShadowData = strState;
            if (pTAppCore)
                pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strNameFsa);
        }
        if (pLFsaType) {
            if (pLFsaType->FIsActiveTask()) {
                if (strng=="") {
                    string strNameFsa = "";
                    string strState = "";
                    string str = strName;
                    LConvStr CS(str);
                    CS.SetSeparator("(");
                    strNameFsa = string(CS);
                    CS.SetSeparator(")");
                    strState = string(CS);
                    strShadowData = strState;
                    if (pTAppCore)
                        pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strNameFsa);
                }
                if (strng != "")
                    dShadowDataSrc = pLFsaType->FGetState() == strng;
                else {
                    dShadowDataSrc = pLFsaType->FGetState() == strShadowData;
                    strng = strShadowData;
                }
                dDataSrc = dShadowDataSrc;
                UpdateVariable();
            }
            else {
                if (strng != "")
                    dShadowDataSrc = pLFsaType->FGetState() == strng;
                else {
                    dShadowDataSrc = pLFsaType->FGetState() == strShadowData;
                    strng = strShadowData;
                }
                dDataSrc = dShadowDataSrc;
                dShadowDataSrc = 0;
                UpdateVariable();
            }
        }
    }
    if (bEvent) {
        if (pLFA && pLFsaOwner) {
            if (pLFA == pLFsaOwner) {
                bIfReadEvent = true;
            }
        }
    }
    return dDataSrc;
}

CVar::operator double()
{
    bUsed	|= true;
    return dDataSrc;
}

void CVar::UpdateVariable()
{
    if (unTypeVar==vtFsastate) {
        if (!pLFsaType) {
            string strNameFsa = "";
            string strState = "";
            string str = strName;
            LConvStr CS(str);
            CS.SetSeparator("(");
            strNameFsa = string(CS);
            CS.SetSeparator(")");
            strState = string(CS);
            strShadowData = strState;
            if (pTAppCore)
                pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strNameFsa);
        }
        else {
            if (pLFsaType->FIsActiveTask()) {
                if (strng=="") {
                    string strNameFsa = "";
                    string strState = "";
                    string str = strName;
                    LConvStr CS(str);
                    CS.SetSeparator("(");
                    strNameFsa = string(CS);
                    CS.SetSeparator(")");
                    strState = string(CS);
                    strShadowData = strState;
                    if (pTAppCore)
                        pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strNameFsa);
                    if (pLFsaType) {
                        bIfCopyFromShadow = true;
                        dShadowDataSrc = pLFsaType->FGetState() == strShadowData;
                        strng = strShadowData;
                    }
                }
                else {
                    string s_tmp = pLFsaType->FGetState();
                    if (strShadowData == "") {
                        strShadowData = s_tmp;
                    }
                    else {
                        if (strShadowData != s_tmp) {
                            strShadowData = s_tmp;
                        }
                        bIfSetNewData = false;
                    }
                }
            }
        }
    }
    if (unTypeVar==6) {
        return;
    }

    if (!bIfCopyFromShadow)
        return;


    if (unTypeVar<=3) {
        dDataSrc = dShadowDataSrc;
        bIfSetNewData = false;
    }
    else if (unTypeVar==4||unTypeVar==7) {
        strng = strShadowData;
    }
    pLFsaAppl = nullptr;					// 2014/08/16 ���-�� �� ��, ����� ��� ������� FTCP ������ ������������������������() \???
                                        // 2014/10/01 � FTCP ����� ������������ pLFsaType � ������ ���������������������������()
    bIfCopyFromShadow = false;
    if (bIfReadEvent) {
        bIfReadEvent = false;
        dDataSrc = 0;
    }

}

string CVar::SetDataSrc(LFsaAppl *pLFA, string d, LFsaAppl *pLWriter)
{
    if (bLocking && pLFA != nullptr) {
        if (pLFsaOwner != pLFA)
            return "";
    }
        if (pLFA && (strName == "strText"||strName == strVarControl_1)) {
            string str;
            if (this->pLFsaAppl)
                str = this->pLFsaAppl->FGetNameVarFSA();
            if (str == "FC_Millet") {
            }
        }

        if (pLFA) {
            if (pTAppCore) {
                if (!bSerial) {
                    if (!pLFsaAppl)
                        pLFsaAppl = pLFA;
                    else {
                        if (pLFsaAppl != pLFA) {
                        // ���� �������, ������� �������� ����������, �� �������� ���������� ���� ���������� - ������� ���������	// 2016_11_04_09_03
                            string str;
                            if (pLFA) {
            //					str = "������ ������: �������� ��������� - " + pLFsaAppl->nameFsa + "," + pLFA->nameFsa;
                                string strName2;
                                if (pLFA->pCVarFSA)
                                    strName2 = pLFA->pCVarFSA->strName;
                                else
                                    strName2 = pLFA->FGetNameFsa();
                                if (pLFsaAppl->pCVarFSA) {
                                    str = "process conflict- " + strName + ":" +pLFsaAppl->pCVarFSA->strName +  "," + strName2;
                                }
                                else {
                                    str = "process conflict-" + strName + ":" +pLFsaAppl->nameFsa +  "," + strName2;
                                }
                            }
                            else {
                                str = "process conflict-" + strName + ":" +pLFsaAppl->pCVarFSA->strName + ", nullptr";
                            }
                            return strng;
                        }
                    }
                }
    //	�������� �� ��������� ������ � ������� �����
                if (nAcntWriters) {
                    if (strShadowData != d) {
                        string strN = "";
                        if (this->bIfLocal) {
                            if (this->pLFsaType) {
                                if (this->pLFsaType->pCVarFSA) {
                                    strN = this->pLFsaType->pCVarFSA->strName +".";
                                }
                            }
                        }
                        string str = "��-� ������ > 1: "  + strN+strName + "<- ";
                        if (pLWriter) {
                            str += strErr + "," +pLWriter->FGetNameVarFSA();
                        }
                        nAcntWriters++;
                    }
                }
                else {
                    nAcntWriters++;
                    if (pLWriter)
                        strErr += pLWriter->FGetNameVarFSA();
                }
            }
        }
        string strTmp;
        // ��������� ��� ������
        if (unTypeVar==vtString) {
            strShadowData = d;
            bIfCopyFromShadow = true;
            if (pTAppCore) {
                if (pTAppCore->pCVarSetting) {										// ���������
                    if ((pTAppCore&&!pTAppCore->pCVarSetting->bIfShadowVariable) || bSerial)
                        UpdateVariable();
                }
            }// ���������
        }
        // fsa
        else if (unTypeVar==vtFsa) {
            strShadowData = d;
            bIfCopyFromShadow = true;
            if (pTAppCore&&!pTAppCore->pCVarSetting->bIfShadowVariable)
                UpdateVariable();
            if (pTAppCore)
                pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strng);
        }
        // fsastate
        else if (unTypeVar==vtFsastate) {
            strShadowData = d;
            bIfCopyFromShadow = true;
            if (pTAppCore&&!pTAppCore->pCVarSetting->bIfShadowVariable)
                UpdateVariable();
            if (strng!="") {
                LConvStr CS(strng);
                CS.SetSeparator("(");
                string strNameFsa = CS;
                CS.SetSeparator(")");
                string strState = CS;
            }

            if (pTAppCore)
                pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strng);
        }

        if (nType == cvarWrite) {
//            ExactTime = LTime();
        }
        return strTmp;
}

string CVar::strGetDataSrc(LFsaAppl *pLFA)
{
        bUsed	|= true;
        if (unTypeVar==4) {
            return strng;
        }
        else if (unTypeVar==7) {
            if (!pLFsaType)
                pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strng);
            if (pLFsaType) {
                if (pLFsaType->FIsActiveTask()) {
                    string str = pLFsaType->FGetState();
                    return str;
                }
                else {
                    string str = pLFsaType->FGetState();
                    return str;
                }
            }
            return "��� ��������";
        }
        return "";
}

void CVar::CreateLink()
{
    if (unTypeVar==7) {
        strShadowData = strName;
        UpdateVariable();
        if (pTAppCore)
            pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strng);
    }
    else if (unTypeVar==8) {
        strShadowData = strName;
        UpdateVariable();
        string str = strName;
        string strNameFsa = "";
        string strState = "";
        if (str!="") {
            LConvStr CS(str);
            CS.SetSeparator("(");
            strNameFsa = string(CS);
            CS.SetSeparator(")");
            strState = string(CS);
            strShadowData = strState;
            UpdateVariable();
        }
        if (pTAppCore)
            pLFsaType = pTAppCore->pSetVarFSA->GetAddressFsa(strNameFsa);
    }
}

CVar&  CVar::operator=(const CVar &var)
{
    if (this != &var) {

        bIfInit = var.bIfInit;				// ����������������� ��� ��������
        strInitValue = var.strInitValue;			// �������� ������������� � ��������� �����
        unTypeVar = var.unTypeVar;
        pLFsaAppl = var.pLFsaAppl;		// ��������� �� �������, ������� �������� ������ �� ��������� ������
        pTNetFsa = var.pTNetFsa;		// ��������� �� "���������� ������������", � �������� "���������" ����������
/////////////////////////////////////////////////////////////////////
        strName = var.strName;			//	��� ����������
        strComment = var.strComment;			// ����������� � ����������
        m_nCountUse = var.m_nCountUse;		// ������� �������������
        strNameNetFsa = var.strNameNetFsa;		// ��� ����������� ������������
//
        strng = var.strng;
        bLocking = var.bLocking;
        nType = var.nType;				// ��� ����������
        bUsed = var.bUsed;				// used - ��������������, ������� ����, ��� ���������� ���� ������������ ��� ����-����
        bIfLocal = var.bIfLocal;			// ������� ���������� ���������� ���� (�� ��������� = false, �.�. ����������)
        bSerial = var.bSerial;			// ��� ������ - ����������������
        bOnlyChanges = var.bOnlyChanges;		//
        bConstant = var.bConstant;				//
        bEvent = var.bEvent;				//
        nError  = var.nError;               // ����������� ������
//////////////////////////////////////////////////////////////////////
        pTAppCore = var.pTAppCore;
        pLFsaType = var.pLFsaAppl;
        pLFsaOwner = var.pLFsaOwner;		// �������� ������� ��� ���������� ����������������� ����
    }
    return *this;
}
