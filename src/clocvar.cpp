#include "clocvar.h"

#include "LConvStr.h"
#include "VarSetting.h"
#include "lfsaappl.h"
#include "TAppCore.h"

CLocVar::CLocVar(void): CVar()
{
}


CLocVar::~CLocVar(void)
{
}

CLocVar::CLocVar(const CLocVar& var):CVar(var)
{
}

CLocVar::CLocVar(LFsaAppl* pF, string &nam): CVar()
{
    MoveToVar(nam);
    pLFsaAppl=pF;
}

void CLocVar::MoveToVar(string &strS)
{
    if (strS!="") {
    LConvStr CS(strS);
// имя переменной
        strName= string(CS);
// комментарий
        strComment= string(CS);
// тип переменной
        unTypeVar= CS;
// флаг инициализации нач.значения переменной
        bIfInit= CS;
// нач.значение
        strInitValue= string(CS);
// тип памяти - последовательный
        bSerial= CS;
// отображать только изменения
        bOnlyChanges= CS;
// константа
        bConstant= CS;
    }
}

bool CLocVar::IfEqu(CLocVar& var)
{
    if (!CVar::IfEqu(var)) return false;
    return true;
}
void CLocVar::UpdateVariable()
{
    if (pLFsaType) {
        CVar::UpdateVariable();
        pLFsaAppl=nullptr;
    }
}

double CLocVar::SetDataSrc(LFsaAppl *pLFA, double d, LFsaAppl *pWr)
{
    if (pLFsaType||!bIfLocal) {
        if (pLFsaType) {
            string strProc = pLFsaType->nameFsa;
            if (pLFA)
             strProc += "." + pLFA->nameFsaProcess;
        }
        double dd = CVar::SetDataSrc(pLFA, d, pWr);

        if (pLFsaType) {
            if ((pLFsaType->pTAppCore&&!pLFsaType->pTAppCore->pCVarSetting->bIfShadowVariable) || bSerial)
                UpdateVariable();
        }
        else {
            if(pLFA) {
                if (!pLFA->pTAppCore->pCVarSetting->bIfShadowVariable || bSerial)
                    UpdateVariable();
            }
        }
        return dd;
    }
    return dDataSrc;
}		// жесткая запись данных

string CLocVar::SetDataSrc(LFsaAppl *pLFA, string strS, LFsaAppl *pWr)
{
//	pLFsaType = pLFA;
    string strVar = strName;
//	if (strVar == "U") {
//		int n = 0;
//	}
    if (pLFsaType||!bIfLocal) {
        if (pLFsaType && pLFA)
            string strProc = pLFA->nameFsa + "." + pLFA->nameFsaProcess;
        string strVar = strName;
        string str = CVar::SetDataSrc(pLFA, strS, pWr);
        if (pLFsaType) {
            if ((pLFsaType->pTAppCore&&!pLFsaType->pTAppCore->pCVarSetting->bIfShadowVariable) || bSerial)
                UpdateVariable();
        }
        else {
            if(pLFA) {
                if (!pLFA->pTAppCore->pCVarSetting->bIfShadowVariable || bSerial)
                    UpdateVariable();
            }
        }
        return str;
    }
    return "";
}
