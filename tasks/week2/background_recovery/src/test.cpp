#include"Recovery.h"

int main()
{
	Recovery recovery;
    string filePath;
    cin>>filePath;
	recovery.readVideo(filePath);
	recovery.process();
	recovery.showResult();
	return 0;
}
