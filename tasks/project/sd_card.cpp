#include <SPI.h>
#include <SD.h>
#include <String.h>

//加法
void add()
{
  //打开两个文件a.txt和b.txt,定位到文件的最后一个字符，从最后开始读起
  File a_file = SD.open("a.txt");
  File b_file = SD.open("b.txt");
  int start_a=a_file.size()-1;
  int start_b=b_file.size()-1;
  a_file.seek(start_a);
  b_file.seek(start_b);
  int pos_a=start_a;
  int pos_b=start_b;

  //result.txt用于存储结果（倒序）
  if (SD.exists("result.txt")) {SD.remove("result.txt");}
  File result_file = SD.open("result.txt",FILE_WRITE);

  //next_plus用于存储进位，add_two用于存两个对应位置相加的结果，this_digit存储进位之后的结果（add_two的个位）
  int next_plus=0;
  int add_two,this_digit;

  //当两个文件都未读完时，每次各读一个字符并计算，然后存入result.txt,每次定位到前一个字符
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

  //a.txt先读完，则只读b.txt
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
  //b.txt先读完，则只读a.txt
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

  //两个文件都读完之后关闭
  a_file.close();
  b_file.close();
  
  //最高位是否有进位1
  if (next_plus>0) {
    char c=next_plus+'0'; 
    result_file.write(c);
  }

  //存储完结果之后关闭result.txt
  result_file.close();

  //创建sum.txt,并打开准备写入
  if (SD.exists("sum.txt")) {SD.remove("sum.txt");}
  File sum_file = SD.open("sum.txt",FILE_WRITE);

  //打开result.txt,定位到文件最后，从最后往前读，依次存入sum.txt中
  result_file = SD.open("result.txt");
  int start_result=result_file.size()-1;
  result_file.seek(start_result);
  int pos_result=start_result;
  
  while(pos_result>=0){
    char c=result_file.peek();
    sum_file.write(c);
    result_file.seek(--pos_result);
  }

  //存储完结果后关闭两个文件，并删除result.txt
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

  //调用加法计算函数
  add();

  //计算完后输出提示
  Serial.println("Done");
}

void loop() {

}
