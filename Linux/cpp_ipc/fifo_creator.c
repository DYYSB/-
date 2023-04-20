#include <sys/stat.h>
#include <stdio.h>
int main()
{
    if(mkfifo("data/fifotest", 0666) != 0)
    {
        printf("FIFO有名管道创建失败！\n");
    }
    return 0;
}