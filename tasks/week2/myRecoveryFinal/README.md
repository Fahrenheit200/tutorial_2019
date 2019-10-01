# 第二周背景还原任务

- **作者**：李金东
- **修订**：李金东
- **日期**：2019-09-29
- **版本**：1.1.0
- **摘要**：这是第二周背景还原任务的ReadMe。介绍了整个项目的思路，所定义的类成员，具体实现的过程，解释了每一个私有函数的作用，分析算法的运行时间

## 基本思路
一开始我想尝试遍历视频钟的每一帧的每一个像素点，对于每一个像素点坐标，寻找出出现次数最多的像素作为这个像素点的最终值，将所有像素点组合起来就构成了一张没有瑕疵的图像。但是由于视频帧数和像素过多，选众数的算法较为低效，实现之后要跑很久才能得出结果，所以最终放弃了这个思路。  
接下来我使用拼接的思路。就是若两张图像的障碍物如果不重叠，P图的障碍物所在的区域为A，Q图的障碍物所在的区域为B，则可以用Q图的区域A取覆盖P图的区域A或者用P图的区域B来覆盖Q图的区域B，以此来得到没有障碍物的图。
## 具体实现方法
我的目的就是找到两张图P Q，用区域覆盖的方式实现图像还原。  
但事实上仅用两张图并不够，若我们有两张障碍物的图P和Q，用absdiff(P,Q,PQdiff)函数进行做差，P和Q相同的部分就会被减去留下黑色，不是黑色的区域就是P Q之间的差异，理想的话PQdiff会有两大块，一块是P的障碍物所在的区域，另一个是Q的障碍物所在的区域。但是仅仅通过PQdiff我们不知道这两块区域的障碍物分别属于谁的，就无从知道是要选P的哪一个区域取覆盖Q。所以后来我是选用三张图P Q R通过两两做差来定位出每一张图的障碍物所在的区域。  
区域为了简便地表示我用一个最小外接矩形Rect变量来存储，而不是用vector<Point>

## 所定义的类
```cpp
class Recovery {
public:
	void readVideo(string filePath);
	void process();
	void showResult();
	void saveResult(string filePath);
private:
	void subprocess();
	void diff(int, int, int);
	void chooseRect(int);
	void expandRect(Rect&);
	void patcha(Rect, int, int);
	bool indexTheSame(int, int, int);
	bool rectOverclapOrVoid();
	bool tooSmalltooClose();
	bool expandNotOverClap(int);
	bool qualityIsGood();
	int chooseTheBestOne();
	Rect findSimilar(int);
	Point getCenterPoint(Rect rect);
	VideoCapture cap;
	vector<Mat> store;
	vector<vector<Point>> cont[3];
	Rect whole;
	Rect areaRect[6];
	Rect singleRect[3];
	Mat finalpic;
	Mat prefinal;
	Mat finaldiff;
	Mat base;
	Mat diffStore[3];
	map<pairIdx, int> findIdx;
	double ratio;
	int scale;
};
```
## 整个过程
首先读取视频，将所有帧压入一个vector里面
```cpp
void Recovery::readVideo(string filePath)
```
由于视频帧数过多，我实现将每一帧的图片进行resize再push进去  
但是在这里resize并不会使我最终复原出来的图像的清晰度，我整个程序的目的是为了找到一个没有障碍物的Rect矩形区域取覆盖一个有障碍物的Rect区域，我只要记录我的Rect的信息和patchingFrom的图的index和patchTo的图的index就行，我最终找到的Rect是经过resize的，但最终进行patching的时候我resize回原来的大小即可。
```cpp
resize(temp, temp, Size(500, src.rows * 500 / src.cols));
store.push_back(temp);
```
这么多帧，我不可能一一的遍历完，我选择的是随机选帧。我固定P图为视频的第一张图，Q图和R图随机选帧
```cpp
p = 0;
q = (rand() % (store.size() - 0)) + 0;
r = (rand() % (store.size() - 0)) + 0;
```
用两个函数来过滤掉Q R重复的帧和已经选过但不符合要求的帧
```cpp
if (indexTheSame(p, q, r)) continue;
if (findIdx.count(qrdx) || findIdx.count(rqdx)) continue;
```
两两图像做差 并且在diff函数调用findContour找到做差后图像的轮廓  
如果做差后图像的轮廓只有一个，说明两张图片的障碍物连在了一起，说明障碍物重叠，不符合要求，重新选帧
```cpp
diff(p, q, PQ_CNT);
if (cont[PQ_CNT].size() <= 1) continue;
diff(q, r, QR_CNT);
if (cont[QR_CNT].size() <= 1) continue;
diff(p, r, PR_CNT);
if (cont[PR_CNT].size() <= 1) continue;
```
在diff函数中 findContour之前我事先进行二值化等预处理  
开操作是为了消除白色的小区域 闭操作是为了消除黑色的小区域
```cpp
cvtColor(image, image, COLOR_BGR2GRAY);
threshold(image, image, 10, 255, THRESH_BINARY);
medianBlur(image, image, 9);

Mat elementA = getStructuringElement(MORPH_RECT, Size(11, 11));
Mat elementB = getStructuringElement(MORPH_RECT, Size(15, 15));
morphologyEx(image, image, MORPH_OPEN, elementA);
morphologyEx(image, image, MORPH_CLOSE, elementB);
diffStore[cntIndex] = image;
```
进行做差查找出轮廓之后我要根据我的轮廓信息找到相应的矩形区域
```cpp
chooseRect(PQ_CNT);
chooseRect(QR_CNT);
chooseRect(PR_CNT);
```
至此，我已经得到了P Q R图的障碍物区域 而且理论上这三个区域两两不重合  
但是我要选哪张图去覆盖哪张图呢 我用chooseTheBestOne()去寻找最佳的组合
```cpp
int to = chooseTheBestOne();
```
选出最好的组合之后调用pathca函数
```cpp
patcha(ret, p, q);
```
整个过程已经完成 但是我用的是随机选帧的办法 难免会遇到不太好的帧 难免得出来的图会有误差，如下图

