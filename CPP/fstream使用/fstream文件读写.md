## 2022.11.3
今天来学习一下使用流格式`fstream`进行文件的读写。

在我比较远古的noip记忆里，进行文件读写的办法大抵也许好像是有四种：
（1）使用`freopen()`函数**重定向**，写法简单，但是运行效率相对较低；
（2）使用C语言风格的`FILE`指针；
（3）我记不得了(＠_＠; )
那这个可能的第四种，就是我们今天需要学习的，使用C++风格的流输入输出库`fstream`。

PS.要在 C++ 中进行文件处理，必须在 C++ 源代码文件中包含头文件`<iostream>`和`<fstream>`。

### 1.fstream库有啥内容？
从最基本的角度来讲，`fstream`库中定义了三种**类**：
（1）**`ifstream`类**：用于进行**文件的读取**；
（2）**`ofstrean`类**：用于进行**文件的创建和文件的写入**；
（3）**`fstream`类**：包含**以上两者的功能**。
用这些类定义成员的方式如下：
```
fstream file1;
```
既然fstream是一个万金油数据类型，那我们就直接用fstream咯(●'◡'●)

### 2.打开文件
`open()`函数是这三种对象的一个成员函数。函数定义如下：
```
void open(const char *filename, ios::openmode mode);
```
前一个传入值是**文件路径**，后一个传入值是**文件的使用方式**。
文件的使用方式如下：
（1）`ios::in`：打开文件以读取；
（2）`ios::out`：打开文件以写入；
（3）`ios::ate`：打开文件后定位到文件末尾；
（4）`ios::app`：打开文件，将所有写入追加到文件末尾；
（5）`ios::trunc`：如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为0。

如果你需要同时使用几种使用方式，可以用`|`分隔开。就像这样：
```
fstream file1;
file1.open("dyy.nb", ios::in | ios::out);
```

### 3.关闭文件
使用`close()`成员函数，使用方式与open类似。
```
fstream file1;
file1.open("dyy.nb", ios::in | ios::out);
file1.close();
```

### 4.读取和写入
用`fstream`方式读取和写入文件的好处，就是它的`iostream`一样，都是流式输入输出，因此`fstream`的使用方式和`cin`还有`cout`是类似的。

在这个例子中，我会将`dyynb`这个字符串输入`dyynb.txt`文件中。

<u>example1.cpp</u>
```
#include <fstream>
using namespace std;

int main()
{
    fstream file1;
    file1.open("dyynb.txt", ios::out);
    file1 << "dyynb";
    file1.close();
    return 0;
}
```
<br>
<u>dyynb.txt</u>
```
dyynb
```
<br>
下面这个例子，我会从`dyydatain.txt`中读取两个数，计算它们的和，输出到`dyydataout.txt`中。
<br>
<u>example2.cpp</u>
```
#include <fstream>
using namespace std;

int main()
{
    ifstream file1;
    file1.open("dyydatain.txt", ios::in);
    ofstream file2;
    file2.open("dyydataout.txt", ios::out);
    int a, b;
    file1 >> a >> b;
    file2 << a + b;
    file1.close();
    file2.close();
    return 0;
}
```
<br><u>dyydatain.txt</u>
```
34 21
```
<br><u>dyydataout.txt</u>
```
55
```
由此可见，`fstream`的使用方式和`iostream`几乎类似，只不过`cin`和`cout`需要换成用户自己定义的对象。

在`string`库中，定义了一个用于读取整行字符串的函数`getline()`。这个函数的定义如这个例子所示：
```
string str;
getline(cin, str);
```
前一个传入值是当前的输入流，后一个传入值是字符串变量的名称。
那既然是输入流，那fstream也是受支持的。

下面这个例子，我会从一个文件里读取一行字符串，然后向屏幕输出这行字符串里大写字母、小写字母、空格、数字和其他字符的数量。

