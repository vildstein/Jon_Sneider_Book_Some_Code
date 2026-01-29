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
#include <windows.h>
#endif

#if defined(OS_DEFINED_CMAKE_LIN)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "tcp_client_defines.h"

SET_ADDRESS_FORWARD_DECL
ERROR_FORWARD_DECL
CLIENT_FUNC_FORWARD_DECL

char* program_name;

int main( int argc, char** argv) {

    SIN peer;
    SOCKET s;

    char* host = DEFAULT_HOST;
    char* port = DEFAULT_PORT;
    char* protocol = DEFAULT_NETWORK_PROTOCOL;

    const int on = 1;

    switch(argc) {
    case 1:
    case 2:
        break;
    case 3:
        host = argv[1];
        port = argv[2];
        break;
    default: break;
    };

    INIT();

    set_address( host, port, &peer, protocol );

    s = socket(AF_INET, SOCK_STREAM, 0 );

    if (!IS_VALID_SOCKET(s)) {
        error(1, errno, "SOCK FUNC FAILED");
    }

    if (connect( s, STRUCT_SOCKADDR_CAST&peer, sizeof(peer))) {
        error(1, errno, "CONNECT FUNC FAILED");
    }

    client(s, &peer);

    EXIT(0);
}


static void set_address(char* host, char* port, struct sockaddr_in* sap, char* protocol) {

    struct servent* sp;
    struct hostent* hp;
    char* endPtr;
    short portNum;

    BZERO_SOCK_ADDR_IN_STRUCT(sap, 0, sizeof(*sap))

    sap->sin_family = AF_INET;

    if (host != NULL) {
        if (!inet_addr(host)) {//if (!inet_aton(host, &sap->sin_addr)) {
            hp = gethostbyname(host);

            if (hp == NULL) {
                error(1, 0, "unknown host %s\n", host);
            }
            sap->sin_addr = *STRUCT_IN_ADDR_CAST hp->h_addr;
        }
    } else {
        sap->sin_addr.s_addr = htonl( INADDR_ANY );
    }
    portNum = (short) strtol(host, &endPtr, 0 );

    if (*endPtr == '\0') {
        sap->sin_port = htons( portNum );
    } else {
        sp = getservbyname( port, protocol);
        if (sp == NULL) {
            error(1, 0, "unknown service: %s\n", port);
        }
        sap->sin_port = sp->s_port;
    }
}

static void client(SOCKET s, SIN* peer) {
    int rc = 0;
    char buf[120];

    for ( ; ; ) {
        rc = recv(s, buf, sizeof(buf), 0);
        if (rc <= 0) {
            break;
        }
        write(1, buf, rc);
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
