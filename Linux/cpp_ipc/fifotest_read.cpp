#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstdio>
int main()
{
    int fd;
    char buffer[1024] = {0};
    if((fd = open("data/fifotest", O_RDONLY)) < 0)
    {
        printf("打开FIFO失败。\n");
        exit(1);
    }
    if(read(fd, buffer, 49) < 0)
    {
        printf("读取FIFO数据失败！");
        close(fd);
        exit(2);
    }
    printf("%s\n", buffer);
    sleep(2);
    close(fd);
    return 0;
}