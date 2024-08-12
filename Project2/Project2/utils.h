#pragma once
#include <iostream>  
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<Mat> readAndProcess(string path);
Mat lung_and_media_make(Mat image4);
bool areAllPixelsBelowThreshold(const cv::Mat& grayImage, int threshold);
Mat normalization(const Mat& image);
Mat add_root2(Mat tree_seed1, Mat tree_seed1_down);
Mat pair_extend(Mat& tree_seed1, Mat& tree_seed1_near);
vector<Mat> images_extend(vector<Mat> images);
Mat normalization2(const Mat& image);
Mat red_show(Mat image);
Mat tree_seed1_make(Mat lung_and_media);
vector<Mat> right_lung_tree(vector<Mat> tree2s);
Mat processStartImg(Mat startImg);
vector<Mat> floodFill3d(vector<Mat> images);