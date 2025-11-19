//#define CMAKE_SOCKET_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include <winsock2.h>

//#ifndef OS
//#define OS ""
//#endif


//CMAKE_SOCKET_INCLUDE

//#include CMAKE_SOCKET_INCLUDE


//#define CMAKE_SOCKET_INCLUDE //CMAKE_SOCK

//CMAKE_SOCKET_INCLUDE

//#include <CMAKE_SOCKET_INCLUDE>

#include "tcp_serv_defines.h"

const char* cmakeInclude = TO_STRING(CMAKE_SOCKET_INCLUDE);

//const char str[30] = {CMAKE_SOCKET_INCLUDE};

int main(void) {
    struct SIN local;
    struct SIN peer;

    char* hname;
    char* sname;

    int peerlen;

    SOCKET sock1;
    SOCKET s;

    const int on = 1;

    //INIT_MAKRO();



    printf("Hello, World!\n");
    printf("%s\n",  cmakeInclude);
    printf("%s\n",  TO_STRING(CMAKE_SOCKET_INCLUDE));

    puts(cmakeInclude);
    //puts(str);
    return 0;
}