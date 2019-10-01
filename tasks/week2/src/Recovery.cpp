#include "Recovery.h"

/*
    readVideo
    @param filePath 文件绝对路径
    根据绝对路径读取需要还原背景的文件
*/
void Recovery::readVideo(string filePath)
{
    this->video_capture.open(filePath);
    if (!video_capture.isOpened())
    {
        // error in opening the video input
        cerr << "Unable to open: " << filePath << endl;
        return;
    }
    this->frame_count = video_capture.get(CAP_PROP_FRAME_COUNT);
}

/*
    process
    进行还原过程
    使用平均背景法
*/
void Recovery::process()
{
    // scale为标准差上下限的倍率
    Mat current_frame, current_frame_f, current_channel[3];
    Mat sum_frame, sum_square_frame, mean_frame, sd_frame;
    Mat high_f, low_f, high_u, low_u, high[3], low[3];
    Mat current_result, current_result_temp[3], result, mask[3];
    double scale = 1.5;

    // 读取视频，计算累加和与平方和
    this->video_capture.read(current_frame);
    current_frame.convertTo(current_frame_f, CV_32F);
    sum_frame = Mat::zeros(current_frame_f.size(), CV_32FC3);
    sum_square_frame = Mat::zeros(current_frame_f.size(), CV_32FC3);
    mean_frame = Mat::zeros(current_frame_f.size(), CV_32FC3);
    sd_frame = Mat::zeros(current_frame_f.size(), CV_32FC3);
    result = Mat::zeros(current_frame.size(), CV_32FC3);
    current_result = Mat::zeros(current_frame.size(), CV_32FC3);
    accumulate(current_frame_f, sum_frame);
    accumulateSquare(current_frame_f, sum_square_frame);

    while (true)
    {
        this->video_capture.read(current_frame);
        if (current_frame.empty()) break;
        current_frame.convertTo(current_frame_f, CV_32F);
        accumulate(current_frame_f, sum_frame);
        accumulateSquare(current_frame_f, sum_square_frame);
    }

    //计算均值与标准差
    mean_frame = sum_frame * (1.0 / this->frame_count);
    sd_frame = sum_square_frame * (1.0 / this->frame_count) -
               mean_frame.mul(mean_frame);
    sqrt(sd_frame, sd_frame);

    //计算背景帧的上下界，并转换为三通道整数，再对通道进行分割
    high_f = mean_frame + sd_frame * scale;
    low_f = mean_frame - sd_frame * scale;
    high_f.convertTo(high_u, CV_8UC3);
    low_f.convertTo(low_u, CV_8UC3);
    split(high_u, high);
    split(low_u, low);

    // 重新读取视频，提取每一帧的背景部分
    this->video_capture.set(CV_CAP_PROP_POS_FRAMES, 0);
    Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
    while (true)
    {
        this->video_capture.read(current_frame);
        if (current_frame.empty()) break;

        // 分通道计算
        split(current_frame, current_channel);
        inRange(current_channel[0], low[0], high[0], mask[0]);
        inRange(current_channel[1], low[1], high[1], mask[1]);
        inRange(current_channel[2], low[2], high[2], mask[2]);

        //对得到的掩码矩阵进行形态学操作，突出前景减少噪声
        morphologyEx(mask[0], mask[0], MORPH_OPEN, element);
        morphologyEx(mask[0], mask[0], MORPH_CLOSE, element);
        morphologyEx(mask[1], mask[1], MORPH_OPEN, element);
        morphologyEx(mask[1], mask[1], MORPH_CLOSE, element);
        morphologyEx(mask[2], mask[2], MORPH_OPEN, element);
        morphologyEx(mask[2], mask[2], MORPH_CLOSE, element);

        // 提取每个通道的背景部分
        current_result_temp[0] = min(current_channel[0], mask[0]);
        current_result_temp[1] = min(current_channel[1], mask[1]);
        current_result_temp[2] = min(current_channel[2], mask[2]);

        // 合并通道，并累计以求平均
        merge(current_result_temp, 3, current_result);
        accumulate(current_result, result);
    }
    // 计算平均背景
    result *= (1.2 / this->frame_count);
    result.convertTo(this->background, CV_8UC3);
}

/*
    showResult
    窗口展示背景还原后的结果
*/
void Recovery::showResult()
{
    this->video_capture.release();
    // 输出背景文件
    imwrite("./result/result.png", this->background);
    namedWindow("Recovery Result", CV_WINDOW_AUTOSIZE);
    imshow("Recovery Result", this->background);
    waitKey(0);
    destroyWindow("Recovery Result");
}