## 任务：OpenCV背景图片还原

## 表头信息

- 作者: 雷发兴
- 修订: 雷发兴
- 日期: 2019年09月28日
- 版本: 1.0.0
- 摘要: 第二周OpenCV背景图片还原任务，编写一个能在理想情况下对视频背景还原的程序。

## 算法思路
核心思想是对视频中的每一帧照片的相同像素点值取众数，例如视频`video0.mp4`共有20帧图片，则对这20帧照片的相同像素点值取众数，循环遍历所有像素点，将所有取得的值写入新的`Mat`对象中，该`Mat`对象就是还原出来的背景图片。由视频的分辨率过高，程序处理时间略长，处理视频`video0.mp4`大概需要7秒钟，处理视频`video1.mp4`大概需要6秒钟，处理视频`video2.mp4`大概需要60秒钟，希望负责测试的人员能够耐心等待。

## 说明内容

### 将处理代码编写在 `Recovery` 类中，分文件 `Recovery.h` / `Recovery.cpp` 对类进行定义/实现，`Recovery` 类如下：

   ```cpp
   class Recovery {

   public:
       /* readVideo
       * @param filePath 文件路径
       * 根据输入路径读取需要还原背景的文件，注意，不是输入绝对路径，具体操作方法见下
       * 下文
	*/
       void readVideo(String filePath);

       /* process
       * 进行还原过程
       */
       void process();

       /* showResult
       * 窗口展示背景还原后的结果
       */
       void showResult();

   private:
	/* getMode
	* @param A 元素为 uchar 型的 vector 容器
	* 获取 A 中的众数
	*/
	uchar getMode(vector<uchar>& A); 
	//储存处理后的图片
	Mat outputImage;
	//进行处理的总帧数
	long totalFrameNumber;	
	//视频文件的路径
	string file_path;	
   };
   ```
### 依赖库

-依赖OpenCV 3.2.0

##一些提醒和建议（必看，必看）
1.  `bin`，`build`，`src`，`include`，`resource` 文件夹均存放在`backgroundRecovery_project`文件夹中，`makefile` 与这些文件夹同级。

2. 视频文件保存在`backgroundRecovery_project`文件目录的`resourse`文件夹中

3. 我的头文件放在`include`文件夹中，`.cpp`源文件均放在`src`文件夹中， **程序处理出来的图片保存在`result`文件夹中** 。

4. `CMakeList.txt` 文件和 `Makefile` 文件与`bin`，`src``build`文件夹同级，保存在backgroundRecovery_project文件夹中，


### 编译提示（画重点，请一定要按提示进行编译操作）
1. 先在终端中将文件目录转换到 `backgroundRecovery_project`文件夹下，即 `tutorial_2019/tasks/week2/backgroundRecovery_project`，然后输入指令 cmake .  **注意，指令为：cmake+空格+"."，不是两点** 生成`Makefile`文件,再输入指令 `make` 即可编译链接生成可执行文件 `Demo`(生成的可执行文件`Demo`就在当前目录`backgroundRecovery_project`下，与`CMakeLists.txt`文件同级)
参考命令行效果如下：
```shell
$ cd tutorial_2019/tasks/week2/backgroundRecovery_project
$ cmake .
$ make
Scanning dependencies of target Demo
[ 33%] Building CXX object CMakeFiles/Demo.dir/src/main.cpp.o
[ 66%] Building CXX object CMakeFiles/Demo.dir/src/Recovery.cpp.o
[100%] Linking CXX executable Demo
[100%] Built target Demo
```

2. 在当前文件目录下，输入指令 ./Demo ./resource/video0.mp4 即可运行可执行文件"Demo"对视频video0.mp4进行处理（不需要转入`build`文件夹中操作，直接在当前文件目录下），**注意，视频文件目录请按要求输入**
参考命令行效果如下：
```shell
$ ./Demo ./resource/video0.mp4
正在处理中，请耐心等待...
process time: 6.29249 s
$ ./Demo ./resource/video1.mp4
正在处理中，请耐心等待...
process time: 5.98777 s
$ ./Demo ./resource/video2.mp4
正在处理中，请耐心等待...
process time: 62.4999 s

```

##注意，为了避免编译链接步骤失败，无法运行程序的情况出现，我准备了一个备用方案 
我在bin文件夹中已经存放了一个事先生成的可执行文件`Demo`，当编译链接操作失败时，可以在终端中转入`bin`文件夹目录直接输入指令 ./Demo ./resource/video0.mp4 运行程序，则处理出来的图片也会生成在bin文件夹中










