// 消息队列进程发送端
#include <iostream>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
struct msg_buf  // 用于投入队列的消息格式，是一个结构体
{
    long mtype; // 第一个成员是消息的类型
    char mtext[256];    // 第二个成员是消息的内容
};

int main()
{
    msg_buf buffer;
    int msg_iden = msgget(114514, IPC_CREAT);   // 创建消息队列
    if(msg_iden == -1)
    {
        std::cout << "消息队列创建失败！程序即将退出。" << std::endl;
        exit(1);
    }

    buffer.mtype = 114; // 设置所要发送的消息类型是114
    for(int i = 0; i < 256; i++)
    {
        buffer.mtext[i] = 0;
    }
    sprintf(buffer.mtext, "Hi there, this is DYY sending a mail via a message queue through client %d.", getpid());
    
    if(msgsnd(msg_iden, &buffer, strlen(buffer.mtext), 0) == -1)    // 发送消息
    {
        std::cout << "消息发送失败。" << std::endl;
        exit(2);
    }

    int recv_length = msgrcv(msg_iden, &buffer, 256, 514, 0);   // 接收返回的消息
    if(recv_length == -1)
    {
        std::cout << "回信接收失败。" << std::endl;
        exit(3);
    }
    else
    {
        std::cout << "接收到来自另一端的回信：" << std::endl << buffer.mtext << std::endl;
    }
    return 0;
}