#include "Config.h"
#if defined(IF_USING_FSM)
#include <TAppProcesses.h>        
#include <SensorLevel.h>
#if defined(IF_SENSOR_1)
SensorLevel *pSensorLevel{nullptr};                             // ссылка на процесс 1
#endif    
#if defined(IF_SENSOR_2)
SensorLevel *pSensorLevel2{nullptr};                             // ссылка на процесс 2
#endif    
void LoadingFsaProsesses() {
#if defined(IF_SENSOR_1)
// создание процесса 1
    pSensorLevel = new SensorLevel("sensor1");                  
// создание описателя процесса (автоматная переменная)
    string vFSA1 = "sensor1;0;0;0;0;InitFsaWorld;1;1";
    static CVarFSA var1(pTAppProcesses,vFSA1);
// загрузка процесса:
//  - выбираем процессу индекс (ячейку) массива процессов
//    сюда ядро поместит ссылку на объект-процесс в ядре
    bool bRet1 = var1.LoadFsa(pSensorLevel); 
// сообщение о загрузке процесса (не обязательно)    
    if (bRet1) Serial.println("Load sensor1");                  
#if defined(IF_USING_FSM_MAX_SPEED)
    pSensorLevel->nDelay = 0;
#else
// устанавливаем параметр задержки процесу   
    pSensorLevel->nDelay = 2000;
// увеличение длительность такта процесса в 10 раз  (t1*t2=100мсек)  
    pSensorLevel->FSetSleep(11);        // t2=110                                
#endif    
#endif    
#if defined(IF_SENSOR_2)
    pSensorLevel2 = new SensorLevel("sensor2");
    string vFSA2 = "sensor2;0;0;0;0;InitFsaWorld;1;1";
    static CVarFSA var2(pTAppProcesses,vFSA2);
    bool bRet2 = var2.LoadFsa(pSensorLevel2);
    if (bRet2) Serial.println("Load sensor2");
#if defined(IF_USING_FSM_MAX_SPEED)
    pSensorLevel->nDelay = 0;
#else
    pSensorLevel2->nDelay = 1000;
#endif    
#endif    
}
#endif