// FDelay.cpp: implementation of the CFDelay class.
//
//////////////////////////////////////////////////////////////////////

#include "fsacore.h"		// FSA support for Finit State Automation Processes
#include "FDelay.h"
#include "VarSetting.h"
#include "netfsa.h"
#include "larc.h"
#include "TAppCore.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static LArc DelayTBL[] = {
    LArc("Delay_st","Delay_s1",	"--", 	"y1"),
    LArc("Delay_s1","00",		"x1",	"--"),
    LArc("Delay_s1","Delay_s1",	"^x1",	"y2"),
    LArc()
  };

CFDelay::CFDelay(long lD, LFsaAppl *pL):LFsaAppl(DelayTBL, "CFDelay", nullptr)
{
    pLFsaAppl = pL;
    int dT;
    dT = pLFsaAppl->pTAppCore->pCVarSetting->dDeltaTime;
    if (dT>0) {
        nAccount = lD/dT;
    }
}

CFDelay::~CFDelay() {}

void CFDelay::FResetActions() {
    lDelay = 0;
}

int CFDelay::x1()
{
//    Serial.print("CFDelay::x1()");
//    Serial.printf("nAccount- %d", nAccount);
//    Serial.print(nAccount);
    return nAccount == 0;
}

void CFDelay::y1() { }

void CFDelay::y2() {
//    Serial.print("<CFDelay:y2()>");
    if (nAccount)
    nAccount--;
}
