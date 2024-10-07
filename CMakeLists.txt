cmake_minimum_required(VERSION 3.18)
project(i7188)

if(CMAKE_C_COMPILER_ID STREQUAL "OpenWatcom")
    add_compile_options(-wcd=211) # Warning! W211: col(28) #pragma attributes for 'malloc_wrapper' may be inconsistent
    add_compile_options(-1 -bt=dos -d0 -ei -j -ms -bcl=dos -fpc)

    # add_link_options(OPTION HEAPSIZE=64k) # no need for DOS, it's already 64k


    # -ecc (set default calling convention to __cdecl) can't be enabled
    # add_compile_options(-ecc)

    # BUG: watcom/h/iostream(60): Error! E671: col(39) function modifier cannot be used on a variable
    # NO FIX :(

    # BUG: Error! E2028: main_ is an undefined reference (https://github.com/open-watcom/open-watcom-v2/issues/1068)
    # FIX:
    # add_link_options(alias main_=_main)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -za99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ze")
endif()

include_directories("lib")

set(MEMORY_MODEL "small")

if(MEMORY_MODEL STREQUAL "small")
   add_compile_options(-ms)
   set(I7188_LIB ${PROJECT_SOURCE_DIR}/lib/i7188s.lib)
elseif(MEMORY_MODEL STREQUAL "large")
   add_compile_options(-ml)
   set(I7188_LIB ${PROJECT_SOURCE_DIR}/lib/i7188l.lib)
endif()

add_executable(lab_1 src/lab_1/main.cpp)
target_link_libraries(lab_1 ${I7188_LIB})

add_executable(lab_2 src/lab_2/main.cpp)
target_link_libraries(lab_2 ${I7188_LIB})
