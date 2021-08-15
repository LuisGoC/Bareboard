CC= arm-none-eabi-gcc
MACH= cortex-m0
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu99 -Wall -O0 #-g (for debug)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_linker.ld -Wl,-Map=final.map
#LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_linker.ld -Wl,-Map=final.map

all:main.o stm32_startup.o syscalls.o GPIO.o NVIC.o final.elf

semi:main.o stm32_startup.o syscalls.o final_sh.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

GPIO.o:GPIO.c
	$(CC) $(CFLAGS) -o $@ $^

NVIC.o:NVIC.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o stm32_startup.o syscalls.o GPIO.o NVIC.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: main.o stm32_startup.o 
	$(CC) $(LDFLAGS_SH) -o $@ $^

clean: 
	rm -rf *.o *.elf *.map

load:
	openocd -f board/st_nucleo_f0.cfg 

flash: clean|all

	@openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program final.elf verify reset exit" 