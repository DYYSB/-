#include <iostream>
#include <sys/msg.h>
#include <stdlib.h>
struct msg_buf  // 用于投入队列的消息格式，是一个结构体
{
    long mtype; // 第一个成员是消息的类型
    char mtext[256];    // 第二个成员是消息的内容
};

int main()
{
    int msg_iden = msgget(114514, IPC_CREAT);
    if(msg_iden == -1)
    {
        std::cout << "消息队列创建失败！程序即将退出。" << std::endl;
        exit(1);
    }

}