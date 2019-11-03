#include "GUI.h"
#include "oled.h"
#include "sys.h"

//菜单首页
void MENU_FST()
{
	OLED_clear(GRAY2);
	OLED_Font_Display(0,0,WHITE,GRAY2,"未闻花名");
	OLED_Font_Display(0,16,WHITE,GRAY2,"天空之城");
	OLED_Font_Display(0,32,WHITE,GRAY2,"生日歌");
	OLED_Font_Display(0,48,WHITE,GRAY2,"童年");
	OLED_Font_Display(0,64,WHITE,GRAY2,"两只老虎");
	OLED_Font_Display(0,80,WHITE,GRAY2,"世上只有妈妈好");
}

//播放界面
void GUI_process(u8 *name)
{
	u8 i,j;
	OLED_clear(GRAY2);
	OLED_Font_Display(8,100,WHITE,GRAY2,name);

}
