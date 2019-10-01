-Author:Breeze Chou

-Revised:Breeze Chou

-Date:2019-9-30

-Version:1.0.0

项目结构

background_recovery

|-bin/(可执行文件)

|- inc/(类声明)

|- src/(类实现)

|- test（测试程序，主函数放在这里面）

|- README.md(说明文档)


编译说明：

在test文档中打开terminal，输入命令$ g++ test.cpp -o test `pkg-config --cflags --libs opencv`

再输入 $ ./test   然后输入视频名即可

本人测试时间都在两分钟以内

