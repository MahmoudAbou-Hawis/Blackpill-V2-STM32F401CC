#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MASTER)


#include "TFT.hpp"
#include "Mahmoud.h"


int main(void)
 {

	display::point start{128,160};
	display::point end{24,114};

	display::TFT screen;
	
	screen.DrawImage(Sofar,&start,128,130);

	display::point center{65,137};
	screen.DrawCircle(&center,21,display::Colors::BLACK);

	display::point Name = {128,30};
	screen.WriteText("Mahmoud \nAbou-Hawis         ",display::Fonts::Font_7X10,display::Colors::BLACK,display::Colors::WHITE,&Name);
	

	while(1);
    return 0;
}
#endif