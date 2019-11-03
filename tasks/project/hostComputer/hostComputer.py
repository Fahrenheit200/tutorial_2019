import serial 

try:
    portx = "COM11"
    # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2400,4800,9600,19200,38400,57600,115200
    bps = 57600
    # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
    timex = 5
    # 打开串口，并得到串口对象
    ser = serial.Serial(portx, bps, timeout=timex)
except Exception as e:
    print("---异常---：", e)

print("Enter 'exit' to exit, 'list' to get the list of music, 'download' to download music to MCU.")
while(1):
    cmd = input("Please input command: ")

    # 退出
    if(cmd == 'exit'):
        break

    # 列出单片机内已有歌曲
    elif(cmd == 'list'):
        # 清空接收缓冲区 
        while ser.in_waiting:
            ser.readline()
        # 发送指令
        ser.write(b'l')
        # 等待接收
        while True:
            if ser.in_waiting:
                break
        music_list = ser.readline().decode('utf-8')
        music_list = music_list.strip(',\n\r')
        music_index = 0
        print("-----------------MUSIC LIST---------------")
        for i in music_list.split(','):
            music_index = music_index + 1
            print(str(music_index) + ". " + i)
        print()

    # 下载音乐到单片机
    elif(cmd == 'download'):
        try:
            file_name = input("Please input the name of txt file: ")
            f1 = open(file_name, 'r')
        except Exception as e:
            print("---打开文件异常---：", e)

        # 读取歌名
        name = f1.readline().strip(' ,\n\r')
        assert f1.readline()[0] == '*'
        # 读取音调
        tones = []
        line = f1.readline()
        while not line[0] == '*':
            line = line.replace("\n", "")
            line = line.replace(" ", "")
            line = line.strip(',')
            tones = tones + line.split(',')
            line = f1.readline()
        for index in range(len(tones)):
            tones[index] = chr(int(tones[index]) + ord('0'))
            assert tones[index] >= '0' and tones[index] <= 'E' # 0-21
        # 读取持续时长
        beats = []
        for line in f1:
            line = line.replace("\n", "")
            line = line.replace(" ", "")
            line = line.strip(',')
            beats = beats + line.split(',')
        for index in range(len(beats)):
            beats[index] = chr(int(beats[index]) + ord('0'))
            assert beats[index] >= '0' and beats[index] <= 'Z' 

        assert len(tones) == len(beats)

        # 清空接收缓冲区 
        while ser.in_waiting:
            print(ser.readline())
        # 发送歌曲名
        ser.write(b'd')
        ser.write(b'n')
        ser.write(bytes(name, encoding='utf-8'))
        ser.write(b'*')
        while True:
            if '*' in ser.readline().decode('utf-8'):
                break

        # 清空接收缓冲区 
        while ser.in_waiting:
            print(ser.readline())        
        # 发送音调
        ser.write(b't')
        for item in tones:
            ser.write(bytes(item, encoding='utf-8'))
        ser.write(b'*')
        while True:
            if '*' in ser.readline().decode('utf-8'):
                break
        
        # 发送每个音调持续时长
        ser.write(b'r')
        for item in beats:
            ser.write(bytes(item, encoding='utf-8'))
        ser.write(b'*')
        # 清空接收缓冲区 
        while ser.in_waiting:
            print(ser.readline())

        # print(tones)
        # print(beats)
        # print(len(beats))
        print("Downloading finished.")
        f1.close()
        
    
    elif(cmd == 'print'):
        # 打印接收缓冲区信息 
        while ser.in_waiting:
            print(ser.readline())
        
# 关闭串口
ser.close()