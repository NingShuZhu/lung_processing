#include <iostream>    
#include <opencv2/opencv.hpp>
#include <cmath>
//#include "functions.h"

using namespace cv;
using namespace std;
//��ͼƬ��������׼״��������30 -> 0��30~70 ->70������170 -> 180
Mat normalization2(const Mat& image) {
	Mat normalizedImg = image.clone();

	for (int i = 0; i < image.rows; i++)//��ͼƬ��������׼״�����ֶα�׼ֵ��30��70 ��110��170
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
Mat tree_seed1_make(Mat lung_and_media)//�˴��������ݸ���������ͨ����һ����ֵΪ180
{
	lung_and_media = normalization2(lung_and_media);//1.ͼ���׼��

	Mat root1;
	lung_and_media.copyTo(root1);  //2.���м�ͼ��ͷ���ͼ���м������ֵ��ԭͼ����
	//root1�ǵ�һ�����
	Point center;                  //3.����һ��180�ĵ㣬�Ա�floodfill��
	int j = lung_and_media.cols * 0.5;
	for (int i = 0.3 * lung_and_media.rows; i < 0.6 * lung_and_media.rows; i++)
	{
		if (i == 0.6 * lung_and_media.rows - 1) { center.x = 3, center.y = 3; break; }
		if (lung_and_media.at<uchar>(i, j) == 180) {
			center.x = j, center.y = i;
			floodFill(root1, center, Scalar(180), 0, Scalar(50), Scalar(5), 4);//�ؼ���
			break;
		}
	}


	Mat tree_seed1 = root1;
	for (int i = 0; i < lung_and_media.rows; i++)//��ͼƬ������ԭ��׼״�����ݸ��ָ�Ϊ0
	{
		for (int j = 0; j < lung_and_media.cols; j++)
		{
			if (lung_and_media.at<uchar>(i, j) == 180)tree_seed1.at<uchar>(i, j) = 0;
		}
	}
	return tree_seed1;
}