#include <iostream>    
#include <opencv2/opencv.hpp>
#include <cmath>
//#include "functions.h"

using namespace cv;
using namespace std;
//将图片修正到标准状况：低于30 -> 0，30~70 ->70，高于170 -> 180
Mat normalization2(const Mat& image) {
	Mat normalizedImg = image.clone();

	for (int i = 0; i < image.rows; i++)//将图片修正到标准状况：分段标准值：30，70 ，110，170
	{
		for (int j = 0; j < image.cols; j++)
		{

			if (image.at<uchar>(i, j) < 30)normalizedImg.at<uchar>(i, j) = 0;
			else if (image.at<uchar>(i, j) <= 70 && image.at<uchar>(i, j) >= 30)
				normalizedImg.at<uchar>(i, j) = 70;
			else if (image.at<uchar>(i, j) > 70 && image.at<uchar>(i, j) < 110)
				normalizedImg.at<uchar>(i, j) = 90;
			else if (image.at<uchar>(i, j) >= 110 && image.at<uchar>(i, j) < 170)
				normalizedImg.at<uchar>(i, j) = 150;
			else if (image.at<uchar>(i, j) >= 170)
				normalizedImg.at<uchar>(i, j) = 180;
		}
	}
	return normalizedImg;
}
Mat red_show(Mat image) {
	Vec3b red(20, 20, 220);
	Vec3b yellow(20, 200, 200);
	Vec3b black(0, 0, 0);
	Mat red_show(image.rows, image.cols, CV_8UC3, black);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (image.at<uchar>(i, j) > 170)red_show.at<Vec3b>(i, j) = red;
			else if (image.at<uchar>(i, j) >= 110 && image.at<uchar>(i, j) <= 170)red_show.at<Vec3b>(i, j) = yellow;
		}
	}
	return red_show;
}
Mat tree_seed1_make(Mat lung_and_media)//此处仅作与纵隔相连的连通区，一并改值为180
{
	lung_and_media = normalization2(lung_and_media);//1.图像标准化

	Mat root1;
	lung_and_media.copyTo(root1);  //2.设中间图像和返回图像，中间操作改值与原图隔离
	//root1是第一步结果
	Point center;                  //3.先找一个180的点，以备floodfill用
	int j = lung_and_media.cols * 0.5;
	for (int i = 0.3 * lung_and_media.rows; i < 0.6 * lung_and_media.rows; i++)
	{
		if (i == 0.6 * lung_and_media.rows - 1) { center.x = 3, center.y = 3; break; }
		if (lung_and_media.at<uchar>(i, j) == 180) {
			center.x = j, center.y = i;
			floodFill(root1, center, Scalar(180), 0, Scalar(50), Scalar(5), 4);//关键句
			break;
		}
	}


	Mat tree_seed1 = root1;
	for (int i = 0; i < lung_and_media.rows; i++)//将图片修正到原标准状况：纵隔恢复为0
	{
		for (int j = 0; j < lung_and_media.cols; j++)
		{
			if (lung_and_media.at<uchar>(i, j) == 180)tree_seed1.at<uchar>(i, j) = 0;
		}
	}
	return tree_seed1;
}