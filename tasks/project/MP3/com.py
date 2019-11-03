import serial
import time
import re

serialPort = "COM3"  # 串口
baudRate = 9600  # 波特率
ser = serial.Serial(serialPort, baudRate, timeout=0.1)
print("参数设置：串口=%s ，波特率=%d" %(serialPort, baudRate))

tune_path="C:/Users/LomGaHong/Desktop/tune.txt"
duation_path="C:/Users/LomGaHong/Desktop/duation.txt"
name_path="C:/Users/LomGaHong/Desktop/name.txt"
instruction=" "

while True:
	s=ser.readline()
	if(s==b'begin\r\n'):
		print("////////////////")
		print("已连接到音乐播放器")
		print("////////////////")
		while True:
			print("请选择你想要执行的操作:")
			print("1.查看音乐播放器中已存储的音乐")
			print("2.下载音乐到音乐播放器")
			print("3.断开连接")
			instruction=input("请输入操作编号：");
			s=ser.readline();
			if(s==b'end\r\n'):
				print("////////////////////")
				print("已与音乐播放器断开连接")
				print("////////////////////")
				break

			if(instruction=="1"):
				ser.write(b'1')
				print("////////////////")
				while True:
					s=ser.readline();#等待响应
					if(s==b'beginone\r\n'):#读到数据头
						print("The music stored in the player is listed below:")
						while True:
							s=ser.readline()
							if(s==b'endone\r\n'):#设置断点
								break
							ss=str(s, encoding = "utf-8")
							print(re.sub('[\r\n]','',ss))#输出
					if(s==b'endone\r\n'):#设置断点
						print("/////////////////////")
						break

			elif(instruction=="2"):
				ser.write(b'2')
				print("////////////////")
				while True:
					s=ser.readline();#等待响应
					if(s==b'begintu\r\n'):#读到数据头
						# tune发送前的准备
						with open(tune_path) as f1:
							tune_data=f1.readline()
						print("读取音符文件：",tune_data)
						tu_store=tune_data.split(',')
						num=int(tu_store[0])
						i=0;
						while(i<=num):
							s=ser.readline();#等待响应
							# ss=str(s, encoding = "utf-8")
							# print(re.sub('[\r\n]','',ss))#输出
							if(s==b'OK\r\n'):#读到数据头
								# print("i=",i)
								print("发送：",tu_store[i])
								# ss=str(s, encoding = "utf-8")
								# print(re.sub('[\r\n]','',ss))#输出
								tune_string=bytes(tu_store[i],'utf-8')
								ser.write(tune_string)
								i=i+1
						while True:
							s=ser.readline();#等待响应
							if(s==b'begindu\r\n'):#读到数据头
								# duation发送前的准备
								with open(duation_path) as f2:
									duation_data=f2.readline()
								print("读取节拍文件：",duation_data)
								du_store=duation_data.split(',')
								i=0;
								while(i<num):
									s=ser.readline();#等待响应
									# ss=str(s, encoding = "utf-8")
									# print(re.sub('[\r\n]','',ss))#输出
									if(s==b'OK\r\n'):#读到数据头
										# print("i=",i)
										print("发送：",du_store[i])
										# ss=str(s, encoding = "utf-8")
										# print(re.sub('[\r\n]','',ss))#输出
										duation_string=bytes(du_store[i],'utf-8')
										ser.write(duation_string)
										i=i+1
								while True:
									s=ser.readline();#等待响应
									# ss=str(s, encoding = "utf-8")
									# print(re.sub('[\r\n]','',ss))#输出
									if(s==b'beginname\r\n'):#读到数据头
										with open(name_path) as f3:
											name_data=f3.readline()
										print(name_data)
										name_string=bytes(name_data,'utf-8')
										ser.write(name_string)
										break
								
							if(s==b'endtwo\r\n'):
								break
					if(s==b'endtwo\r\n'):
						break	

			elif(instruction=="3"):
				ser.write(b'3')
				print("////////////////////")
				print("已与音乐播放器断开连接")
				print("////////////////////")
				break
			else:
				print("//////////////////")
				print("命令无效，请重新输入")
				print("//////////////////")
	if(instruction=="3" or s==b'end\r\n'):
		break
ser.close() 