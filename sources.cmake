# Setting SDK sources
set(EFM32SDKSRC
    # System scripts
    sdk/platform/common/src/sl_assert.c
    sdk/platform/common/src/sl_syscalls.c
    sdk/platform/common/toolchain/src/sl_memory.c

    # Startup scripts
    sdk/platform/Device/SiliconLabs/EFM32ZG/Source/startup_efm32zg.c
    sdk/platform/Device/SiliconLabs/EFM32ZG/Source/system_efm32zg.c

    # EmLib sources
    sdk/platform/emlib/src/em_cmu.c
    sdk/platform/emlib/src/em_core.c
    sdk/platform/emlib/src/em_emu.c
    sdk/platform/emlib/src/em_gpio.c
    sdk/platform/emlib/src/em_msc.c
    sdk/platform/emlib/src/em_rtc.c
    sdk/platform/emlib/src/em_system.c
    sdk/platform/emlib/src/em_timer.c
    sdk/platform/emlib/src/em_i2c.c
)

# Setting SDK includes
set(EFM32SDKINC
    sdk/platform/CMSIS/core/include
    sdk/platform/common/inc
    sdk/platform/common/toolchain/inc
    sdk/platform/Device/SiliconLabs/EFM32ZG/Include
    sdk/platform/emlib/inc
)

# Core application sources
set(EFM32CORESRC
    core/main.c
)

# Core application include
set(EFM32COREINC
    core/
)


# Core library sources
set(EFM32LIBSRC

    lib/EEPROM/src/eeprom.c

    lib/EEFS/src/eefs_fileapi.c
    lib/EEFS/src/eefs_filesys.c
)

# Core library include
set(EFM32LIBINC

    lib/EEPROM/inc

    lib/EEFS/inc
)