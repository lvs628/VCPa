
// FDelay.h: interface for the CFDelay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FDELAY_H)
#define AFX_FDELAY_H

#pragma once
#include "lfsaappl.h"
#include "ctime.h"

class CFDelay : public LFsaAppl
{
public:
    void FResetActions();
    CFDelay(long lD, LFsaAppl *pL);
    virtual ~CFDelay();

protected:
    int x1();
    void y1();
    void y2();

protected:
    double lDelay;
    double dDelta;
    LFsaAppl *pLFsaAppl{nullptr};
    int nAccount{0};
};

#endif // !defined(AFX_FDELAY_H)
