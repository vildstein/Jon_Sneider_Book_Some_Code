cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME "TCP_Serv_Skeleton")

project(${PROJECT_NAME} C)
message(STATUS "PROJECT_NAME =  ${PROJECT_NAME}")

set(CMAKE_SOCKET_INCLUDE "#include <winsock2.h>")
message(STATUS "CMAKE_SOCKET_INCLUDE =  ${CMAKE_SOCKET_INCLUDE}")

#if ()
#    CMAKE_OS

set(CMAKE_C_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.c
        tcp_serv_defines.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE "CMAKE_SOCKET_INCLUDE =  ${CMAKE_SOCKET_INCLUDE}")
