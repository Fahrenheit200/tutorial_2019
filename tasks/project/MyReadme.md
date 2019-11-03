# Task：实现一个四旋翼飞行器的模拟

## Head Message

- Author: 王广烁

- Revised: 王广烁

- Date: 2019年11月1日

- Version: 1.0.0

- Abstract: 完成了四旋翼飞行器的部分模拟任务

- Achievement: 完成了对四旋翼模型的物理演算，并且能够进行仿真，完成了三维图像轨迹的动态显示，完成了角度的翻转，完成了上升到指定高度与悬停的任务


## Notice

- 参考到matlab的官方教程，如果使用了四个油门作为输入量的话，反而会使得操控难度变高。所以我将输入量转化为U1,U2,U3,U4,分别为垂直上升下降高度，roll角度，yaw角度与pitch角度。

- 没有完成的任务：姿态环的实现，定点的实现，开放设计环节，构建三维模型，没有加入风阻与模拟低气压环境（还挺多没做完的的...）

- 本次的任务都是由simulink进行搭建，所以整个工程只有用到simulink，不清楚需要什么代码规范...

## What I did in each file

- myQuad.slx：本次模拟器的仿真主要由simulink进行实现。

- myQuadDynamic.m：.m文件主要用来将simulink仿真得到的数据传入工作空间中，之后再使用函数将运动的轨迹实时显示出来。

- Physics_principles.pdf：解释了四旋翼无人系统的物理原理

## How to run the code

- 打开matlab之后运行文件，先打开myQuad.slx文件，点击运行。待其compile完之后，便回到工作空间点击开myQuadDynamic.m文件，点击运行，便可以显示从h=0到h=1.5的定高与悬停轨迹。（注意：因为1.5m较低，所以如果运行.m文件之后，代表四旋翼飞行器的点会在半秒之内直接上升到1.55m，之后会有微微的调整至1.5m，大约0.8秒之后就不能看出四旋翼飞行器在移动了）


## Physics principles of the Quad

- 此部分会以pdf形式附在第三个文件里面









