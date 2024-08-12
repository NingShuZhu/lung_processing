#include <iostream>    
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

//const double PI = 3.141592653589793;

Mat lung_and_media_make(Mat image4)     //此函数将纵隔设为白色180，外界仍为0，两肺70-160
{
    //Mat b(512,512,CV_8UC1,Scalar(0));
    //floodFill(image4, image4, Point(2, 2),  Scalar(0),0, Scalar(0), Scalar(2), 4);
    
    Mat lung_and_media;
    image4.copyTo(lung_and_media);
    //以下在image5作两条横向粗线，隔开纵隔于外界
    int i_begin = 0.33 * image4.rows, i_end = 0.67 * image4.rows;
    int j_begin = 0.49 * image4.cols, j_end = 0.51 * image4.cols;
    for (int i = 0; i < image4.rows; i++)
    {
        for (int j = 0; j < j_end; j++)//正向横扫一遍，改值为10，至遇到
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }
    for (int i = 0; i < image4.rows; i++)
    {
        for (int j = image4.cols - 1; j > j_begin; j--)//反向横扫一遍
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }

    for (int j = 0; j < image4.cols; j++)
    {
        for (int i = 0; i < i_begin; i++)//纵向从上端扫一遍，至0.33线
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }
    for (int j = 0; j < image4.cols; j++)
    {
        for (int i = image4.rows - 1; i > i_end; i--)//纵向从底往上扫一遍，至0.67线
        {
            if (image4.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 10;
            else if (image4.at<uchar>(i, j) >= 30)break;
        }
    }

    for (int i = 0; i < image4.rows; i++)//image5纵隔区0改为180，外界修正回0
    {
        for (int j = 0; j < image4.cols; j++)
        {
            if (lung_and_media.at<uchar>(i, j) == 0)lung_and_media.at<uchar>(i, j) = 180;
        }
    }
    for (int i = 0; i < image4.rows; i++)//image5外界修正回0
    {
        for (int j = 0; j < image4.cols; j++)
        {
            if (lung_and_media.at<uchar>(i, j) == 10)lung_and_media.at<uchar>(i, j) = 0;
        }
    }

    return lung_and_media;//返回纵隔为180，外界与胸廓为0，两肺密度为70-160的图
}           //2-1函数完成