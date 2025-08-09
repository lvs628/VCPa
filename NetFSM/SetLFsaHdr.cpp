#include "SetLFsaHdr.h"
#include <algorithm>

CSetLFsaHdr::CSetLFsaHdr(void)
{
	nNumElement=0;
}

CSetLFsaHdr::~CSetLFsaHdr(void)
{
	 ArrayFsaHdr.clear();
}

int CSetLFsaHdr::Size()
{
	return ArrayFsaHdr.size();
}

void CSetLFsaHdr::Add(LFsaAppl *pL, string str, TNetFsa	*pN, int n)
{
	LFsaHdr var;
	var.pLFsaAppl		= pL;
	var.strNameLFsaAppl	= str;
	var.pNetFsa			= pN;
	var.nNumInArray		= n;
	ArrayFsaHdr.push_back(var);
}
void CSetLFsaHdr::Add(LFsaHdr &var)
{
//	int nn = ArrayFsaHdr.size();
	ArrayFsaHdr.push_back(var);
	nNumElement++;
}
// ����� ��������� �� ������ �� ��������� ��������
LFsaHdr* CSetLFsaHdr::GetAdressHdrFsa(LFsaAppl *pL)
{
//	int nn = ArrayFsaHdr.size();
	LFsaHdr *var;
	CIteratorLFsaHdr next = ArrayFsaHdr.begin();
	while (next != ArrayFsaHdr.end()) {
		var = &*next;
		if ((*next).pLFsaAppl == pL) {
			return var;
		}
		next++;
	}
    return nullptr;
}

// ����� ��������� �� ������ �� ��������� ��������
LFsaHdr* CSetLFsaHdr::GetAdressHdrFsa(int n)
{
    int nn = int(ArrayFsaHdr.size());
    if (n>nn) return nullptr;

	CIteratorLFsaHdr next = ArrayFsaHdr.begin();
	for (int i=0; i<n; i++) {
		next++;
	}
	return &*next;
}

bool CSetLFsaHdr::Clear(LFsaHdr &var)
{
	CIteratorLFsaHdr next=find(ArrayFsaHdr.begin(), ArrayFsaHdr.end(), var);
	if (next!=ArrayFsaHdr.end()) {
		ArrayFsaHdr.erase(next); 
		return true;
		}
	else return false;
}
LFsaHdr& CSetLFsaHdr::operator[] (int n)
{
	LFsaHdr var;
	CIteratorLFsaHdr next = ArrayFsaHdr.begin();
    int nn = int(ArrayFsaHdr.size());
	if (n>nn) return *ArrayFsaHdr.end();

	for (int i=0; i<n; i++) {
		next++;
	}
	return *next;
}
