/*****************************************************************
 * @file        Recovery.hpp
 * @brief       This file void class Recvory.
 * Details.
 *
 * @version     1.0.1
 * @author      林嘉鸿
 * @email       1073097404@qq.com
 *
 * ----------------------------------------------------------------
 *  Change History:
 *  <Date>      |<Version>      |<Author>       |<Description>
 *  ---------------------------------------------------------------
 *  2019/09/29  |1.0.1          |林嘉鸿         |Create file
 *
 *  ***************************************************************/

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class Recovery{
        public:
                void readVideo(String);
                void process();
                void showResult();
	private:
		String filePath;
		VideoCapture cap;
		Mat result;
};

