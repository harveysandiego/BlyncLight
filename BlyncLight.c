#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EmbravaApi/hidapi.h"
#include "EmbravaApi/embravaapi.h"
#include "EmbravaApi/constants.h"

extern SDeviceInfo aosDeviceInfo[MAX_DEVICES_SUPPORTED];

// Function to get the string name of the device type based on its ID
const char* get_device_type_name(unsigned char device_type) {
    switch (device_type) {
        case DEVICETYPE_BLYNC_CHIPSET_TENX_10:
            return "Blync Chipset TenX 10";
        case DEVICETYPE_BLYNC_CHIPSET_TENX_20:
            return "Blync Chipset TenX 20";
        case DEVICETYPE_BLYNC_CHIPSET_V30:
            return "Blync Chipset V30";
        case DEVICETYPE_BLYNC_CHIPSET_V30S:
            return "Blync Chipset V30S";
        case DEVICETYPE_BLYNC_HEADSET_CHIPSET_V30_LUMENA110:
            return "Blync Headset Chipset Lumena110";
        case DEVICETYPE_BLYNC_WIRELESS_CHIPSET_V30S:
            return "Blync Wireless Chipset V30S";
        case DEVICETYPE_BLYNC_MINI_CHIPSET_V30S:
            return "Blync Mini Chipset V30S";
        case DEVICETYPE_BLYNC_HEADSET_CHIPSET_V30_LUMENA120:
            return "Blync Headset Chipset Lumena120";
        case DEVICETYPE_BLYNC_HEADSET_CHIPSET_V30_LUMENA:
            return "Blync Headset Chipset Lumena";
        case DEVICETYPE_BLYNC_HEADSET_CHIPSET_V30_LUMENA210:
            return "Blync Headset Chipset Lumena210";
        case DEVICETYPE_BLYNC_HEADSET_CHIPSET_V30_LUMENA220:
            return "Blync Headset Chipset Lumena220";
        case DEVICETYPE_BLYNC_EMBRAVA_EMBEDDED_V30:
            return "Blync Embedded Device V30";
        case DEVICETYPE_BLYNC_MINI_CHIPSET_V40S:
            return "Blync Mini Chipset V40S";
        case DEVICETYPE_BLYNC_WIRELESS_CHIPSET_V40S:
            return "Blync Wireless Chipset V40S";
        case DEVICETYPE_BLYNC_CHIPSET_V40:
            return "Blync Chipset V40";
        case DEVICETYPE_BLYNC_CHIPSET_V40S:
            return "Blync Chipset V40S";
        case DEVICETYPE_BLYNC_NAMEDISPLAY_DEVICE:
            return "Blync Named Display Device";
        case DEVICETYPE_BLYNC_PLANTRONICS_STATUS_INDICATOR:
            return "Blync Plantronics Status Indicator";
        case DEVICETYPE_BLYNC_MINI_CHIPSET_V40S_VERSION20:
            return "Blync Mini Chipset V40S Version 2.0";
        case DEVICETYPE_BLYNC_CHIPSET_V40_VERSION20:
            return "Blync Chipset V40 Version 2.0";
        case DEVICETYPE_BLYNC_CHIPSET_V40S_VERSION20:
            return "Blync Chipset V40S Version 2.0";
        default:
            return "Unknown Device Type";
    }
}

// Function to set a color for a specific device
void set_light_color(const char *color, int device_index) {
    if (strcmp(color, "red") == 0) {
        TurnOnRedLight(device_index);
    } else if (strcmp(color, "green") == 0) {
        TurnOnGreenLight(device_index);
    } else if (strcmp(color, "blue") == 0) {
        TurnOnBlueLight(device_index);
    } else if (strcmp(color, "cyan") == 0) {
        TurnOnCyanLight(device_index);
    } else if (strcmp(color, "magenta") == 0) {
        TurnOnMagentaLight(device_index);
    } else if (strcmp(color, "yellow") == 0) {
        TurnOnYellowLight(device_index);
    } else if (strcmp(color, "white") == 0) {
        TurnOnWhiteLight(device_index);
    } else if (strcmp(color, "orange") == 0) {
        TurnOnOrangeLight(device_index);
    } else {
        printf("Unknown color: %s\n", color);
    }
}

