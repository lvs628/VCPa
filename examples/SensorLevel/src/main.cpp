#include "Config.h"
#include <Arduino.h>
#if defined(IF_USING_FSM)
#include <TAppProcesses.h>        // ядро интерпретации автоматов
#endif
void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200); Serial.println();
  Serial.println("Demo project - SensorLevelFSM");
#if defined(IF_USING_FSM)
// создаем среду для автоматов
  VCPaCore_init();                // создание ядра FSM
// загружаем автоматные процессы  
  LoadingFsaProsesses();
  string str = "Setting1";
  CVarSetting *pVarSet = pTAppProcesses->pSetVarSetting->GetAddressVar(str);
  #if defined(IF_USING_FSM_MAX_SPEED)
    if (pVarSet) { pVarSet->dDeltaTime = 2; }          // дискретное время процессов - 2 мсек
  #else
    if (pVarSet) { pVarSet->dDeltaTime = 10; }          // дискретное время процессов - t1 = 10 мсек
  #endif
#endif
}
#if defined(IF_USING_FSM)
#include <SensorLevel.h>
  #if defined(IF_SENSOR_1)
  // указатель на автомат, созданный в  LoadFsaProcesses
  extern SensorLevel *pSensorLevel;
  // для сохранения текущего состояния автомата
  // используется, когда разрешено отображение состояния (см. ниже)
  String strSavNameState1 = "";
  #endif
  #if defined(IF_SENSOR_2)
  extern SensorLevel *pSensorLevel2;
  String strSavNameState2 = "";
  #endif
#endif
// отображать состояния процессов (см. создание процессов в LoadFsaProcesses)
//#define IF_VIEW_STATE_SENSORLEVEL1      
//#define IF_VIEW_STATE_SENSORLEVEL2      
void loop() {
#if defined(IF_USING_FSM)
// моделирование дискретного времени сети автоматов 
  VCPaCore_TimerEvent(0);
  #if defined(IF_VIEW_STATE_SENSORLEVEL1)
    String strState1 = pSensorLevel->FGetState().c_str();
    if (strSavNameState1 != strState1) {
      strSavNameState1 = strState1;
      Serial.printf("%s(%s)\n", pSensorLevel->FGetNameVarFSA().c_str(), strState1);
    }
  #endif
  #if defined(IF_VIEW_STATE_SENSORLEVEL2)
    String strState2 = pSensorLevel2->FGetState().c_str();
    if (strSavNameState2 != strState2) {
      strSavNameState2 = strState2;
      Serial.printf("%s(%s)\n", pSensorLevel2->FGetNameVarFSA().c_str(), strState2);
    }
  #endif
#else
// запуск обычной функции LevelView()
  #if defined(IF_SENSOR_1)
  unsigned long lastUpdateTimeLevel = 0;
  const long updateIntervalLevel = 1000;
    if (millis() - lastUpdateTimeLevel >= updateIntervalLevel) {
      lastUpdateTimeLevel = millis();
      // читаем входы датчика уровня  
      void LevelView();
      LevelView();
    }
  #endif
#endif
}
