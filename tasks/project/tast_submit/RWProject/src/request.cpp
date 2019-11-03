#include <fstream>
#include <algorithm>
#include <thread>
#include "request.h"

Request::Request(int _rid, RequestType rt, int st, int durat):
	rid(_rid), type(rt), start_t(st), duration(durat)
{
}

Request::Request(int _rid, const string& rt, int st, int durat):
	rid(_rid), start_t(st), duration(durat)
{
	if (rt == "W")
		type = W;
	else
		type = R;
}

