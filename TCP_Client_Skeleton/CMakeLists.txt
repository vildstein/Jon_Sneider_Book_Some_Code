cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME "TCP_Client_Skeleton")

project(${PROJECT_NAME} C)
message(STATUS "PROJECT_NAME =  ${PROJECT_NAME}")

message(STATUS "CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")

set(CMAKE_C_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.c
        tcp_client_defines.h)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE OS_DEFINED_CMAKE_LIN)
    message(STATUS "LINUX DEFINED")
else ()
    target_compile_definitions(${PROJECT_NAME} PRIVATE OS_DEFINED_CMAKE_WIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
    message(STATUS "DEFINED NOT LINUX")
endif()