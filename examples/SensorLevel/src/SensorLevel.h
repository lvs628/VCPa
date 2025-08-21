#ifndef __SENSORLEVEL_H
#define __SENSORLEVEL_H

#if defined(IF_USING_FSM)
#include <lfsaappl.h>
class SensorLevel:public LFsaAppl 
{
public:
    void LevelView();
    SensorLevel(string strNam = "SENSORLEVEL");
    ~SensorLevel() {};
    // Номера выводов для цифровых входов сенсора
    const int gpioLevel1{18};
    const int gpioLevel2{19};
    const int gpioLevel3{21};
    int nDelay{0};
    float fLevel{0};
protected:    
    int x1(); int x2();
    void y1(); void y2(); void y3(); void y4();
    bool level1{false};
    bool level2{false};
    bool level3{false};
    bool bIfViewError{false};
    float fSavLevel{-1};
};
#endif
#endif // __SENSORLEVEL_H
