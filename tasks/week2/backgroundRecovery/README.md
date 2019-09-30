## 任务：背景图片还原

- 作者：蓝钰乔
- 修订：蓝钰乔
- 日期：2019年09月30日
- 版本：1.0.0
- 摘要：背景图片还原任务



## 算法

算法的原理比较简单，是受 *Learning OpenCV* 中背景建模的平均帧法的启发，对视频的每一帧全部叠加求平均，只要帧数够多就可以还原出背景。

## 编译方法

1. 在终端中将工作目录转到`backgroundRecovery`下

   ```shell
   $ cd tutorial_2019/tasks/week2/backgroundRecovery_project
   ```

   

2. 输入命令`make`，终端显示

   ```shell
   g++ -c src/Recovery.cpp include/Recovery.h `pkg-config --cflags --libs opencv` -I include/ -I src/
   g++ -c src/main.cpp include/Recovery.h  `pkg-config --cflags --libs opencv` -I src/ -I include/
   g++ -o Recovery.o main.o `pkg-config --cflags --libs opencv` -I include/ -o bin/test.out
   ```

   

3. 转到`bin`目录下

   ```
   $ cd bin
   ```

   

4. 执行测试文件，传入视频开始处理（以video0.mp4为例）

   ```shell
   $ ./test.out ../../resource/video0.mp4
   ```

   

5. 可以在终端看到处理的时间以及处理的结果

   ```shell
   processing time: 2.47838s
   ```

   

6. 按任意键关闭输出的窗口，并进入`result`目录查看输出的图片

   ```shell
   $ cd ..
   $ cd result
   ```

   

