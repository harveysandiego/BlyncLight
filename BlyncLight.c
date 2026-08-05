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
bool set_light_color(const char *color, int device_index) {
    if (strcmp(color, "red") == 0) {
        return TurnOnRedLight(device_index);
    } else if (strcmp(color, "green") == 0) {
        return TurnOnGreenLight(device_index);
    } else if (strcmp(color, "blue") == 0) {
        return TurnOnBlueLight(device_index);
    } else if (strcmp(color, "cyan") == 0) {
        return TurnOnCyanLight(device_index);
    } else if (strcmp(color, "magenta") == 0) {
        return TurnOnMagentaLight(device_index);
    } else if (strcmp(color, "yellow") == 0) {
        return TurnOnYellowLight(device_index);
    } else if (strcmp(color, "white") == 0) {
        return TurnOnWhiteLight(device_index);
    } else if (strcmp(color, "orange") == 0) {
        return TurnOnOrangeLight(device_index);
    } else {
        printf("Unknown color: %s\n", color);
        return false;
    }
}

// Function to flash the light at a specific speed
bool flash_light(int device_index, const char *speed) {
    byte flash_speed;
    if (strcmp(speed, "low") == 0) {
        flash_speed = 0x01;
    } else if (strcmp(speed, "medium") == 0) {
        flash_speed = 0x02;
    } else if (strcmp(speed, "high") == 0) {
        flash_speed = 0x03;
    } else if (strcmp(speed, "pulse") == 0) {
        flash_speed = 0x04;
    } else {
        printf("Unknown flash speed: %s\n", speed);
        return false;
    }

    if (!SelectLightFlashSpeed(device_index, flash_speed)) {
        return false;
    }
    return StartLightFlash(device_index);
}

void log_succeeded(bool succeeded) {
    printf("Command %s\n", succeeded ? "succeeded" : "failed");
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
                log_succeeded(ResetLight(i));
            }
        } else if (strcmp(argv[2], "flash") == 0) {
            if (argc != 4) {
                printf("Missing speed:\n");
                printf("  flash <speed> - Flash the light at a speed (low, medium, high, pulse)\n");
                return 1;
            }
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(flash_light(i, argv[3]));
            }
        } else if (strcmp(argv[2], "stop_flash") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(StopLightFlash(i));
            }
        } else if (strcmp(argv[2], "dim") == 0) {
            for (int i = 0; i < num_devices; i++) {
				log_succeeded(SetLightDim(i));
            }
        } else if (strcmp(argv[2], "clear_dim") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(ClearLightDim(i));
            }
        } else if (strcmp(argv[2], "music") == 0) {
            if (argc != 4) {
                printf("Missing number:\n");
                printf("  music <number> - Play music track <number>\n");
                return 1;
            }
            int music_number = atoi(argv[3]);
            for (int i = 0; i < num_devices; i++) {
                bool cmdA = SelectMusicToPlay(i, (byte)music_number);
                bool cmdB = StartMusicPlay(i);
                log_succeeded(cmdA && cmdB);
            }
        } else if (strcmp(argv[2], "stop_music") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(StopMusicPlay(i));
            }
        } else if (strcmp(argv[2], "repeat") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(SetMusicRepeat(i));
            }
        } else if (strcmp(argv[2], "clear_repeat") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(ClearMusicRepeat(i));
            }
        } else if (strcmp(argv[2], "volume") == 0) {
            if (argc != 4) {
                printf("Missing level:\n");
                printf("  volume <level> - Set volume level (1-10)\n");
                return 1;
            }
            int volume_level = atoi(argv[3]);
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(SetMusicVolume(i, (byte)volume_level));
            }
        } else if (strcmp(argv[2], "mute") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(SetVolumeMute(i));
            }
        } else if (strcmp(argv[2], "unmute") == 0) {
            for (int i = 0; i < num_devices; i++) {
                log_succeeded(ClearVolumeMute(i));
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
                log_succeeded(TurnOnRGBLights(i, (byte)red, (byte)green, (byte)blue));
            }
        } else {
            for (int i = 0; i < num_devices; i++) {
                char* color = argv[2];
                log_succeeded(set_light_color(color, i));
            }
        }
    }
    // If the user specifies a single device index
    else {
        int device_index = atoi(argv[1]);
        if (device_index >= 0 && device_index < num_devices) {
            if (strcmp(argv[2], "reset") == 0) {
                log_succeeded(ResetLight(device_index));
            } else if (strcmp(argv[2], "flash") == 0) {
                if (argc != 4) {
                    printf("Missing speed:\n");
                    printf("  flash <speed> - Flash the light at a speed (low, medium, high, pulse)\n");
                    return 1;
                }
                log_succeeded(flash_light(device_index, argv[3]));
            } else if (strcmp(argv[2], "stop_flash") == 0) {
                log_succeeded(StopLightFlash(device_index));
            } else if (strcmp(argv[2], "dim") == 0) {
				log_succeeded(SetLightDim(device_index));
            } else if (strcmp(argv[2], "clear_dim") == 0) {
                log_succeeded(ClearLightDim(device_index));
            } else if (strcmp(argv[2], "music") == 0) {
                if (argc != 4) {
                    printf("Missing number:\n");
                    printf("  music <number> - Play music track <number>\n");
                    return 1;
                }
                int music_number = atoi(argv[3]);
                bool cmdA = SelectMusicToPlay(device_index, (byte)music_number);
                bool cmdB = StartMusicPlay(device_index);
                log_succeeded(cmdA && cmdB);
            } else if (strcmp(argv[2], "stop_music") == 0) {
                log_succeeded(StopMusicPlay(device_index));
            } else if (strcmp(argv[2], "repeat") == 0) {
                log_succeeded(SetMusicRepeat(device_index));
            } else if (strcmp(argv[2], "clear_repeat") == 0) {
                log_succeeded(ClearMusicRepeat(device_index));
            } else if (strcmp(argv[2], "volume") == 0) {
                if (argc != 4) {
                    printf("Missing level:\n");
                    printf("  volume <level> - Set volume level (1-10)\n");
                    return 1;
                }
                int volume_level = atoi(argv[3]);
                log_succeeded(SetMusicVolume(device_index, (byte)volume_level));
            } else if (strcmp(argv[2], "mute") == 0) {
                log_succeeded(SetVolumeMute(device_index));
            } else if (strcmp(argv[2], "unmute") == 0) {
                log_succeeded(ClearVolumeMute(device_index));
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
                log_succeeded(TurnOnRGBLights(device_index, (byte)red, (byte)green, (byte)blue));
            } else {
                log_succeeded(set_light_color(argv[2], device_index));
            }
        } else {
            printf("Invalid device index: %d\n", device_index);
        }
    }

    CloseDevices(num_devices);

    return 0;
}
