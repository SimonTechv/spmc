from srclist import all_includes, all_sources, all_defines, linkerfile


app_name = "spmc"


def options(opt):
    opt.load('gcc gas') # Подгружаем тулчейн GCC


def configure(conf): 
    
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-gcc'], var='CC')            # Компилятор С
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-gcc'], var='AS')            # Транслятор Assmbler
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-gcc'], var='LINK_CC')       # Компоновщик
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-ar'],  var='AR')            # Архиватор
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-objcopy'], var='OBJCOPY')   # Даватор .hex и .bin
    conf.find_program([r'C:/Cross Compilers/12.2.rel1_2023.7/bin/arm-none-eabi-size'], var='SIZE')         # Вычислит размер исходника

    conf.load('gcc gas') # Подгружаем тулчейн GCC

def build(bld):

    # Скрипт линковщика
    linker_script = bld.path.find_node(linkerfile)

    # Флаги компиляции
    bld.env.CFLAGS = [
        '-mcpu=cortex-m0plus', 
        '-mthumb',
        '-mfloat-abi=softfp',
        '-ffunction-sections',
        '-fdata-sections',
        '-specs=nosys.specs',
        '-c',
        '-Wall',
        '-fmessage-length=0',
        '-g',
        '-gdwarf-2',
        '-O',
        '-std=c11',
    ]

    # Флаги линковки
    bld.env.LINKFLAGS = [
        f'-T{linker_script}',
        '-mcpu=cortex-m0plus', 
        '-mthumb',
        '-mfloat-abi=softfp',
        '-Xlinker', '--gc-sections',
        f'-Wl,-Map,{app_name}.map',
        '--specs=nosys.specs',
        # '-Wl,--no-warn-rwx-segments'
    ]

    bld.env.ASFLAGS = ['-mcpu=cortex-m0plus', '-mthumb', '-x', 'assembler-with-cpp']

    # Основная цель
    bld.program(
        features='c cprogram',
        source=all_sources,             # Исходные файлы
        includes=all_includes,          # Заголовочные файлы
        defines=all_defines,            # Глобальные макроопределения
        target=f'{app_name}.elf',       # Имя выходного файла
        lib=['m', 'c']                  # Библиотеки (стандартные)
    )

    # Output .bin и .hex
    bld(rule='${OBJCOPY} -O binary ${SRC} ${TGT}', source=f'{app_name}.elf', target=f'{app_name}.bin', shell=False)
    bld(rule='${OBJCOPY} -O ihex ${SRC} ${TGT}', source=f'{app_name}.elf', target=f'{app_name}.hex', shell=False)

    # Sizes .elf
    bld(rule='${SIZE} ${SRC}', source=f'{app_name}.elf', always=True, shell=False)
