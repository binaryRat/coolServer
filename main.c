#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "server.h"
#include "handler.h"

int main( int argc, char *argv[]) {
       int opt;
       
       bool needDemonize = false;
       int port = 80;

       while ((opt = getopt(argc, argv, "dp:")) != -1) {
              switch (opt) {
                     case 'd': 
                            needDemonize = true; 
                            break;
                     case 'p': 
                            port = atoi(optarg); 
                            break;
                     case '?':
                            if (optopt == 'p')
                                   fprintf (stderr, "Option -%d requires an argument.\n", optopt);
                            else
                                   fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                            
                            fprintf(stderr, "Usage: %s [-p PORT] [DEMONIZE -d]\n", argv[0]);                  
                            
                            return 1;
                     default:
                            exit(EXIT_FAILURE);
                     }
       }
       if(needDemonize) demonize(); 

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

