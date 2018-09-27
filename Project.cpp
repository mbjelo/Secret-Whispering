#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h> 
#include <net/if.h>
#include <errno.h>
#include <linux/if_tun.h>


#define BUFSIZE 2000 
#define IFF_TAP	0x0002


class Tunnel { //class header
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

  strcpy(dev, ifr.ifr_name);

return fd;
} 
void Encrypt(char *buf, int n){
 
 char *bufpoint=buf
 char c;
 int b;
 
 for(int x=0;X<n;x++){

  c=*(bufpoint+x)
  b=(int)c;
  b=b*k-1;
  *(bufpoint+x)=b;
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
    //public method declarations
private:
    //private fields
    //private method declarations
};

void main(){   //// network_fd is file descriptor for socket from packets for encryption are read, it should be passed to thic code as argument


    char buffer[BUFSIZE];//buffer for reading packet from socket
    char * tunname = "tun";
    taptunnel Tunnel; //create tunel object
    int tapfiledesc=taptunnel.Create(tunname,IFF_TAP);
    fd_set rd_network; 
    int redytoread;
    while(1){

        FD_ZERO(&rd_network);
        FD_SET(network_fd, &rd_network); //network_fd is file descriptor for socket from which is data read for encryption and passing to tap interface. It should be given as parameter to this code
         
        redytoread = select(1, &rd_network, NULL, NULL, NULL);

        if (redytoread < 0 && errno == EINTR){
           continue;
        }
        if (redytoread < 0) {
         perror("select()");
         exit(1);
        }

        if(FD_ISSET(network_fd, &rd_network)) {

        int readed_bytes= taptunnel.Read(network_fd,buffer,BUFSIZE);
        taptunnel.Encrypt(buffer,readed_bytes);
        taptunnel.Write(tapfiledesc,buffer,readed_bytes);

        }

    }
}