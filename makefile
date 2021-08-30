OBJS= main.o stm32_startup.o syscalls.o GPIO.o NVIC.o UART.o
CC= arm-none-eabi-gcc
MACH= cortex-m0
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu99 -Wall -O0 -g3 #(for debug)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_linker.ld -Wl,-Map=final.map
#LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_linker.ld -Wl,-Map=final.map

all: $(OBJS) final.elf

semi: $(OBJS) final_sh.elf

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: $(OBJS)
	$(CC) $(LDFLAGS_SH) -o $@ $^

clean: 
	rm -rf *.o *.elf *.map

misra_test: 
	cppcheck --inline-suppr --quiet --std=c99 --template=gcc --force main.c UART.c NVIC.c

load:
	openocd -f board/st_nucleo_f0.cfg 

debug:
	gdb final.elf -x=commands.gdb

flash: clean|all

	@openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program final.elf verify reset exit" 