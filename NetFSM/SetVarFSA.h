#ifndef __CSETVARFSA_H
#define __CSETVARFSA_H

#include <string>
using namespace std;
#include "VarFSA.h"
#include "SetVar.h"

class TAppCore;
class CSetVarFSA :
	public CSetVar
{
public:
	void SetSaveSet(bool b);
    CSetVarFSA(TAppCore *pInfo, string strNam);
	~CSetVarFSA(void);
	LFsaAppl* GetAddressFsa(string strNam);
	void UpdateLinks(string name, int nT);
	void CreateProcesses();
    void CreateLink();
	bool CreateLink(TNetFsa *pNet, CVarFSA &var);
	bool LoadAllFsa();
	bool LoadFsa(string strNam);
	LFsaAppl* LoadFsa(string strNam, LFsaAppl *pFsa);
    bool Add(CVarFSA &var);
    bool Replace(CVarFSA &var);
    bool Delete(CVarFSA &var);
    CVarFSA* GetAddressVar(string nam);
	CVarFSA* GetAddressVar(string nam, string lib, string fsa="");
	CArrayVarFSA *pArray;
};

#endif //__CSETVARFSA_H
