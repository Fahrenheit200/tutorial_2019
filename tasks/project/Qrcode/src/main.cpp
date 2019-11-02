#include "Qrcode.h"

int main(int argc, char* argv[]) {
	Qrcode q(argv[1]);
	q.show();
 	return 0;
}
