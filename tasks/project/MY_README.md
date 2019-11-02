## README of Final Project
- Author:林嘉鸿
- Revised:林嘉鸿
- Date:2019-11-2
- Version:1.0.0
- Abstract:这篇README说明了大项目的具体细节

### 文件说明
- MP3文件夹中的Arduino文件夹：音频播放器的arduino的代码，其中Host是UNO烧写到UNO板的代码，Slave是烧写到NANO板的代码
- MP3文件夹中的com.py文件：在Windows运行的上位机的python代码
- SD1文件夹：拓展部分实现大数相加程序的代码

### 进度说明
- 已完成内容：播放音乐、OLED交互界面、按键互动、动态显示频谱、上位机通信、下载音乐、大数相加
- 未完成内容：大数相乘

### 运行环境
- Win10 64位
- Arduino 1.8.10
- python3

### 硬件需求
- 一块Arduino UNO
- 一块Arduino NANO

### 需要用到的Arduino库
- #include <avr/pgmspace.h>
- #include<Adafruit_SSD1306.h>
- #include <arduinoFFT.h>
- #include <SPI.h>
- #include <SD.h>
