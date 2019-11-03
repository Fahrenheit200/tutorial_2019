# 大数计算

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-11-2
- Version: 1.0.0
- Abstract: Arduino大数计算程序

## 使用的开发板
Arduino DUE

## 依赖库
> SD  
> SPI

## 运行
将程序下载到开发板，通过Arduino IDE的串口监视器看到初始化SD卡完毕后，在串口监视器向开发板发送字符's'即开始，执行完毕可以看到开发板发过来的信息。

## 输入文件
SD卡中的a.txt和b.txt

## 输出文件
SD卡中的SUM.TXT和PRODUCT.TXT