// 消息队列进程接收端
#include <iostream>
#include <sys/msg.h>
#include <stdlib.h>
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

    int recv_stat = msgrcv(msg_iden, &buffer, 256, 114, 0);
    if(recv_stat == -1)
    {
        std::cout << "消息接收错误。" << std::endl;
        exit(2);
    }
    else
    {
        std::cout << "接收到来自发送端的消息：" << std::endl;
        std::cout << buffer.mtext << std::endl;
    }
    
    memset(buffer.mtext, 0, 256);
    buffer.mtype = 514;
    strcpy(buffer.mtext, "Roger. Now replying.");
    if(msgsnd(msg_iden, &buffer, sizeof(buffer.mtext), 0) == -1)
    {
        std::cout << "回信接收失败。" << std::endl;
        exit(3);
    }
    else
    {
        std::cout << "对方接收已确认。" << std::endl;
    }
    return 0;
}