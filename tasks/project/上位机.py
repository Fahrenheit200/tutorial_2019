import serial
import easygui as g

ser = serial.Serial('COM11',9600)
if not ser.isOpen():#检验串口是否打开
    ser.open()#打开串口


while(1):
    choice=g.buttonbox(msg='请选择以下操作', title='上位机程序', choices=('查看歌单', '下载歌曲', '退出'))
    if choice=='查看歌单':
        ser.write('k'.encode('utf-8')) #发送查看歌单的信号
        a=ser.readline().decode('utf-8')
        print("已有"+a[0:len(a)-2:1]+"首歌")
        for i in range(int(a[0:len(a)-2:1])):
            song_name=ser.readline().decode('utf-8')
            print(str(i+1)+"."+song_name[0:len(song_name)-2:1])#去掉最后的换行符

    if choice=='下载歌曲':
        pass

    if choice=='退出':
        exit()
