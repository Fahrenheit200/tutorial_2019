#include "../include/Recovery.h"


int main(int argc, char** argv){
    Recovery rcvy;
    rcvy.readVideo(string(argv[1]));
    rcvy.process();
    rcvy.showResult();
    return 0;
}


/* 遍历所有像素点取平均值 */
void bitwise_or2(cv::InputArray _src1, cv::InputArray _src2, cv::OutputArray _dst, cv::InputArray _mask = noArray()){
    Mat src1 = _src1.getMat(), src2 = _src2.getMat(), mask = _mask.getMat();
    _dst.create(src1.size(), src1.type()); 
    Mat dst = _dst.getMat();

    for(int j=0; j<src1.rows; j++)
        for(int k=0; k<src1.cols; k++){
            if(mask.at<unsigned char>(j,k) > 0){
                dst.at<Vec3b>(j,k)[0] = (src1.at<Vec3b>(j,k)[0] + src2.at<Vec3b>(j,k)[0])/2;
                dst.at<Vec3b>(j,k)[1] = (src1.at<Vec3b>(j,k)[1] + src2.at<Vec3b>(j,k)[1])/2;
                dst.at<Vec3b>(j,k)[2] = (src1.at<Vec3b>(j,k)[2] + src2.at<Vec3b>(j,k)[2])/2;
            }
        }
}


void Recovery::readVideo(String filePath){
    file_path = filePath;
    capture.open(filePath);
    if(!capture.isOpened())
        cout << "Error in opening video." << endl;
}


void Recovery::process(){
    /* 开始计时 */
    auto start_time = system_clock::now();
    
    Mat mask, mask_tmp, diff_color, diff_gray;
    int i = 0, index1, index2;

    /* 保存视频到Mat数组 */
    int cap_size = capture.get(CAP_PROP_FRAME_COUNT) * 4 / 5;
    Mat cap[cap_size];
    for(int i=0; i<cap_size; i++)
        capture >> cap[i];
    capture.release();

    int ele_size = cap[i].cols / 30;
    Mat element = getStructuringElement(MORPH_RECT, Size(ele_size, ele_size));  //腐蚀卷积核
    
    result = Mat::zeros(cap[0].rows, cap[0].cols, CV_8UC3);
    Mat result_tmp = Mat::zeros(cap[0].rows, cap[0].cols, CV_8UC3);
    
    srand(int(time(NULL)));
    while (i < cap_size / 21 + 10){
        /* 随机选取两帧图片，找出图片中不同的像素点，滤波腐蚀后做成掩膜 */
        do{
            index1 = rand() % cap_size;
            index2 = rand() % cap_size;
        }while(abs(index1 - index2) <= cap_size/30+1);

        absdiff(cap[index2], cap[index1], diff_color);
        cvtColor(diff_color, diff_gray, COLOR_BGR2GRAY);
        threshold(diff_gray, mask, 10, 255, THRESH_BINARY);
        bitwise_not(mask, mask);
        medianBlur(mask, mask, 11);
        erode(mask, mask, element);
        medianBlur(mask, mask, 11);

        if(i == 0)
            /* result为空时，随机两帧图片用掩膜取或，生成result */
            bitwise_or2(cap[index2], cap[index1], result, mask);
        else{
            /* result不为空时，随机两帧图片用掩膜取或，生成result_tmp */
            bitwise_or2(cap[index2], cap[index1], result_tmp, mask);

            /* result和result_tmp取或 */
            for(int j=0; j<mask.rows; j++)
                for(int k=0; k<mask.cols; k++){
                    if(result.at<Vec3b>(j,k) == Vec3b(0,0,0))
                        result.at<Vec3b>(j,k) = result_tmp.at<Vec3b>(j,k);
                    else if(result_tmp.at<Vec3b>(j,k) == Vec3b(0,0,0))
                        ;
                    else{
                        result.at<Vec3b>(j,k)[0] = (result_tmp.at<Vec3b>(j,k)[0] + result.at<Vec3b>(j,k)[0])/2;
                        result.at<Vec3b>(j,k)[1] = (result_tmp.at<Vec3b>(j,k)[1] + result.at<Vec3b>(j,k)[1])/2;
                        result.at<Vec3b>(j,k)[2] = (result_tmp.at<Vec3b>(j,k)[2] + result.at<Vec3b>(j,k)[2])/2;
                    }
                    
                }
        }              
        i++;
    }

    /* 结束计时并显示消耗时间 */
    auto end_time = system_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "Process time:" << double(duration.count())/1000000 << "s" << endl;
}


void Recovery::showResult(){
    /* 显示最后结果 */
    if(!result.empty()){
        namedWindow("result", WINDOW_NORMAL);
        imshow("result", result);
        waitKey(0);
        destroyWindow("result");
    }else
        cout << "No result" << endl;
    
    /* 保存为图片 */
    imwrite("./result/res" + file_path.substr(16, 1) +  ".jpg", result);
}
