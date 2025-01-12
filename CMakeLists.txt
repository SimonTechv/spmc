cmake_minimum_required(VERSION 3.31.3)

# Project languages
project(smpc C CXX ASM)

# Set exec name
set(EXEC ${PROJECT_NAME}-elf)

# Compile options
set(C_STANDARD 11)
set(CXX_STANDARD 11)

# Configure project sources
include(sources.cmake)

# Set executable output file
add_executable(${EXEC} ${EFM32SDKSRC} ${EFM32CORESRC} ${EFM32LIBSRC})

# Set include directories
target_include_directories(${EXEC} PRIVATE ${EFM32SDKINC} ${EFM32COREINC} ${EFM32LIBINC})

# Defines for SiliconLabs SDK libraries
target_compile_definitions(${EXEC} PUBLIC
    DEBUG_EFM=1
    EFM32ZG210F32=1
)

# Compile options
target_compile_options(${EXEC} PRIVATE
    -mcpu=cortex-m0plus
    -mthumb
    -mfloat-abi=softfp
    -specs=nano.specs
    -fdata-sections
    -ffunction-sections
    -c 
    -fmessage-length=0
    -Wall
    -g 
    -gdwarf-2 
    -Og
)

# Link options
target_link_options(${EXEC} PRIVATE
    -T${CMAKE_SOURCE_DIR}/sdk/ldscript/linkerfile.ld
    -mcpu=cortex-m0plus
    -mthumb
    -mfloat-abi=softfp
    -lc
    -lm
    --specs=nano.specs
    -Wl,-Map=${EXEC}.map,--cref
    -Wl,--gc-sections
    -Wl,--no-warn-rwx-segments 
)

# Post build options
include(postbuild.cmake)