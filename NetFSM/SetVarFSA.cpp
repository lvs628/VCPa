#include "stdafx.h"
#include "SetVar.h"
#include "SetVarFSA.h"
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;
#include "setvarfsaobject.h"
#include "TAppCore.h"

CSetVarFSA::CSetVarFSA(TAppCore *pInfo, string strNam):
	CSetVar(pInfo, strNam)
{
	pArray = new CArrayVarFSA();
//	pArray->resize(100);
//	int n = pArray->capacity();
	bSaveSet = false;
}

CSetVarFSA::~CSetVarFSA(void)
{
    if (bSaveSet) {
        SaveDat();
        bSaveSet = false;
        }
	if (pArray) {
		CIteratorVarFSA next=pArray->begin();
		while (next != pArray->end()) {
			if (next->pLFsaAppl) {
				string str = next->strName;
				if (next->itrCVarFsaObject) {
					if (!next->itrCVarFsaObject->bIfWnd) {
                        delete next->pLFsaAppl;
                        next->pLFsaAppl = nullptr;
					}
				}
				// ���� ���� �� ������� ���� (��� �������, ����������� ��� �������-����), ��
				// ����� ������� � ������� ��������
				//
                if (next->bIfCreate&&next->pLFsaAppl) {
                    delete next->pLFsaAppl;
                    next->pLFsaAppl = nullptr;
                }
			}
			next++;
		}
		pArray->clear();
		delete pArray;
        pArray = nullptr;
	}
}

void CSetVarFSA::CreateLink()
{
	CIteratorVarFSA next=pArray->begin();
	while (next!=pArray->end()) {
		next->CreateLink();
		next++;
		}
}

bool CSetVarFSA::CreateLink(TNetFsa *pNet, CVarFSA &var)
{
	CIteratorVarFSA next=find(pArray->begin(), pArray->end(), var);
	if (next!=pArray->end()) {
		next->CreateLink();
		return true;
	}
	else
 		return false;

}

bool CSetVarFSA::LoadAllFsa()
{
	CIteratorVarFSA next=pArray->begin();
	while (next!=pArray->end()) {
		CVarFsaObject var;
		var.SetName(next->strNameFsa);
		TItrVarFsaObject itrFsaObj= pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.begin();
		itrFsaObj = find(pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.begin(),
			pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.end(), var);
		if (itrFsaObj !=pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.end()) {
			var = *itrFsaObj;
			LFsaAppl *pL = itrFsaObj->GetAddress();
			if (pL)
				next->LoadFsa(pL);
		}
		next++;
	}
	return true;
}

bool CSetVarFSA::LoadFsa(string strNam)
{

	CIteratorVarFSA next=pArray->begin();
	while (next!=pArray->end()) {
		if (next->strNameFsa == strNam) {
			CVarFsaObject var;
			var.SetName(next->strName);
			
			TItrVarFsaObject itrFsaObj= pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.begin();
			itrFsaObj = find(pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.begin(),
				pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.end(), var);
			if (itrFsaObj !=pTAppCore->pSetVarFsaObject->ArrayVarFsaObject.end()) {
				LFsaAppl *pL = itrFsaObj->GetAddress();
				if (pL)
					next->LoadFsa(pL);
				return true;
			}
		}
		next++;
	}
	return false;
}

LFsaAppl* CSetVarFSA::LoadFsa(string strNam, LFsaAppl *pFsa)
{
//    if (strNam == "���-maxim") {
//        int n=2;
//    }
    CVarFSA *pV = GetAddressVar(strNam);
    LFsaAppl *pF=pFsa;
    if (pV) {
        // ��������� ������� �� ������� � ������ ���������
        if (pF) {
            // ��������� ������� �������� �������� ����������
            bool bIfLoad = pV->LoadFsa(pF);
            if (bIfLoad) {
                pTAppCore->pSetVarFsaObject->Add(strNam, pF, false);
                return pF;
            }
            return nullptr;
        }
        return nullptr;
    }
    return nullptr;
}

