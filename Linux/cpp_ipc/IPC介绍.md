# 进程间通信的多种方式
进程间通信（InterProcess Communication, 简称IPC），是指在不同进程之间交换或传递数据。
<br>以Linux系统为例。

## 方式一：无名管道(pipe)
无名管道用于从父进程向子进程**单向**传递数据。
在Linux系统的<unistd.h>头文件中，定义了用于开启一个无名管道的函数`pipe()`。
函数原型如下：
```
int pipe(int* ___pipedes);
```
这里的pipedes地址，需要传入的实际上是一个2位大小的int型数组地址。我们假设这个数组为`pipe_fd[2]`，那么`pipe_fd[0]`是管道读取端的文件标识符，`pipe_fd[1]`是管道写入端的文件标识符。
<br><br>
以下是一个程序示例。在这个示例中，由该程序通过调用fork()函数创建出一个自身的副本，这个副本会作为该程序所属进程的子进程而存在。

``` unnamed_pipe.cpp
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