// Function to flash the light at a specific speed
void flash_light(int device_index, const char *speed) {
    if (strcmp(speed, "low") == 0) {
        SelectLightFlashSpeed(device_index, 0x01);
    } else if (strcmp(speed, "medium") == 0) {
        SelectLightFlashSpeed(device_index, 0x02);
    } else if (strcmp(speed, "high") == 0) {
        SelectLightFlashSpeed(device_index, 0x03);
    } else if (strcmp(speed, "pulse") == 0) {
        SelectLightFlashSpeed(device_index, 0x04);
    } else {
        printf("Unknown flash speed: %s\n", speed);
    }
    StartLightFlash(device_index);
}

int main(int argc, char *argv[]) {
    int num_devices = 0;

    // Initialize the Blync devices
    InitBlyncDevices(&num_devices, aosDeviceInfo);

    if (num_devices == 0) {
        printf("No devices found.\n");
        return 1;
    }

    if (argc < 3) {
        printf("Usage: %s <device_index|all> <command> [options]\n", argv[0]);
        printf("Commands:\n");
        printf("  reset - Turn off the light.\n");
        printf("  <color> - Set a color (red, green, blue, cyan, magenta, yellow, white, orange)\n");
        printf("  rgb <r> <g> <b> - Set RGB color values (0-255)\n");
        printf("  flash <speed> - Flash the light at a speed (low, medium, high, pulse)\n");
        printf("  stop_flash - Stop flashing the light\n");
        printf("  dim - Dim the light by 50%%\n");
        printf("  clear_dim - Clear the dim effect\n");
        printf("  music <number> - Play music track <number>\n");
        printf("  stop_music - Stop playing music\n");
        printf("  repeat - Set music repeat\n");
        printf("  clear_repeat - Clear music repeat\n");
        printf("  volume <level> - Set volume level (1-10)\n");
        printf("  mute - Mute the volume\n");
        printf("  unmute - Unmute the volume\n");
        printf("  info - List device's unique IDs and types\n");
        return 1;
    }

    // If the user specifies "all"
    if (strcmp(argv[1], "all") == 0) {
        if (strcmp(argv[2], "reset") == 0) {
            for (int i = 0; i < num_devices; i++) {
                ResetLight(i);
            }
        } else if (strcmp(argv[2], "flash") == 0) {
            if (argc != 4) {
                printf("Missing speed:\n");
                printf("  flash <speed> - Flash the light at a speed (low, medium, high, pulse)\n");
                return 1;
            }
            for (int i = 0; i < num_devices; i++) {
                flash_light(i, argv[3]);
            }
        } else if (strcmp(argv[2], "stop_flash") == 0) {
            for (int i = 0; i < num_devices; i++) {
                StopLightFlash(i);
            }
        } else if (strcmp(argv[2], "dim") == 0) {
            for (int i = 0; i < num_devices; i++) {
				SetLightDim(i);
            }
        } else if (strcmp(argv[2], "clear_dim") == 0) {
            for (int i = 0; i < num_devices; i++) {
                ClearLightDim(i);
            }
        } else if (strcmp(argv[2], "music") == 0) {
            if (argc != 4) {
                printf("Missing number:\n");
                printf("  music <number> - Play music track <number>\n");
                return 1;
            }
            int music_number = atoi(argv[3]);
            for (int i = 0; i < num_devices; i++) {
                SelectMusicToPlay(i, (byte)music_number);
                StartMusicPlay(i);
            }
        } else if (strcmp(argv[2], "stop_music") == 0) {
            for (int i = 0; i < num_devices; i++) {
                StopMusicPlay(i);
            }
        } else if (strcmp(argv[2], "repeat") == 0) {
            for (int i = 0; i < num_devices; i++) {
                SetMusicRepeat(i);
            }
        } else if (strcmp(argv[2], "clear_repeat") == 0) {
            for (int i = 0; i < num_devices; i++) {
                ClearMusicRepeat(i);
            }
        } else if (strcmp(argv[2], "volume") == 0) {
            if (argc != 4) {
                printf("Missing level:\n");
                printf("  volume <level> - Set volume level (1-10)\n");
                return 1;
            }
            int volume_level = atoi(argv[3]);
            for (int i = 0; i < num_devices; i++) {
                SetMusicVolume(i, (byte)volume_level);
            }
        } else if (strcmp(argv[2], "mute") == 0) {
            for (int i = 0; i < num_devices; i++) {
                SetVolumeMute(i);
            }
        } else if (strcmp(argv[2], "unmute") == 0) {
            for (int i = 0; i < num_devices; i++) {
                ClearVolumeMute(i);
            }
        } else if (strcmp(argv[2], "info") == 0) {
            for (int i = 0; i < num_devices; i++) {
                printf("Device %d:\n", i);
                printf("  Unique ID: %u\n", GetDeviceUniqueId(i));
                printf("  Device Type: %s\n", get_device_type_name(aosDeviceInfo[i].byDeviceType));
                printf("  Device Name: %s\n", aosDeviceInfo[i].pchDeviceName);
            }
        } else if (strcmp(argv[2], "rgb") == 0) {
            if (argc != 6) {
                printf("Missing r,g,b:\n");
                printf("  rgb <r> <g> <b> - Set RGB color values (0-255)\n");
                return 1;
            }
            for (int i = 0; i < num_devices; i++) {
                int red = atoi(argv[3]);
                int green = atoi(argv[4]);
                int blue = atoi(argv[5]);
                TurnOnRGBLights(i, (byte)red, (byte)green, (byte)blue);
            }
        } else {
            for (int i = 0; i < num_devices; i++) {
                char* color = argv[2];
                set_light_color(color, i);
            }
        }
    }
    // If the user specifies a single device index
    else {
        int device_index = atoi(argv[1]);
        if (device_index >= 0 && device_index < num_devices) {
            if (strcmp(argv[2], "reset") == 0) {
                ResetLight(device_index);
            } else if (strcmp(argv[2], "flash") == 0) {
                if (argc != 4) {
                    printf("Missing speed:\n");
                    printf("  flash <speed> - Flash the light at a speed (low, medium, high, pulse)\n");
                    return 1;
                }
                flash_light(device_index, argv[3]);
            } else if (strcmp(argv[2], "stop_flash") == 0) {
                StopLightFlash(device_index);
            } else if (strcmp(argv[2], "dim") == 0) {
				SetLightDim(device_index);
            } else if (strcmp(argv[2], "clear_dim") == 0) {
                ClearLightDim(device_index);
            } else if (strcmp(argv[2], "music") == 0) {
                if (argc != 4) {
                    printf("Missing number:\n");
                    printf("  music <number> - Play music track <number>\n");
                    return 1;
                }
                int music_number = atoi(argv[3]);
                SelectMusicToPlay(device_index, (byte)music_number);
                StartMusicPlay(device_index);
            } else if (strcmp(argv[2], "stop_music") == 0) {
                StopMusicPlay(device_index);
            } else if (strcmp(argv[2], "repeat") == 0) {
                SetMusicRepeat(device_index);
            } else if (strcmp(argv[2], "clear_repeat") == 0) {
                ClearMusicRepeat(device_index);
            } else if (strcmp(argv[2], "volume") == 0) {
                if (argc != 4) {
                    printf("Missing level:\n");
                    printf("  volume <level> - Set volume level (1-10)\n");
                    return 1;
                }
                int volume_level = atoi(argv[3]);
                SetMusicVolume(device_index, (byte)volume_level);
            } else if (strcmp(argv[2], "mute") == 0) {
                SetVolumeMute(device_index);
            } else if (strcmp(argv[2], "unmute") == 0) {
                ClearVolumeMute(device_index);
            } else if (strcmp(argv[2], "info") == 0) {
                printf("Device %d:\n", device_index);
                printf("  Unique ID: %u\n", GetDeviceUniqueId(device_index));
                printf("  Device Type: %s\n", get_device_type_name(aosDeviceInfo[device_index].byDeviceType));
                printf("  Device Name: %s\n", aosDeviceInfo[device_index].pchDeviceName);
            } else if (strcmp(argv[2], "rgb") == 0) {
                if (argc != 6) {
                    printf("Missing r,g,b:\n");
                    printf("  rgb <r> <g> <b> - Set RGB color values (0-255)\n");
                    return 1;
                }
                int red = atoi(argv[3]);
                int green = atoi(argv[4]);
                int blue = atoi(argv[5]);
                TurnOnRGBLights(device_index, (byte)red, (byte)green, (byte)blue);
            } else {
                set_light_color(argv[2], device_index);
            }
        } else {
            printf("Invalid device index: %d\n", device_index);
        }
    }

    CloseDevices(num_devices);

    return 0;
}
