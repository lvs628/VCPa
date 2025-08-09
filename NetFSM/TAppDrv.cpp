#include "stdafx.h"
#include "tappdrv.h"
#include "TAppCore.h"
#include "TSetVarRead.h"

TAppDrv::TAppDrv(TAppCore *pT)
{
	pTAppCore	= pT;
    pSetVarRead	= 0;		// ������ �������� ����������

    ReloadVCPa();
}

TAppDrv::~TAppDrv(void)
{
	if (pTAppCore->bSaveSensors) {
		pSetVarRead->SetSaveSet(true);
	}
    if (pSetVarRead)
        delete pSetVarRead;
    pSetVarRead = NULL;
}

void TAppDrv::SetSaveSet(void)
{
	pSetVarRead->SetSaveSet(true);
}

bool TAppDrv::LinkVar()
{
	pTAppCore->LinkVar();
	pSetVarRead->CreateLink();
	return true;
}

void TAppDrv::SaveConfiguration(void)
{
	if (pSetVarRead) {
		pSetVarRead->SetSaveSet(true);
		if (pSetVarRead->IfSave()) {
			pSetVarRead->SaveDat();
			pSetVarRead->SetSaveSet(false);
		}
	}
}

void TAppDrv::ReloadVCPa(void)
{
	if (pSetVarRead) delete pSetVarRead;
	pSetVarRead = NULL;

	pSetVarRead		= new TSetVarRead(this, "Read");	

}
