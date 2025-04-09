# Описываем тут конфигурацию проекта

linkerfile = 'sdk/ldscript/linkerfile.ld'

inc = {
    'sdk_includes' : [
        'sdk/platform/common/inc',
        'sdk/platform/common/toolchain/inc',
        'sdk/platform/emlib/inc',
    ],

    'cmsis_includes' : [
        'sdk/platform/Device/SiliconLabs/EFM32ZG/Include',
        'sdk/platform/CMSIS/core/include',
    ],

    'core_includes' : [
        'core'
    ],

    'lib_includes' : [
        'lib/EEPROM/inc',
        'lib/EEFS/inc',
    ]
}


src = {
    'sdk_sources' : [
        'sdk/platform/emlib/src/em_cmu.c',
        'sdk/platform/emlib/src/em_core.c',
        'sdk/platform/emlib/src/em_emu.c',
        'sdk/platform/emlib/src/em_gpio.c',
        'sdk/platform/emlib/src/em_msc.c',
        'sdk/platform/emlib/src/em_rtc.c',
        'sdk/platform/emlib/src/em_system.c',
        'sdk/platform/emlib/src/em_timer.c',
        'sdk/platform/emlib/src/em_i2c.c',
    ],

    'cmsis_sources' : [
        'sdk/platform/common/src/sl_assert.c',
        'sdk/platform/common/src/sl_syscalls.c',
        'sdk/platform/common/toolchain/src/sl_memory.c',
        'sdk/platform/Device/SiliconLabs/EFM32ZG/Source/startup_efm32zg.c',
        'sdk/platform/Device/SiliconLabs/EFM32ZG/Source/system_efm32zg.c',
        
    ],

    'core_sources' : [
        'core/main.c'
    ],

    'lib_sources' : [
        'lib/EEPROM/src/eeprom.c',
        'lib/EEFS/src/eefs_fileapi.c',
        'lib/EEFS/src/eefs_filesys.c',
    ]
}

defs = {
    'sdk_defines': [
        'DEBUG_EFM=1',
    ],

    'cmsis_defines': [
        'EFM32ZG210F32=1'
    ],

    'core_defines': [
    ],

    'lib_defines' : [
    ]

}

# Собираем все include в большой список
all_includes = [item for sublist in inc.values() for item in sublist]

# Собираем все sources в большой список
all_sources = [item for sublist in src.values() for item in sublist]

# Собираем все defines в большой список
all_defines = [item for sublist in defs.values() for item in sublist]