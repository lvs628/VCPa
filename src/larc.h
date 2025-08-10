#ifndef LARC_H
#define LARC_H

#include <string>
using namespace std;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                             LArc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class LArc
{
 public:
    LArc();
    LArc(const char[], const char[], const char[], const char[]);
    ~LArc();
 public:
    const char* szSt1{nullptr}, *szSt2{nullptr};
    const char* szMX{nullptr}, *szMY{nullptr};
    unsigned long ulMx{0},ulRx{0},ulMy{0};
};

#endif // LARC_H
