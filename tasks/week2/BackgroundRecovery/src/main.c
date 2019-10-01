#include "Recovery.h"

int main(int argc, char* argv[]) {
	Recovery ry;
	ry.readVideo(argv[1]);
	ry.process();
	ry.showResult();
    return 0;
}

