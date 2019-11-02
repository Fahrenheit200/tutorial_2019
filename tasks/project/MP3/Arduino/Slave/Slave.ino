#include <arduinoFFT.h>

arduinoFFT FFT = arduinoFFT(); 

//设置端口
void setup() {
  pinMode(13, OUTPUT);//1
  pinMode(12, OUTPUT);//2
  pinMode(11, OUTPUT);//3
  pinMode(10, OUTPUT);//4
  pinMode(9, OUTPUT);//5
  pinMode(8, OUTPUT);//6
  pinMode(7, OUTPUT);//7
  pinMode(6, OUTPUT);//8
  pinMode(2, OUTPUT);//9
  pinMode(3, OUTPUT);//10
  pinMode(4, OUTPUT);//11
  pinMode(5, OUTPUT);//12
  pinMode(A3, OUTPUT);//13
  pinMode(A2, OUTPUT);//14
  pinMode(A1, OUTPUT);//15
  pinMode(A0, OUTPUT);//16
  
  digitalWrite(13, LOW);//1
  digitalWrite(12, LOW);//2
  digitalWrite(11, LOW);//3
  digitalWrite(10, LOW);//4
  digitalWrite(9, LOW);//5
  digitalWrite(8, LOW);//6
  digitalWrite(7, LOW);//7
  digitalWrite(6, LOW);//8
  digitalWrite(2, HIGH);//9
  digitalWrite(3, HIGH);//10
  digitalWrite(4, HIGH);//11
  digitalWrite(5, HIGH);//12
  digitalWrite(A3, HIGH);//13
  digitalWrite(A2, HIGH);//14
  digitalWrite(A1, HIGH);//15
  digitalWrite(A0, HIGH);//16
  
  pinMode(A5,INPUT);
  Serial.begin(9600);

}

#define SAMPLES 64
double data;
int count=0;
double store[SAMPLES];
double result[8];
double vReal[SAMPLES];
double vImag[SAMPLES];

void loop() {
  //不断从A5接收信号
  data=digitalRead(A5);
  store[count]=data;
  //将接收到的信号进行FFT处理
  if(count==63)
  {
    count=0;
    for(int i=0; i<SAMPLES; i++)
    {
      vReal[i]=store[i];
      vImag[i]=0;                         
    }
    //FFT
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    for(int i=0; i<8; i++)
    {
      //将结果整理成8个量，对应矩阵的八列
      result[i]=vReal[32+4*i]+vReal[33+4*i]+vReal[34+4*i]+vReal[35+4*i];
      Serial.println(i);
      Serial.println(result[i]);
      if (result[i]<2)
        result[i]=1;
      else if (result[i]<4)
        result[i]=2;
      else if (result[i]<6)
        result[i]=3;
      else if (result[i]<8)
        result[i]=4;
      else if (result[i]<10)
        result[i]=5;
      else if (result[i]<12)
        result[i]=6;
      else if (result[i]<14)
        result[i]=7;
      else
        result[i]=8;
    }
  }
  //显示
  pp_display(result);
  count++;
}

//用于清空矩阵显示的函数
void pp_clear(){
  digitalWrite(2, LOW);//9
  digitalWrite(3, LOW);//10
  digitalWrite(4, LOW);//11
  digitalWrite(5, LOW);//12
  digitalWrite(A3, LOW);//13
  digitalWrite(A2, LOW);//14
  digitalWrite(A1, LOW);//15
  digitalWrite(A0, LOW);//16
}

//用于在矩阵进行显示的函数（输入一个八位的数组）
void pp_display(double arr[]){
  //这类的数组，1表示不亮，0表示亮
  int pos1[]={0,1,1,1,1,1,1,1};
  set_pos(pos1);
  set_height(int(arr[0]));
  pp_clear();
  int pos2[]={1,0,1,1,1,1,1,1};
  set_pos(pos2);
  set_height(int(arr[1]));
  pp_clear();
  int pos3[]={1,1,0,1,1,1,1,1};
  set_pos(pos3);
  set_height(int(arr[2]));
  pp_clear();
  int pos4[]={1,1,1,0,1,1,1,1};
  set_pos(pos4);
  set_height(int(arr[3]));
  pp_clear();
  int pos5[]={1,1,1,1,0,1,1,1};
  set_pos(pos5);
  set_height(int(arr[4]));
  pp_clear();
  int pos6[]={1,1,1,1,1,0,1,1};
  set_pos(pos6);
  set_height(int(arr[5]));
  pp_clear();
  int pos7[]={1,1,1,1,1,1,0,1};
  set_pos(pos7);
  set_height(int(arr[6]));
  pp_clear();
  int pos8[]={1,1,1,1,1,1,1,0};
  set_pos(pos8);
  set_height(int(arr[7]));
  pp_clear();
}

//用于设置矩阵某一列显示亮或不亮的函数
void set_pos(int pos[]){
  if(pos[0]==0)
    digitalWrite(13,LOW);
  else
    digitalWrite(13,HIGH);
  if(pos[1]==0)
    digitalWrite(12,LOW);
  else
    digitalWrite(12,HIGH);
  if(pos[2]==0)
    digitalWrite(11,LOW);
  else
    digitalWrite(11,HIGH);
  if(pos[3]==0)
    digitalWrite(10,LOW);
  else
    digitalWrite(10,HIGH);
  if(pos[4]==0)
    digitalWrite(9,LOW);
  else
    digitalWrite(9,HIGH);
  if(pos[5]==0)
    digitalWrite(8,LOW);
  else
    digitalWrite(8,HIGH);
  if(pos[6]==0)
    digitalWrite(7,LOW);
  else
    digitalWrite(7,HIGH);
  if(pos[7]==0)
    digitalWrite(6,LOW);
  else
    digitalWrite(6,HIGH);
}

//用于设置矩阵某一列显示的高度的函数
void set_height(int h){
  switch(h)
  {
    case 1:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, LOW);//12
      digitalWrite(A3, LOW);//13
      digitalWrite(A2, LOW);//14
      digitalWrite(A1, LOW);//15
      digitalWrite(A0, HIGH);//16
      break;
    }
    case 2:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, LOW);//12
      digitalWrite(A3, LOW);//13
      digitalWrite(A2, LOW);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    }
    case 3:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, LOW);//12
      digitalWrite(A3, LOW);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    }
    case 4:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, LOW);//12
      digitalWrite(A3, HIGH);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    } 
    case 5:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, HIGH);//12
      digitalWrite(A3, HIGH);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    } 
    case 6:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, HIGH);//11
      digitalWrite(5, HIGH);//12
      digitalWrite(A3, HIGH);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    } 
    case 7:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, HIGH);//10
      digitalWrite(4, HIGH);//11
      digitalWrite(5, HIGH);//12
      digitalWrite(A3, HIGH);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    } 
    case 8:{
      digitalWrite(2, HIGH);//9
      digitalWrite(3, HIGH);//10
      digitalWrite(4, HIGH);//11
      digitalWrite(5, HIGH);//12
      digitalWrite(A3, HIGH);//13
      digitalWrite(A2, HIGH);//14
      digitalWrite(A1, HIGH);//15
      digitalWrite(A0, HIGH);//16
      break;
    }
    default:{
      digitalWrite(2, LOW);//9
      digitalWrite(3, LOW);//10
      digitalWrite(4, LOW);//11
      digitalWrite(5, LOW);//12
      digitalWrite(A3, LOW);//13
      digitalWrite(A2, LOW);//14
      digitalWrite(A1, LOW);//15
      digitalWrite(A0, LOW);//16
      break;
    }  
  }
}
