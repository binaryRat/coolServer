#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "handler.h"

int main( int argc, char *argv[]) {
       
       demonize();

       int port = atoi(argv[1]);

       int socket_definer = get_binded_soket(port);
       if(socket_definer == -1){

              printf("Error getting socket, shutdown\n");

              return 0;
       }

       printf("Server started on port : %d\nStarting request handler ...\n",port);

       handle_requests(socket_definer);
       
       close(socket_definer);

       return 0;
}

