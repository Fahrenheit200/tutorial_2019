#ifndef NOTETWO_H
#define NOTETWO_H

#define EL1 330
#define EL2 370
#define EL3 415
#define EL4 440
#define EL5 494
#define EL6 554
#define EL7 622
#define EM1 659
#define EM2 740
#define EM3 831
#define EM4 880
#define EM5 988
#define EM6 1109
#define EM7 1245
#define EH1 1318

const int sky_castle_tune[]=
{EL6,EL7,  EM1,EL7,EM1,EM3,  EL7,EL3,  EL6,EL5,EL6,EM1,   EL5,EL3,  EL4,EL3,EL4,EM1,EM1,   EL3,EM1,  EL7,EL4,EL4,EL7,
 EL7,0,EL6,EL7,  EM1,EL7,EM1,EM3,  EL7,EL3,EL3,   EL6,EL5,EL6,EM1,  EL5,EL3,  EL4,EM1,EL7,EL7,EM1,  EM2,EL3,EM1,0,   EM1,EL7,EL6,EL7,EL5,
 EL6,0,EM1,EM2,  EM3,EM2,EM3,EM4,EM5,   EM2,EL5,  EM2,EM1,EL7,EM1,EM1,EM1,EM2,EM3};

 const float duration[]=
 {
	0.5,0.5,  1+0.5,0.5,1,1,   1,1,1,1,   1,0.5,1,1,  1,1,1,1,  1,0.5,0.5,0.5,1
 }




#endif