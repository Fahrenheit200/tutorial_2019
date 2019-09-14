## OpenCV背景图片还原具体任务说明
**编写一个能在理想情况下对视频背景还原的程序。**

### 这个project重点需要预备队员掌握以下内容：

- 1、了解并熟练掌握OpenCV的基础操作
- 2、makefile多文件编译。
- 3、命令行参数的应用

### 具体要求： 

1. 给定三个背景被物体遮挡的视频(./resource/*.mp4)，程序每次读取一个视频，还原出背景并使用`imshow`函数长时间展示出来。
2. README中，写明编译方法、测试方法，简述算法实现流程
3. **将结果图片保存在自己项目里新建的result文件夹中**
4. 命令行输出Recover.process()的处理时间（如1.343s）
5. 编写一个Recovery类，遵守团队代码规范下，分文件Recovery.h / Recovery.cpp对类进行定义/实现，Recovery类如下：

```
/*
* public方法、属性不可变且必须实现
* private方法、属性可自行增添
* 主函数中必须使用public方法；
*/
class Recovery{

public:
    /* readVideo
    * @param filePath 文件绝对路径
    * 根据绝对路径读取需要还原背景的文件
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

};
```


### 输入与输出格式参考：

**必须使用命令行参数进行输入**  
以下终端格式仅供参考，表述完整即可。  
输入是把视频的路径作为参数，在屏幕中长时间展示出还原出的背景图片  
如0.mp4最终还原如下：

![](result/res0.jpg)

1.mp4结果如下：
![](result/res1.JPG)

2.mp4结果如下：
![](result/res2.png)


命令行输入参数如下

```
ubuntu$: ./bin/demo ./resource/0.mp4
1.423s
^C
ubuntu$:
```


### 提醒与建议：

1. OpenCV的彩色像素值访问操作
2. STL中vector、queue等的应用
3. 可能会用到统计的基础知识和方法
4. OpenCV基础工具函数：findContours、blur、medianBlur等



### 最终功能要求：

把视频的背景完整还原


### 评分细项说明：

- 我们根据工程和结果图评判功能要求是否达标。具体如下。
- 0. 无法还原彩色图，可还原灰度图，评分在以下的基础上*0.8
- 1. 有结果图，且肉眼上不存在大量突兀噪点，达到第1点。  
- 2. 完美还原`0.mp4`,`1.mp4`的背景，达到第2点。
- 3. 完美还原`2.mp4`的背景，达到第3点。
- 4. 运算还原速度在1.5s内，达到第4点。


