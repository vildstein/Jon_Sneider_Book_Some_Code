#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/time.h>

#if defined(OS_DEFINED_CMAKE_WIN)
#include <winsock2.h>
#include <winsock.h>
#endif

#if defined(OS_DEFINED_CMAKE_LIN)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "tcp_serv_defines.h"

//const char* cmakeInclude = TO_STRING(CMAKE_SOCKET_INCLUDE);

char* program_name;

SET_ADDRESS_FORWARD_DECL
ERROR_FORWARD_DECL

int main( int argc, char** argv) {


    struct sockaddr_in local;
    struct sockaddr_in peer;

    char* hostName;
    char* serverName;

    int peerLen;

    SOCKET sock1;
    SOCKET s;

    const int on = 1;

    INIT() //??? why MACRO?

    if (argc == 2) {
        hostName == NULL;
        serverName = argv[ 1 ];
    } else {
        hostName == argv[ 1 ];
        serverName = argv[ 2 ];
    }

    set_address( hostName, serverName, &local, "tcp"); //Check this

    s = socket(AF_INET, SOCK_STREAM, 0 );

    if (!IS_VALID_SOCKET(s)) {
        error(1, errno, "socket mistake");
    }

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) {
        error(1, errno, "socket call mistake");
    }

    if ( bind( s, (struct sockaddr*) &local, sizeof(local)) ) {
        error(1, errno, "bind mistake");
    }

    if (listen(s, NLISTEN)) {
        error(1, errno, "listen mistake");
    }

    //do {} while (0);

    EXIT(0);
    //return 0;
}


static void set_address(char* hostName, char* serverName, struct sockaddr_in* sap, char* protocol) {

    struct servent* sp;
    struct hostent* hp;
    char* endPtr;
    short port;

    BZERO_SOCK_ADDR_IN_STRUCT
    sap->sin_family = AF_INET;

    if (hostName != NULL) {
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
        sap->sin_port = htons( port );
    } else {
        sp = getservbyname( serverName, protocol);
        if (sp == NULL) {
            error(1, 0, "unknown service: %s\n", sp);
        }
        sap->sin_port = sp->s_port;
    }
}

void error(int status, int err, char* format, ...) {
    va_list ap;

    va_start(ap, format);
    fprintf(stderr, "%s: ", program_name);
    vfprintf(stderr, format, ap);

    va_end(ap);

    if (err) {
        fprintf(stderr, ": %s (%d)\n", strerror( err ), err);
    }
    if (status) {
        EXIT(status);
    }
}