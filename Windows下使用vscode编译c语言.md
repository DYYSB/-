<a name="FxNzY"></a>
## 准备材料：
- Visual Studio Code
- mingw-gcc编译套件
<a name="oUMFN"></a>
## 配置方法：
<a name="lKeOX"></a>
### 1.配置编译环境
先下载mingw-w64的包：<br />[https://sourceforge.net/projects/mingw-w64/files/mingw-w64/](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/)<br />向下拖动一点，然后在这里选择`x86_64-win32-seh`这个选项（至少我是使用的这个选项）<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675165184889-f2762947-e50d-41ef-be09-b3e87803599b.png#averageHue=%23faf9f9&clientId=u51ece3e1-ae8d-4&from=paste&height=579&id=uca4607c9&name=image.png&originHeight=869&originWidth=1080&originalType=binary&ratio=1&rotation=0&showTitle=false&size=101582&status=done&style=none&taskId=u6723725b-ad52-410a-8c30-26bbc706e37&title=&width=720)<br />为了方便，我把这个选项的下载链接也贴出来：<br />[https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z)

- i686和x86_64的区别：i686编译32位程序，x86_64编译64位程序。除非做特殊的测试，或者程序会在一台很老很老的电脑上运行，否则选择x86_64。
- posix和win32的区别：posix是Unix/Linux系统支持的系统资源管理接口，通过它我们可以进行系统层面的调度，比如并发编程使用的pthread库就是来自于此。win32是Windows的系统接口，但是由于历史原因，Windows也兼容posix接口。如果你不会调用到posix提供的API，或者你不会把你的程序移植到非Windows系统上，或者你根本不知道我这一段话在讲什么，那么选择win32。
- seh和sjlj的区别：sjlj兼容Windows的异常处理API，seh不包含任何异常处理相关的API。大学的c语言学习暂时不会接触到异常处理，两者都可以，但是sjlj会增大编译出的二进制文件的大小，同时会有一定的性能损耗。

在下载完成后，会得到一个7z格式的压缩包。将这个压缩包解压到一个**英文目录**，得到如下文件：<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675165814372-f9b47c1b-f8a6-4888-89a7-22a05d470459.png#averageHue=%23fafaf8&clientId=u51ece3e1-ae8d-4&from=paste&height=379&id=u1b7b9609&name=image.png&originHeight=569&originWidth=674&originalType=binary&ratio=1&rotation=0&showTitle=false&size=36859&status=done&style=none&taskId=u9910fc55-9eb7-479f-80b4-cc27f3160bc&title=&width=449.3333333333333)<br />然后进行**环境变量**的配置。配置环境变量的目的是让系统知道编译器的位置。<br />使用搜索或者其他方式打开“编辑系统环境变量”窗口。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675165888324-1c192512-be10-4ba0-ac0b-3ac5877f1397.png#averageHue=%23535353&clientId=u51ece3e1-ae8d-4&from=paste&height=685&id=u29615579&name=image.png&originHeight=1028&originWidth=1196&originalType=binary&ratio=1&rotation=0&showTitle=false&size=583970&status=done&style=none&taskId=u162fc3c6-1a03-4c02-9ffa-37a490c3fe8&title=&width=797.3333333333334)<br />在弹出的窗口中选择“环境变量”。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675165934219-70ae869a-a592-4d30-8ae3-bfcabce7037c.png#averageHue=%23f7f7f6&clientId=u51ece3e1-ae8d-4&from=paste&height=559&id=u6126fefe&name=image.png&originHeight=839&originWidth=747&originalType=binary&ratio=1&rotation=0&showTitle=false&size=37585&status=done&style=none&taskId=uad0105f7-2472-4d70-ba15-d223301f9fa&title=&width=498)<br />在这里选择“系统变量”的“Path”选项，双击。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675165965189-9a3945c1-5d0e-48b8-8df6-b829fa09ec33.png#averageHue=%23f2f1f0&clientId=u51ece3e1-ae8d-4&from=paste&height=621&id=uadd00891&name=image.png&originHeight=931&originWidth=970&originalType=binary&ratio=1&rotation=0&showTitle=false&size=55446&status=done&style=none&taskId=ufbad6a04-bc6a-4cbd-ba4f-244ac69da4a&title=&width=646.6666666666666)<br />在出现的窗口中，双击选中第一行空白行，选择“浏览”，然后选择你解压缩得到的文件夹里的`bin`文件夹。<br />最后的效果应如这里的选中行所示。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166032850-ea818ddd-e3f0-4672-9c64-5733ee1c9aaa.png#averageHue=%23f3f2f1&clientId=u51ece3e1-ae8d-4&from=paste&height=531&id=u76541c65&name=image.png&originHeight=796&originWidth=827&originalType=binary&ratio=1&rotation=0&showTitle=false&size=48563&status=done&style=none&taskId=u541d75f5-26ac-466c-b58a-1493675bd1a&title=&width=551.3333333333334)<br />然后打开终端或是cmd，输入`gcc -v`。如果输出的信息不是“找不到命令”相关的信息，而是与如下信息类似的信息，那么编译环境配置成功。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166147404-bd953298-fd2e-4bb2-8a20-7225c360b34e.png#averageHue=%232d2d2d&clientId=u51ece3e1-ae8d-4&from=paste&height=637&id=u19d59347&name=image.png&originHeight=956&originWidth=1732&originalType=binary&ratio=1&rotation=0&showTitle=false&size=193605&status=done&style=none&taskId=uccb3d276-2274-4bbf-a4d4-fbc6e831e0a&title=&width=1154.6666666666667)
<a name="wtCfF"></a>
### 2.配置Visual Studio Code
先安装vscode，安装后打开。<br />在没有安装任何扩展的情况下，vscode的界面为英语。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166296145-ed12a325-cdbe-4c6a-8083-9396ef940de4.png#clientId=u51ece3e1-ae8d-4&from=paste&height=382&id=u9e0aca2e&name=image.png&originHeight=573&originWidth=73&originalType=binary&ratio=1&rotation=0&showTitle=false&size=8377&status=done&style=none&taskId=ubc78f2d5-8a01-4bf0-8e95-07dda4e8e4e&title=&width=48.666666666666664)<br />这是vscode左侧的导航栏，从上往下依次是**资源管理器**、搜索、Git源代码管理、**运行和调试**、**扩展**、远程连接。<br />加粗的三项为重要内容。<br />首先点开左边第五项，即**扩展**，然后搜索chinese，安装下图所示的扩展。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166439796-15781e91-d521-4b75-87f2-2c0b6d58c6bc.png#averageHue=%234486af&clientId=u51ece3e1-ae8d-4&from=paste&height=327&id=u82a5bce7&name=image.png&originHeight=490&originWidth=469&originalType=binary&ratio=1&rotation=0&showTitle=false&size=74488&status=done&style=none&taskId=ud10b9fcd-a50d-45d3-aa99-945624442d7&title=&width=312.6666666666667)<br />安装完成之后重启，应该可以显示中文界面了。<br />然后在**扩展**里，搜索c++，安装如图所示的扩展包。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166518486-1abaff2d-4a84-455d-a2b1-05508a7444be.png#averageHue=%235e8ba3&clientId=u51ece3e1-ae8d-4&from=paste&height=397&id=ubc1e66df&name=image.png&originHeight=596&originWidth=481&originalType=binary&ratio=1&rotation=0&showTitle=false&size=84388&status=done&style=none&taskId=ubada19a1-2885-4449-8bab-be630dcee22&title=&width=320.6666666666667)<br />（其实这个Pack内的核心功能由C/C++这个扩展提供，可以单独安装这个扩展，但是为了达到更好的效果，可以安装扩展包。）<br />安装完成之后，Visual Studio Code的配置完成。
<a name="Lnoac"></a>
### 3.配置工作文件夹
在Visual Studio Code里，不论是什么语言，每一个项目都是基于文件夹的。<br />当你打开了一个文件夹之后，vscode最下面的紫色状态条会变成**蓝色**，同时在资源管理器里可以看见当前文件夹下的所有文件和文件夹。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675166819413-1043f557-cec4-4ac4-9dcd-56a014602bb7.png#averageHue=%233383b6&clientId=u51ece3e1-ae8d-4&from=paste&height=344&id=uae67873b&name=image.png&originHeight=516&originWidth=461&originalType=binary&ratio=1&rotation=0&showTitle=false&size=19036&status=done&style=none&taskId=u6cca915c-26f4-4a2d-a26f-e2f251db289&title=&width=307.3333333333333)<br />首先新建一个c文件。比如，我这里新建了一个test.c文件。<br />这个文件的效果是，输出10行`Hello world!`。
```c
#include <stdio.h>
int main()
{
    for(int i = 0; i < 10; i++)
    {
        printf("Hello world!\n");
    }
    return 0;
}
```
在编写完程序之后，按下F5。
> 请注意：大部分的笔记本电脑的Fn系列按键都是有功能的，并且有一部分的电脑默认打开了FnLock选项。
> 因此，如果你发现你的F5按下之后实现的是F5这个按键上笔记本厂商设置的默认功能而非编译，那么请关闭FnLock或者使用Fn+F5。

![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167146270-ec892e9a-9033-424c-833d-2c3bb970ee17.png#averageHue=%23c3dcdb&clientId=u51ece3e1-ae8d-4&from=paste&height=187&id=uedbe627a&name=image.png&originHeight=281&originWidth=981&originalType=binary&ratio=1&rotation=0&showTitle=false&size=43930&status=done&style=none&taskId=u73c2896d-6266-4096-a06c-a6f58c32181&title=&width=654)<br />在弹出的窗口中，选择`C/C++: gcc.exe 生成活动文件`。<br />在选择之后，你会注意到两件事情：

1. 在你的资源管理器内，多了一个`.vscode`文件夹，里面多了一个`tasks.json`文件。
2. 你的程序已经编译，并且运行过一遍了。

![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167290031-8b57a32a-e816-442f-900f-9fa33fd5f497.png#averageHue=%23292a2d&clientId=u51ece3e1-ae8d-4&from=paste&height=127&id=u08f43afb&name=image.png&originHeight=190&originWidth=192&originalType=binary&ratio=1&rotation=0&showTitle=false&size=7480&status=done&style=none&taskId=ua7120673-7470-4f2a-befa-4e0af4aeac7&title=&width=128)<br />不论是什么语言，在工作文件夹下的.vscode文件夹内，存放着对于这个工作文件夹的编译和调试设置。<br />在内部最常接触到的是tasks.json和launch.json，后者是调试使用的配置，如果它存在就使用这个文件内部的调试指令进行调试，如果不存在就使用全局调试设置。<br />因此，刚刚实际上已经经过了一次调试的过程，只不过调试使用的是全局设置。<br />理论上我们的vscode已经可以用来编写c语言的程序了，但是为了让调试过程更加符合我们的需求，我们可以自定义launch.json。<br />先确保当前的代码页是你的c语言源文件，然后选中左侧的**运行和调试**选项框，选择`创建launch.json文件`。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167710313-e2dafa79-26df-4528-9874-ed0c4ca5eaeb.png#averageHue=%235d6e64&clientId=u51ece3e1-ae8d-4&from=paste&height=265&id=u9e26506d&name=image.png&originHeight=397&originWidth=643&originalType=binary&ratio=1&rotation=0&showTitle=false&size=40058&status=done&style=none&taskId=u93120e71-494a-4ac9-b0f2-bbb9942be9b&title=&width=428.6666666666667)<br />在弹出的代码框中，选择GDB的选项。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167738975-7a0d59dd-27e5-434a-8d3f-c12236631a17.png#averageHue=%2393b8c3&clientId=u51ece3e1-ae8d-4&from=paste&height=126&id=u23329151&name=image.png&originHeight=189&originWidth=930&originalType=binary&ratio=1&rotation=0&showTitle=false&size=13025&status=done&style=none&taskId=ucc3d5137-9f54-4737-9aa2-a46d0a91f1c&title=&width=620)

- Windows的选项是指使用Visual Studio的msvc编译器进行调试，但是由于我们使用的是gcc，因此使用gdb调试。

你会看到一个launch.json文件。选择`添加配置`，然后选择`(gdb)启动`的选项。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167855565-9cb75f81-d1eb-406b-b3e5-8d6e82c82c3d.png#averageHue=%231f1e1e&clientId=u51ece3e1-ae8d-4&from=paste&height=547&id=u19f977cb&name=image.png&originHeight=821&originWidth=1991&originalType=binary&ratio=1&rotation=0&showTitle=false&size=68671&status=done&style=none&taskId=u39202d74-ce56-4bbc-9961-e6b13ffc3db&title=&width=1327.3333333333333)<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167880856-60d98bd3-299c-46e1-8b0f-bb937ffb944f.png#averageHue=%23566f60&clientId=u51ece3e1-ae8d-4&from=paste&height=347&id=u65a00518&name=image.png&originHeight=520&originWidth=692&originalType=binary&ratio=1&rotation=0&showTitle=false&size=77553&status=done&style=none&taskId=u096ec1bc-2e78-4d4a-95df-59a9dbd11b2&title=&width=461.3333333333333)<br />注意：这是一份例样，我们需要根据我们的需要进行一部分的自定义。<br />以下这些选项一定需要修改，否则不能成功调试。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675167965982-2b80a252-a688-439a-9d20-82064f19a03f.png#averageHue=%23222120&clientId=u51ece3e1-ae8d-4&from=paste&height=238&id=ufd6fea99&name=image.png&originHeight=357&originWidth=923&originalType=binary&ratio=1&rotation=0&showTitle=false&size=58009&status=done&style=none&taskId=uc17f96b1-25ff-445b-80ad-96306212195&title=&width=615.3333333333334)<br />program项：指向编译得到的二进制文件。<br />如果你希望得到类似于Dev-C++这类IDE一样的单文件编译运行的效果，将这一项改为：<br />`"program": "${workspaceFolder}/${fileBasenameNoExtension}.exe",`<br />`${workspaceFolder}`是当前的工作文件夹的动态字符串，`${fileBasenameNoExtension}`是当前打开的源文件去掉扩展名的动态字符串，在这个字符串后加上`.exe`就是这一个源文件编译出的二进制文件。<br />这里可以修改为其他的样式，但是在这里不做展开。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675168245034-63b9b217-0c39-4601-a654-ee43de07e236.png#averageHue=%23252220&clientId=u51ece3e1-ae8d-4&from=paste&height=133&id=u554bf3de&name=image.png&originHeight=199&originWidth=962&originalType=binary&ratio=1&rotation=0&showTitle=false&size=38319&status=done&style=none&taskId=u79ab4b23-44e4-4407-b7ae-49ab5178b26&title=&width=641.3333333333334)<br />在里面添加一项preLaunchTask项。<br />这一项的意义是在调试之前运行一个命令。如果希望在调试之前进行一遍编译，就把这一项改为之前按下F5，得到的tasks.json里的命令的label。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675168384300-e01ead5a-98b2-4e94-bd35-e9f1bf540f0f.png#averageHue=%2323201f&clientId=u51ece3e1-ae8d-4&from=paste&height=82&id=u84385b5e&name=image.png&originHeight=123&originWidth=539&originalType=binary&ratio=1&rotation=0&showTitle=false&size=15519&status=done&style=none&taskId=ub8adc1a5-9780-495b-becd-9641710af43&title=&width=359.3333333333333)<br />miDebuggerPath项：调试器的位置。<br />由于之前我们已经做过了配置环境变量的工作，我们只需要把这一项改为：<br />`"miDebuggerPath": "gdb",`<br />gdb.exe存在于之前配置环境变量时输入的文件夹内，所以系统会告诉vscode`gdb.exe`存在于哪里，给vscode调用。<br />其他的选项不用操作，保存launch.json，回到之前的c语言文件，按下F5（或者Fn+F5），就可以得到调试的结果。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675168621960-9b1d6e13-5611-4e3d-ae9c-a95e9fb596d2.png#averageHue=%23b8a075&clientId=u51ece3e1-ae8d-4&from=paste&height=960&id=u5b7b6b4f&name=image.png&originHeight=1440&originWidth=2560&originalType=binary&ratio=1&rotation=0&showTitle=false&size=217631&status=done&style=none&taskId=u95d0e8f5-af1c-4949-b797-d7a3f60e828&title=&width=1706.6666666666667)<br />默认设置下，与Dev-C++的黑框不同，vscode会将终端集成在程序UI的下方。<br />你可以通过修改launch.json中的这一项：<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675168717705-02008a81-6d37-4092-a0a9-6ea1062d3b14.png#averageHue=%23242120&clientId=u51ece3e1-ae8d-4&from=paste&height=79&id=u781cb1c4&name=image.png&originHeight=119&originWidth=401&originalType=binary&ratio=1&rotation=0&showTitle=false&size=13119&status=done&style=none&taskId=u9ce5cd92-a4b6-4ad2-a0f7-e8224c1fc51&title=&width=267.3333333333333)<br />将false改为true，这样vscode的调试器会调用一个外部终端。<br />但是由于vscode的外部终端默认没有暂停选项，所以你只会看到一个一闪而过的黑框。
> 这里有一个方法，将launch.json中的这两项改成：
> "program":"C:\\Windows\\System32\\cmd.exe",
> "args": ["/c","${fileDirname}/${fileBasenameNoExtension}.exe","&","pause"],
> 本质上是讲目标程序定位到cmd，然后给cmd传输两个参数，前一个参数是你的程序位置，后一个参数让cmd暂停。
> 我自己没有试验过，我不敢保证这样还能不能正确地进行调试，但是如果只是运行，这样可以实现目的。

这里我提供我的版本的tasks.json和launch.json，可以实现类似于Dev-C++的单文件运行的效果，但是代码执行在下方的集成终端内。
```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "E:\\DeveloperTools\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```
```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) 启动",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/${fileBasenameNoExtension}.exe",
            "args": [],
            "preLaunchTask": "C/C++: gcc.exe 生成活动文件",
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```
<a name="BK3Lu"></a>
### 4.使用Visual Studio Code进行调试
上面的所有过程实际上都是调试的过程。<br />只不过我们没有设置断点，所以程序不会在任何一行中断，可以得到仅运行的效果。<br />但是有的时候，我们需要在某处暂停或是单步执行，来查看变量的变化或者异常出现的位置。<br />我们用一个含有数组的程序为例。
```c
#include <stdio.h>
int main()
{
    int fibonacci[3] = {1, 1, 0};
    while(fibonacci[2] < 10000)
    {
        fibonacci[2] = fibonacci[0] + fibonacci[1];
        fibonacci[0] = fibonacci[1];
        fibonacci[1] = fibonacci[2];
    }
    printf("%d\n", fibonacci[2]);
    return 0;
}
```
这个程序会不断地演算斐波那契数列，直到得到一个大于10000的数。<br />我们首先设置一个断点。断点的设置方法是在你希望暂停的那一行代码前面点红。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169657191-28bad8a3-3e50-4930-8053-df7319b5b636.png#averageHue=%231f1f1e&clientId=u51ece3e1-ae8d-4&from=paste&height=338&id=ub6370191&name=image.png&originHeight=507&originWidth=829&originalType=binary&ratio=1&rotation=0&showTitle=false&size=49005&status=done&style=none&taskId=u15e7f3c3-0eea-4485-9278-5068398758d&title=&width=552.6666666666666)<br />之后的调试过程中，程序会在这一行暂停。我们按下F5（或者Fn+F5），开始调试。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169700715-bec1c413-b62e-409f-91bc-a2e946a1bb3e.png#averageHue=%235a5a27&clientId=u51ece3e1-ae8d-4&from=paste&height=443&id=uf2b4e0bc&name=image.png&originHeight=664&originWidth=1391&originalType=binary&ratio=1&rotation=0&showTitle=false&size=93586&status=done&style=none&taskId=u3f373c5e-2c02-4b5d-8a19-9d5ddf13827&title=&width=927.3333333333334)<br />黄色高亮行代表程序目前的执行位置。<br />左边的**变量**窗口里，会列出所有在当前代码域的变量，比如这里的**fibonacci[3]数组的三个元素**。我们将箭头点开，可以看到第0、1、2三个元素的数值。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169796206-b833c8e4-5cef-4824-a35f-75503cffcda9.png#averageHue=%23212a32&clientId=u51ece3e1-ae8d-4&from=paste&height=143&id=u5f86e608&name=image.png&originHeight=215&originWidth=223&originalType=binary&ratio=1&rotation=0&showTitle=false&size=6914&status=done&style=none&taskId=uc30e1a93-9ebd-4a8f-9d23-fa17a9f675d&title=&width=148.66666666666666)<br />我们也可以在下面的监视窗口，设置一个我们希望一直观察的变量，比如fibonacci[2]。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169913212-4ac9f8f2-f2f1-4c18-bcd3-4a1064002f53.png#averageHue=%233a8ec4&clientId=u51ece3e1-ae8d-4&from=paste&height=92&id=ud0177733&name=image.png&originHeight=138&originWidth=431&originalType=binary&ratio=1&rotation=0&showTitle=false&size=7432&status=done&style=none&taskId=u63ed3e85-7623-4529-85ff-bc0a43005ec&title=&width=287.3333333333333)<br />然后回车，就可以对fibonacci[2]这个变量进行监视。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169937333-49a7b83b-2be9-4707-b6e3-329631f77383.png#averageHue=%23252527&clientId=u51ece3e1-ae8d-4&from=paste&height=78&id=u5a1d3a4d&name=image.png&originHeight=117&originWidth=263&originalType=binary&ratio=1&rotation=0&showTitle=false&size=4386&status=done&style=none&taskId=u7033265c-4fef-445f-ab1e-4fcfad35e1a&title=&width=175.33333333333334)<br />这里的监视的对象可以是一个**变量**，也可以是一个**表达式**。<br />然后我们会注意到UI里有一个控制条。<br />![image.png](https://cdn.nlark.com/yuque/0/2023/png/33721123/1675169988911-0bd457a1-5a99-4e7e-a922-a24437d87523.png#averageHue=%23b46c5d&clientId=u51ece3e1-ae8d-4&from=paste&height=46&id=u46d71341&name=image.png&originHeight=69&originWidth=294&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3428&status=done&style=none&taskId=u42e851ea-7619-42ed-bec3-ec37981fe01&title=&width=196)<br />里面最常用的三个按钮是第一个**继续**（F5），第三个**单步执行**（F11）和最后一个**结束**。<br />**继续**的效果是让程序跳转到下一个断点处。<br />注意这个gif中，左侧变量的变化。<br />![test2.gif](https://cdn.nlark.com/yuque/0/2023/gif/33721123/1675170689351-14f0455b-b85a-4bff-9010-ed871595b9e0.gif#averageHue=%23779393&clientId=u51ece3e1-ae8d-4&from=drop&id=u86ae9fdf&name=test2.gif&originHeight=642&originWidth=1306&originalType=binary&ratio=1&rotation=0&showTitle=false&size=275119&status=done&style=none&taskId=u71d682d1-5315-4598-8b12-afd6025258b&title=)<br />**单步执行**是让程序一行一行向下执行。<br />注意这个gif中，高亮行和左侧变量的变化（左侧变量有一定的延迟）。<br />![test22.gif](https://cdn.nlark.com/yuque/0/2023/gif/33721123/1675170889131-7cdcfeef-53ba-4d86-88fd-241bf6c9812b.gif#averageHue=%231e1f22&clientId=u51ece3e1-ae8d-4&from=drop&id=ua71ad2eb&name=test22.gif&originHeight=642&originWidth=1305&originalType=binary&ratio=1&rotation=0&showTitle=false&size=817309&status=done&style=none&taskId=u49148483-bda4-480a-a79d-5c42114732e&title=)

