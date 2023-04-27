# 进程间通信的多种方式
进程间通信（InterProcess Communication, 简称IPC），是指在不同进程之间交换或传递数据。
<br>以Linux系统为例。

## 方式一：无名管道（pipe）
无名管道用于从父进程向子进程**单向**传递数据。
在Linux系统的<unistd.h>头文件中，定义了用于开启一个无名管道的函数`pipe()`。
函数原型如下：
```c++
int pipe(int* ___pipedes);
```
这里的pipedes地址，需要传入的实际上是一个2位大小的int型数组地址。我们假设这个数组为`pipe_fd[2]`，那么`pipe_fd[0]`是管道读取端的文件标识符，`pipe_fd[1]`是管道写入端的文件标识符。
<br><br>
以下是一个程序示例。在这个示例中，由该程序通过调用fork()函数创建出一个自身的副本，这个副本会作为该程序所属进程的子进程而存在。

```c++
#include <iostream>
#include <unistd.h>
int main()
{
    // 创建两个管道的文件标识符，分别标识管道的两头
    int pipe_fd[2] = {0};
    char buffer[35] = {0};
    // pid记录由父线程fork出来的子线程的线程ID
    pid_t pid = 0;
    if(pipe(pipe_fd) < 0)   // pipe函数用于开启管道，传入值是管道文件标识符数组，创建成功后两个文件标识符原地传出，1为写，0为读，是单向的
    {
        std::cout << "管道创建失败！" << std::endl;
    }

    if((pid = fork()) < 0)  //  fork函数用于复制当前线程为一个副本作为当前线程的子线程。这个线程会被安排到管道另一端。
    {
        std::cout << "子线程创建失败！" << std::endl;
    }
    else if(pid > 0)    // 如果这个线程的pid是大于0的，那么这个线程是父线程，得到的是子线程的pid
    {
        close(pipe_fd[0]);  // 关闭这个进程的读取端管道，父进程只负责写
        write(pipe_fd[1], "Hi there, this is DYY.", 22);
    }
    else    // 如果是等于0的，那么这个线程是子线程
    {
        close(pipe_fd[1]);  // 关闭这个进程的写入端管道，子进程只负责读
        read(pipe_fd[0], buffer, 35);
        std::cout << "从管道另一端读取到数据：" << buffer << std::endl;
    }
    return 0;
}
```

## 方式二：有名管道（FIFO）
FIFO用于在两个没有联系的进程之间**单向**地传递数据。<br>
在开启FIFO通信之后，Linux会在硬盘中开启一个特殊的**文件**用于进行FIFO通信。<br>
也就是说，FIFO的本质就是系统给两个进程建立了一个文件，写进程在文件里写数据，读进程在文件里读取数据。<br>
<br>这里有一个程序，这个程序的作用是建立一个FIFO文件（即开启一个FIFO有名管道）。
```c++
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
```
注意这一个语句：
```c++
mkfifo("data/fifotest", 0666);
```
这个函数存在于<sys/stat.h>头文件内。函数定义如下：
```c
int mkfifo (const char *__path, __mode_t __mode)
```
两个传入参数，前一个是FIFO文件的存放路径，后一个是该文件的八进制权限（类型是unsigned int）。<br>另外，mkfifo本身也是一个Linux命令，可以通过命令的方式建立FIFO文件，但是在这里不展开。<br><br>
一个FIFO文件创建之后，需要被两个进程打开，其中一个进程以读取形式打开，另外一个进程以写入形式打开。
<br>默认情况下，在其中一个进程通过调用open函数打开FIFO文件之后，程序会阻塞，直到FIFO的另一端也调用了open函数打开了FIFO。但是在open函数中，可以通过调整函数输入参数来进行非阻塞的操作。
<br>open函数需要两个传入参数，前一个是文件位置，后一个是打开参数。
<br>在这里，对应FIFO类型文件有几种打开参数：
```
O_WRONLY：阻塞式写入（Write only）
O_RDONLY：阻塞式读取（Read only）
O_WRONLY | O_NONBLOCK：非阻塞式写入（Write only | Non_block）
O_RDONLY | O_NONBLOCK：非阻塞式读取（Read only | Non_block）
```

下面是一个例子。
<br>写入端：
```c++
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

    if(write(fd, buffer, 48) < 0)   // 通过write函数向文件中写入。
    // 三个传入参数，第一个是文件描述符（这里的文件描述符应该指向FIFO文件），第二个是要写入的字符串，第三个是写入长度。
    {
        printf("写入管道失败。\n");
        close(fd);
        exit(2);
    }
    // sleep(2);
    close(fd);
    return 0;
}
```
读取端：
```c++
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
    if(read(fd, buffer, 49) < 0)    // 通过read函数从文件中读出数据。
    // 三个传入参数，第一个是文件描述符（此处应该指向FIFO文件），第二个是存储读取到的数据的存储字符串，第三个是读取最大长度。
    {
        printf("读取FIFO数据失败！");
        close(fd);
        exit(2);
    }
    printf("%s\n", buffer);
    // sleep(2);
    close(fd);
    return 0;
}
```
在运行这两个程序之前，首先先创建FIFO文件，然后依次运行这两个程序。
运行第一个程序之后，程序会阻塞，直到运行第二个程序（这两个程序的运行顺序无关，一端不论是读还是写永远会等待另一端连接），程序随即结束。
<br>读取端可以读取到这一行信息：
```
Hi there, this is DYY sending a mail via a FIFO.
```
使用FIFO的限制是，两端必须提前知道FIFO文件的位置。也就是说，系统要提前给两端的程序提供FIFO接口。

## 方式三：消息队列
消息队列是存在于内核中的IPC机制，本质上是存储在内核中的一张链表。
<br>消息队列独立于读程序和写程序而存在。不像之前的管道必须要依附于两个进程才能发挥作用，消息队列是解耦合于任何程序的。写程序只需要向消息队列里面扔消息，扔进去就可以跑了；读程序只需要从消息队列里面拿数据，不用等写程序往里面扔。
<br><br>需要注意的是，经过实验，发送和接收消息需要root权限。
<br><br>消息队列中，一个消息以一个结构体类型的形式存在。这个结构体的形式如下：
```c
struct msg_buf  // 用于投入队列的消息格式，是一个结构体
{
    long mtype; // 第一个成员是消息的类型
    char mtext[];    // 第二个成员是消息的内容
};
```
在读写消息的时候，发送端会以这种形式传输自己的消息，接收端以这种形式解读传过来的数据。

这里有一个简单的例子，两个进程之间会做两次握手。
<br>发送端：
```c++
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
```
接收端：
```c++
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
```
发送进程的显示内容如下：
```
接收到来自另一端的回信：
Roger. Now replying.
```
接收进程的显示内容如下：
```
接收到来自发送端的消息：
Hi there, this is DYY sending a mail via a message queue through client 2244.
对方接收已确认。
```
下面来详细讲这两个程序里用到的消息队列相关的API和参数。再次提醒，调用这些API需要使用root权限。