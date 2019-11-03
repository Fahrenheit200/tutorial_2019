#include "contours.hpp"
int lower, upper;
Mat std_contours(Mat src, int lower_threshold, int upper_threshold)
{
    Mat src_gray, canny_output;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    GaussianBlur(src_gray, src_gray, Size(5, 5), 3);
    Canny(src_gray, canny_output, lower_threshold, upper_threshold, 3);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE,
                 CHAIN_APPROX_SIMPLE);
    Mat drawing(canny_output.size(), CV_8UC3, Scalar(0,0,0));
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(255, 255, 255);
        drawContours(drawing, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
    }
    return move(drawing);
}

void threshold_callback(int, void* img)
{
    Mat src = *((Mat*)img);
    cout << "lower: " << lower << ", "
         << "upper: " << upper << endl;
    Mat contour = std_contours(src, lower, upper);
    imshow(result_window, contour);
    imwrite(result_filename, contour);
}

void contour_compare(string filename)
{
    Mat original = imread(filename);
    lower = 100;
    upper = 200;
    namedWindow(result_window, WINDOW_AUTOSIZE);
    Mat contour = std_contours(original, lower, upper);
    imshow(result_window, contour);
    createTrackbar("min:", result_window, &lower, max_threshold,
                   threshold_callback, &original);
    createTrackbar("max:", result_window, &upper, max_threshold,
                   threshold_callback, &original);
    waitKey(0);
    destroyWindow(result_window);
}