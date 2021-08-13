target remote localhost:3333
monitor reset init
monitor flash write_image erase final.elf
monitor reset