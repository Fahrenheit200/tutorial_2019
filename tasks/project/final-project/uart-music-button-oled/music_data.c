typedef unsigned char uint8;
typedef unsigned int uint16;
uint16 code reloadTHTL[3][7]={{0xF88B,0xF95B,0xFA14,0xFA66,0xFB03,0xFB8F,0xFC0B},
									{0xFC43,0xFCAB,0xFD08,0xFD33,0xFD81,0xFDC7,0xFE05},
									{0xFB21,0xFE55,0xFE84,0xFE99,0xFEC0,0xFEE3,0xFF02}};
uint16 code freq[3][7]={{262,293,329,349,392,440,494},
							  {523,586,658,697,783,879,987},
							  {1045,1171,1316,1393,1563,1755,1971}};
float code clapDiv[7]={1.0,0.5,0.25,0.125,0.0625,0.0315,0.015625};
float oneClapTime=2.5;
float soundpercent=0.5;
uint8 tot; //0x6666
uint8 musicBuff[192];
uint8 musicLength;
uint8 whichSong;
uint16 code dataStart[20]= {0,192,384,576,768,960,1152,1344,1536,1728,
						   1920,2112,2304,2496,2688,2880,3072,3264,3456,3648};
