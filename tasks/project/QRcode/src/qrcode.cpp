#include "qrcode.hpp"

int threshold_value = 200;
int threshold_type = 0;
int const max_binary_value = 255;
void QRcode_section_detect(Mat &src, Mat output[])
{
    int id;
    Mat src_gray, dst, res, tmp, stats, centroids;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    int nccomps = connectedComponentsWithStats(dst, tmp, stats, centroids, 4);
    imwrite("test.png", dst);
    vector<vector<int>> qr_info;
    for (int i = 0; i < nccomps; ++i)
    {
        int w = stats.at<int>(i, cv::CC_STAT_WIDTH),
            h = stats.at<int>(i, cv::CC_STAT_HEIGHT),
            area = stats.at<int>(i, cv::CC_STAT_AREA);
        int l = stats.at<int>(i, cv::CC_STAT_LEFT),
            t = stats.at<int>(i, cv::CC_STAT_TOP);
        double diff = abs(h - w), avg = (h + w) / 2.0;
        double ratio = diff / avg;
        if (ratio < 0.1 && area > 1000)
        {
            qr_info.push_back(vector<int>{h, w, l, t});
        }
    }
    if (qr_info.size() == 2)
    {
        int outer_c_w, outer_c_h, inner_c_w, inner_c_h;
        if (qr_info[0][0] > qr_info[1][0] && qr_info[0][1] > qr_info[1][1])

        {
            Rect qr_size_pos(qr_info[0][2], qr_info[0][3], qr_info[0][0],
                             qr_info[0][1]);

            outer_c_h = qr_info[0][2] + qr_info[0][0] / 2;
            outer_c_w = qr_info[0][3] + qr_info[0][1] / 2;
            inner_c_h = qr_info[1][2] + qr_info[1][0] / 2;
            inner_c_w = qr_info[1][3] + qr_info[1][1] / 2;
            id = (inner_c_h > outer_c_h) + (inner_c_w > outer_c_w) * 2;
            res = dst(qr_size_pos);
            res.copyTo(output[id]);
        }
        else
        {
            Rect qr_size_pos(qr_info[1][2], qr_info[1][3], qr_info[1][0],
                             qr_info[1][1]);
            res = dst(qr_size_pos);
            outer_c_h = qr_info[1][2] + qr_info[1][0] / 2;
            outer_c_w = qr_info[1][3] + qr_info[1][1] / 2;
            inner_c_h = qr_info[0][2] + qr_info[0][0] / 2;
            inner_c_w = qr_info[0][3] + qr_info[0][1] / 2;
            id = (inner_c_h > outer_c_h) + (inner_c_w > outer_c_w) * 2;
            res = dst(qr_size_pos);
            res.copyTo(output[id]);
        }
    }
    else
    {
        Rect qr_size_pos(qr_info[0][2], qr_info[0][3], qr_info[0][0],
                         qr_info[0][1]);
        id = 3;
        res = dst(qr_size_pos);
        res.copyTo(output[id]);
    }
}
Mat QRcode_section_splice(Mat input[])
{
    int max_row = -1, max_col = -1;
    for (int i = 0; i <= 3; ++i)
    {
        if (input[i].cols > max_col)
            max_col = input[i].cols;
        if (input[i].rows > max_row)
            max_row = input[i].rows;
    }
    Mat qrcode(max_row * 2, max_col * 2, CV_8U);
    input[0].copyTo(
        qrcode(Rect(max_col - input[0].cols, max_row - input[0].rows,
                    input[0].cols, input[0].rows)));
    input[1].copyTo(qrcode(
        Rect(max_col, max_row - input[2].rows, input[1].cols, input[1].rows)));
    input[2].copyTo(qrcode(
        Rect(max_col - input[2].cols, max_row, input[2].cols, input[2].rows)));
    input[3].copyTo(
        qrcode(Rect(max_col, max_row, input[3].cols, input[3].rows)));
    return qrcode;
}