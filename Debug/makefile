################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
startengene.lss \

FLASH_IMAGE += \
startengene.hex \

EEPROM_IMAGE += \
startengene.eep \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: startengene.elf secondary-outputs

# Tool invocations
startengene.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,startengene.map -mmcu=atmega48 -o "startengene.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

startengene.lss: startengene.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S startengene.elf  >"startengene.lss"
	@echo 'Finished building: $@'
	@echo ' '

startengene.hex: startengene.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex startengene.elf  "startengene.hex"
	@echo 'Finished building: $@'
	@echo ' '

startengene.eep: startengene.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex startengene.elf  "startengene.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: startengene.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega48 startengene.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: startengene.elf
	@echo 'Invoking: AVRDude'
	/usr/bin/avrdude -pm48 -cusbasp -y -u -Uflash:w:startengene.hex:a -Ulfuse:w:0xde:m -Uhfuse:w:0xdf:m -Uefuse:w:0x1:m
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) startengene.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
