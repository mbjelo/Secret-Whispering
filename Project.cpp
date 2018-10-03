#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
#include <net/if.h>
#include <errno.h>
#include <linux/if_tun.h>


#define BUFSIZE 2000 
#define IFF_TAP	0x0002


class Tunnel { 

public:

int Create(char *dev, int flags) { 

  struct ifreq ifr;
  int fd, err;
  char *clonedev = "/dev/net/tun";

  if( (fd = open(clonedev , O_RDWR)) < 0 ) {
    perror("Opening /dev/net/tun");
    return fd;
  }

  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;

  if (*dev) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if( (err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0 ) {
    perror("ioctl(TUNSETIFF)");
    close(fd);
    return err;
  }

return fd;
} 


void Encrypt(char *buf,int *buftun,int n, int key){
 
 char c;
 int b;
 
 for(int x=0;X<n;x++){                          /*In this for loop is implemented simple encription algorithm. 
                                                  algorithm pick every char in input buffer, convert it to int 
                                                  and do multiplication with key value k then substract 1. Decription 
                                                  is done with reverse alogirhm. */
     c=*(bufpoint+x);
     b=(int)c;
     b=b*k-1;
     *(buftun+x)=b;
 }

}


int Write(int fd, char *buf, int n){

  int nwrite;

  if((nwrite=write(fd, buf, n)) < 0){
    perror("Writing data");
    exit(1);
  }
  return nwrite;
}


int Read(int fd, char *buf, int n){

  int nread;

  if((nread=read(fd, buf, n)) < 0){
    perror("Reading data");
    exit(1);
  }
  return nread;
}
    
private:
};

void main(){   


    char buffer[BUFSIZE];                          //buffer for reading packet from socket
    int  buffertun[BUFSIZE];                       //buffer for sending data to tunnel
    char * tunname = "tun";
    fd_set rd_network;                             /*file description set which will be used 
                                                     for detection if there is data for reading 
                                                     in socket file */
    
    
    int redytoread;
    int k=3;                                       /*this is key used in encryption algorithn. 
                                                    It can be input from some other function 
                                                    or defined or calculated on any other way. */

    taptunnel Tunnel;                              //create tunnel object
    int tap_fd=taptunnel.Create(tunname,IFF_TAP);  //create tap tunnel and return tunnel file descriptor
    
    while(1){

        FD_ZERO(&rd_network); 
        FD_SET(network_fd, &rd_network);            /*network_fd is file descriptor for socket from which 
                                                     is data read for encryption and passing to tap interface. 
                                                     It should be given as parameter to this code */
         
        redytoread = select(1, &rd_network, NULL, NULL, NULL);

        if (redytoread < 0 && errno == EINTR){
           continue;
        }
        if (redytoread < 0) {
         perror("select()");
         exit(1);
        }

        if(FD_ISSET(network_fd, &rd_network)) {

        int readed_bytes= taptunnel.Read(network_fd,buffer,BUFSIZE);  //reading data from socket fd
        taptunnel.Encrypt(buffer,buffertun,readed_bytes,k);           //encrypting data
        taptunnel.Write(tap_fd,buffertun,readed_bytes);               //writing data to tap tunnel fd

        }

    }
}