我的代码运行的不算太慢，所以我想能不能多重复几次这整个过程，得出多张finalPic，然后从中找到相对好的
```cpp
prefinal = finalpic.clone();
while (1) {
	subprocess();
	absdiff(prefinal, finalpic, finaldiff);
	if (qualityIsGood()) break;
	prefinal = finalpic.clone();
}
```
至此我的整个思路就完成了

## 每一个私有成员的简要解释
下面我来一一解释这些private函数是怎么用的
```cpp
//用process()重复调用subprocess()来得到多张finalpic来选出最好地图 以免得到一张图效果不好
	void subprocess();
//两张图片进行二值化滤波等处理并进行做差找到障碍物轮廓
	void diff(int, int, int);
//通过障碍物轮廓来划定障碍物所在地矩形区域
	void chooseRect(int);
//通过开操作闭操作的处理得到的障碍物矩形框可能会变小 在这里进行适当放大
	void expandRect(Rect&);
//得到最后的矩形区域进行覆盖patching
	void patcha(Rect, int, int);
//检查随机函数得出来的三张picture的图会不会是一样的
	bool indexTheSame(int, int, int);
//检查由障碍物轮廓得到的矩形区域会不会重合
	bool rectOverclapOrVoid();
//检查障碍物的矩形区域会不会相互隔地太近而影响patchin
	bool tooSmalltooClose();
//在进行矩形区域适当扩大时，检查这样地扩大会不会导致重叠
	bool expandNotOverClap(int);
//鉴定subprocess得到的图片是否质量良好可以作为输出图像
	bool qualityIsGood();
//在已选出的P Q R三张图里面，选择最好的<from,to>组合
	int chooseTheBestOne();
//一个辅助函数，用来找到P Q R障碍物的矩形区域
	Rect findSimilar(int);
//一个辅助函数 用于找到一个Rect 的中心点 方便最后对Rect进行resize
	Point getCenterPoint(Rect rect);
//读取视频
	VideoCapture cap;
//存储每一帧图像
	vector<Mat> store;
//用来存储三张diff得到的图的路径
	vector<vector<Point>> cont[3];
//存储基图p
	Mat base;
//存储两两图做差得到的结果
	Mat diffStore[3];
//用map来记录已经遍历过的Q R图的index组合 防止重复选一样的帧
	map<pairIdx, int> findIdx;
//记录我的图像的resize处理信息，方便后面复原
	double ratio;
	int scale;
  ```
## 程序运行时间
在windows里面和在ubuntu里面运行时间相差较大  
我自己写了一个测试函数让程序分别对这三个video进行生成100张还原图并输出它们的用时  
这些运行记录保存在./result文件夹下

## 依赖库
opencv 3.4.2

## 编译提示
进入myRecovery后运行
参考命令行效果如下：
```shell
$ ./bin/demo ./resource/video0.mp4
Process time: 1.423s
^C
$
```
即可
  
  
  
  