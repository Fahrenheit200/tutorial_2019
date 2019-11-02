/*
SD卡模块       MEGA
    CS    --   GND
    SCK   --   52
    MOSI  --   51
    MISO  --   50
UNO从机        MEGA
    RX    --   TX1
    TX    --   RX1
按键和蜂鸣器引脚见宏定义
*/

#include <TimerThree.h>
#include <SPI.h>
#include <SD.h>

#define SERIAL_TX_BUFFER_SIZE   256
#define SERIAL_RX_BUFFER_SIZE   256

#define LAST_SONG_BUTTON        23
#define FAST_RETURN_BUTTON      25
#define STOP_CONTINUE_BUTTON    27
#define FAST_FORWARD_BUTTON     29
#define NEXT_SONG_BUTTON        26
#define LAST_PAGE_BUTTON        22
#define NEXT_PAGE_BUTTON        24
#define BUZZER_PIN              2
#define MAIN_PAGE               0

File myFile;

/* 用作按键和开关的缓冲数组 */
byte LAST_SONG_BUTTON_BUFF = B11111111;   
byte FAST_RETURN_BUTTON_BUFF = B11111111;  
byte STOP_CONTINUE_BUTTON_BUFF = B11111111;   
byte FAST_FORWARD_BUTTON_BUFF = B11111111;
byte NEXT_SONG_BUTTON_BUFF = B11111111;
byte LAST_PAGE_BUTTON_BUFF = B11111111;
byte NEXT_PAGE_BUTTON_BUFF = B11111111;

boolean is_STOP_CONTINUE_BUTTON = false;
boolean is_stop = true;

boolean change_song = true;
boolean change_choose = false;
boolean change_beat = false;
boolean change_stop = false;

uint8_t page_num = 4;
uint8_t page_index = MAIN_PAGE; 
int song_length = 0;
int beat_index = 0;
uint8_t song_num = 0;
uint8_t song_index = 0;
char choose_song_index = 0;

// 当前播放的音乐
char song_tones[1000];
char song_beats[1000];

// 各个音调的频率
int standard_tone[] = {
    -1 ,262, 294, 330, 349, 392, 440, 494,      // 低音1-7
    523, 587, 659, 698, 784, 880, 988,          // 中音1-7
    1046, 1175, 1318, 1397, 1568, 1760, 1967,   // 高音1-7
    2084, 2349
};


/* Timer3中断响应，3ms执行一次 */
void event(){
    // 更新各个按键的缓冲数组
    LAST_SONG_BUTTON_BUFF = (LAST_SONG_BUTTON_BUFF << 1) | digitalRead(LAST_SONG_BUTTON);
    FAST_RETURN_BUTTON_BUFF = (FAST_RETURN_BUTTON_BUFF << 1) | digitalRead(FAST_RETURN_BUTTON);
    STOP_CONTINUE_BUTTON_BUFF = (STOP_CONTINUE_BUTTON_BUFF << 1) | digitalRead(STOP_CONTINUE_BUTTON);
    FAST_FORWARD_BUTTON_BUFF = (FAST_FORWARD_BUTTON_BUFF << 1) | digitalRead(FAST_FORWARD_BUTTON);
    NEXT_SONG_BUTTON_BUFF = (NEXT_SONG_BUTTON_BUFF << 1) | digitalRead(NEXT_SONG_BUTTON);
    LAST_PAGE_BUTTON_BUFF = (LAST_PAGE_BUTTON_BUFF << 1) | digitalRead(LAST_PAGE_BUTTON);
    NEXT_PAGE_BUTTON_BUFF = (NEXT_PAGE_BUTTON_BUFF << 1) | digitalRead(NEXT_PAGE_BUTTON);

    /* 按下 “上一首” 按键 */
    if(LAST_SONG_BUTTON_BUFF == B00000001){
        song_index = (song_index - 1 + song_num) % song_num;
        change_song = true;
    }

    /* 按下 “快退” 按键 */
    if(FAST_RETURN_BUTTON_BUFF == B00000001){
        int i = int(song_length * 0.1);
        if(beat_index - i < 0)
            beat_index = 0;
        else
            beat_index -= i;
        change_beat = true;
    }

    /* 按下 “播放/暂停/选择” 按键 */
    if(STOP_CONTINUE_BUTTON_BUFF == B00000000)      // 记录按下暂停键
        is_STOP_CONTINUE_BUTTON = true;
    if(is_STOP_CONTINUE_BUTTON)
        if(STOP_CONTINUE_BUTTON_BUFF == B11111111){  // 松开暂停键
            if(page_index == MAIN_PAGE){
                is_stop = !is_stop;
                change_stop = true;
            }
            else{
                song_index = (page_index - 1) * 4 + choose_song_index;
                change_song = true;
                page_index = MAIN_PAGE;
                change_choose = true;
            }
            is_STOP_CONTINUE_BUTTON = false;
        }

    /* 按下 “快进” 按键 */    
    if(FAST_FORWARD_BUTTON_BUFF == B00000001){
        int i = int(song_length * 0.1);
        if(beat_index + i > song_length)
            beat_index = song_length;
        else
            beat_index += i;
        change_beat = true;
    }

    /* 按下 “下一首” 按键 */
    if(NEXT_SONG_BUTTON_BUFF == B00000001){
        song_index = (song_index + 1) % song_num;
        change_song = true;
    }

    /* 按下 “上一页” 按键 */
    if(LAST_PAGE_BUTTON_BUFF == B00000001){
        if(page_index == MAIN_PAGE){
            page_index = page_num - 1;
            choose_song_index = (song_num - 1) % 4;
        }else{
            choose_song_index--;
            if(choose_song_index < 0){
                page_index = (page_index - 1) % page_num;
                choose_song_index = 3;
            }
        }
        change_choose = true;
    }

    /* 按下 “下一页” 按键 */
    if(NEXT_PAGE_BUTTON_BUFF == B00000001){
        if(page_index == MAIN_PAGE){
            page_index = (page_index + 1) % page_num;
            choose_song_index = 0;
        }else if(page_index == page_num - 1){
            choose_song_index++;
            if(choose_song_index > (song_num - 1) % 4){
                page_index = (page_index + 1) % page_num;
                choose_song_index = 0;
            }
        }else{
            choose_song_index++;
            if(choose_song_index == 4){
                page_index = (page_index + 1) % page_num;
                choose_song_index = 0;
            }
        }
        change_choose = true;
    }
}


