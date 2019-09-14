## OpenCV背景图片还原具体任务说明
**编写一个能在理想情况下对视频背景还原的程序。**

### 这个project重点需要预备队员掌握以下内容：

- 1、了解并熟练掌握OpenCV的基础操作。
- 2、makefile多文件编译。
- 3、命令行参数的应用。

### 具体要求： 

- 1、给定三个背景被物体遮挡的视频(./resource/*.mp4)，程序每次读取一个视频，还原出背景并使用`imshow`函数长时间展示出来。
- 2、使用计时工具，在命令行输出Recover.process()的处理时间。（如1.343s）
- 3、请在README中写明编译方法、测试方法，简述算法实现流程。
- 4、按照[《团队代码规范》](https://github.com/SYSU-AERO-SWIFT/tutorial_2019/blob/master/docs/team_code_style.md) 中第三点工程目录格式，分bin，build，src，include，resource文件夹，makefile与这些文件夹同级。
- 5、**将结果图片保存在自己项目里新建的result文件夹中。**
- 6、将处理代码编写在Recovery类中，分文件Recovery.h / Recovery.cpp对类进行定义/实现，Recovery类如下：

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
输入是把视频的路径作为参数，在屏幕中长时间展示出还原出的背景图片。  
如video0.mp4最终还原如下：

![](result/res0.jpg)

video1.mp4结果如下：
![](result/res1.jpg)

video2.mp4结果如下：
![](result/res2.png)


命令行输入参数如下：

```
ubuntu$: ./bin/demo ./resource/video0.mp4
Process time: 1.423s
^C
ubuntu$:
```


### 提醒与建议：

- 1. OpenCV的彩色像素值访问操作。
- 2. 会涉及STL中vector、queue等的应用。
- 3. 可能会用到统计的基础知识和方法。
- 4. OpenCV基础工具函数：findContours、blur、medianBlur等。
- 5. 计时的库可用time.h或chrono。



### 评分细项说明：

- 我们根据工程和结果图评判功能要求是否达标。具体如下。

- 1. 如无法还原彩色图，可还原灰度图，评分在以下的基础上乘**0.5倍**。
- 2. 有结果图，且肉眼上不存在大量突兀噪点，达到第1点。  
- 3. 输出结果图中，缺陷噪点集中区约占图片面积1/10：得**0%**分数，只有零散噪点：得**50%**分数，基本完美还原：得**100%**分数。
- 4. 成功还原`video0.mp4`的背景，达到第2点。
- 5. 成功还原`video1.mp4`的背景，达到第3点。
- 6. 成功还原`video2.mp4`的背景，达到第4点。

### 附录：结果图片效果参考

大片集中缺陷，分值0%：
![](result/0%.png)

零散噪点，分值50%：
![](result/50%.png)

完美，分值100%：
![](result/res1.jpg)

