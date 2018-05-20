cmake_minimum_required(VERSION 3.10)
project(MTM_FLIX C)

set(CMAKE_C_STANDARD 99)

add_executable(MTM_FLIX main.c mtmflix.h set.h list.h map.h mtm_ex3.h  user.h user.c series.c series.h )
target_link_libraries(MTM_FLIX ${CMAKE_SOURCE_DIR}/libmtm.a ${CMAKE_SOURCE_DIR}/libmtm_ex3.a)
set(CMAKE_C_FLAGS "-std=c99 ")