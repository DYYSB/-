#include <cstdio>
#include <thread>
#include <termio.h>

bool if_running;

int scanKeyboard()
{
    int input;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    // 这里有一个位操作，ICANON是一个整行缓存，~了它的目的是屏蔽整行缓存实现单个读取
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
      
    input = getchar();
      
    tcsetattr(0,TCSANOW,&stored_settings);
    return input;
}

void printmy()
{
    while(if_running)
    {
        printf("Hello world!");
    }
}

void getkey()
{
    if(scanKeyboard() == 'a')
    {
        if_running = false;
    }
}

int main()
{
    if_running = true;
    std::thread t1(printmy);
    std::thread t2(getkey);
    t1.detach();
    t2.join();
    return 0;
}