#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd=open("foo", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR, S_IWUSR);
    for (int i=0; i<5000; i++)
    {
    write(fd, "abcde", 5);
    }
    fsync(fd); 
    close(fd);
} 
