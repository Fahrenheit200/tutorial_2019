/*
NANO    D2 D3 D4 D5 D6 D7 D8 D9
点阵    16 15 14 13 12 11 10 9
点阵     1  2  3  4  5  6   7   8
NANO    A5 A4 A3 A2 A1 D10 D11 D12
采样引脚 A0 -- MEGA pin2
*/

#include <TimerOne.h>
#include <math.h>

// 点阵引脚与Arduino引脚对应关系
uint8_t lattice_rows[8] = {9, 4, 12, 6, A5, 11, A4, A1};  
uint8_t lattice_cols[8] = {5, A3, A2, 8, 10, 7, 3, 2};      

char lattice_show[8] = {1, 1, 1, 1, 1, 1, 1, 1};

const uint16_t samples_N = 64;              // 采样个数，为2的整数次方
const double sampling_frequency = 5000;     // 采样频率
uint8_t sample_index = 0;
boolean is_compute = false;
boolean is_sample = true;
float vReal[samples_N];
float vImag[samples_N];

void Swap (float &a, float &b){
    float t = a;
    a = b;
    b = t;
}

/* 位反转置换 */
void bitrp (float *xreal, float *ximag, int n){
    int i, j, a, b, p = 0;
 
    for (i = 1; i < n; i *= 2){
        p ++;
    }
    for(i = 0; i < n; i ++){
        a = i;
        b = 0;
        for(j = 0; j < p; j ++){
            b = (b << 1) + (a & 1);   
            a >>= 1;       
        }
        if(b > i){
            Swap(xreal[i], xreal[b]);
            Swap(ximag[i], ximag[b]);
        }
    }
}

/* FFT运算函数 */
void myFFT(float *xreal, float *ximag, int n);

/* 中断响应函数，按照一定的间隔进行采样 */
void sample(){
    if(is_sample){
        vReal[sample_index] = 5.0 * analogRead(A0) / 1023;
        vImag[sample_index] = 0.0;
        sample_index = (sample_index + 1) % samples_N;
        if(sample_index == 0){
            is_compute = true;
            is_sample = false;
        }  
    } 
}

void setup() {
    Serial.begin(9600);
    
    // 引脚初始化
    for(int i=0; i<8; i++){
        pinMode(lattice_rows[i], OUTPUT);
        digitalWrite(lattice_rows[i], LOW);
        pinMode(lattice_cols[i], OUTPUT);
        digitalWrite(lattice_cols[i], HIGH);
    }

    // 定时器1初始化
    Timer1.initialize(round(1.0/sampling_frequency*1000000));
    Timer1.attachInterrupt(sample); 
    interrupts();
}

void loop() {
    if(is_compute){
        noInterrupts(); 
        float abscissa, tmp;
        myFFT(vReal, vImag, samples_N);

        // 将数据分成8份，用于点阵显示
        for (uint16_t i = 0; i < 8; i++){
            tmp = 0;
            for(uint16_t j = 0; j < samples_N / 8 / 2; j++){
                tmp += vReal[i * samples_N / 8 / 2 + j];
            }
            tmp = tmp / (samples_N / 8 / 2);
            lattice_show[i] = int(tmp / 2);
            if(lattice_show[i] > 8)
                lattice_show[i] = 8;
        }
        
//        for (uint16_t i = 0; i < samples_N/2; i++){
//            abscissa = ((i * 1.0 * sampling_frequency) / samples_N);
//            Serial.print(abscissa, 6);
//            Serial.print("Hz");
//            Serial.print(" ");
//            Serial.println(vReal[i], 4);
//        }
//        Serial.println();
        
        is_compute = false;
        is_sample = true;  
        sample_index = 0;
        interrupts(); 
    }
    
    /* Display */
    for(int i=0; i<8; i++){
        digitalWrite(lattice_cols[i], LOW);
        for(int j=7; j>=8-lattice_show[i]; j--)
            digitalWrite(lattice_rows[j], HIGH);            
        //delay(1);
        delayMicroseconds(10);
        
        for(int j=7; j>=8-lattice_show[i]; j--)
            digitalWrite(lattice_rows[j], LOW); 
        digitalWrite(lattice_cols[i], HIGH);       
    }
}

void myFFT(float *xreal, float *ximag, int n)
{
    float wreal[n/2], wimag[n/2], treal, timag, ureal, uimag, arg;
    int m, k, j, t, index1, index2;

    // 去除直流分量
    float mean = 0;
    for (uint16_t i = 0; i < n; i++)
        mean += xreal[i]; 
    mean /= n;
    for (uint16_t i = 0; i < n; i++)
      xreal[i] -= mean;
    
    bitrp(xreal, ximag, n);
 
    // 计算 1 的前 n / 2 个 n 次方根的共轭复数 W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
    arg = - 2 * PI / n;
    treal = cos(arg);
    timag = sin(arg);
    wreal[0] = 1.0;
    wimag[0] = 0.0;
    for(j = 1; j < n / 2; j ++){
        wreal[j] = wreal[j - 1] * treal - wimag[j - 1] * timag;
        wimag[j] = wreal[j - 1] * timag + wimag[j - 1] * treal;
    }
 
    for(m = 2; m <= n; m *= 2){
        for(k = 0; k < n; k += m){
            for(j = 0; j < m / 2; j ++){
                index1 = k + j;
                index2 = index1 + m / 2;
                t = n * j / m; 
                treal = wreal[t] * xreal[index2] - wimag[t] * ximag[index2];
                timag = wreal[t] * ximag[index2] + wimag[t] * xreal[index2];
                ureal = xreal[index1];
                uimag = ximag[index1];
                xreal[index1] = ureal + treal;
                ximag[index1] = uimag + timag;
                xreal[index2] = ureal - treal;
                ximag[index2] = uimag - timag;
            }
        }
    }

    // Complex To Magnitude
    for(uint16_t i = 0; i < n / 2; i++)
        xreal[i] = sqrt(xreal[i] * xreal[i] + ximag[i] * ximag[i]);
}
