#=============================================================================#
#                                                                             #
#          .o.                   .oooooo.             .oooo.     .oooo.       #
#         .888.                 d8P'  `Y8b          .dP""Y88b  .dP""Y88b      #
#        .8"888.      .ooooo.  888                        ]8P'       ]8P'     #
#       .8' `888.    d88' `88b 888                      .d8P'      <88b.      #
#      .88ooo8888.   888   888 888          8888888   .dP'          `88b.     #
#     .8'     `888.  888   888 `88b    ooo          .oP     .o o.   .88P      #
#    o88o     o8888o `Y8bod8P'  `Y8bood8P'          8888888888 `8bd88P'       #
#                                                                             #
#=============================================================================#

cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# General settings
project ("AdventOfCode2023")
set (SOURCE_DIR src)

# Day  1
set(DAY01_DIR ${SOURCE_DIR}/day01)
add_executable (Day01 ${DAY01_DIR}/main.cpp ${DAY01_DIR}/main.hpp)

# Day  2
set(DAY02_DIR ${SOURCE_DIR}/day02)
add_executable (Day02 ${DAY02_DIR}/main.cpp ${DAY02_DIR}/main.hpp)
