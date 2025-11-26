#ifndef TCP_SERV_DEFINES_H
#define TCP_SERV_DEFINES_H

#define INIT_MACRO()    program_name = \
                        program_name = ( strrchr(argv[ 0 ], '/' ) ) ? \
                        program_name++ : \
                        (program_name = argv[ 0 ] );

#define EXIT(s) exit( s )
#define CLOSE(s) if ( close( s ) ) error( 1, errno, \
                 "ошибка mistake close " )

#define SET_ERRNO(e) errno = ( e )

#define IS_VALID_SOCKET(e) ( (e) >= 0 )

#define TO_STRING(value) #value

#define SOCKET int
#define SIN sockaddr_in

#define SET_ADDRESS_FORWARD_DECL static void set_address(char* hostName, char* sname, struct sockaddr_in* sap, char* protocol);
#define ERROR_FORWARD_DECL void error(int status, int err, char* format, ...);

#endif //TCP_SERV_DEFINES_H
