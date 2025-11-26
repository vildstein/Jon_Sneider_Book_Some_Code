#if defined(OS_DEFINED_CMAKE_WIN)
#include <winsock2.h>
#endif

#if defined(OS_DEFINED_CMAKE_LIN)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif


#include <stdio.h>
#include <unistd.h>
#include <errno.h>


//#include <cstring>
#include <sys/unistd.h>

#include <stdlib.h>

#include <stdarg.h>


//#include <netdb.h>

#include <fcntl.h>
#include <sys/time.h>




#include "tcp_serv_defines.h"

const char* cmakeInclude = TO_STRING(CMAKE_SOCKET_INCLUDE);

char* program_name;

SET_ADDRESS_FORWARD_DECL
ERROR_FORWARD_DECL

//const char str[30] = {CMAKE_SOCKET_INCLUDE};

int main( int argc, char** argv) {


    struct sockaddr_in local;
    struct sockaddr_in peer;

    char* hName;
    char* sName;

    int peerLen;

    SOCKET sock1;
    SOCKET s;

    const int on = 1;

    INIT_MACRO() ; //??? why MACRO?

    if (argc == 2) {
        hName == NULL;
        sName = argv[ 1 ];
    } else {
        hName == argv[ 1 ];
        sName = argv[ 2 ];
    }

    set_address( hName, sName, &local, "tcp");



    //printf("Hello, World!\n");
    //printf("%s\n",  cmakeInclude);
    //printf("%s\n",  TO_STRING(CMAKE_SOCKET_INCLUDE));

    //puts(cmakeInclude);
    //puts(str);
    return 0;
}


static void set_address(char* hostName,
                        char* serverName,
                        struct sockaddr_in* sap,
                        char* protocol) {

    struct srvent* sp;
    struct hostent* hp;
    char* endPtr;
    short port;

    // bzero( sap, sizeof( *sap) ); change for memset
#if defined(OS_DEFINED_CMAKE_WIN)
    memset(sap, int(0), sizeof(*sap));
#elif defined(OS_DEFINED_CMAKE_LIN)
    bzero(sap, sizeof(*sap));
#endif
    sap->sin_family = AF_INET;

    if (serverName != NULL) {
        if (!inet_aton(hostName, &sap->sin_addr)) {
            hp = gethostbyname(hostName);
            if (hostName == NULL) {
                error(1, 0, "unknown host %s\n", hostName);
            }
            sap->sin_addr = *(struct in_addr*)hp->h_addr;
        }
    } else {
        sap->sin_addr.s_addr = htonl( INADDR_ANY );
    }
    port = (short)strtol(serverName, &endPtr, 0 );

    if (*endPtr != '\0') {
        sap->sin_addr.s_addr = htons( port );
    } else {
        sp = getserverbyname( serverName, protocol);
    }


}