// LConvStr.cpp: implementation of the LConvStr class.
//
//////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include <memory.h>
#include <stdlib.h>
#include "LConvStr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LConvStr::LConvStr()
{
 Str = nullptr; strSep =";";
 strSav= "";
}

LConvStr::LConvStr(string& str)
{
#if defined (ARDUINO_ARCH_ESP32)    
	if (str.length() > sizeof(ach))
		Serial.println("LConvStr: Long string!");
#endif    
	Str = &str; strSep =";";
	strSav= str;
}

LConvStr::~LConvStr() {
 Str = nullptr;
}

LConvStr::operator int() 
{
	if (Parse()) return atoi(ach);
	return 0;
}

LConvStr::operator bool() 
{
	int N;
	if (Parse()) N = atoi(ach);
	else return false;
	if (!N) return false;
	else return true;
}

LConvStr::operator unsigned int() 
{
    if (Parse()) return uint(atoi(ach));
	return 0;
}

LConvStr::operator long() 
{
	if (Parse()) return atol(ach);
	return 0;
}

LConvStr::operator string() 
{
	if (Parse()) return string(ach);
	return "";
}

LConvStr::operator double() 
{
    if (Parse()) return stod(ach);
	return 0;
}

bool LConvStr::Parse()
{
	int nFl, n, nStart, nEnd;
	memset(ach,'\0',sizeof(ach));
    if (*Str=="") return false;
    if ((*Str)[0]==strSep[0]) {
        Str->erase(0,1);
        return true;
		}
    nStart=int(Str->find_first_not_of(strSep));
	if (nStart<0) return false;
    nFl=nEnd=int(Str->find_first_of(strSep));
    if (nEnd<0) nEnd = int(Str->size());
	n= nEnd-nStart; 
    Str->copy(ach,uint(n),uint(nStart));
	ach[n]=0; 
	if (nFl<0) {
        Str->erase(0,uint(n));
	}
    else Str->erase(0,uint(n+1));
	return true;

}

string LConvStr::SetSeparator(string str)
{	
	string Str;
	Str = strSep;
	strSep = str;
	return Str;
}

string LConvStr::SetStr(string str)
{	
    Str = &str; strSep =";";
	strSav= str;
	return strSav;
}

bool LConvStr::operator !()
{
	int nFl;
    nFl=int(Str->find_first_of(strSep));
	if (nFl<0) return false;
	else return true;
}
