#include "GUI.h"
#include "oled.h"
#include "sys.h"

//�˵���ҳ
void MENU_FST()
{
	OLED_clear(GRAY2);
	OLED_Font_Display(0,0,WHITE,GRAY2,"δ�Ż���");
	OLED_Font_Display(0,16,WHITE,GRAY2,"���֮��");
	OLED_Font_Display(0,32,WHITE,GRAY2,"���ո�");
	OLED_Font_Display(0,48,WHITE,GRAY2,"ͯ��");
	OLED_Font_Display(0,64,WHITE,GRAY2,"��ֻ�ϻ�");
	OLED_Font_Display(0,80,WHITE,GRAY2,"����ֻ�������");
}

//���Ž���
void GUI_process(u8 *name)
{
	u8 i,j;
	OLED_clear(GRAY2);
	OLED_Font_Display(8,100,WHITE,GRAY2,name);

}
