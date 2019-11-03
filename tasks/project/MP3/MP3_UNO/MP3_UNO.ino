/*
OLED模块       UNO
    CS    --   12
    DC    --   11
    RES   --   RESET
    D0    --   10
    D1    --   9
MEGA主机       UNO
    RX1   --   TX
    TX1   --   RX
*/

#include <U8glib.h>

#define OLED_D0                 10
#define OLED_D1                 9
#define OLED_DC                 11
#define OLED_CS                 12
#define MAIN_PAGE               0

U8GLIB_SSD1306_128X64 u8g(OLED_D0, OLED_D1, OLED_CS, OLED_DC); 

boolean is_stop = true;
char song_names[600] = "abc";
uint16_t song_name_index[50] = {0};
uint8_t page_index = 0;
uint8_t song_num = 1;
uint8_t song_index = 0;
uint8_t choose_song_index = 0;
uint16_t song_name_flag = 0;
uint16_t beat_index = 0;
uint16_t song_length = 100;


/* 显示某个页面的歌曲列表 */
void draw_song_list(int index){
    char tmp[30] = "00.";
    if(index < 9){
        tmp[0] = (index + 1) + '0';
        tmp[1] = '.';
        tmp[2] = '\0';
    }else{
        tmp[0] = (index + 1) / 10 + '0';
        tmp[1] = (index + 1) % 10 + '0';
    }
    strcat(tmp, &song_names[song_name_index[index]]);
    switch(index % 4){
        case 0: u8g.drawStr(0, 13, tmp); break;
        case 1: u8g.drawStr(0, 29, tmp); break;
        case 2: u8g.drawStr(0, 45, tmp); break;
        case 3: u8g.drawStr(0, 61, tmp); break;
    }
}

void draw() {
    u8g.setFont(u8g_font_6x13);                 //设置要显示字符的字体

    // 编辑播放页面显示内容
    if(page_index == MAIN_PAGE){
        // 显示进度条
        u8g.drawRFrame(10, 3, 108, 7, 1);           
        u8g.drawRBox(10, 3, int(108.0*(beat_index+1)/song_length), 7, 1);   
        // 显示正在播放的歌曲序号及名称
        char tmp[30] = "00.";
        if(song_index < 9){
            tmp[0] = (song_index + 1) + '0';
            tmp[1] = '.';
            tmp[2] = '\0';
        }else{
            tmp[0] = (song_index + 1) / 10 + '0';
            tmp[1] = (song_index + 1) % 10 + '0';
        }
        strcat(tmp, &song_names[song_name_index[song_index]]);
        u8g.drawStr(0, 32, tmp);

        // 显示下方各个图案
        /*   6-21  31-46   56-71   81-96  106-122 */
        u8g.drawTriangle(8, 53, 21, 43, 21, 63);    // 上一首三角形
        u8g.drawBox(6, 43, 3, 20);                  // 上一首矩形
        u8g.drawTriangle(39, 53, 46, 43, 46, 63);   // 快退三角形1
        u8g.drawTriangle(31, 53, 38, 43, 38, 63);   // 快退三角形2
        if(is_stop)
            u8g.drawTriangle(71, 53, 56, 43, 56, 63);// 播放三角形
        else{
            u8g.drawBox(56, 43, 5, 20);             // 暂停矩形1
            u8g.drawBox(67, 43, 5, 20);             // 暂停矩形2
        }
        u8g.drawTriangle(88, 53, 81, 43, 81, 63);   // 快进三角形1
        u8g.drawTriangle(96, 53, 89, 43, 89, 63);   // 快进三角形2
        u8g.drawTriangle(119, 53, 106, 43, 106, 63);// 下一首三角形
        u8g.drawBox(120, 43, 3, 20);                // 下一首矩形 

    // 编辑歌曲列表界面显示内容
    }else{
        draw_song_list(4 * page_index - 4);
        if((song_num + 4 - page_index * 4) > 1)
            draw_song_list(4 * page_index - 3);
        if((song_num + 4 - page_index * 4) > 2)
            draw_song_list(4 * page_index - 2);
        if((song_num + 4 - page_index * 4) > 3)
            draw_song_list(4 * page_index - 1);             
    }
    u8g.setColorIndex(1);                     //显示对象为不透明
    
    // 编辑歌曲列表界面的下划线
    if(page_index != MAIN_PAGE){
        switch (choose_song_index){
            case 0:  u8g.drawLine(0, 14, 127, 14);  break;
            case 1:  u8g.drawLine(0, 30, 127, 30);  break;
            case 2:  u8g.drawLine(0, 46, 127, 46);  break;
            case 3:  u8g.drawLine(0, 62, 127, 62);  break;
            default:    break;
        }
    }
}

void setup(){
    // 初始化串口
    Serial.begin(38400);
    while(!Serial) ;

    // 从MEGA主机读取SD卡内已有歌曲的名称
    Serial.write('^');
    while(!Serial.available()) ;
    if(char(Serial.read()) == '^'){
        song_num = 0;
        song_name_index[0] = 0;
        while(!Serial.available()) ;
        char tmp = char(Serial.read());
        while(tmp != '^'){
            if(tmp == '\0'){
                song_num++;
                song_name_index[song_num] = song_name_flag + 1;
            }
            song_names[song_name_flag] = tmp;
            song_name_flag++;
            while(!Serial.available()) ;
            tmp = char(Serial.read());
        }
    }
}

void loop(){
    // 从MEGA主机读取信息
    if(Serial.available()){
        switch(char(Serial.read())){
            // 更新歌曲目前播放的节拍下标
            case 'b':
                beat_index = 0;  
                while(Serial.available() < 2) ;  
                beat_index += char(Serial.read()) * 128;  
                beat_index += char(Serial.read());
                break;

            // 更新歌曲长度信息
            case 's':  
                song_length = 0;
                while(Serial.available() < 2) ;  
                song_length += char(Serial.read()) * 128;
                song_length += char(Serial.read()); 
                break;
            
            case 'c':  while(!Serial.available());  choose_song_index = char(Serial.read());  break;

            // 更新OLED显示页码
            case 'p':  while(!Serial.available());  page_index = char(Serial.read());  break;

            // 更新正在播放音乐的下标
            case 'o':  while(!Serial.available());  song_index = char(Serial.read());  break;

            // 更新暂停/播放状态
            case 'i':  is_stop = !is_stop;  break;

            // 添加上位机下载新歌曲的名称
            case 'd':  
                while(!Serial.available()) ;
                char tmp = char(Serial.read());
                while(tmp != '^'){
                    if(tmp == '\0'){
                        song_num++;
                        song_name_index[song_num] = song_name_flag + 1;
                    }
                    song_names[song_name_flag] = tmp;
                    song_name_flag++;
                    while(!Serial.available()) ;
                    tmp = char(Serial.read());
                }  
                break;
            default:  break;
        }
    }
    
    // 更新OLED显示
    u8g.firstPage();  
    do {
        draw();
    } while( u8g.nextPage() );
}
