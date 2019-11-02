#include <SPI.h>
#include <SD.h>
#include <String.h>

//加法
void add()
{
  File a_file = SD.open("a.txt");
  File b_file = SD.open("b.txt");
  int start_a=a_file.size()-1;
  int start_b=b_file.size()-1;
  a_file.seek(start_a);
  b_file.seek(start_b);
  int pos_a=start_a;
  int pos_b=start_b;

  if (SD.exists("result.txt")) {SD.remove("result.txt");}
  File result_file = SD.open("result.txt",FILE_WRITE);
  
  int next_plus=0;
  int add_two,this_digit;
  
  while(pos_a>=0 && pos_b>=0){
    add_two=(a_file.peek()-'0')+(b_file.peek()-'0')+next_plus;
    if (add_two>=10){//进位
      this_digit=add_two-10;
      next_plus=1;
    }
    else{//不进位
      this_digit=add_two;
      next_plus=0;
    }
    char c=this_digit+'0'; 
    result_file.write(c);
    a_file.seek(--pos_a);
    b_file.seek(--pos_b);
  }

  if (pos_a<0){
    while(pos_b>=0){
      add_two=(b_file.peek()-'0')+next_plus;
      if (add_two>=10){//进位
        this_digit=add_two-10;
        next_plus=1;
      }
      else{//不进位
        this_digit=add_two;
        next_plus=0;
      }
      char c=this_digit+'0'; 
      result_file.write(c);
      b_file.seek(--pos_b);
    }
  }
  if (pos_b<0){
    while(pos_a>=0){
      add_two=(a_file.peek()-'0')+next_plus;
      if (add_two>=10){//进位
        this_digit=add_two-10;
        next_plus=1;
      }
      else{//不进位
        this_digit=add_two;
        next_plus=0;
      }
      char c=this_digit+'0'; 
      result_file.write(c);
      a_file.seek(--pos_a);
    }  
  }

  a_file.close();
  b_file.close();
  
  //最高位是否有进位1
  if (next_plus>0) {
    char c=next_plus+'0'; 
    result_file.write(c);
  }

  result_file.close();

  if (SD.exists("sum.txt")) {SD.remove("sum.txt");}
  File sum_file = SD.open("sum.txt",FILE_WRITE);

  result_file = SD.open("result.txt");
  int start_result=result_file.size()-1;
  result_file.seek(start_result);
  int pos_result=start_result;
  
  while(pos_result>=0){
    char c=result_file.peek();
    sum_file.write(c);
    result_file.seek(--pos_result);
  }
  
  sum_file.close();
  result_file.close();

  if (SD.exists("result.txt")) {SD.remove("result.txt");}
}

void setup() {
  Serial.begin(9600);

  //初始化sd卡
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  add();
  
  Serial.println("Done");
}

void loop() {

}
