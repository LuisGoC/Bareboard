target remote localhost:3333
monitor arm semihosting enable
monitor reset init
load
monitor reset halt