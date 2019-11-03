#include <SPI.h>
#include <SD.h>

// MEGA SRAM 8KBSS_PIN = 53; MOSI_PIN = 51; MISO_PIN = 50; SCK_PIN = 52;
// UNO  SRAM 2KB   CS:4  SCK:13  MOSI:11  MISO:12  
// DUE  SRAM 64KB and 32KB
//     SPI
// MISO   +5V
// SPCK   MOSI
// RESET  GND

const int vector_size = 4000;
int8_t a_tmp[vector_size] = {0};
int8_t b_tmp[vector_size] = {0};
int8_t ccl_tmp[2*vector_size] = {0};
int a_length = 0;
int b_length = 0;
File myFile;

void setToZero(int8_t *a){
    for(int i=0; i<vector_size; i++)
        a[i] = 0;
}

void calculateSum(){
    int8_t carry_flag1 = 0;
    int index = 0;
    int file_num = max(a_length, b_length) / vector_size + 1;
    for(int i=file_num-1; i>=0; i--){
        /* 读a.txt中的vector_size位数 */
        myFile = SD.open("a.txt");
        if(myFile){
            index = 0;
            setToZero(a_tmp);
            while(myFile.available()) {
                if(index >= a_length-vector_size*(file_num-i) && index < a_length-vector_size*(file_num-i-1))
                    a_tmp[index-(a_length-vector_size*(file_num-i))] = myFile.read() - '0';
                else
                    myFile.read();
                index++;
                if(index == a_length-vector_size*(file_num-i-1))
                    break;
            }
            myFile.close();
        }else{
            Serial.println("error opening a.txt");
        }
        
        /* 读b.txt中的vector_size位数 */
        myFile = SD.open("b.txt");
        if(myFile){
            index = 0;
            setToZero(b_tmp);
            while(myFile.available()) {
                if(index >= b_length-vector_size*(file_num-i) && index < b_length-vector_size*(file_num-i-1))
                    b_tmp[index-(b_length-vector_size*(file_num-i))] = myFile.read() - '0';
                else
                    myFile.read();
                index++;
                if(index == b_length-vector_size*(file_num-i-1))
                    break;
            }
            myFile.close();
        }else{
            Serial.println("error opening b.txt");
        }
        
        /* 将a.txt和b.txt中的vector_size位数相加 */
        for(int j=vector_size-1; j>=0; j--){
            ccl_tmp[j] = (carry_flag1 + a_tmp[j] + b_tmp[j]) % 10;
            carry_flag1 = (carry_flag1 + a_tmp[j] + b_tmp[j]) / 10;
        }

        /* 写入sumi.txt暂存 */
        char file_name[] = "sum00.txt";
        file_name[3] = i / 10 + '0';
        file_name[4] = i % 10 + '0';
        myFile = SD.open(file_name, FILE_WRITE);
        if(myFile){
            for(int j=0; j<vector_size; j++){
                myFile.write(ccl_tmp[j] + '0');
            }
            myFile.close();
        }else{
            Serial.println("error opening sumi.txt");
        }  
    }

    /* 若sum.txt已存在，则先删除原本的sum.txt */
    if(SD.exists("sum.txt"))
        SD.remove("sum.txt");
        
    boolean zero_end = false;   // 判断前面的0是否完全去除
    /* 将各个暂存文件写入sum.txt */
    for(int i=0; i<file_num; i++){
        //读sumi.txt
        char file_name[] = "sum00.txt";
        file_name[3] = i / 10 + '0';
        file_name[4] = i % 10 + '0';
        myFile = SD.open(file_name);
        if(myFile){
            myFile.read(ccl_tmp, vector_size);
            myFile.close();
        }else{
            Serial.println("error opening sumi.txt");
        } 

        //写进sum.txt
        myFile = SD.open("sum.txt", FILE_WRITE);
        if(myFile){
            for(int j=0; j<vector_size; j++){
                if(!zero_end){
                    if(ccl_tmp[j] != '0'){
                        zero_end = true;
                        myFile.write(ccl_tmp[j]);
                    }
                }else{
                    myFile.write(ccl_tmp[j]);
                }  
            }
            myFile.close();
        }else{
            Serial.println("error opening sum.txt");
        } 
    }

    /* 删除暂存文件 */
    for(int i=0; i<file_num; i++){
        char file_name[] = "sum00.txt";
        file_name[3] = i / 10 + '0';
        file_name[4] = i % 10 + '0';
        SD.remove(file_name);
    }
}

