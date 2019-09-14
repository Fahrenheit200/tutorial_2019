## 基础考核 - 第二周（9.23-9.29）

必学内容：

- 1、入门OpenCV。
- 2、使用makefile。
- 3、掌握基本的markdown语法。

选修内容：

- 1、多旋翼无人机飞行操控。（队伍会提供[DJI Flight Simulator](https://www.dji.com/cn/simulator)飞行模拟器，如果你在学校有空余时间，可以来实验室的模拟器上练习。训练飞行器操控技巧的一个重要目的在于：避免损失贵重的无人机。无人机在调试或实际飞行时可能遇到意外情况或者失控，如果没有良好的飞行器操控技巧我们不会冒险让你使用无人机。）
- 2、习惯阅读英文文档以及官方Document。

本周任务：
- 1、编写一个**多文件**的C++程序，用OpenCV写一个视频背景还原器。具体要求请阅读[详细说明](https://github.com/SYSU-AERO-SWIFT/tutorial_2019/blob/master/tasks/week2/background_recovery.md)。并阅读[《中大空中机器人团队代码规范》](https://github.com/SYSU-AERO-SWIFT/tutorial_2019/wiki/%E5%9B%A2%E9%98%9F%E5%8D%8F%E4%BD%9C%E8%A7%84%E8%8C%83) ，按照相应规范编写该程序。
- 2、为上述工程写一个makefile文件并编译运行通过。
- 3、用git上传到Github上，并使用markdown按照《团队代码规范》写一份说明文档`README.md`。
- 4、完成[程序设计能力练习](https://github.com/SYSU-AERO-SWIFT/tutorial_2019/blob/master/tasks/week2/programming_exercise.md)第二周题目链表加法，使用g++编译。  
- 5、 完成[Shell练习题](https://github.com/SYSU-AERO-SWIFT/tutorial_2019/blob/master/shell_exercise.md)。可参考[菜鸟教程](http://www.runoob.com/linux/linux-shell.html)，掌握基础命令即可。

评分标准：  

| 评分项               | 积分值                      |
| ----------------    | -------------------------- |
| 还原并显示背景图  | 60分       |
| 成功还原video0.mp4背景图                  | 0～30分        |
| 成功还原video1.mp4背景图                  | 0～50分        |
| 成功还原video2.mp4背景图                  | 0～20分        |
| 输出程序运行计时                  | 5分        |
| 程序还原时间均在限时内 | 10分（附加，总分不超过200）|
| 使用 makefile 成功编译运行       | 10分              |
| 编写说明文档       | 10分              |
| 完成第二周程序设计题 | 5分              |
| Shell 练习题       | 10分              |
