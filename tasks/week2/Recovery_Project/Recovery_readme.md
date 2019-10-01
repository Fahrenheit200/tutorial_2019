# Task：OpenCV背景图片还原

## Head Message

- Author: 王广烁

- Revised: 王广烁

- Date: 2019年09月29日

- Version: 1.0.0

- Abstract: 完成了第二周还原背景的任务

- Achievement: 完成了三个视频的背景还原，并带有计时功能，使用了makefile文件进行编译，编写了说明文档md（也就是此文档）


## My Algorithm

- 核心思想：补丁法

- 首先，先读取一个视频，将每一帧都存进一个vector内。之后选取中间的两个相邻帧，那么其相减就可以得到在纯黑背景下的障碍物，这样我们便可以用boundingRect函数来获取其中一个矩形框补丁。之后，我们获取随便帧，同样地用相减的方法得到两个障碍框，如果障碍框之间互不相交（可以通过函数进行判断），则记录下位置。这样就可以求出补丁的位置，并将随便帧中没有障碍物的背景块copyto到相邻帧的指定帧的同一位置上。

##Notice

- process过程只需要用零点几秒，但是实际等待时间会久于显示的运行时间。这是因为计时函数只计时了在数组中找到几个帧并且打补丁的过程，而没有计时存视频的过程（存视频的过程在readVideo中，所以没有算其时间）。如果算上其时间（之前在未整合成类的、单个cpp的计时中，Windows VS运行环境下video0需要3秒，video1需要2秒，video2需要10秒，在Ubuntu中video2进程会因为内存爆了被停止，video1与video0的运行速度均低于10秒）

- 运行后的结果图片在result文件夹中（所以在没有运行的时候result文件夹是空的）

- Resource文件夹是空的（方便上传也方便师兄师姐下载）

- 如果要进行编译请从“cmake . ”命令开始，因为文件没有上传makefile等相关文件，只有CmakeLists.txt文件

- 如果cmake不成功，也请直接输入$ ./bin/main ./Resource/video0.mp4进行文件测试即可

## Description

- 用`Recovery` 类来实现背景还原的功能，通过.h文件与.cpp文件对此类进行声明与实现即可。

- recovery类如下



				class Recovery {
				
				public:
					/* readVideo
					* @param filePath 文件绝对路径
					* 根据绝对路径读取需要还原背景的文件
					*/
					void readVideo(string filePath);
				
					/* process
					* 进行还原过程
					*/
					void process();
					/* showResult
					* 窗口展示背景还原后的结果
					*/
					void showResult();
				
				private:
				
					Mat result; 			
				
					VideoCapture test_video;       
				
					int count; 				
				
					vector<Mat> video_shot_arr;   
				
				};	



##Where I put my files

- bin         main函数

- include     Recovery.h

- src         Recovery.cpp

- test        test.cpp

- build       test.o Recovery.o(但是使用了cmake之后.o文件就会自动被clean掉)

- Resource    存放三个视频

- result      存放输出结果图片

## Library Dependencies

-依赖OpenCV 3.2.0

## Compiling Method

进入Recovery_Project的文件后，右键“在终端打开”，之后点击在终端输入“cmake .”,之后再输入“make”成功编译之后输入“./bin/main ./Resource/video0.mp4”，此处也可以直接换成video1或video2.（注意：由于算法的缺陷，video2非常消耗内存，不过之前已经发给马飞鹏师兄进行过测试，消耗时间为50s）.

- 命令行输入如下

		$ cmake .		

		$ make

		$ ./bin/main ./Resource/video0.mp4



	








