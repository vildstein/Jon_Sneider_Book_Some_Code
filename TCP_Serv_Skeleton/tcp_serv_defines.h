#ifndef TCP_SERV_DEFINES_H
#define TCP_SERV_DEFINES_H


#if defined(OS_DEFINED_CMAKE_LIN)

#define INIT()		program_name = \
					strrchr(argv[ 0 ], '/' )  ? \
					program_name++ : \
					( program_name = argv[ 0 ] );

#define BZERO_SOCK_ADDR_IN_STRUCT bzero(sap, sizeof(*sap));

#elif defined(OS_DEFINED_CMAKE_WIN)

#define INIT() WSAStartup();
#define BZERO_SOCK_ADDR_IN_STRUCT memset(sap, int(0), sizeof(*sap));

#endif

#define EXIT(s) exit( s )
#define CLOSE(s) if ( close( s ) ) error( 1, errno, \
                 "ошибка mistake close " )

#define SET_ERRNO(e) errno = ( e )

#define IS_VALID_SOCKET(e) ( (e) >= 0 )

#define TO_STRING(value) #value

#define NLISTEN 5

#define SOCKET int
#define SIN sockaddr_in

#define SET_ADDRESS_FORWARD_DECL static void set_address(char* hostName, char* sname, struct SIN* sap, char* protocol);
#define ERROR_FORWARD_DECL void error(int status, int err, char* format, ...);
#define SERVER_FUNC_FORWARD_DECL static void server(SOCKET s, struct SIN* peer);

#endif //TCP_SERV_DEFINES_H
