#include <iostream>    
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

//const double PI = 3.141592653589793;

Mat lung_and_media_make(Mat image4)     //�˺������ݸ���Ϊ��ɫ180�������Ϊ0������70-160
{
    //Mat b(512,512,CV_8UC1,Scalar(0));
    //floodFill(image4, image4, Point(2, 2),  Scalar(0),0, Scalar(0), Scalar(2), 4);
    
    Mat lung_and_media;
    image4.copyTo(lung_and_media);
    //������image5������������ߣ������ݸ������
    int i_begin = 0.33 * image4.rows, i_end = 0.67 * image4.rows;
    int j_begin = 0.49 * image4.cols, j_end = 0.51 * image4.cols;
    for (int i = 0; i < image4.rows; i++)
    {
        for (int j = 0; j < j_end; j++)//�����ɨһ�飬��ֵΪ10��������
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }
    for (int i = 0; i < image4.rows; i++)
    {
        for (int j = image4.cols - 1; j > j_begin; j--)//�����ɨһ��
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }

    for (int j = 0; j < image4.cols; j++)
    {
        for (int i = 0; i < i_begin; i++)//������϶�ɨһ�飬��0.33��
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }
    for (int j = 0; j < image4.cols; j++)
    {
        for (int i = image4.rows - 1; i > i_end; i--)//����ӵ�����ɨһ�飬��0.67��
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }

    for (int i = 0; i < image4.rows; i++)//image5�ݸ���0��Ϊ180�����������0
    {
        for (int j = 0; j < image4.cols; j++)
        {
            if (lung_and_media.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 180;
        }
    }
    for (int i = 0; i < image4.rows; i++)//image5���������0
    {
        for (int j = 0; j < image4.cols; j++)
        {
            if (lung_and_media.at<uchar>(i, j) == 10)lung_and_media.at<uchar>(i, j) = 0;
        }
    }

    return lung_and_media;//�����ݸ�Ϊ180�����������Ϊ0�������ܶ�Ϊ70-160��ͼ
}           //2-1�������