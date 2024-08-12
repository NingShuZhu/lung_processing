#include <iostream>    
#include <opencv2/opencv.hpp>
#include <cmath>
//#include "functions.h"

using namespace cv;
using namespace std;

Mat add_root2(Mat tree_seed1, Mat tree_seed1_down)//返回一个仅有“树”的迭加图
{
	int row = tree_seed1.rows;
	int col = tree_seed1.cols;
	Mat add_root(row, col, CV_8UC1, Scalar(0));
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (tree_seed1.at<uchar>(i, j) > 170 || tree_seed1_down.at<uchar>(i, j) > 170)  //
			{
				add_root.at < uchar >(i, j) = 180;
			}
		}
	}
	//imshow("add_root：", add_root);
	//waitKey(3000);

	return add_root;//返回一个仅有180和0的图,只有“树”
}
Mat branch_extend(Mat image, Mat add_root) //上层或下层图像与共同根比对，同位点符合条件记为180
{
	int row = image.rows;
	int col = image.cols;
	Mat extend_image;
	image.copyTo(extend_image);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (image.at < uchar >(i, j) >= 110 && add_root.at < uchar >(i, j) > 170)
			{
				extend_image.at < uchar >(i, j) = 175;
			}
		}
	}
	//Point center(2,2);                  //先找一个180的点，以备floodfill用
	//int j = extend_image.cols * 0.5;
	//for (int i = 0.3 * image.rows; i < 0.65 * extend_image.rows; i++)
	//{
	//	if (extend_image.at<uchar>(i, j) == 175) { center.x = j, center.y = i; break; }
	//	if (i = 0.64 * extend_image.rows) {
	//		j = 1000; break;
	//	}

	//}
	//floodFill(extend_image, center, Scalar(175), 0, Scalar(50), Scalar(5), 4);//关键句
	Point seed(2, 2);
	int num = 0;

	for (int i = 0.25 * row; i < 0.75 * row; i++)
	{

		for (int j = 0.25 * col; j < 0.75 * col; j++) {
			if (extend_image.at < uchar >(i, j) == 175)
			{
				seed.y = i;
				seed.x = j;
				floodFill(extend_image, seed, Scalar(180), 0, Scalar(50), Scalar(1), 4);//关键句
				num = 1;
			}

		}

	}

	return extend_image;
}

Mat pair_extend(Mat& tree_seed1, Mat& tree_seed1_near)
{
	Mat add_root = add_root2(tree_seed1, tree_seed1_near);

	tree_seed1_near = branch_extend(tree_seed1_near, add_root);
	return tree_seed1_near;
}
vector<Mat> images_extend(vector<Mat> images)//不去改变images原图，输出全部树枝显示的图集
{
	vector<Mat> tree2s, result;
	Mat image1, image2;
	int size = images.size();
	for (int n = 0; n < size; n++)
	{
		Mat image_n;
		images[n].copyTo(image_n);
		tree2s.push_back(image_n);//将全部图片copy入tree2s图集
	}
	if (size < 20) {
		cout << "files error!" << endl;
	}
	for (int i = 0.3 * size; i < 0.8 * size; i++)//第一轮，从上往下
	{
		image1 = tree2s[i];
		image2 = tree2s[i + 1];
		image2 = pair_extend(image1, image2);
		tree2s[i + 1] = image2;
	}
	for (int i = 0.8 * size - 1; i > 0.21 * size; i--)//第2轮，反向来一遍
	{
		image1 = tree2s[i];
		image2 = tree2s[i - 1];
		image2 = pair_extend(image1, image2);
		tree2s[i - 1] = image2;
	}

	for (int i = 0.21 * size + 1; i < 0.86 * size + 1; i++)//第3轮，从上往下
	{
		image1 = tree2s[i];
		image2 = tree2s[i + 1];
		image2 = pair_extend(image1, image2);
		tree2s[i + 1] = image2;
	}
	for (int i = 0.86 * size - 1; i > 0.08 * size; i--)//第4轮，反向来一遍
	{
		image1 = tree2s[i];
		image2 = tree2s[i - 1];
		image2 = pair_extend(image1, image2);
		tree2s[i - 1] = image2;
	}
	for (int k = 0; k < 3; k++)
	{
		for (int n = 10; n < 0.8 * size; n++)
		{
			for (int i = 0.1 * image1.rows; i < 0.9 * image1.rows; i++)
			{
				for (int j = 0.1 * image1.cols; j < 0.9 * image1.cols; j++)
				{
					if (tree2s[n].at<uchar>(i, j) == 180 && (tree2s[n].at<uchar>(i - 1, j) == 0 || tree2s[n].at<uchar>(i + 1, j) == 0))
					{
						tree2s[n].at<uchar>(i, j) = 0;
						continue;
					}
					if (tree2s[n].at<uchar>(i, j) == 180 && (tree2s[n].at<uchar>(i, j - 1) == 0 || tree2s[n].at<uchar>(i, j + 1) == 0))
					{
						tree2s[n].at<uchar>(i, j) = 0;
						continue;
					}

				}
			}
		}
	}
	for (int n = 0.8 * size; n < 0.9 * size; n++)
	{
		for (int i = 0.1 * image1.rows; i < 0.9 * image1.rows; i++)
		{
			for (int j = 0.1 * image1.cols; j < 0.9 * image1.cols; j++)
			{
				if (tree2s[n].at<uchar>(i, j) == 180) {
					tree2s[n].at<uchar>(i, j) = 70;
					continue;
				}
			}
		}
	}
	return tree2s;
}

vector<Mat> right_lung_tree(vector<Mat> tree2s)
{
	int row = tree2s[0].rows;
	int half_col = tree2s[0].cols / 2;
	vector<Mat> right_lungs;
	Mat right_lung(row, half_col, CV_8UC1, Scalar(0));;
	int size = tree2s.size();
	for (int k = 0; k < size; k++)
	{
		Mat b(row, half_col, CV_8UC1, Scalar(0));

		for (int i = 0; i < row; i++)   //将半边树枝保留拷到右肺容器中
		{
			for (int j = 0; j < half_col; j++)
			{
				if (tree2s[k].at < uchar >(i, j) == 180) {
					b.at < uchar >(i, j) = 180;
				}
			}
		}
		right_lungs.push_back(b);
	}
	return right_lungs;

}