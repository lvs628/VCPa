#ifndef CSetLFsaHdr_H
#define CSetLFsaHdr_H

#include "LFsaHdr.h"

class CSetLFsaHdr
{
public:
	LFsaHdr* GetAdressHdrFsa(int n);			// ����� ��������� �� ������ �� ��������� ��������
	LFsaHdr* GetAdressHdrFsa(LFsaAppl *pL);			// ����� ��������� �� ������ �� ��������� ��������
	void Add(LFsaAppl *pL, string str, TNetFsa	*pN, int n);
	void Add(LFsaHdr &var);
	bool Clear(LFsaHdr &var);
	int Size();
	CSetLFsaHdr(void);
	~CSetLFsaHdr(void);
	LFsaHdr& operator[] (int i);
private:
	CArrayLFsaHdr	ArrayFsaHdr;// ������ �������� ��������
	int nNumElement;
};

#endif // DEFINETYPES_H
