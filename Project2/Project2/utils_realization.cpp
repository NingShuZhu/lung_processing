#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

// ����ͼ���ÿһ�����أ�����Ƿ���������ֵ��������ֵ
bool areAllPixelsBelowThreshold(const cv::Mat& grayImage, int threshold) {

    for (int row = 0; row < grayImage.rows; ++row) {
        for (int col = 0; col < grayImage.cols; ++col) {
            // ��ȡ��ǰ���صĻҶ�ֵ
            uchar pixelValue = grayImage.at<uchar>(row, col);
            // ����Ƿ񳬹���ֵ
            if (pixelValue >= threshold) {
                return false;
            }
        }
    }
    return true;
}

//��ͼƬ��������׼״��������30 -> 0��30~70 ->70������160 -> 160
Mat normalization(const Mat& image) {
    Mat normalizedImg = image.clone();

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)//��ѭ��--��ͼ�����յ���ɨһ��
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

// ����3d floodFill�����ͼ�����ݸ���ɫ->floodFill����ͨ����->�ָ��ݸ���
Mat processStartImg(Mat startImg) {
    // ���ݸ���ɫ
    Mat middleColored = lung_and_media_make(startImg);

    // ����һ��middleColored���ں����ָ��ݸ�
    Mat copiedMiddle;
    middleColored.copyTo(copiedMiddle);

    // �ҵ�һ��180�ĵ㣬�Ա�floodfill��
    Point center;                  
    //int j = middleColored.cols * 0.5;
    //for (int i = 0.3 * middleColored.rows; i < 0.6 * middleColored.rows; i++)
    //{
    //    if (i == 0.6 * middleColored.rows - 1) { center.x = 3, center.y = 3; break; }
    //    if (middleColored.at<uchar>(i, j) == 180) {
    //        center.x = j, center.y = i;

    //        // floodFill�����ݸ���ͨ��Ѫ��
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

            // floodFill�����ݸ���ͨ��Ѫ��
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
    

    // ��ͼƬ������ԭ��׼״�����ݸ��ָ�Ϊ0
    for (int i = 0; i < middleColored.rows; i++)
    {
        for (int j = 0; j < middleColored.cols; j++)
        {
            if (copiedMiddle.at<uchar>(i, j) == 180) middleColored.at<uchar>(i, j) = 0;
        }
    }

    return middleColored;
}