void calculateProduct(){
    int file_num_a = (a_length - 1) / vector_size + 1;
    int file_num_b = (b_length - 1) / vector_size + 1;
    int file_num = file_num_a + file_num_b;
    /* 初始化生成暂存文件 */
    for(int i=0; i<file_num; i++){
        char file_name[] = "prod000.txt";
        file_name[4] = i / 10 / 10 + '0';
        file_name[5] = i / 10 % 10 + '0';
        file_name[6] = i % 10 + '0';
        if(SD.exists(file_name))
            SD.remove(file_name);
        myFile = SD.open(file_name, FILE_WRITE);
        if(myFile){
            for(int j=0; j<vector_size; j++){
                myFile.write('0');
            }
            myFile.close();
        }else{
            Serial.println("error creating producti.txt when initialize");
        }
    }

    Serial.println("Finished creating producti.txt.");

    int index = 0;
    for(int i=file_num_a-1; i>=0; i--){
      
    Serial.print("i: ");
    Serial.println(i);
        
        /* 读a.txt中的vector_size位数 */
        myFile = SD.open("a.txt");
        if(myFile){
            index = 0;
            setToZero(a_tmp);
            while(myFile.available()){
                if(index >= a_length-vector_size*(file_num_a-i) && index < a_length-vector_size*(file_num_a-i-1))
                    a_tmp[index-(a_length-vector_size*(file_num_a-i))] = char(myFile.read()) - '0';
                else
                    myFile.read();
                index++;
                if(index == a_length-vector_size*(file_num_a-i-1))
                    break;
            }
            myFile.close();
        }else{
            Serial.println("error opening a.txt");
        }
        
        for(int j=file_num_b-1; j>=0; j--){
            /* 读b.txt中的vector_size位数 */
            myFile = SD.open("b.txt");
            if(myFile){
                index = 0;
                setToZero(b_tmp);
                while(myFile.available()) {
                    if(index >= b_length-vector_size*(file_num_b-j) && index < b_length-vector_size*(file_num_b-j-1))
                        b_tmp[index-(b_length-vector_size*(file_num_b-j))] = myFile.read() - '0';
                    else
                        myFile.read();
                    index++;
                    if(index == b_length-vector_size*(file_num_b-j-1))
                        break;
                }
                myFile.close();
            }else{
                Serial.println("error opening b.txt");
            }
            
            /* ccl_tmp数组清零 */
            for(int m=0; m<2*vector_size; m++)
                ccl_tmp[m] = 0;

            /* a.txt和b.txt中的vector_size位数相乘 */
            for(int m=vector_size-1; m>=0; m--){
                for(int n=vector_size-1; n>=0; n--){
                    index = 0;
                    ccl_tmp[m+n+1] += (a_tmp[m] * b_tmp[n]) % 10;
                    ccl_tmp[m+n] += (a_tmp[m] * b_tmp[n]) / 10;
                    while(ccl_tmp[m+n+1-index] >= 10){
                        ccl_tmp[m+n-index] += ccl_tmp[m+n+1-index] / 10;
                        ccl_tmp[m+n+1-index] = ccl_tmp[m+n+1-index] % 10;
                        index++;
                    }
                }
            }

            /* 读取product(i+j+1).txt */
            char file_name[] = "prod000.txt";
            file_name[4] = (i+j+1) / 10 / 10 + '0';
            file_name[5] = (i+j+1) / 10 % 10 + '0';
            file_name[6] = (i+j+1) % 10 + '0';
            myFile = SD.open(file_name);
            if(myFile){
                for(int m=0; m<vector_size; m++){
                    b_tmp[m] = myFile.read() - '0';
                }
                myFile.close();
            }else{
                Serial.println("error opening product(i+j+1).txt");
            }
            for(int m=vector_size-1; m>=0; m--)
                ccl_tmp[m+vector_size] = ccl_tmp[m+vector_size] + b_tmp[m];
            
            /* 读取product(i+j).txt */
            file_name[4] = (i+j) / 10 / 10 + '0';
            file_name[5] = (i+j) / 10 % 10 + '0';
            file_name[6] = (i+j) % 10 + '0';
            myFile = SD.open(file_name);
            if(myFile){
                for(int m=0; m<vector_size; m++){
                    b_tmp[m] = myFile.read() - '0';
                }
                myFile.close();
            }else{
                Serial.println("error opening product(i+j).txt");
            }
            for(int m=vector_size-1; m>=0; m--)
                ccl_tmp[m] = ccl_tmp[m] + b_tmp[m];

            /* 处理ccl_tmp的进位 */
            for(int m=2*vector_size-1; m>0; m--)
                if(ccl_tmp[m] >= 10){
                    ccl_tmp[m-1] += ccl_tmp[m] / 10;
                    ccl_tmp[m] = ccl_tmp[m] % 10;
                }
            if(ccl_tmp[0] >= 10){
                char carry_num = ccl_tmp[0] / 10;
                ccl_tmp[0] = ccl_tmp[0]  % 10;
                /* 有进位则将进位数写入product(i+j-1).txt */
                file_name[4] = (i+j-1) / 10 / 10 + '0';
                file_name[5] = (i+j-1) / 10 % 10 + '0';
                file_name[6] = (i+j-1) % 10 + '0';
                myFile = SD.open(file_name);
                if(myFile){
                    for(int m=0; m<vector_size; m++){
                        b_tmp[m] = myFile.read() - '0';
                    }
                    myFile.close();
                }else{
                    Serial.println("error creating product(i+j-1).txt");
                }
                b_tmp[vector_size-1] += carry_num;
                for(int m=vector_size-1; m>0; m--)
                    if(b_tmp[m] >= 10){
                        b_tmp[m-1] += b_tmp[m] / 10;
                        b_tmp[m] = b_tmp[m] % 10;
                    }
                myFile = SD.open(file_name, O_READ | O_WRITE);
                if(myFile){
                    for(int m=0; m<vector_size; m++){
                        myFile.write(b_tmp[m] + '0');
                    }
                    myFile.close();
                }else{
                    Serial.println("error creating product(i+j-1).txt");
                }
            }

            /* 将ccl_tmp写入product(i+j).txt */
            file_name[4] = (i+j) / 10 / 10 + '0';
            file_name[5] = (i+j) / 10 % 10 + '0';
            file_name[6] = (i+j) % 10 + '0';
            myFile = SD.open(file_name, O_READ | O_WRITE);
            if(myFile){
                for(int m=0; m<vector_size; m++){
                    myFile.write(ccl_tmp[m] + '0');
                }
                myFile.close();
            }else{
                Serial.println("error creating product(i+j).txt");
            }

            /* 将ccl_tmp写入product(i+j+1).txt */
            file_name[4] = (i+j+1) / 10 / 10 + '0';
            file_name[5] = (i+j+1) / 10 % 10 + '0';
            file_name[6] = (i+j+1) % 10 + '0';
            myFile = SD.open(file_name, O_READ | O_WRITE);
            if(myFile){
                for(int m=0; m<vector_size; m++){
                    myFile.write(ccl_tmp[m+vector_size] + '0');
                }
                myFile.close();
            }else{
                Serial.println("error creating product(i+j+1).txt");
            }
        }
    }

    if(SD.exists("product.txt"))
        SD.remove("product.txt");
    boolean zero_end = false;   // 判断前面的0是否完全去除
    /* 将暂存文件中的数写入product.txt */
    for(int i=0; i<file_num; i++){
        // 读producti.txt
        char file_name[] = "prod000.txt";
        file_name[4] = i / 10 / 10 + '0';
        file_name[5] = i / 10 % 10 + '0';
        file_name[6] = i % 10 + '0';
        myFile = SD.open(file_name);
        if(myFile){
            myFile.read(ccl_tmp, vector_size);
            myFile.close();
        }else{
            Serial.println("error opening 读producti.txt");   
        } 

        // 写进product.txt
        myFile = SD.open("product.txt", FILE_WRITE);
        if(myFile){
            for(int j=0; j<vector_size; j++){
                if(!zero_end){
                    if(ccl_tmp[j] != '0'){
                        zero_end = true;
                        myFile.write(ccl_tmp[j]);
                    }
                }else{
                    myFile.write(ccl_tmp[j]);
                }  
            }
            myFile.close();
        }else{
            Serial.println("error opening product.txt");
        } 
    }

    /* 删除暂存文件 */
    for(int i=0; i<file_num; i++){
        char file_name[] = "product000.txt";
        file_name[7] = i / 10 / 10 + '0';
        file_name[8] = i / 10 % 10 + '0';
        file_name[9] = i % 10 + '0';
        SD.remove(file_name);
    }
}

void setup() {
    Serial.begin(9600);
    while(!Serial) {;} 

    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("Initialization failed!");
        while(1);
    }
    Serial.println("Initialization done.");
    
}

void loop() {
    if(Serial.available()){
        if(Serial.read() == 's'){
            Serial.println("Start");
            
            myFile = SD.open("a.txt");
            if(myFile){
                a_length = myFile.size();
                myFile.close();
            }else{
                Serial.println("error opening a.txt");
            }
            
            myFile = SD.open("b.txt");
            if(myFile){
                b_length = myFile.size();
                myFile.close();
            }else{
                Serial.println("error opening b.txt");
            }
            
            calculateSum();
            Serial.println("Sum finished");
            calculateProduct();
            Serial.println("Product finished");
        }
    }
    
}
