#include <SPI.h>
#include <SD.h>
#define MAXN 100
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long ulong;
File inA, inB, outC, outD;
uint8 chipSelect = 4;
char inAbuff[MAXN + 1];
char inBbuff[MAXN + 1];
char dBuff[MAXN+1];
char ret[MAXN + 2];
char carryBit[2];
char tmp;
int lenA, lenB, lenD, t, i;

void longCharAdd(char *A, char *B, char *C, uint8 base);
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  inA = SD.open("a.txt");
  lenA = inA.size();
  inA.close();

  inB = SD.open("b.txt");
  lenB = inB.size();
  inB.close();

  carryBit[0] = '0';
  carryBit[1] = '\0';
  for (t = 0; t < 300; t++) {
    Serial.println("Read!");
    Serial.print(lenA);
    Serial.print(" ");
    Serial.print(lenB);
    Serial.println();
    if (lenA <= 0) lenA = 0;
    if (lenB <= 0) lenB = 0;
    if (lenA == 0 && lenB == 0) break;
    inA = SD.open("a.txt");
    for (i = 0; i < MAXN && (lenA - 1 - i) >= 0; i++) {
      inA.seek(lenA - 1 - i);
      inAbuff[i] = inA.peek();
    }
    inAbuff[i] = '\0';
    inA.close();

    inB = SD.open("b.txt");
    for (i = 0; i < MAXN && (lenB - 1 - i) >= 0; i++) {
      inB.seek(lenB - 1 - i);
      inBbuff[i] = inB.peek();
    }
    inBbuff[i] = '\0';
    inB.close();

    longCharAdd(inAbuff, inBbuff, ret, 10);
    longCharAdd(ret, carryBit, ret, 10);

    if (ret[MAXN] != '\0') carryBit[0] = ret[MAXN];
    else carryBit[0] = '0';
    Serial.print("CarryBit: ");
    Serial.println(carryBit);
    ret[MAXN] = '\0';

    outD = SD.open("d.txt", FILE_WRITE);
    outD.write(ret, strlen(ret));
    outD.close();
    Serial.println("Write!");
    lenA -= MAXN;
    lenB -= MAXN;
  }
  outD = SD.open("d.txt", FILE_WRITE);
  lenD = outD.size();
  Serial.println("lenD!");
  Serial.println(lenD);
  outD.close();
  Serial.println("Reverse Begin!");
  for(t=0;t<300;t++){
    if(lenD<=0) break;
    Serial.println(lenD);
    outD = SD.open("d.txt", FILE_WRITE);
    for(i=0;i<MAXN&&lenD-i-1>=0;i++){
      outD.seek(lenD-i-1);
      dBuff[i]=outD.peek();
    }
    dBuff[i]='\0';
    outD.close();
    
    outC=SD.open("c.txt", FILE_WRITE);
    outC.write(dBuff,strlen(dBuff));
    outC.close();
    
    lenD-=MAXN;
  }
  outC.close();
  outD.close();
  Serial.println("Finish!");
  Serial.println("Inverse Finish!");
  SD.remove("d.txt");
}
void loop() {
}
//cstring needed to be included
//A,B are the input, C is the output
//A,B is the reversed char form of a super long integer
//base decides calculating as binary,oct,hex,or dec
void longCharAdd(char *A, char *B, char *C, uint8 base)
{
  int i = 0;
  int a = 0, b = 0;
  //deal with the main part
  while (i < strlen(A) && i < strlen(B))
  {
    a = ((A[i] - '0') + (B[i] - '0') + b) % base;
    b = ((A[i] - '0') + (B[i] - '0') + b) / base;
    C[i] = a + '0';
    i++;
  }
  //find the longer integer and represent as S
  char *S;
  if (strlen(A) > strlen(B)) S = A;
  else S = B;
  //deal with the rest
  while (i < strlen(S))
  {
    a = (S[i] - '0' + b) % base;
    b = (S[i] - '0' + b) / base;
    C[i] = a + '0';
    i++;
  }
  if (b != 0)
    C[i++] = b + '0';
  C[i] = '\0';
  return;
}
