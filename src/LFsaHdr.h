#ifndef LFsaHdr_h
#define LFsaHdr_h
#pragma once
#include <string>
#include <list>
using namespace std;

class TNetFsa;
class LFsaAppl;
class LFsaHdr {
public:
	int Num() { return nNumInArray; }
	void SetNum(int n) { nNumInArray = n; }
	LFsaHdr(void);
	LFsaHdr(const LFsaHdr& var);
	~LFsaHdr(void);
	LFsaAppl	*pLFsaAppl;
	string		strNameLFsaAppl;
	string		strNameCVarFSA;
	TNetFsa		*pNetFsa;
	bool operator==(const LFsaHdr &var) const;
	bool operator<(const LFsaHdr &var) const;
	bool operator!=(const LFsaHdr &var) const;
	bool operator>(const LFsaHdr &var) const;
private:
	int			nNumInArray;
	friend class CSetLFsaHdr;
};
typedef list<LFsaHdr> CArrayLFsaHdr;
typedef list<LFsaHdr>::iterator CIteratorLFsaHdr;
typedef list<LFsaHdr*> CArrayILFsaHdr;
typedef list<LFsaHdr*>::iterator CIteratorILFsaHdr;
#endif
