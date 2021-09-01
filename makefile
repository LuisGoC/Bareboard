INC_DIR = app/Inc/
SRC_DIR = app/Src/
OBJ_DIR = Obj/
OBJS= $(OBJ_DIR)main.o $(OBJ_DIR)stm32_startup.o $(OBJ_DIR)syscalls.o $(OBJ_DIR)GPIO.o $(OBJ_DIR)NVIC.o $(OBJ_DIR)UART.o
CC= arm-none-eabi-gcc
MACH= cortex-m0
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu99 -Wall -O0 -g3 -I app/Inc #(for debug)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_linker.ld -Wl,-Map=final.map
#LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_linker.ld -Wl,-Map=final.map

all: $(OBJS) final.elf

semi: $(OBJS) final_sh.elf

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR) 
	$(CC) -MD $(CFLAGS) -o $@ $<

-include $(OBJ_DIR)*.d

final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: $(OBJS)
	$(CC) $(LDFLAGS_SH) -o $@ $^

clean: 
	rm -rf $(OBJ_DIR) *.elf *.map

misra_test: 
	cppcheck --addon=misra.json --inline-suppr --quiet --std=c99 --template=gcc --force app/Src -I app/Inc

load:
	openocd -f board/st_nucleo_f0.cfg 

debug:
	arm-none-eabi-gdb final.elf -x=commands.gdb

flash: clean|all

	@openocd -f interface/stlink.cfg -f target/stm32f0x.cfg -c "program final.elf verify reset exit" 