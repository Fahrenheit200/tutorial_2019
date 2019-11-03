#include <SPI.h>
#include <SD.h>
File myFile1;
File myFile2;
File sum2;
File sum;
static char flag=0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
  char a;
  char b;
  myFile1 = SD.open("1.txt");
  myFile2 = SD.open("2.txt");
  sum2=SD.open("SUM2.TXT",FILE_WRITE);
  for(int i=myFile1.size()-1,j=myFile2.size()-1; i>=0 || j>=0; i--, j--)
   {
    myFile1.seek(i);        //定位到第i位 i逐渐减小也即从尾部遍历大数
    if(i<0) a=0+48;         //i小于0说明文件中的数已经遍历完之后a为0 但不知道为什么读取出的数与实际整数总会相差48
    else a=myFile1.read();  //读取文件的第i位
    
    myFile2.seek(j);
    if(j<0) b=0+48;
    else b=myFile2.read();

    int c=int(a)-48+int(b)-48+flag;     //计算对应为的和，并加上进数，减去48便可将a,b当作普通整数
    flag=0;   //进数清0

    //如果和大于10 减去10 并进位数置1
    if(c>9) 
    {
      Serial.print("inif:");
      Serial.println(c);
      c-=10;
      flag=1;
    }
    
    sum2.print(c); // 将该位的和写入文件
   }
    myFile1.close();
    myFile2.close();
    sum2.close();

    //将上面过程的和数反转 使高位在前
    sum=SD.open("SUM.TXT",FILE_WRITE);
    sum2=SD.open("sum2.txt");
    Serial.println("writing sum.txt");
    for(int i=sum2.size()-1;i>=0;i--)
    {
        sum2.seek(i);
        sum.write(sum2.read());
    }
    Serial.println("done");
    sum.close();
    sum2.close();

}
void loop() {  
  // nothing happens after setup
}
