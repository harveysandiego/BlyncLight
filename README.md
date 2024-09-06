# README

Command line utility for controlling Embrava BlyncLights on Linux.

## Build
`make all`

## Usage

```
Usage: ./BlyncLight <device_index|all> <command> [options]
Commands:
  reset - Turn off the light.
  <color> - Set a color (red, green, blue, cyan, magenta, yellow, white, orange)
  rgb <r> <g> <b> - Set RGB color values (0-255)
  flash <speed> - Flash the light at a speed (low, medium, high, pulse)
  stop_flash - Stop flashing the light
  dim - Dim the light by 50%
  clear_dim - Clear the dim effect
  music <number> - Play music track <number>
  stop_music - Stop playing music
  repeat - Set music repeat
  clear_repeat - Clear music repeat
  volume <level> - Set volume level (1-10)
  mute - Mute the volume
  unmute - Unmute the volume
  info - List device's unique IDs and types
```
