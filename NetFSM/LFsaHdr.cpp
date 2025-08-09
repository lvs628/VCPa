#include "stdafx.h"
#include "LFsaHdr.h"

LFsaHdr::LFsaHdr(void)
{
    pLFsaAppl		= nullptr;
    strNameLFsaAppl	= "";
    pNetFsa			= nullptr;
    nNumInArray		= 0;
    strNameCVarFSA	= "";
}

LFsaHdr::~LFsaHdr(void)
{
}
bool LFsaHdr::operator==(const LFsaHdr &var) const
{
    if (pLFsaAppl==var.pLFsaAppl) return true;
    else return false;
}

bool LFsaHdr::operator<(const LFsaHdr &var) const
{
    return strNameLFsaAppl<var.strNameLFsaAppl;
}

bool LFsaHdr::operator!=(const LFsaHdr &var) const
{
    if (pLFsaAppl!=var.pLFsaAppl) return true;
    else return false;
}

bool LFsaHdr::operator>(const LFsaHdr &var) const
{
    return strNameLFsaAppl>var.strNameLFsaAppl;
}

LFsaHdr::LFsaHdr(const LFsaHdr &var)
{
    pLFsaAppl		= var.pLFsaAppl;
    strNameLFsaAppl	= var.strNameLFsaAppl;
    pNetFsa			= var.pNetFsa;
    nNumInArray		= var.nNumInArray;
    strNameCVarFSA	= var.strNameCVarFSA;
}