<u>example3.cpp</u>
```
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream file1;
    file1.open("dyydatain.txt", ios::in);
    string str;
    getline(file1, str);        //注意这一行
    int upper = 0, lower = 0, blank = 0, number = 0, others = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            upper++;
        else if (str[i] >= 'a' && str[i] <= 'z')
            lower++;
        else if (str[i] >= '0' && str[i] <= '9')
            number++;
        else if (str[i] == ' ')
            blank++;
        else
            others++;
    }
    cout << upper << " upper cases, " << lower << " lower cases, " << number << " numbers, " << blank << " blanks, " << others << " other characters. ";
    file1.close();
    return 0;
}
```
<br><u>dyydatain.txt</u>
```
123asdADSDFF aaa sd/*-gdf4568 465rt/*-89H(*Uh9)
```
输出结果如下：
```
8 upper cases, 14 lower cases, 13 numbers, 3 blanks, 9 other characters. 
```

直接使用`file1 >> str`也是可以读入字符串的，但是用法和使用`cin`读取字符串一样，以空格和回车作为分隔符。

当然，也是可以用一个超级大的字符数组，来读入整个文件的内容。

<u>example4.cpp</u>
```
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream file1;
    file1.open("dyydatain.txt", ios::in);
    char str[30000] = {'\0'};
    for(int i = 0; !file1.eof(); i++)
    {
        file1 >> str[i];
    }
    for(int i = 0; i < strlen(str); i++)
    {
        cout << str[i];
    }
    file1.close();
    return 0;
}
```
<br><u>dyydatain.txt</u>
```
I'm sitting here in a boring room
It's just another rainy Sunday afternoon
I'm wasting my time I got nothing to do
I'm hanging around I'm waiting for you
But nothing ever happens and I wonder
I'm driving around in my car
I'm driving too fast I'm driving too far
I'd like to change my point of view
I feel so lonely I'm waiting for you
But nothing ever happens, and I wonder
I wonder how, I wonder why
Yesterday you told me about the blue blue sky
And all that I can see
is just another lemon tree
I'm turning my head up and down
I'm turning turning turning
turning turning around
And all that I can see
is just a yellow (another) lemon tree
```

输出如下：
```
I'msittinghereinaboringroomIt'sjustanotherrainySundayafternoonI'mwastingmytimeIgotnothingtodoI'mhangingaroundI'mwaitingforyouButnothingeverhappensandIwonderI'mdrivingaroundinmycarI'mdrivingtoofastI'mdrivingtoofarI'dliketochangemypointofviewIfeelsolonelyI'mwaitingforyouButnothingeverhappens,andIwonderIwonderhow,IwonderwhyYesterdayyoutoldmeabouttheblueblueskyAndallthatIcanseeisjustanotherlemontreeI'mturningmyheadupanddownI'mturningturningturningturningturningaroundAndallthatIcanseeisjustayellow(another)lemontree
```
可见，用流格式直接输入字符仍然会过滤掉空格、回车和逗号。
在cin中，可以使用`cin.get()`函数，来避免过滤这些符号。在文件流中，这个函数仍然是适用的。
<br><u>example5.cpp</u>
```
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream file1;
    file1.open("dyydatain.txt", ios::in);
    char str[30000] = {'\0'};
    for(int i = 0; !file1.eof(); i++)
    {
        str[i] = file1.get();
    }
    for(int i = 0; i < strlen(str); i++)
    {
        cout << str[i];
    }
    file1.close();
    return 0;
}
```
输入文件dyydatain.txt和上一个文件一致。输出如下：
```
I'm sitting here in a boring room
It's just another rainy Sunday afternoon
I'm wasting my time I got nothing to do
I'm hanging around I'm waiting for you
But nothing ever happens and I wonder
I'm driving around in my car
I'm driving too fast I'm driving too far
I'd like to change my point of view
I feel so lonely I'm waiting for you
But nothing ever happens, and I wonder
I wonder how, I wonder why
Yesterday you told me about the blue blue sky
And all that I can see
is just another lemon tree
I'm turning my head up and down
I'm turning turning turning
turning turning around
And all that I can see
is just a yellow (another) lemon tree
```
除了我不知道最后一个符号是不是'\0'以外，其他的输入和输出都是没有问题的。