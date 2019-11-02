# -*- coding: utf-8 -*-
import PySimpleGUI as sg
from serial import Serial
import struct
#form = sg.FlexForm('串口通信 Music Up&Reloader', default_element_size=(80, 1))

com=('COM1','COM2','COM3','COM4','COM5','COM6','COM7','COM8','COM9','COM10')
baud_rate=('1200','2400','4800','9600','115200')
Stop_bit=('1','1.5','2')
data_bit=('8','7','6','5')
verify=('无','奇校验','偶校验')

layoutBasic =  [[sg.Text('COM口:'),sg.InputCombo(com,size=(30, 1))],
                [sg.Text('波特率:'),sg.InputCombo(baud_rate,size=(30, 1))],
                [sg.Text('停止位:'),sg.InputCombo(Stop_bit,size=(30, 1))],
                [sg.Text('数据位:'),sg.InputCombo(data_bit,size=(30, 1))],
                [sg.Text('奇偶位:'),sg.InputCombo(verify,size=(30, 1))],
                [sg.RButton('连接串口',size=(20,1)),sg.RButton('关闭串口',size=(20,1))]]

layoutInputBox=[[sg.Text('名字:'),sg.InputText(default_text='/*音乐名 ASCII 小于15个字符*/',key='musicName',size=(30,1)),
                 sg.Text('序号:'),sg.InputText(default_text='/*写入的位置*/',key='writeIndex',size=(30,1))],
                [sg.Text('音乐:'),sg.Multiline(default_text='/*音符和节拍*/',key='musicContent',size=(80, 5))],
                [sg.RButton('上传',size=(20,1))]]

layoutOutputBox=[[sg.Text('读取的音乐序号:'),sg.InputText(default_text='/*小于20*/',key='musicIndex',size=(15,1)),sg.RButton('读取',size=(10,1))],
                 [sg.Text('音乐:'),sg.Multiline(default_text='',key='readMusic',size=(80, 5))]]

layout=[[sg.Frame('选择参数',layoutBasic)],
        [sg.Frame('上传音乐',layoutInputBox)],
        [sg.Frame('读取音乐',layoutOutputBox)]]
#form.Layout(layout).Read()

window=sg.Window('串口通信 Music Up&Reloader').Layout(layout)
totnum=0

def processUpload(name,content,writepos):
    tempContent=content.split(' ')
    dat=[]
    dat.append(int('0xfa',16)) #起始位
    if int(writepos)>int(totnum[0]):
        writepos=totnum[0]
    dat.append(int(writepos))
    for i in range(min(len(name),14)):
        dat.append(ord(name[i]))
    for i in range(14-len(name)):
        dat.append(int('0x00',16))
    dat.append(len(name))
    dat.append(len(tempContent))
    print(len(tempContent))
    print(tempContent)
    for i in range(min(len(tempContent),176)):
        dat.append(int(tempContent[i],16))
    dat.append(int('0xff',16)) #起始位
    return dat

def processIndex(index):
    dat=[]
    dat.append(int('0xfc',16)) #起始位
    dat.append(int(index))
    dat.append(int('0xff',16)) #结束位
    return dat

def getName(nameLine):
    name=''
    length=int(nameLine[14])
    for i in range(length):
        name=name+chr(int(nameLine[i]))
    return name

def getNumber(nameLine):
    if int(nameLine[15])==0:
        return 176
    return int(nameLine[15])
    
def getMusic(musicData):
    music=''
    for i in range(len(musicData)):
        tmp=hex(musicData[i])
        if len(tmp)==3:
            tmp='0x0'+tmp[2]
        music=music+tmp+' '
    return music

isRun=True

while True:
    button, value = window.Read(timeout = 100)

    if button==None and value==None:
        print('程序已结束')
        isRun=False
        break
#------------------------------------------------------------------------------
    if button=='连接串口':
        ser = Serial()
        ser.port = value[0]
        ser.baudrate = int(value[1])
        ser.stopbits=1
        ser.bytesize=8
        ser.parity='N'

        ser.timeout=5
        try:
            ser.open()
            sg.Popup('连接成功')
            ser.write(struct.pack(("B"),int('0xfd',16)))
            totnum=ser.read(1)
            sg.Popup('总共已存 '+str(int(totnum[0]))+' 首歌')
        except Exception as e:
            sg.Popup('连接失败')

#------------------------------------------------------------------------------
    if button=='关闭串口':
        try:
            ser.write(struct.pack(("B"),int('0x99',16)))
            sg.Popup('关闭成功')
        except Exception as e:
            sg.Popup('关闭失败')
    if button=='上传':
        if ser!=None and ser.is_open:
            if value['musicName']!='' and value['musicContent']!='':
                try:
                    name=value['musicName']
                    content=value['musicContent']
                    writepos=value['writeIndex']
                    sendData=processUpload(name,content,writepos)
                    for i in range(len(sendData)):
                        ser.write(struct.pack(("B"),sendData[i]))
                    sg.Popup('下载成功')
                    ser.write(struct.pack(("B"),int('0xfd',16)))
                    totnum=ser.read(1)
                    '''
                    feedback=ser.read(1)
                    if feedback[0]==1:
                        sg.Popup('下载成功')
                    else:
                        sg.Popup('下载失败')
                        continue
                    '''
                except Exception as e:
                    sg.Popup('写入失败')
            else:
                sg.Popup('请输入内容')
        else:
            sg.Popup('没有连接')
            continue
#------------------------------------------------------------------------------
    if button=='读取':
        if ser!=None and ser.is_open:
            if value['musicIndex']!='':
                try:
                    index=value['musicIndex']
                    sendData=processIndex(index);
                    for i in range(len(sendData)):
                        ser.write(struct.pack(("B"),sendData[i]))
                    
                    feedback=ser.read(1)
                    if feedback[0]==1:
                        sg.Popup('发送请求成功')
                    else:
                        print(feedback[0])
                        sg.Popup('发送请求失败')
                        continue
                    
                    nameLine=ser.read(16)
                    nameText=getName(nameLine)
                    num=getNumber(nameLine)
                    
                    musicData=ser.read(num)
                    musicText=getMusic(musicData)
                    
                    text='name:\n'+nameText+'\n'+'music:\n'+musicText
                    window.FindElement('readMusic').Update(text)
                except Exception as e:
                    sg.Popup('读取失败')
            else:
                sg.Popup('请输入内容')
                continue
        else:
            sg.Popup('没有连接')
            continue
ser.close()