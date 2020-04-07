cmake_minimum_required(VERSION 3.6)
project(measuring_time C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(measuring_time main.c my_functions.c run_MPI_functions.c lol.h run_my_functions.c misc_for_my_funcs.c)

target_link_libraries(measuring_time ${MPI_LIBRARIES})

include_directories(${MPI_INCLUDE_PATH})

if(MPI_COMPILE_FLAGS)
    set_target_properties(measuring_time PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
    set_target_properties(measuring_time PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()