void setup() {
  	// 初始化串口0与上位机通信
    Serial.begin(57600);
    Serial.println("Hello");
    // 初始化串口1与从机UNO通信
    Serial1.begin(38400);

    // 引脚初始化
    pinMode(LAST_SONG_BUTTON, INPUT_PULLUP);
    pinMode(FAST_RETURN_BUTTON, INPUT_PULLUP);
    pinMode(STOP_CONTINUE_BUTTON, INPUT_PULLUP);
    pinMode(FAST_FORWARD_BUTTON, INPUT_PULLUP);
    pinMode(NEXT_SONG_BUTTON, INPUT_PULLUP);
    pinMode(LAST_PAGE_BUTTON, INPUT_PULLUP);
    pinMode(NEXT_PAGE_BUTTON, INPUT_PULLUP);

	  // Timer3 中断初始化
    Timer3.initialize(3000);
    Timer3.attachInterrupt(event);
    interrupts();

    // 初始化SD卡
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("Initialization of SD card failed!");
        while(1);
    }
    Serial.println("Initialization done.");

    // 获取SD内的歌曲数
    char file_name[] = "00.txt";
    while(1){
        file_name[0] = (song_num + 1) / 10 + '0';
        file_name[1] = (song_num + 1) % 10 + '0';
        if(SD.exists(file_name)){
            song_num++;
        }else{
            break;
        }
    }
    page_num = (song_num + 3) / 4 + 1; 
}


