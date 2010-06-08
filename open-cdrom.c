/* 
 * [NAME]:    Open your cdrom
 * [AUTHOR]:  Stefano Viola
 * [CONTACT]: stefanoviola@sannioglug.org
 *
 *
 * Licenze GLPv3
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      3 of the License, or (at your option) any later version.
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/version.h>
#include <linux/cdrom.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,1,0)
#include <linux/ucdrom.h>
#endif

void main(){
  printf("\nCD eject - Test\n");
  //char *deviceName;  /* name of device */
  int fd; 	   /* file descriptor for device */
  int worked = 0;    /* set to 1 when successfully ejected */
  fd = OpenDevice("/dev/cdrom");
  worked = EjectCdrom(fd);
  
  if(worked)
    printf("Esito: %d CD espulso\n\n",worked);
  else
    printf("Errore espulsione CD!");
  
}

/* Open a device file. */
int OpenDevice(const char *fullName)
{
  int fd = open(fullName, O_RDONLY|O_NONBLOCK);
  if (fd == -1) {
    printf("\nNon posso espellere!\n\n");
    exit(1);
  }
  return fd;
}

int EjectCdrom(int fd)
{
  int status = -1;
  
#if defined(CDROMEJECT)
  status = ioctl(fd, CDROMEJECT);
#elif defined(CDIOCEJECT)
  status = ioctl(fd, CDIOCEJECT);
#else
#error
#endif
   return (status == 0);
}
