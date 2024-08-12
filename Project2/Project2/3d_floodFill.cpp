#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

vector<Mat> floodFill3d(vector<Mat> images) {
	vector<Mat> result;

	// ��ͼƬ���Ƶ��µ�vector�����ں�������
	for (int i = 0; i < images.size(); i++) {
		Mat img;
		images[i].copyTo(img);
		result.push_back(img);
	}

	// �������м��ͼΪfloodFill���
	int idx = images.size() / 2;
	Mat root = result[idx];

	// �������ͼ�����ݸ���ɫ->floodFill����ͨ������
	result[idx] = processStartImg(root);

	//// ��ʼ����floodFill
	//Mat imgToFill;

	//// �ȴ�������ϱ���ͼƬ
	//for (int i = idx - 1; i >= 0; i--) {
	//	root = result[i + 1];
	//	imgToFill = result[i];

	//	// ����ͼƬ�е����أ��ҵ�����ͼ��>=130, <=160����root��Ϊ180�ĵ㣬�ĵ�175
	//	for (int m = 0; m < root.rows; m++) {
	//		for (int n = 0; n < root.cols; n++) {
	//			if (root.at<uchar>(m, n) == 180 && imgToFill.at<uchar>(m, n) >= 130 && imgToFill.at<uchar>(m, n) <= 160)
	//				imgToFill.at<uchar>(m, n) = 175;
	//		}
	//	}

	//	// ����ͼ��175�ĵ㶼floodFill��180
	//	Point seed(2, 2);

	//	for (int i = 0; i < imgToFill.rows; i++) {
	//		for (int j = 0; j < imgToFill.cols; j++) {
	//			if (imgToFill.at < uchar >(i, j) == 175) {
	//				seed.y = i;
	//				seed.x = j;
	//				floodFill(imgToFill, seed, Scalar(180), 0, Scalar(50), Scalar(1), 4);//�ؼ���
	//			}

	//		}

	//	}
	//}

	return result;
}