void loop() {
    // 若接受到从机UNO发来的请求，将所有歌曲的名称发送到UNO
    if(Serial1.available()){
        if(char(Serial1.read()) == '^'){
            Serial1.write('^');
            for(int i = 1; i <= song_length; i++){
                char file_name[] = "00.txt";
                file_name[0] = i / 10 + '0';
                file_name[1] = i % 10 + '0';
                myFile = SD.open(file_name);
                if(myFile){
                    char tmp = myFile.read();
                    while(tmp != '*'){
                        Serial1.write(tmp);
                        tmp = myFile.read();
                    }
                    Serial1.write('\0');
                    myFile.close();
                }else{
                    Serial.println("error opening (song_index + 1).txt");   
                }
            }
            Serial1.write('^');
            change_song = true;
        }
    }

    // 与上位机进行通信
    if(Serial.available()){
        char cmd1 = char(Serial.read());

        // 向上位机发送歌曲列表信息
        if(cmd1 == 'l'){
            for(int i = 1; i <= song_num; i++){
                char file_name[] = "00.txt";
                file_name[0] = i / 10 + '0';
                file_name[1] = i % 10 + '0';
                myFile = SD.open(file_name);
                if(myFile){
                    char tmp = myFile.read();
                    while(tmp != '*'){
                        Serial.write(tmp);
                        tmp = myFile.read();
                    }
                    Serial.write(',');
                    myFile.close();
                }else{
                    Serial.println("error opening song_index.txt");   
                }
            }
            Serial.println();

        // 从上位机读取新歌曲信息    
        }else if(cmd1 == 'd'){
            song_num++;
            page_num = (song_num + 3) / 4 + 1;
            char file_name[] = "00.txt";
            file_name[0] = song_num / 10 + '0';
            file_name[1] = song_num % 10 + '0';
            myFile = SD.open(file_name, FILE_WRITE);
            if(!myFile){
                Serial.println("error creating new (song_num + 1).txt");
                while(1) ;
            }

            //  从上位机读取歌名
            while(!Serial.available()) ;
            if(char(Serial.read()) == 'n'){
                while(!Serial.available()) ;
                char tmp = char(Serial.read());
                while(tmp != '*'){
                    myFile.write(tmp);
                    while(!Serial.available()) ;
                    tmp = char(Serial.read());
                }
                myFile.write('*');
                Serial.println('*'); 
                Serial.println("Name finished");
            }

            //  从上位机读取音调
            while(!Serial.available()) ;
            if(char(Serial.read()) == 't'){
                while(!Serial.available()) ;
                char tmp = char(Serial.read());
                while(tmp != '*'){
                    myFile.write(tmp);
                    while(!Serial.available()) ;
                    tmp = char(Serial.read());
                }
                myFile.write('*');
                Serial.println("*"); 
                Serial.println("Tone finished"); 
            }

            //  从上位机读取音调持续时间
            while(!Serial.available()) ;
            if(char(Serial.read()) == 'r'){
                while(!Serial.available()) ;
                char tmp = char(Serial.read());
                while(tmp != '*'){
                    myFile.write(tmp);
                    while(!Serial.available()) ;
                    tmp = char(Serial.read());
                }
                myFile.write('*');
                Serial.println("Duration finished"); 
            }
            myFile.close();

            // 更新UNO从机中的信息
            myFile = SD.open(file_name);
            if(!myFile){
                Serial.println("error opening (song_num + 1).txt");
                while(1) ;
            }
            Serial1.write('d');
            char tmp = char(myFile.read());
            while(tmp != '*'){
                Serial1.write(tmp);
                tmp = char(myFile.read());
            }
            Serial1.write('\0');
            Serial1.write('^');
            myFile.close();
        }
    }
    
    if(change_choose){
        Serial1.write('c');
        Serial1.write(char(choose_song_index));
        Serial1.write('p');
        Serial1.write(char(page_index));
        change_choose = false;
    }

    if(change_stop){
        // 将暂停/播放状态发送给UNO
        Serial1.write('i');
        change_stop = false;
    }

    if(change_beat){
        // 将节拍下标发送给UNO
        Serial1.write('b');
        Serial1.write(char(beat_index / 128));
        Serial1.write(char(beat_index % 128)); 
        change_beat = false;
    }

    // 读取另一首歌
    if(change_song){
        //　从txt文件中读取音乐到单片机SRAM中
        char file_name[] = "00.txt";
        file_name[0] = (song_index + 1) / 10 + '0';
        file_name[1] = (song_index + 1) % 10 + '0';
        myFile = SD.open(file_name);
        if(myFile){
            while(myFile.read() != '*') ;
            char tmp = myFile.read();
            song_length = 0;
            while(tmp != '*'){
                song_tones[song_length] = tmp - '0';
                song_length++;
                tmp = myFile.read();
            }
            tmp = myFile.read();
            song_length = 0;
            while(tmp != '*'){
                song_beats[song_length] = tmp - '0';
                song_length++;
                tmp = myFile.read();
            }
            Serial.println(song_length);
            myFile.close();
        }else{
            Serial.println("error opening (song_index + 1).txt");   
        } 
        beat_index = 0;
        change_song = false;
        // 将歌曲长度下标发送给UNO
        Serial1.write('s');
        Serial1.write(char(song_length / 128));
        Serial1.write(char(song_length % 128)); 
        // 将节拍下标发送给UNO
        Serial1.write('b');
        Serial1.write(char(beat_index / 128));
        Serial1.write(char(beat_index % 128));  
        // 将歌曲下标发送给UNO
        Serial1.write('o');
        Serial1.write(char(song_index));
    }

    // 控制蜂鸣器播放音乐
    if(!is_stop){
        if(beat_index < song_length){
            char this_tone = song_tones[beat_index];
            if(this_tone == 0){
                delay(song_beats[beat_index] * 90);
            }else{
                tone(BUZZER_PIN, standard_tone[this_tone]);
                delay(song_beats[beat_index] * 90);
                noTone(BUZZER_PIN);
            }
            // 将节拍下标发送给UNO
            Serial1.write('b');
            Serial1.write(char(beat_index / 128));
            Serial1.write(char(beat_index % 128)); 
            beat_index++;
        } 
    }     
}
