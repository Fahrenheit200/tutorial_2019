import os, random
from random import randint
class Request:
	def __init__(self, rid, type, st, duration):
		self.rid = int(rid)
		self.type = type
		self.st = int(st)
		self.duration = int(duration)
	def __repr__(self):
		return f"{self.rid} {self.type} {self.st} {self.duration}"

def genData():
	req_dict = {}
	max_tick = randint(0, 10)
	ecnt = 1
	outputs = []
	for i in range(max_tick):
		cnt = randint(0, 3)
		if cnt: req_dict[i] = []
		for j in range(cnt):
			rtype = random.choice(["R", "R", "R", "R", "W"])
			req = Request(ecnt, rtype, i, randint(1, 7))
			req_dict[i].append((req, "request"))
			outputs.append(repr(req))
			ecnt += 1
	with open("test.in", "w") as f:
		f.write('\n'.join(outputs))
	# with open("test.in", "wb") as f:
	# 	f.write(bytes('\n'.join(outputs), encoding='ascii'))
	print("Gen Data OK")
	return req_dict
def loadData():
	## Load data
	# finame = input("Fin: ")
	# foutname = input("Fout: ")
	os.system("./ThreadDispatch test.in > test.out")
	foutname = "test.out"
	with open(foutname, "r") as f:
		data_out = f.read().strip().split('\n')
	print("Load data_out OK")
	return data_out

def reshapeData(data_in):
	## Reshape data
	data_in = list(map(lambda x: Request(*(x.strip().split(' ' ))), data_in))
	req_dict = {}
	for req in data_in:
		req_dict.setdefault(req.st, []).append((req, "request"))
	return req_dict

def simulate(req_dict):
	## Simulator
	tick = 0
	q = []
	event = {}
	running_pool = []
	occupy = None
	max_input_tick = max(req_dict.keys())
	while 1:
		if not q and not running_pool and tick > max_input_tick: break
		if tick in req_dict:
			for req, action in req_dict[tick]:
				if action == "request":
					if req.type == "R":
						q.append(req)
					else:
						p = len(q) - 1
						while p >= 0 and q[p].type == "R": p -= 1
						q.insert(p + 1, req)
				elif action == "exit":
					running_pool.remove(req)
					event.setdefault(tick, []).append((req, tick, "exit"))
				else:
					raise Exception()
		if not running_pool:
			occupy = None
		if not occupy and q:
			req = q.pop(0)
			event.setdefault(tick, []).append((req, tick, "start"))
			req_dict.setdefault(tick + req.duration, []).append((req, "exit"))
			running_pool.append(req)
			occupy = req.type
		if occupy == "R":
			while len(q) and q[0].type == "R":
				req = q.pop(0)
				event.setdefault(tick, []).append((req, tick, "start"))
				req_dict.setdefault(tick + req.duration, []).append((req, "exit"))
				running_pool.append(req)
		tick += 1
	print("simuation OK")
	return event

def check(data_out, event):
	## Check
	ok = True
	for line in data_out:
		line = line.strip()
		if (line.startswith("[main]")): continue
		if (line.endswith("exit")):
			items = line.split(' ')
			rid = int(items[2][:-1])
			t = int(items[3][:-2])
			found = False
			for e in event.get(t, []):
				if e[0].rid == rid and e[2] == "exit":
					found = True
			if not found:
				print(rid, t, "exit")
				print(event.get(t))
				ok = False
				break
		else:
			items = line.split(' ')
			rid = int(items[2][:-1])
			t = int(items[3][:-2])
			found = False
			for e in event.get(t, []):
				if e[0].rid == rid and e[2] == "start":
					found = True
			if not found:
				print(rid, t, "start")
				print(event.get(t))
				ok = False
				break
	if not ok:
		print("Fail")
		input("Press to continue")
	else:
		print("OK")

while 1:
	req_dict = genData()
	if not req_dict:
		print("Empty input, try again")
		continue
	data_out = loadData()
	events = simulate(req_dict)
	check(data_out, events)
input()
