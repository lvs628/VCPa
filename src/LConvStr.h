// LConvStr.h: interface for the LConvStr class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LCONVSTR_H
#define LCONVSTR_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <string>
using namespace std;

class LConvStr
{
public:
	LConvStr();
	LConvStr(string& str);
	virtual ~LConvStr();
	string SetSeparator(string str);
	string SetStr(string str);
	operator int();
	operator unsigned int();
	operator bool();
	operator long();
	operator double();
	operator string();
	bool operator !();
private:
    string	*Str;
    char ach[1024];
    string	strSav;
protected:
	bool Parse();
	string strSep;
};

#endif // !defined(AFX_LCONVSTR_H__77B70602_30CC_11D1_87A5_000001355996__INCLUDED_)
