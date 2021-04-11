// This is a test program to receive UDP packet
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>

main(int argc, char *argv[]){
  const char ihost_nd[]="192.168.0.10";  //128.197.41.10";//192.168.0.10";
  int np=1000, udp_s, i, l=0, flags, addr_l; FILE *fd;
  socklen_t addrlen=16; char buf[9000];
  struct sockaddr_in  addr;

  if(argc>1) np=atoi(argv[1]);
  if(np==0) printf("Zero packets requested!!!\n");
  //  printf("s = %s, np = %d\nb",argv[1],np);

//EDITADO POR ALFONSO
  char str0[50]= "./Documents/ZavarzinDAQ288/";//En este se guarda todo 1
  char str1[20];//Nombre del folder
  char str2[20];
  //char str2[20] = "udp.raw";	
  
  printf("\n2019-10-18/");		
  printf("\nNombre de la carpeta? ");
  scanf("%s",str1);
  strcat( str0, str1);

  printf("\nEJEMPLO: udp.raw");	
  printf("\nNombre del archivo y extension? ");
  scanf("%s",str2);  

  strcat( str0, str2);
  //printf(str1);	

  fd = fopen(str0,"w+");//LINEA MORTAL - NOTA Dirección desde el home

//MODIFICADO 
  inet_aton(ihost_nd, &addr.sin_addr);
  addr.sin_family=AF_INET;
  addr.sin_port=0x505; // 5*256=1285.

  udp_s=socket(PF_INET, SOCK_DGRAM,0); //IPPROTO_UDP);
  if(bind(udp_s, &addr, addrlen))
    printf(" %s\n",strerror(errno));
  
  for(i=0; i<np; i++) {
    l=recv(udp_s, buf, 9000, 0);
    // printf(" %s L= %d\n",strerror(errno),l);
    fwrite(buf,1,l,fd);
  }
}


