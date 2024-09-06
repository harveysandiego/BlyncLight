#ifndef EMBRAVAAPI_H
#define EMBRAVAAPI_H

#include <stdbool.h>
#include "constants.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef unsigned char byte;
    typedef unsigned char Byte;

    typedef struct _sDeviceInfo
    {
        char *pchDeviceName;
        char *pchDeviceId;
        unsigned char byDeviceType;
        char path[255];
        hid_device *pHandle;
        int nDeviceIndex;

    } SDeviceInfo, *PSDeviceInfo;

    SDeviceInfo aosDeviceInfo[10];

    void InitBlyncDevices(int *PnNumberOfBlyncDevices, SDeviceInfo aosDeviceInfo[]);
    void CloseDevices(int nNumberOfDevices);
    bool ResetLight(int nDeviceIndex);
    bool TurnOnRedLight(int nDeviceIndex);
    bool TurnOnGreenLight(int nDeviceIndex);
    bool TurnOnBlueLight(int nDeviceIndex);
    bool TurnOnCyanLight(int nDeviceIndex);
    bool TurnOnMagentaLight(int nDeviceIndex);
    bool TurnOnYellowLight(int nDeviceIndex);
    bool TurnOnWhiteLight(int nDeviceIndex);
    bool TurnOnOrangeLight(int nDeviceIndex);
    bool TurnOnRGBLights(int nDeviceIndex, byte byRedLevel, byte byGreenLevel, byte byBlueLevel);
    bool SetLightDim(int nDeviceIndex);
    bool ClearLightDim(int nDeviceIndex);
    bool SelectLightFlashSpeed(int nDeviceIndex, Byte bySelectedFlashSpeed);
    bool StartLightFlash(int nDeviceIndex);
    bool StopLightFlash(int nDeviceIndex);
    bool SelectMusicToPlay(int nDeviceIndex, Byte bySelectedMusic);
    bool StartMusicPlay(int nDeviceIndex);
    bool StopMusicPlay(int nDeviceIndex);
    bool SetMusicRepeat(int nDeviceIndex);
    bool ClearMusicRepeat(int nDeviceIndex);
    bool SetMusicVolume(int nDeviceIndex, Byte byVolumeLevel);
    bool SetVolumeMute(int nDeviceIndex);
    bool ClearVolumeMute(int nDeviceIndex);
    unsigned int GetDeviceUniqueId (int nDeviceIndex);

#ifdef __cplusplus
}
#endif

#endif // EMBRAVAAPI_H
