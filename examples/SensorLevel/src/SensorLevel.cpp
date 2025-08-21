#include "Config.h"
#include <Arduino.h>
#if defined(IF_USING_FSM)
#include <stdafx.h>
#include "SensorLevel.h"
LArc TBL_SENSORLEVEL[] = {
  LArc("ss",		"ss","^x1^x2",  "y1"), 
  LArc("ss",		"s1","x1",      "y1"), 
  LArc("ss",		"er","x2",      "y3"), 
  LArc("s1",		"ss","--",      "y2"),
  LArc("er",		"er","--",      "y4"),
  LArc()
};
SensorLevel::SensorLevel(string strNam):
  LFsaAppl(TBL_SENSORLEVEL, strNam)
{
// конфигурирование пинов датчика уровня
  pinMode(gpioLevel1, INPUT); pinMode(gpioLevel2, INPUT); pinMode(gpioLevel3, INPUT);
  bIfViewError = false;
}
// ПРЕДИКАТЫ
int SensorLevel::x1() { return nDelay > 0; }
int SensorLevel::x2() { return nDelay < 0; }
// ДЕЙСТВИЯ
void SensorLevel::y1() { LevelView(); }
// создание задержки
void SensorLevel::y2() { FCreateDelay(nDelay); }
// ошибка в задании задержки
void SensorLevel::y3() { Serial.printf("%s(%s):error nDelay=%d\n", FGetNameVarFSA().c_str(), FGetState().c_str(), nDelay); }
void SensorLevel::y4() { 
  if (!bIfViewError) { Serial.printf("%s(%s)\n", FGetNameVarFSA().c_str(), FGetState().c_str()); bIfViewError = true; }
}
// Отображение состояния датчика уровня
void SensorLevel::LevelView()
{
  level1 = digitalRead(gpioLevel1);
  level2 = digitalRead(gpioLevel2);
  level3 = digitalRead(gpioLevel3);
  if (!level1&&level2&&level3) fLevel=30;
  else if (level1&&!level2) fLevel=60;
  else if (!level3) fLevel=90;
  else if (level1&&level2&&level3) fLevel=0;
  else fLevel=-1;
  if (fSavLevel!=fLevel) {
    Serial.printf("%s:Level has changed its state: %.f\n", FGetNameVarFSA().c_str(), fLevel);
    fSavLevel = fLevel;
  }
}
#else
#if defined(IF_SENSOR_1)
// Номера входных пинов датчика
int gpioLevel1{18}; int gpioLevel2{19}; int gpioLevel3{21};
// текущее состояние входов
bool level1{0x0}; bool level2{0x0}; bool level3{0x0}; 
float fLevel{0}; float fSavLevel{-1};
// Отображение состояния датчика уровня
void LevelView()
{
  level1 = digitalRead(gpioLevel1);
  level2 = digitalRead(gpioLevel2);
  level3 = digitalRead(gpioLevel3);
  if (!level1&&level2&&level3) fLevel=30;
  else if (level1&&!level2) fLevel=60;
  else if (!level3) fLevel=90;
  else if (level1&&level2&&level3) fLevel=0;
  else fLevel=-1;
  if (fSavLevel!=fLevel) {
    Serial.printf("Level has changed its state: %.f\n", fLevel);
    fSavLevel = fLevel;
  }
}
#endif
#endif