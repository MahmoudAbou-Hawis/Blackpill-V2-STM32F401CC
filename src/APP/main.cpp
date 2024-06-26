#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MASTER)


#include "TFT.hpp"
#include "Mahmoud.h"
#include "switch_cfg.h"
#include "switch.h"
#include "schedular.h"

display::TFT screen;




int main(void)
 {
	SWITCH_enuInit();
	display::point start{128,160};
	display::point end{24,114};

/*	
	screen.DrawImage(Sofar,&start,128,130);

	display::point center{65,137};
	screen.DrawCircle(&center,21,display::Colors::BLACK);

	display::point Name = {128,30};
	screen.WriteText("Mahmoud \nAbou-Hawis         ",display::Fonts::Font_7X10,display::Colors::BLACK,display::Colors::WHITE,&Name);

*/

	char *  arr[2] = {"photos" , "videos"};
	char *  photos[3] = {"ITI.png" , "Eid.png", "sofar.png"};

	int mainList = screen.OptionList(arr,2);
	int secondryList = screen.OptionList(photos,3);
	screen.ShowOptionList(mainList);
	
	for(int i = 0 ; i < 1500000;i++);
	for(int i = 0 ; i < 100000;i++);

	screen.ShowOptionList(secondryList);
	for(int i = 0 ; i < 1500000;i++);

	screen.next();
	for(int i = 0 ; i < 1500000;i++);
	screen.DrawImage(Sofar,&start,128,160);

	while(1);
    return 0;
}
#endif