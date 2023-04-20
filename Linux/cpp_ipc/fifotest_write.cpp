#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>  // File Control Operations
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int fd;
    char buffer[1024] = "Hi there, this is DYY sending a mail via a FIFO.";
    if((fd = open("data/fifotest", O_WRONLY)) < 0)
    {
        printf("尝试打开文件FIFO文件失败！是否没有运行打开FIFO的程序？\n");
        exit(1);
    }

    if(write(fd, buffer, 48) < 0)
    {
        printf("写入管道失败。\n");
        close(fd);
        exit(2);
    }
    sleep(2);
    close(fd);
    return 0;
}