#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

// 遍历图像的每一个像素，检查是否所有像素值都低于阈值
bool areAllPixelsBelowThreshold(const cv::Mat& grayImage, int threshold) {

    for (int row = 0; row < grayImage.rows; ++row) {
        for (int col = 0; col < grayImage.cols; ++col) {
            // 获取当前像素的灰度值
            uchar pixelValue = grayImage.at<uchar>(row, col);
            // 检查是否超过阈值
            if (pixelValue >= threshold) {
                return false;
            }
        }
    }
    return true;
}

//将图片修正到标准状况：低于30 -> 0，30~70 ->70，高于160 -> 160
Mat normalization(const Mat& image) {
    Mat normalizedImg = image.clone();

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)//此循环--从图左到右终点线扫一遍
        {
            if (image.at<uchar>(i, j) < 30)normalizedImg.at<uchar>(i, j) = 0;
            else if (image.at<uchar>(i, j) < 70 && image.at<uchar>(i, j) >= 30)
                normalizedImg.at<uchar>(i, j) = 70;
            else if (image.at<uchar>(i, j) > 160)
                normalizedImg.at<uchar>(i, j) = 160;
        }
    }
    return normalizedImg;
}

// 处理3d floodFill的起点图（给纵隔上色->floodFill找连通的树->恢复纵隔）
Mat processStartImg(Mat startImg) {
    // 给纵隔上色
    Mat middleColored = lung_and_media_make(startImg);

    // 复制一份middleColored用于后续恢复纵隔
    Mat copiedMiddle;
    middleColored.copyTo(copiedMiddle);

    // 找到一个180的点，以备floodfill用
    Point center;                  
    //int j = middleColored.cols * 0.5;
    //for (int i = 0.3 * middleColored.rows; i < 0.6 * middleColored.rows; i++)
    //{
    //    if (i == 0.6 * middleColored.rows - 1) { center.x = 3, center.y = 3; break; }
    //    if (middleColored.at<uchar>(i, j) == 180) {
    //        center.x = j, center.y = i;

    //        // floodFill找与纵隔连通的血管
    //        floodFill(middleColored, center, Scalar(180), 0, Scalar(50), Scalar(5), 4);
    //        break;
    //    }
    //}
    int i = middleColored.rows * 0.5;
    for (int j = 0.3 * middleColored.cols; j < 0.6 * middleColored.cols; j++)
    {
        if (j == 0.6 * middleColored.cols - 1) { center.x = 3, center.y = 3; break; }
        if (middleColored.at<uchar>(i, j) == 180) {
            center.x = j, center.y = i;

            // floodFill找与纵隔连通的血管
            floodFill(middleColored, center, Scalar(180), 0, Scalar(25), Scalar(5), 4);
            break;
        }
    }

    //cout << "x=" << center.x << "; y=" << center.y << endl;

    /*for (int i = 100; i < 400; i++) {
        for (int j = 0; j < middleColored.cols; j++) {
            cout << (int)middleColored.at<uchar>(i, j) << ',';
        }
        cout << endl;
    }*/
    

    // 将图片修正到原标准状况：纵隔恢复为0
    for (int i = 0; i < middleColored.rows; i++)
    {
        for (int j = 0; j < middleColored.cols; j++)
        {
            if (copiedMiddle.at<uchar>(i, j) == 180) middleColored.at<uchar>(i, j) = 0;
        }
    }

    return middleColored;
}