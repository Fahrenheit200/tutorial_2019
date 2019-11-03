#include <math.h>
#define DAT_NUM 64
#define DAT_POW 6

typedef unsigned char uint8;
typedef unsigned int uint16;

typedef struct {
	float real;
	float img;
}Complex;

double code PI = 3.1415926;
Complex dat[DAT_NUM];
Complex code wt[DAT_NUM]={
	{  1.000000, -0.000000},
	{  0.995185, -0.098017},
	{  0.980785, -0.195090},
	{  0.956940, -0.290285},
	{  0.923880, -0.382683},
	{  0.881921, -0.471397},
	{  0.831470, -0.555570},
	{  0.773010, -0.634393},
	{  0.707107, -0.707107},
	{  0.634393, -0.773010},
	{  0.555570, -0.831470},
	{  0.471397, -0.881921},
	{  0.382683, -0.923880},
	{  0.290285, -0.956940},
	{  0.195090, -0.980785},
	{  0.098017, -0.995185},
	{  0.000000, -1.000000},
	{ -0.098017, -0.995185},
	{ -0.195090, -0.980785},
	{ -0.290285, -0.956940},
	{ -0.382683, -0.923880},
	{ -0.471397, -0.881921},
	{ -0.555570, -0.831470},
	{ -0.634393, -0.773010},
	{ -0.707107, -0.707107},
	{ -0.773010, -0.634393},
	{ -0.831470, -0.555570},
	{ -0.881921, -0.471397},
	{ -0.923880, -0.382683},
	{ -0.956940, -0.290285},
	{ -0.980785, -0.195090},
	{ -0.995185, -0.098017},
	{ -1.000000, -0.000000},
	{ -0.995185,  0.098017},
	{ -0.980785,  0.195090},
	{ -0.956940,  0.290285},
	{ -0.923880,  0.382683},
	{ -0.881921,  0.471397},
	{ -0.831470,  0.555570},
	{ -0.773010,  0.634393},
	{ -0.707107,  0.707107},
	{ -0.634393,  0.773010},
	{ -0.555570,  0.831470},
	{ -0.471397,  0.881921},
	{ -0.382683,  0.923880},
	{ -0.290285,  0.956940},
	{ -0.195090,  0.980785},
	{ -0.098017,  0.995185},
	{ -0.000000,  1.000000},
	{  0.098017,  0.995185},
	{  0.195090,  0.980785},
	{  0.290285,  0.956940},
	{  0.382683,  0.923880},
	{  0.471397,  0.881921},
	{  0.555570,  0.831470},
	{  0.634393,  0.773010},
	{  0.707107,  0.707107},
	{  0.773010,  0.634393},
	{  0.831470,  0.555570},
	{  0.881921,  0.471397},
	{  0.923880,  0.382684},
	{  0.956940,  0.290285},
	{  0.980785,  0.195090},
	{  0.995185,  0.098017}
};

void fastFourier();
void posRearrange();
float getDat(uint8 t);
void clearDat();
void pushDat(uint8 index,uint8 s);

void add(Complex ,Complex ,Complex *);
void mul(Complex ,Complex ,Complex *);
void sub(Complex ,Complex ,Complex *);

void pushDat(uint8 index,uint8 s){
	dat[index].real=s;
}
void clearDat(){
	uint8 i;
	for(i=0;i<64;i++)
	dat[i].real=dat[i].img=0;
}
float getDat(uint8 t){
	return sqrt(dat[t].real*dat[t].real+dat[t].img*dat[t].img);
}
void fastFourier()
{
	uint8 p = 0, q = 0, k = 0, len = 0;
	Complex prev, next, result;
	posRearrange();
	for (p = 0; p < DAT_POW; p++) {
		len = 1 << p;
		for (q = 0; q < DAT_NUM; q = q + 2 * len) {
			for (k = 0; k < len; k++) {
				mul(dat[q + k + len], wt[DAT_NUM*k / 2 / len], &result);
				add(dat[q + k], result, &prev);
				sub(dat[q + k], result, &next);
				dat[q + k] = prev;
				dat[q + k + len] = next;
			}
		}
	}
}
void posRearrange()
{
	Complex temp;
	uint8 i = 0, j = 0, k = 0;
	double t;
	for (i = 0; i < DAT_NUM; i++) {
		k = i; j = 0;
		t = DAT_POW;
		while ((t--) > 0) {
			j = j << 1;
			j |= (k & 1);
			k = k >> 1;
		}
		if (j > i) {
			temp = dat[i];
			dat[i] = dat[j];
			dat[j] = temp;
		}
	}
}
void add(Complex a, Complex b, Complex *c) {
	c->real = a.real + b.real;
	c->img = a.img + b.img;
}
void mul(Complex a, Complex b, Complex *c) {
	c->real = a.real*b.real - a.img*b.img;
	c->img = a.real*b.img + a.img*b.real;
}
void sub(Complex a, Complex b, Complex *c) {
	c->real = a.real - b.real;
	c->img = a.img - b.img;
}
