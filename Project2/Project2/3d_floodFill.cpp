#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

vector<Mat> floodFill3d(vector<Mat> images) {
	vector<Mat> result;

	// 将图片复制到新的vector中用于后续操作
	for (int i = 0; i < images.size(); i++) {
		Mat img;
		images[i].copyTo(img);
		result.push_back(img);
	}

	// 先以正中间的图为floodFill起点
	int idx = images.size() / 2;
	Mat root = result[idx];

	// 处理起点图（给纵隔上色->floodFill找连通的树）
	result[idx] = processStartImg(root);

	//// 开始立体floodFill
	//Mat imgToFill;

	//// 先从起点往上遍历图片
	//for (int i = idx - 1; i >= 0; i--) {
	//	root = result[i + 1];
	//	imgToFill = result[i];

	//	// 遍历图片中的像素，找到在新图中>=130, <=160且在root中为180的点，改到175
	//	for (int m = 0; m < root.rows; m++) {
	//		for (int n = 0; n < root.cols; n++) {
	//			if (root.at<uchar>(m, n) == 180 && imgToFill.at<uchar>(m, n) >= 130 && imgToFill.at<uchar>(m, n) <= 160)
	//				imgToFill.at<uchar>(m, n) = 175;
	//		}
	//	}

	//	// 将新图中175的点都floodFill到180
	//	Point seed(2, 2);

	//	for (int i = 0; i < imgToFill.rows; i++) {
	//		for (int j = 0; j < imgToFill.cols; j++) {
	//			if (imgToFill.at < uchar >(i, j) == 175) {
	//				seed.y = i;
	//				seed.x = j;
	//				floodFill(imgToFill, seed, Scalar(180), 0, Scalar(50), Scalar(1), 4);//关键句
	//			}

	//		}

	//	}
	//}

	return result;
}