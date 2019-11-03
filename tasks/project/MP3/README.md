# MP3

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-11-2
- Version: 1.0.0
- Abstract: MP3

## 使用的开发板
一块Arduino MAGE，一块Arduino UNO v3， 一块Arduino NANO（主程序中有各自的硬件连接说明）

## 依赖库
1.MEGA
> SD &emsp; TimerThree  &emsp; SPI    

2.UNO
> U8glib   

3.NANO
> TimerOne   

## 运行
将三个程序分别下载到对应的开发板后，按下UNO上面的RESET按钮一次，通过面包板上面的7个按键进行交互。

## 按键说明
从左到右依次为  
上一首（橙） &emsp; 快退（绿） &emsp; 播放/暂停/选择（蓝） &emsp; 快进（黄） &emsp; 下一首（棕）  
右侧两个黑色按键为 &emsp; 上一页 &emsp; 下一页
