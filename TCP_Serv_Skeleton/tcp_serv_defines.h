#ifndef TCP_SERV_DEFINES_H
#define TCP_SERV_DEFINES_H

#define INIT_MAKRO()           (program_name = \
                                strrchr( argv[ 0 ], '/') ) ? \
                                (program_name = argv[ 0 ] )

#define EXIT(s) exit( s )
#define CLOSE(s) if ( close( s ) ) error( 1, errno, \
                 "ошибка mistake close " )

#define SET_ERRNO(e) errno = ( e )

#define IS_VALID_SOCKET(e) ( (e) >= 0 )

#define TO_STRING(value) #value

#define SOCKET int
#define SIN sockaddr_in

#endif //TCP_SERV_DEFINES_H
