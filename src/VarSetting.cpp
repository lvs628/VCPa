#include "stdafx.h"
#include "vcpalibrary.h"
#include "VarSetting.h"
#include "ArrayNetFsa.h"

#include "netfsa.h"

CVarSetting::CVarSetting()
{
    strName  = "";
    pTAppCore			= nullptr;

    dDeltaTime = 0;
    bIfSynchronousOperation = false;

    strNameNetFsa		= "";
    pTNetFsa			= nullptr;
    bIfShadowVariable	= false;
    bIfStopAllTasks		= false;
    strNetFsaDefault	= "";		// имя переменной пространства по умолчанию
}

CVarSetting::CVarSetting(const CVarSetting& var)
{
    pTAppCore			= var.pTAppCore;
    strName				= var.strName;
    dDeltaTime			= var.dDeltaTime;							// флаг пуска задачи Общий экран
    bIfSynchronousOperation		= var.bIfSynchronousOperation;							// флаг пуска задачи Общий экран
    strNameNetFsa		= var.strNameNetFsa;
    pTNetFsa			= var.pTNetFsa;
    bIfShadowVariable	= var.bIfShadowVariable;
    bIfStopAllTasks		= var.bIfStopAllTasks;
    strNetFsaDefault	= var.strNetFsaDefault;		// имя переменной пространства по умолчанию
}

CVarSetting::CVarSetting(TAppCore *pPr)
{
	pTAppCore			= pPr;
	
	dDeltaTime = 0;
	bIfSynchronousOperation = false;
	strNameNetFsa		= "";
    pTNetFsa			= nullptr;
	bIfShadowVariable	= false;
	bIfStopAllTasks		= false;
    strNetFsaDefault	= "";		// имя переменной пространства по умолчанию
}

CVarSetting::CVarSetting(TAppCore *pPr, string &nam)
{
	MoveToVar(nam);
	pTAppCore		= pPr;
    pTNetFsa = nullptr;
	if (strNameNetFsa != "") {
		if (strNameNetFsa != "InitFsaWorld") {
            pTNetFsa = pPr->pCArrayNetFsa->GetNetFsa(strNameNetFsa, "");
		}
		else {
			pTNetFsa = pPr->pCArrayNetFsa->pNetFsa;
		}
	}
	else {
		pTNetFsa = pPr->pCArrayNetFsa->pNetFsa;
	}
}

bool CVarSetting::IfEqu(CVarSetting& var)
{
	if (strName!= var.strName) return false;
	if (bIfSynchronousOperation!=var.bIfSynchronousOperation) return false;
	if (dDeltaTime!=var.dDeltaTime) return false;
	if (strNameNetFsa!=var.strNameNetFsa) return false;
	if (bIfShadowVariable!=var.bIfShadowVariable) return false;
	if (bIfStopAllTasks!=var.bIfStopAllTasks) return false;
	if (strNetFsaDefault!=var.strNetFsaDefault) return false;
    return true;
}

void CVarSetting::MoveToVar(string &Str)
{
    vector<string> strList = splitString(Str, ";");  // Разбиваем по ";"
    const int n = strList.size();
    if (n==1) {
        strName				= strList[0];			// 1- Имя переменной
        return;
    }
// имя переменной
    strName				= strList[0];			// 1- Имя переменной
    bIfSynchronousOperation = stoi(strList[1]);	// 4- =1, если выбран синхронный режим дискретного времени
    dDeltaTime			= stod(strList[2]);		// 5- длительность в милисекундах "жесткого" дискретного такта системы
    strNameNetFsa		= strList[3];			// 8- имя автоматного пространства
    bIfShadowVariable	= stoi(strList[4]);	// 11- "теневой" режим работы данных
    bIfStopAllTasks		= stoi(strList[5]);	// 14- признак останова всех задач "автоматного пространства"
    strNetFsaDefault	= strList[6];			// 17- имя переменной пространства по умолчанию
}

int CVarSetting::operator==(const CVarSetting &var) const	
{ 
	return strName==var.strName; 
}

