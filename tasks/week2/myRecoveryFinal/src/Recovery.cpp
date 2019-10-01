#include "Recovery.h"
bool operator <(const pairIdx &A, const pairIdx &B) {
	if (A.q != B.q) return A.q < B.q;
	return A.r < B.r;
}
bool Recovery::qualityIsGood() {
	Mat image;
	int t;
	image = finaldiff;
	cvtColor(image, image, COLOR_BGR2GRAY);
	threshold(image, image, 10, 255, THRESH_BINARY);
	medianBlur(image, image, 9);

	Mat element = getStructuringElement(MORPH_RECT, Size(11, 11));
	morphologyEx(image, image, MORPH_OPEN, element);
	t = countNonZero(image);
	if (t > 200) return 0;
	return 1;	
}
void Recovery::subprocess() {
	int p, q, r;
	pairIdx qrdx,rqdx;
	cont[PQ_CNT].clear();
	cont[QR_CNT].clear();
	cont[PR_CNT].clear();
	diffStore[0].release();
	diffStore[1].release();
	diffStore[2].release();
	while (1) {
		p = 0;
		q = (rand() % (store.size() - 0)) + 0;
		r = (rand() % (store.size() - 0)) + 0;
		qrdx.q = q;
		qrdx.r = r;
		rqdx.q = r;
		rqdx.r = q;
		if (indexTheSame(p, q, r)) continue;
		if (findIdx.count(qrdx) || findIdx.count(rqdx)) continue;
		findIdx[qrdx] = 1;
		findIdx[rqdx] = 1;

		diff(p, q, PQ_CNT);
		if (cont[PQ_CNT].size() <= 1) continue;
		diff(q, r, QR_CNT);
		if (cont[QR_CNT].size() <= 1) continue;
		diff(p, r, PR_CNT);
		if (cont[PR_CNT].size() <= 1) continue;

		chooseRect(PQ_CNT);
		chooseRect(QR_CNT);
		chooseRect(PR_CNT);

		if (rectOverclapOrVoid()) continue;
		if (tooSmalltooClose()) continue;

		singleRect[1] = findSimilar(Q_IDX);
		singleRect[2] = findSimilar(R_IDX);
		if (singleRect[1].area() == 0 || singleRect[2].area() == 0) continue;

		singleRect[0] = findSimilar(P_IDX);
		int to = chooseTheBestOne();
		Rect ret = singleRect[to];
		expandRect(ret);

		if (to == Q_IDX) patcha(ret, p, q);
		else patcha(ret, p, r);
		break;
	}
	return;
}
void Recovery::saveResult(string filePath) {
	imwrite(filePath, finalpic);
	return;
}
void Recovery::readVideo(string filePath) {
	path=filePath;
	cap.open(filePath);
	Mat src, temp;
	while (1) {
		cap >> src;
		if (src.empty()) break;
		temp = src.clone();
		resize(temp, temp, Size(500, src.rows * 500 / src.cols));
		store.push_back(temp);
	}
	cap.set(CAP_PROP_POS_FRAMES, 0);
	cap >> src;
	base = src.clone();
	ratio = cap.get(CAP_PROP_FRAME_WIDTH) / 500.0;
	scale = sqrt(temp.cols*temp.cols + temp.rows*temp.rows);
	whole = Rect(0, 0, temp.cols, temp.rows);
	return;
}
void Recovery::process() {
	findIdx.clear();
	srand((unsigned)time(0));
	subprocess();
	prefinal = finalpic.clone();
	while (1) {
		subprocess();
		absdiff(prefinal, finalpic, finaldiff);
		if (qualityIsGood()) break;
		prefinal = finalpic.clone();
	}
	return;
}
void Recovery::expandRect(Rect &ret) {
	Size expSize(80, 80);
	ret = ret + expSize;
	Point pt;
	pt.x = cvRound(expSize.width / 2.0);
	pt.y = cvRound(expSize.height / 2.0);
	ret = ret - pt;
	ret = ret & whole;
	return;
}
bool Recovery::expandNotOverClap(int t) {
	Rect temp = singleRect[t];
	expandRect(temp);
	if ((temp&singleRect[0]).area() == 0) return 1;
	else return 0;
}
int Recovery::chooseTheBestOne() {
	int to;
	if (singleRect[Q_IDX].area() < singleRect[R_IDX].area()) {
		if (expandNotOverClap(Q_IDX) || !expandNotOverClap(R_IDX)) to = Q_IDX;
		else to = R_IDX;
	}
	else {
		if (expandNotOverClap(R_IDX) || !expandNotOverClap(Q_IDX)) to = R_IDX;
		else to = Q_IDX;
	}
	return to;
}
bool Recovery::indexTheSame(int a, int b, int c) {
	if (a == b) return 1;
	if (a == c) return 1;
	if (b == c) return 1;
	return 0;
}
bool Recovery::tooSmalltooClose() {
	Rect a, b;
	Point aCenter, bCenter;
	double aArea, bArea, relativeDist;
	for (int i = 0; i < 2; i++) {
		a = areaRect[2 * i];
		b = areaRect[2 * i + 1];
		aCenter = getCenterPoint(a);
		bCenter = getCenterPoint(b);
		relativeDist = sqrt((aCenter.x - bCenter.x)*(aCenter.x - bCenter.x) +
			(aCenter.y - bCenter.y)*(aCenter.x - bCenter.x)) / scale;
		aArea = a.area();
		bArea = b.area();
		if (aArea / bArea > 15 || bArea / aArea > 15) return 1;
		if (relativeDist < 0.1) return 1;
	}
	return 0;
}
Point Recovery::getCenterPoint(Rect rect)
{
	Point cpt;
	cpt.x = rect.x + cvRound(rect.width / 2.0);
	cpt.y = rect.y + cvRound(rect.height / 2.0);
	return cpt;
}
void Recovery::showResult() {
	/*
	rectangle(diffStore[0], areaRect[0], Scalar(255), 8);
	rectangle(diffStore[0], areaRect[1], Scalar(255), 8);
	rectangle(diffStore[1], areaRect[2], Scalar(255), 8);
	rectangle(diffStore[1], areaRect[3], Scalar(255), 8);
	rectangle(diffStore[2], areaRect[4], Scalar(255), 8);
	rectangle(diffStore[2], areaRect[5], Scalar(255), 8);
	namedWindow("diffPQ", WINDOW_NORMAL);
	namedWindow("diffQR", WINDOW_NORMAL);
	namedWindow("diffPR", WINDOW_NORMAL);
	namedWindow("final", WINDOW_NORMAL);
	imshow("diffPQ", diffStore[0]);
	imshow("diffQR", diffStore[1]);
	imshow("diffPR", diffStore[2]);
	imshow("final", finalpic);
	*/
	string filename="./result/recoveredPicture0.jpg";
	filename[25]=path[16];
	
	saveResult(filename);
	namedWindow("final", WINDOW_NORMAL);
	imshow("final", finalpic);
	waitKey(0);
	return;
}
bool Recovery::rectOverclapOrVoid() {
	if (areaRect[0].empty() || areaRect[1].empty() ||
		areaRect[2].empty() || areaRect[3].empty() ||
		areaRect[4].empty() || areaRect[5].empty()) return 1;
	if ((areaRect[0] & areaRect[1]).empty() &&
		(areaRect[2] & areaRect[3]).empty() &&
		(areaRect[4] & areaRect[5]).empty()) return 0;
	return 1;
}
void Recovery::diff(int a, int b, int cntIndex) {
	Mat ABdiff, image;
	image = diffStore[cntIndex];
	absdiff(store[a], store[b], image);
	cvtColor(image, image, COLOR_BGR2GRAY);
	threshold(image, image, 10, 255, THRESH_BINARY);
	medianBlur(image, image, 9);

	Mat elementA = getStructuringElement(MORPH_RECT, Size(11, 11));
	Mat elementB = getStructuringElement(MORPH_RECT, Size(15, 15));
	morphologyEx(image, image, MORPH_OPEN, elementA);
	morphologyEx(image, image, MORPH_CLOSE, elementB);
	diffStore[cntIndex] = image;

	cont[cntIndex].clear();
	vector<Vec4i> hierarchy;
	findContours(image, cont[cntIndex], hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());

	return;
}
void Recovery::chooseRect(int cntIndex) {
	areaRect[2 * cntIndex] = Rect(0, 0, 0, 0);
	areaRect[2 * cntIndex + 1] = Rect(0, 0, 0, 0);

	Rect first(0, 0, 0, 0), second(0, 0, 0, 0), third(0, 0, 0, 0), temp;
	for (int i = 0; i < cont[cntIndex].size(); i++) {
		temp = boundingRect(cont[cntIndex][i]);
		if (temp.area() > first.area()) {
			third = second;
			second = first;
			first = temp;
		}
		else if (temp.area() > second.area()) {
			third = second;
			second = temp;
		}
		else if (temp.area() > third.area()) {
			third = temp;
		}
	}
	if (third.area() == 0 || 5 * third.area() < second.area()) {
		areaRect[2 * cntIndex] = first;
		areaRect[2 * cntIndex + 1] = second;
	}
	else {
		areaRect[2 * cntIndex] = Rect(0, 0, 0, 0);
		areaRect[2 * cntIndex + 1] = Rect(0, 0, 0, 0);
	}
	return;
}
Rect Recovery::findSimilar(int t) {
	int error = 10;
	Rect a, b, c, d;
	if (t == Q_IDX) {
		a = areaRect[0];
		b = areaRect[1];
		c = areaRect[2];
		d = areaRect[3];
	}
	else if (t == R_IDX) {
		a = areaRect[2];
		b = areaRect[3];
		c = areaRect[4];
		d = areaRect[5];
	}
	else if (t == P_IDX) {
		a = areaRect[4];
		b = areaRect[5];
		c = areaRect[0];
		d = areaRect[1];
	}
	if (abs(a.tl().x - c.tl().x) <= error && abs(a.tl().y - c.tl().y) <= error) return a;
	if (abs(a.tl().x - d.tl().x) <= error && abs(a.tl().y - d.tl().y) <= error) return a;
	if (abs(b.tl().x - c.tl().x) <= error && abs(b.tl().y - c.tl().y) <= error) return b;
	if (abs(b.tl().x - d.tl().x) <= error && abs(b.tl().y - d.tl().y) <= error) return b;
	return Rect(0, 0, 0, 0);
}
void Recovery::patcha(Rect ret, int from, int to) {
	cap.set(CAP_PROP_POS_FRAMES, to);
	cap >> finalpic;
	int lefti	= ret.tl().x*ratio;
	int righti	= ret.br().x*ratio;
	int upi		= ret.tl().y*ratio;
	int downi	= ret.br().y*ratio;
	for (int i = lefti; i < righti; i++)
		for (int j = upi; j < downi; j++)
			finalpic.at<Vec3b>(j, i) = base.at<Vec3b>(j, i);
	return;
}