CVarFSA* CSetVarFSA::GetAddressVar(string nam)
{
//	if (nam == "CycleNorm")
//		int n =1;
	CVarFSA vn;
	CVarFSA *pVn;
	vn.strName=nam;
	CIteratorVarFSA next=find(pArray->begin(), pArray->end(), vn);
	if (next!=pArray->end()) {
        if (next->bRemoteVariable)
            return nullptr;
		pVn = &(*next);
		return pVn;
	}
	else
        return nullptr;
}
CVarFSA* CSetVarFSA::GetAddressVar(string nam, string lib, string fsa)
{
	CVarFSA vn;
	CVarFSA *pVn;
	vn.strName=nam;
	CIteratorVarFSA next= pArray->begin();
	while (next!=pArray->end()) {
		if (next->strName == nam) {
			if (lib == "") {
				pVn = &(*next);
				return pVn;
			}
		}
		next++;
	}
    return nullptr;
}

void CSetVarFSA::CreateProcesses()
{
	CIteratorVarFSA next=pArray->begin();
	while (next != pArray->end()) {
        next->CreateProcessFSA();
		next++;
	}
}

LFsaAppl* CSetVarFSA::GetAddressFsa(string strNam)
{
	CVarFSA* p = this->GetAddressVar(strNam);
	if (p) return p->pLFsaAppl;
    return nullptr;

}

void CSetVarFSA::UpdateLinks(string name, int nT)
{
	CIteratorVarFSA next=pArray->begin();
	while (next != pArray->end()) {
		if (name=="") {
			if (next->bIfCreate) {
				next->pLFsaAppl->FUpdateLinks(name, nT);
			}
		}
		else {
			if (next->strNameFsa == name&& next->bIfCreate) {
				next->pLFsaAppl->FUpdateLinks(name, nT);
			}
		}
		next++;
	}
}

void CSetVarFSA::SetSaveSet(bool b) 
{
	if (b) {
		string str = strFileName;
	}
	bSaveSet = b;
}

//===================================================================
//											Add
//===================================================================
bool CSetVarFSA::Add(CVarFSA &var)
{
    CIteratorVarFSA next=find(pArray->begin(), pArray->end(), var);
    if (next==pArray->end()) {
        pArray->push_back(var);
        next=find(pArray->begin(), pArray->end(), var);
        next->CreateLink();
        SetSaveSet(true);
        return true;
        }
    else {
        if (next->bRemoteVariable) {
            bool bRet = Delete(var);
            if (bRet) {
                pArray->push_back(var);
                next=find(pArray->begin(), pArray->end(), var);
                next->CreateLink();
                SetSaveSet(true);
                return true;
            }
            return false;
        }
        return false;
    }
}
//===================================================================
//											Delete
//===================================================================
bool CSetVarFSA::Delete(CVarFSA &var)
{
    CIteratorVarFSA next=find(pArray->begin(), pArray->end(), var);
    if (next!=pArray->end()) {
//		CVarFSA *p = &(*next);
        if (next->pLFsaAppl) {
            string str = next->strName;
            if (next->itrCVarFsaObject) {
                if (!next->itrCVarFsaObject->bIfWnd) {
                    delete next->pLFsaAppl;
                    next->pLFsaAppl = nullptr;
                }
            }
            // если даже не удалено выше (для объекта, помеченного как процесс-окно), то
            // будет удалено в массиве объектов
            //
            if (next->bIfCreate&&next->pLFsaAppl) {
                delete next->pLFsaAppl;
            }
            next->pLFsaAppl = nullptr;
        }
        next->bRemoteVariable = true;
        pArray->erase(next);
        SetSaveSet(true);
        return true;
        }
    else return false;
}
//===================================================================
//											Replace
//===================================================================
bool CSetVarFSA::Replace(CVarFSA &var)
{
    CVarFSA *p = GetAddressVar(var.strName);
    if (p) {
        if (p->IfEqu(var))
            return false;
        else {
            *p = var;
            SetSaveSet(true);
            return true;
		}
    }

    return false;
}
