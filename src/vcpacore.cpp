#include "vcpacore.h"
#include "TAppProcesses.h"
#include "ArrayNetFsa.h"
#include "VarSetting.h"
#include "SetVarSetting.h"
#include "netfsa.h"

VCPaCore::VCPaCore()
{

}
TAppProcesses *pTAppProcesses = nullptr;
TAppProcesses* VCPaCore_init()
{
    pTAppProcesses = nullptr;
    pTAppProcesses = new TAppProcesses();
    bool bRet = pTAppProcesses->LoadConfiguration();
    if (!bRet) {
        return nullptr;
    }
    return pTAppProcesses;
}

void VCPaCore_delete() {
    if (pTAppProcesses)
        delete pTAppProcesses;
    pTAppProcesses = nullptr;
}

static TPIteratorNetFsa IIteratorNetFsa;
static TIteratorCVarSetting nextSet;
void VCPaCore_TimerEvent(int nId) {
//*
    if (pTAppProcesses) {
        pTAppProcesses->llVCPaSystemTime++;
        IIteratorNetFsa = pTAppProcesses->pCArrayNetFsa->PArrayNetFsa.begin();

        nextSet = pTAppProcesses->pSetVarSetting->pArray->begin();
        while (nextSet != pTAppProcesses->pSetVarSetting->pArray->end()) {
            CVarSetting *pCV = &(*nextSet);
            if (!pCV->bIfStopAllTasks) {
                if (nextSet->pTNetFsa) {
                    pTAppProcesses->pCurrentNetFsa = nextSet->pTNetFsa;
                    nextSet->pTNetFsa->pCVarSetting = pCV;		// не убирать ни в коем случае!!!!!!!!!!!!!!!!!!!!!!
                    nextSet->pTNetFsa->OnIdle(pCV);
                }
            }
            nextSet++;
        }
    }

//*/
}
