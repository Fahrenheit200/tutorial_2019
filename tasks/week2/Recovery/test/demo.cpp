#include "../inc/Recovery.h"
int main(int argc, char** argv)
{
	Recovery re;
	re.readVideo(argv[1]);
	re.process();
	re.showResult();
	return 0;
}
