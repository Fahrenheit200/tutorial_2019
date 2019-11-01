#include <SPI.h>
#include <SD.h>
#include <String.h>

//加法
String& add(String& x,String& y)
{
  //使a是长度短的
  String a,b;
  if (x.length()>y.length()){
    a=y;
    b=x;
  }
  else{
    a=x;
    b=y;
  }
  
  static String result="";
  int next_plus=0;
  int i,j;
  
  //i=a.length()-1到0, j=b.length()-1到b.length()-a.length()
  for(i=a.length()-1,j=b.length()-1;i>=0;i--,j--){
    int add_two=String(a[i]).toInt()+String(b[j]).toInt()+next_plus;
    int this_digit;
    if (add_two>=10){//进位
      this_digit=add_two-10;
      next_plus=1;
    }
    else{//不进位
      this_digit=add_two;
      next_plus=0;
    }
    result=String(this_digit)+result; 
  }

  //j=b.length()-a.length()-1到0  
  for(j=b.length()-a.length()-1;j>=0;j--){
    int add_two=String(b[j]).toInt()+next_plus;
    int this_digit;
    if (add_two>=10){//进位
      this_digit=add_two-10;
      next_plus=1;
    }
    else{//不进位
      this_digit=add_two;
      next_plus=0;
    }
    result=String(this_digit)+result;
  }
  
  //最高位是否有进位1
  if (next_plus>0) result=String(next_plus)+result;

  //除去最前面的0
  int zeros=0;
  while(result[zeros]=='0'){
    zeros++;
  }
  result.remove(0,zeros);
  
  //返回结果
  return result;
}

//乘法
String& multiply(String& x,String& y)
{
  //除去两个数最前面的0
  if (x[0]=='0'){
    int zeros=0;
    while(x[zeros]=='0'){
      zeros++;
    }
    x.remove(0,zeros);
  }
  if (y[0]=='0'){
    int zeros=0;
    while(y[zeros]=='0'){
      zeros++;
    }
    y.remove(0,zeros);
  }
  
  //乘法处理，先不进位
  long m=x.length(),n=y.length(),len=m+n;
  int num_result[len]={0};//m位*n位乘法结果的长度是m+n或m+n-1,所有位置初始化为0
  //memset(num_result,0,len);
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++){
      //根据竖式乘法的原则，结果中的第x位=第i位和第j位（i+j==x）相乘的结果之和（的个位），暂时不考虑进位，第一位是0
      num_result[i+j+1]+=(x[i]-'0')*(y[j]-'0');
    }
  }
  
  //从低位向高位遍历，进位计算出最终结果
  for(int i=len-1;i>0;i--){
    num_result[i-1]+=num_result[i]/10;//高位等于原本数值加低位进位
    num_result[i]%=10;//低位（当前位）数值等于个位上的数
  }

  //查看第一位是否有进位
  int start=0;
  if (num_result[0]==0) start=1;
  static String result="";
  for(int i=start;i<len;i++)
    result+=String(num_result[i]);

  return result;
}

//读取文件数据
String readNumber(String file_name)
{
  File show_file = SD.open(file_name);
  String content="";
  if (show_file) {
    while (show_file.available()) {
      content+=String(show_file.read()-'0'); 
    }
    show_file.close();
  } 
  return content;
}

//修改文件数据
bool modifyNumber(String file_name,String content)
{
  if (SD.exists(file_name)) SD.remove(file_name);
  File modify_file = SD.open(file_name,FILE_WRITE);

  if (modify_file) {
    modify_file.print(content);
    modify_file.close();
    return true;
  } 
  else//未成功打开文件
    return false;
}

void setup() {
  Serial.begin(9600);
  //初始化sd卡
  SD.begin(4);
  
  //读a,b
  String a=readNumber("a.txt");
  String b=readNumber("b.txt");

  //add
  String add_result=add(a,b);

  //multiply
  String multiply_result=multiply(a,b);
  
  //存结果sum.txt和product.txt
  modifyNumber("sum.txt",add_result);
  modifyNumber("product.txt",multiply_result);

  Serial.println("Done");
}

void loop() {
  
}
