/**
* @file gate.cpp
* @brief Gate和Board的实现
* @author bbpumpkin
* @version 1.0.0
* @date 2019-10-14
*/
#include "gate.h"

Gate::Gate(GateType t, int _gid)
{
	type = t;
	gid = _gid;
	clear();
}
void Gate::clear()
{
	input_buf = 0;
	output_buf = 0;
	mask = 0;
}
Gate::OutputSet Gate::getOutput() const
{
	return output_buf;
}
int Gate::getGid() const
{
	return gid;
}
void Gate::connectTo(Gate& dst, int bid)
{
	Dst dst_info;
	dst_info.dst = &dst;
	dst_info.dst_id = bid;
	mp.push_back(dst_info);
}

void Gate::setBit(bool b_in, int dst_id)
{
	int in = b_in << dst_id;
	int bmask = 1 << dst_id;
	input_buf &= ~bmask;
	input_buf |= (in & bmask);
	mask |= bmask;
}
void Gate::propogate(Gate::InputSet in)
{
	output_buf = handle(in);
	for (Dst& dst_info : mp)
	{
		dst_info.dst->setBit(output_buf, dst_info.dst_id);
		dst_info.dst->propogate();
	}
}
void Gate::propogate()
{
	if (!isAllSet()) return;
	propogate(input_buf);
}
Gate::OutputSet Gate::handle(Gate::InputSet in)
{
	switch (type)
	{
	case VOID: return in;
	case NOT: return in ^ 1;
	case AND: return bool(in & 1) & bool(in & 2);
	case OR: return bool(in & 1) | bool(in & 2);
	case XOR: return bool(in & 1) ^ bool(in & 2);
	}
}
bool Gate::isAllSet() const
{
	switch (type)
	{
	case NOT: return mask == 1;
	case VOID: return true;
	default: return mask == 3;
	}
	return false;
}

bool Board::add(Gate::GateType type, int gid)
{
	if (gates.count(gid)) return false;
	gates[gid] = Gate(type, gid);
	return true;
}

const map<int, Gate>& Board::listGate() const
{
	return gates;
}

void Board::clear()
{
	for (auto it = gates.begin(); it != gates.end(); ++it)
	{
		it->second.clear();
	}
}

bool Board::connect(int from_gid, int to_gid, int bmask)
{
	if (!gates.count(from_gid) || !gates.count(to_gid)) return false;
	gates[from_gid].connectTo(gates[to_gid], bmask);
	return true;
}

//bool Board::setInputGates(const vector<Port>& ports)
//{
//	for (Port port : ports)
//	{
//		if (!gates.count(port.gid)) return false;
//	}
//	input_gates = ports;
//	return true;
//}

bool Board::setOutputGates(const vector<int>& gids)
{
	for (int gid : gids)
	{
		if (!gates.count(gid)) return false;
	}
	output_gates = gids;
	return true;
}

map<int, Gate::OutputSet> Board::calculate(const map<Port, Gate::InputSet>& ins)
{
	for (auto it = ins.begin(); it != ins.end(); ++it)
	{
		Port port = it->first; Gate::InputSet in = it->second;
		gates[port.gid].setBit(in, port.bmask);
		gates[port.gid].propogate();
	}
	map<int, Gate::OutputSet> res;
	for (int i = 0; i < output_gates.size(); i++)
	{
		int ogid = output_gates[i];
		res[ogid] = gates[ogid].getOutput();
	}
	return res;
}
