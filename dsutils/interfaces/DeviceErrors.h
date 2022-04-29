#ifndef DEVICEERRORS_H
#define DEVICEERRORS_H

enum  DeviceStatus
{
  dsNoError,                  //00
  dsClosed,                   //01
  dsErrorOpen,                //02
  dsErrorRead,                //03
  dsErrorWrite,               //04
  dsErrorMemory,              //05
  dsErrorAlreadyStarted,      //06
  dsErrorNotStarted,          //07
  dsErrorMissingGpioManager,  //08
  dsErrorNoMedia,             //09
  dsErrorTimeout,             //10
  dsErrorInvalidMethod,       //11
  dsErrorNotIdle,             //12
  dsErrorPowerOff,            //13
  dsErrorPowerOn,             //14
  dsErrorFatal                //15
};

inline const char* deviceStatusToString(DeviceStatus ds)
{
  unsigned int ner = static_cast<unsigned int>(ds);
  const char* cszUnknown = "Unknown device error";
  const char* cszStatus[] = {
    "Ok", "Device\'s closed", "Opening error", "Read error", "Write error",
    "Memory access error", "Device's already started", "Device's not started",
    "Missing GPIO manager", "No media for operation", "Operation's timed out",
    "Invalid method used", "Device's not idle", "Cannot power device off",
    "Cannot power device on", "Fatal error arised"
  };

  if (ner <= static_cast<int>(dsErrorFatal)) return cszStatus[ner];
  else return cszUnknown;
}

#endif // DEVICEERRORS_H
