#define BLOCK 50

#include <SPI.h>
#include <SD.h>
 
File File_a;
File File_b;
File Summid;
File Sum;
File File_last;

int a_num=0;
int b_num=0;
int a_or_b=0; //0表示a大，1表示b大

String a_path="a.TXT";
String b_path="b.TXT";

int a_times;
int b_times;
int big_times;
int small_times;

int a_rest;
int b_rest;
int big_rest;
int small_rest;

int a_store;
int b_store;
int last_store;
int sum_store;

int a_cursor=0;
int b_cursor=0;
int last_cursor;
int sum_cursor;

int num1[BLOCK];
int num2[BLOCK];
int summid;
int sum[BLOCK];

int flag=0;//进位

void setup() 
{
  Serial.begin(9600); //设置波特率
  while (!Serial) 
  {
    ;//等待串行端口连接。 仅适用于本机USB端口
  }
  
  Serial.print("正在初始化···");
  if (!SD.begin(A5)) {
    Serial.println("初始化失败！");
    return;
  }
  Serial.println("初始化完毕！");//初始化结束

  SD.remove("summid.txt");
  SD.remove("sum.txt");

//////////////////////////////////////////////////////////////////
  //获取总长以及计算参数
  
  File_a = SD.open(a_path);
  if (File_a) {
    Serial.println("a.txt:");
    while (File_a.available()) {
      File_a.read();  //不断循环读取
      a_num++;
    }
    Serial.println(a_num);
    File_a.close();
  } 
  else {
    Serial.println("error opening b.txt");
  }

  File_b = SD.open(b_path);//打开指定文件
  if (File_b) {
    Serial.println("b.txt:");
    while (File_b.available()) {
      File_b.read();  //不断循环读取
      b_num++;
    }
    Serial.println(b_num);
    File_b.close();
  } 
  else {
    Serial.println("error opening b.txt");
  }

  a_times=a_num/BLOCK;
  a_rest=a_num%BLOCK;
  b_times=b_num/BLOCK;
  b_rest=b_num%BLOCK;

  if(a_num<b_num){
    a_or_b=1;
    small_times=a_times;
    big_times=b_times;
    small_rest=a_rest;
    big_rest=b_rest;
  }
  else{
    a_or_b=0;
    small_times=b_times;
    big_times=a_times;
    small_rest=b_rest;
    big_rest=a_rest;
  }
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  //完整BLOCK运算加法
  Summid=SD.open("summid.txt",FILE_WRITE);
  
  for(int count=0;count<small_times;count++){/////////////
    a_cursor=a_num-BLOCK-count*BLOCK;
    b_cursor=b_num-BLOCK-count*BLOCK;
    
    File_a=SD.open(a_path);
    if(File_a){
      int i1=0;
      int i2=0;
      while(File_a.available()&&i1<a_cursor){
        File_a.read();//读取但不记录
        i1++;
      }
      for(i2=0;i2<BLOCK;i2++){
        a_store=File_a.read()-'0';
        num1[i2]=a_store;
      }
      File_a.close();
    }
    else {
      Serial.println("error opening a.txt");
    }
    
    File_b=SD.open(b_path);
    if(File_b){
      int i3=0;
      int i4=0;
      while(File_b.available()&&i3<b_cursor){
        File_b.read();//读取但不记录
        i3++;
      }
      for(i4=0;i4<BLOCK;i4++){
        b_store=File_b.read()-'0';
        num2[i4]=b_store;
      }
      File_b.close();
    } 
    else {
      Serial.println("error opening b.txt");
    }
    
    //运算和储存
    for(int i5=BLOCK-1;i5>=0;i5--){
      summid=num1[i5]+num2[i5]+flag;
      if(summid>9){
        flag=1;
        summid=summid-10;
      }
      else{
        flag=0;
      }    
      Summid.print(summid);
    }
//    Serial.println(count);
  }
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  //不完整BLOCK运算加法
  a_cursor=a_num-small_times*BLOCK-small_rest;
  b_cursor=b_num-small_times*BLOCK-small_rest;
  
  File_a=SD.open(a_path);
  if(File_a){
    int i1=0;
    int i2=0;
    while(File_a.available()&&i1<a_cursor){
      File_a.read();//读取但不记录
      i1++;
    }
    for(i2=0;i2<small_rest;i2++){
      a_store=File_a.read()-'0';
      num1[i2]=a_store;
    }
    File_a.close();
  }
  else {
    Serial.println("error opening a.txt");
  }

  File_b=SD.open(b_path);
  if(File_b){
    int i3=0;
    int i4=0;
    while(File_b.available()&&i3<b_cursor){
      File_b.read();//读取但不记录
      i3++;
    }
    for(i4=0;i4<small_rest;i4++){
      b_store=File_b.read()-'0';
      num2[i4]=b_store;
    }
    File_b.close();
  } 
  else {
    Serial.println("error opening b.txt");
  }

  //运算和储存
  for(int i5=small_rest-1;i5>=0;i5--){
    summid=num1[i5]+num2[i5]+flag;
    if(summid>9){
      flag=1;
      summid=summid-10;
    }
    else{
      flag=0;
    }    
    Summid.print(summid);
  }


//////////////////////////////////////////////////////////////////
  //处理尾缀
  
  //不在同一个BLOCK
  if(a_times!=b_times){
    ////////////////////
    //第一段
    ////////////////////
    if(a_or_b==0){//a更长
      File_last=SD.open(a_path);
      last_cursor=a_num-(small_times+1)*BLOCK;
    }
    else{
      File_last=SD.open(b_path);
      last_cursor=b_num-(small_times+1)*BLOCK;
    }
    if(File_last){
      int i7=0;
      int i8=0;
      while(File_last.available()&&i7<last_cursor){
        File_last.read();//读取但不记录
        i7++;
      }
      for(i8=0;i8<BLOCK-small_rest;i8++){
        last_store=File_last.read()-'0';
        num1[i8]=last_store;
      }
      for(int i5=BLOCK-small_rest-1;i5>=0;i5--){
        summid=num1[i5]+flag;
        if(summid>9){
          flag=1;
          summid=summid-10;
        }
        else{
          flag=0;
        }
        Summid.print(summid);
      }
    }
    ////////////////////
    //第二段
    ////////////////////
    for(int count=0;count<(big_times-small_times-1);count++){/////////////
      if(a_or_b==0){//a更长
        last_cursor=a_num-(small_times+2)*BLOCK-count*BLOCK;
      }
      else{
        last_cursor=b_num-(small_times+2)*BLOCK-count*BLOCK;
      }
      if(File_last){
        int i1=0;
        int i2=0;
        while(File_last.available()&&i1<last_cursor){
          File_last.read();//读取但不记录
          i1++;
        }
        for(i2=0;i2<BLOCK;i2++){
          last_store=File_a.read()-'0';
          num1[i2]=last_store;
        }
      }
      else {
        Serial.println("error opening a.txt");
      }
      
      //运算和储存
      for(int i5=BLOCK-1;i5>=0;i5--){
        summid=num1[i5]+flag;
        if(summid>9){
          flag=1;
          summid=summid-10;
        }
        else{
          flag=0;
        }    
        Summid.print(summid);
      }
//      Serial.println(count);
    }
    ////////////////////
    //第三段
    ////////////////////
    last_cursor=0;
    if(File_last){
      int i8=0;
      for(i8=0;i8<big_rest;i8++){
        last_store=File_last.read()-'0';
        num1[i8]=last_store;
      }
      for(int i5=big_rest-1;i5>=0;i5--){
        summid=num1[i5]+flag;
        if(summid>9){
          flag=1;
          summid=summid-10;
        }
        else{
          flag=0;
        }
        Summid.print(summid);
      }
    }
    File_last.close();
  }
  //在同一个BLOCK
  else{
    if(a_or_b==0){//a更长
      File_last=SD.open(a_path);
    }
    else{
      File_last=SD.open(b_path);
    }
    last_cursor=0;
    if(File_last){
      int i8=0;
      for(i8=0;i8<big_rest-small_rest;i8++){
        last_store=File_last.read()-'0';
        num1[i8]=last_store;
      }
      for(int i5=big_rest-small_rest-1;i5>=0;i5--){
        summid=num1[i5]+flag;
        if(summid>9){
          flag=1;
          summid=summid-10;
        }
        else{
          flag=0;
        }
        Summid.print(summid);
      }
    }
    File_last.close();
  }

  if(flag==1)
    Summid.print(flag);
  
  Summid.close();   
//////////////////////////////////////////////////////////////////
  //检验
  Summid=SD.open("summid.TXT");
  Serial.println("summid.txt:");
  while (Summid.available()) {
    Serial.write(Summid.read());  //不断循环读取
  }
  Serial.println(" ");
  Summid.close();
/////////////////////////////////////////////////////////////////
  //反过来
  int len;
  if(a_or_b==0)
    len=a_num+flag;
  else
    len=b_num+flag;
    
  for(int count=0;count<big_times;count++){
    Summid=SD.open("summid.TXT");
    sum_cursor=len-BLOCK-count*BLOCK;//定位
    if(Summid){
      int i5=0;
      int i6=0;
      int i7=0;
      while(Summid.available()&&i5<sum_cursor){
        Summid.read();//读取但不记录
        i5++;
      }
      for(i6=0;i6<BLOCK;i6++){
        sum_store=Summid.read()-'0';
        sum[BLOCK-1-i6]=sum_store;
      }
      Summid.close();
      Sum=SD.open("sum.txt",FILE_WRITE);
      for(i7=0;i7<BLOCK;i7++){
        Sum.print(sum[i7]);
      }
      Sum.close();
    } 
    else {
      Serial.println("error opening a.txt");
    }
//    Serial.println(count);
  }
  sum_cursor=0;
  Summid=SD.open("summid.TXT");
  if(Summid){
    int i7=0;
    int i8=0;
    for(i8=0;i8<len-big_times*BLOCK;i8++){
      sum_store=Summid.read()-'0';
      sum[i8]=sum_store;
    }
    Summid.close();
    Sum=SD.open("sum.txt",FILE_WRITE);
    for(i7=len-big_times*BLOCK-1;i7>=0;i7--){
      Sum.print(sum[i7]);
    }
    Sum.close();
  }
  Summid.close();
  
//////////////////////////////////////////////////////////////////
  //检验
  Sum=SD.open("sum.TXT");
  Serial.println("sum.txt:");
  while (Sum.available()) {
    Serial.write(Sum.read());  //不断循环读取
  }
  Sum.close();
/////////////////////////////////////////////////////////////////
}


void loop() {
  
}
