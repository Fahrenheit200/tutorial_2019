typedef unsigned char uint8;
typedef unsigned int uint16;

void delay50ms(uint16 t);
void delay1ms(uint16 t);

void delay50ms(uint16 t)
{
	uint16 i;
	for(;t>0;t--)
	for(i=6245;i>0;i--);
}
void delay1ms(uint16 t)
{
	uint8 i;
	while (t--)
	for (i=0;i<123;i++);
}
