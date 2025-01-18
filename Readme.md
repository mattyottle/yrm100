'C:\Program Files\usbipd-win\usbipd.exe' list
'C:\Program Files\usbipd-win\usbipd.exe' bind -b 1-1
'C:\Program Files\usbipd-win\usbipd.exe' bind -b 2-1

& 'C:\Program Files\usbipd-win\usbipd.exe' attach -a -b 1-1 -w


sudo chmod 666 /dev/ttyACM0 /dev/ttyACM1
sudo chmod 666 /dev/bus/usb/001/010

 udevadm info -a -n /dev/ttyACM* | grep -i vendor


./fbt flash_usb FLIP_PORT=/dev/ttyACM0
./fbt launch APPSRC=applications_user/yrm100
./fbt fap_dist
./fbt fap_dist APPSRC=applications_user/yrm100


sudo chmod 666 /dev/ttyACM0 /dev/ttyACM1


lsusb
ls -l /dev/ttyACM*
lsusb -v -d 303a:4002
 udevadm info -a -n /dev/ttyACM1 | grep -i vendor
lsof /dev/ttyACM1
sudo udevadm control --reload-rules


sudo /home/username/vscode/official-firmware/toolchain/current/bin/openocd \
    -f interface/cmsis-dap.cfg \
    -f ./scripts/debug/stm32wbx.cfg \
    -c "cmsis-dap vid_pid 0x303a 0x4002" \
    -c "transport select swd" \
    -c "adapter speed 1000" \
    -c "init" \
    -c "reset halt"


./fbt fap_yrm100


nano ~/.bashrc
source ~/.bashrc

../../scripts/storage.py list /ext/apps/misc
 ../../scripts/storage.py remove /ext/apps/misc/yrm100.fap
../../scripts/storage.py list /ext/apps/misc

# transfer fap to flipper
../../scripts/storage.py send ~/.ufbt/build/yrm100.fap /ext/apps/misc/yrm100.fap
  
   openocd -f interface/cmsis-dap.cfg -f target/stm32wbx.cfg
   
   
   find . -type f -exec sh -c 'echo "Filename: $1"; cat "$1"' _ {} \;
./fbt build APPSRC=applications_user/yrm100 DEBUG=yes LIB_DEBUG=yes
# builds the app with an elf, not clear if the elf has to be deleted first                                                                                                                                                                                                                                                                                                              , 

arm-none-eabi-gdb build/f7-firmware-D/.extapps/yrm100_d.elf

openocd   -f interface/cmsis-dap.cfg   -f target/stm32wbx.cfg   -c "stm32wbx.cpu configure -rtos auto"


 target remote localhost:3333
 monitor reset halt
 monitor reset run
 
 screen /dev/ttyACM1 115200  //attach to flipper for log


# GDB Debugging
Method 1 - Command line:
```
arm-none-eabi-gdb -ex "add-symbol-file build/f7-firmware-D/firmware.elf" build/f7-firmware-D/.extapps/yrm100_d.elf
```

Method 2 - GDB session:
```
file build/f7-firmware-D/.extapps/yrm100_d.elf   # Load first ELF
add-symbol-file build/f7-firmware-D/firmware.elf  # Add second ELF
target remote localhost:3333
monitor reset halt
```

# gdb check memory mappings
info proc mappings
maintenance info sections



# reset with openocd
telnet localhost 4444
reset run
exit