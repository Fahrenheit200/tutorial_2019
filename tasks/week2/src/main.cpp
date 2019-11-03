#include "Recovery.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Input argument is valid!" << endl;
        return -1;
    }
    // 初始化类
    Recovery video_to_recovery;
    string filename(argv[1]);
    video_to_recovery.readVideo(filename);

    // 开始计时并处理视频
    auto start = chrono::system_clock::now();
    video_to_recovery.process();
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Process time: " << elapsed_seconds.count() << "s\n";
    
    // 展示结果
    video_to_recovery.showResult();

}