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

cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project settings
project ("AdventOfCode2023")
set (SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

add_compile_definitions(SOURCE_DIR="${SOURCE_DIR}")

#=============================================================================#
# Day  1                                                                      #
#=============================================================================#
set(DAY01_DIR ${SOURCE_DIR}/day01)
add_executable (Day01 
  ${DAY01_DIR}/main.cpp ${DAY01_DIR}/main.hpp)

#=============================================================================#
# Day  2                                                                      #
#=============================================================================#
set(DAY02_DIR ${SOURCE_DIR}/day02)
add_executable (Day02 
  ${DAY02_DIR}/main.cpp ${DAY02_DIR}/main.hpp
  ${DAY02_DIR}/game.cpp ${DAY02_DIR}/game.hpp
  ${DAY02_DIR}/set.cpp ${DAY02_DIR}/set.hpp)

#=============================================================================#
# Day  3                                                                      #
#=============================================================================#
set(DAY03_DIR ${SOURCE_DIR}/day03)
add_executable (Day03 
  ${DAY03_DIR}/main.cpp
  ${DAY03_DIR}/engine_schematic.cpp ${DAY03_DIR}/engine_schematic.hpp)

#=============================================================================#
# Day  4                                                                      #
#=============================================================================#
set(DAY04_DIR ${SOURCE_DIR}/day04)
add_executable (Day04 
  ${DAY04_DIR}/main.cpp
  ${DAY04_DIR}/scratchcard.cpp ${DAY04_DIR}/scratchcard.hpp
  ${DAY04_DIR}/scratchcard_pile.cpp ${DAY04_DIR}/scratchcard_pile.hpp)

#=============================================================================#
# Day  5                                                                      #
#=============================================================================#
set(DAY05_DIR ${SOURCE_DIR}/day05)
add_executable (Day05 
  ${DAY05_DIR}/main.cpp
  ${DAY05_DIR}/almanac.cpp ${DAY05_DIR}/almanac.hpp
  ${DAY05_DIR}/map.cpp ${DAY05_DIR}/map.hpp)

#=============================================================================#
# Day  6                                                                      #
#=============================================================================#
set(DAY06_DIR ${SOURCE_DIR}/day06)
add_executable (Day06 
  ${DAY06_DIR}/main.cpp
  ${DAY06_DIR}/race.cpp ${DAY06_DIR}/race.hpp)

#=============================================================================#
# Day  7                                                                      #
#=============================================================================#
set(DAY07_DIR ${SOURCE_DIR}/day07)
add_executable (Day07 
  ${DAY07_DIR}/main.cpp
  ${DAY07_DIR}/pocketbet.cpp ${DAY07_DIR}/pocketbet.hpp
  ${DAY07_DIR}/hand.cpp ${DAY07_DIR}/hand.hpp)

#=============================================================================#
# Day  8                                                                      #
#=============================================================================#
set(DAY08_DIR ${SOURCE_DIR}/day08)
add_executable (Day08 
  ${DAY08_DIR}/main.cpp
  ${DAY08_DIR}/numeric.hpp
  ${DAY08_DIR}/map.cpp ${DAY08_DIR}/map.hpp
  ${DAY08_DIR}/node.cpp ${DAY08_DIR}/node.hpp)

#=============================================================================#
# Day  9                                                                      #
#=============================================================================#
set(DAY09_DIR ${SOURCE_DIR}/day09)
add_executable (Day09 
  ${DAY09_DIR}/main.cpp
  ${DAY09_DIR}/report.cpp ${DAY09_DIR}/report.hpp)

#=============================================================================#
# Day 10                                                                      #
#=============================================================================#
set(DAY10_DIR ${SOURCE_DIR}/day10)
add_executable (Day10 
  ${DAY10_DIR}/main.cpp
  ${DAY10_DIR}/piping.cpp ${DAY10_DIR}/piping.hpp
  ${DAY10_DIR}/matrix.cpp ${DAY10_DIR}/matrix.hpp)

#=============================================================================#
# Day 11                                                                      #
#=============================================================================#
set(DAY11_DIR ${SOURCE_DIR}/day11)
add_executable (Day11 
  ${DAY11_DIR}/main.cpp
  ${DAY11_DIR}/image.cpp ${DAY11_DIR}/image.hpp)
