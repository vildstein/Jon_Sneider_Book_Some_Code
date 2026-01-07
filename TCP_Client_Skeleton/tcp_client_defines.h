#ifndef TCP_CLIENT_DEFINES_H
#define TCP_CLIENT_DEFINES_H


#if defined(OS_DEFINED_CMAKE_LIN)

#define INIT()		program_name = \
					strrchr(argv[ 0 ], '/' )  ? \
					program_name++ : \
					( program_name = argv[ 0 ] );

#define BZERO_SOCK_ADDR_IN_STRUCT(sap, s_of) bzero(sap, s_of); //bzero(sap, sizeof(*sap));
#define SOCKET int
#define IS_VALID_SOCKET(e) ( (e) >= 0 )

#elif defined(OS_DEFINED_CMAKE_WIN)

#define INIT() //WSAStartup();
#define BZERO_SOCK_ADDR_IN_STRUCT(sap, int_ch, s_of) memset(sap, int_ch, s_of); //bzero(sap, 0, sizeof(*sap));
#define SOCKET size_t
#define IS_VALID_SOCKET(e) ( (e) != INVALID_SOCKET )

#endif

#define EXIT(s) 	puts("exit");	\
			        exit( s );

#define CLOSE(s) if ( close( s ) ) error( 1, errno, \
                 "ошибка mistake close " )

//#define SET_ERRNO(e) errno = ( e )
//#define TO_STRING(value) #value

//#define NLISTEN 5

#define SIN struct sockaddr_in
#define STRUCT_SOCKADDR_CAST (struct sockaddr*)
#define STRUCT_IN_ADDR_CAST (struct in_addr*)

#define DEFAULT_HOST {"localhost"}
#define DEFAULT_PORT {"9000"}
#define DEFAULT_NETWORK_PROTOCOL {"tcp"};

#define SET_ADDRESS_FORWARD_DECL static void set_address(char* host, char* port, struct sockaddr_in* sap, char* protocol);
#define ERROR_FORWARD_DECL void error(int status, int err, char* format, ...);
#define CLIENT_FUNC_FORWARD_DECL static void client(SOCKET s, SIN* peer);

#endif //TCP_SERV_DEFINES_H
