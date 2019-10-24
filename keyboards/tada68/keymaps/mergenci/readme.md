# Mergenci's TADA68 layout

The original version that was developed before the fork was based on v0.6.440, commit 
13493d3a78ebb05c4012f908a2ec2575d74e49aa. In case of an unexpected behavior, try that 
version.

Original build and install instructions are at `qmk_firmware/keyboards/tada68/readme.md`.

0. Change directory into `qmk_firmware`.

1. To compile, run:
```
make tada68:default:flashbin
```

2. Mount keyboard as an external drive by clicking on the reset button on its back.

3. Don't use Finder to copy compiled FLASH.bin file, or to see what's inside the 
   keyboard filesystem, because it creates system files and directories inside, 
   therefore messing with the function of keyboard. Delete any files or directories 
   other than FLASH.bin using a command line:
```
cd /Volumes/TADA68\ \ 
rm -fr .Trashes/ .fseventsd/ ._.Trashes ._FLASH.bin
cd / # To stop using the drive so that it could be ejected.
```

4. Inside `qmk_firmware` directory, copy compiled FLASH.bin using command:
```
cp -r FLASH.bin /Volumes/TADA68\ \ 
```

5. Eject TADA68 drive from Finder, or hit ESC on the keyboard.

6. Keyboard should be working now. If not disconnect and reconnect.
