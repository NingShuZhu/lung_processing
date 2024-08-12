#include <iostream>    
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "utils.h"

using namespace cv;
using namespace std;
namespace fs = std::filesystem;
vector<Mat> readAndProcess(string path) {
    //�ȶ������зǿյ�ͼƬ -> images
    vector<Mat> images;

    // 1. ��ȡͼƬ
    // ����ͼ���ļ���·��
    string folderPath = path;
    // ���ô�����ͼ���ļ���·��
    string processedPath = "C://files6//tree";
    string processedPath2 = "C://files6//tree_c";
    string processedPath3 = "C://files6//tree_color";
    // ��ȡ�ļ����е�����ͼ���ļ�
    vector<string> imageFiles;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".jpg" || entry.path().extension() == ".png")) {
            imageFiles.push_back(entry.path().string());
        }
    }
    vector<Mat> processedImgs; //Ԥ������ͼ��
    // ����Ƿ���ͼ���ļ�
    if (imageFiles.empty()) {
        cerr << "No image files found in the specified directory!" << endl;
        return processedImgs;
    }

    // 2. ����ȫ��ͼ��Ӧ��func => �µ�ͼ��
    for (const auto& filePath : imageFiles) {
        // ��ȡͼ��
        cv::Mat image = cv::imread(filePath, 0);
        if (image.empty()) {
            cerr << "Could not open or find the image: " << filePath << endl;
            continue;
        }

        //���ͼ���Ƿ�Ϊȫ�ڣ����ǣ�����
        if (!areAllPixelsBelowThreshold(image, 30))
            images.push_back(image);
    }


    int idx = 0;
    for (const auto& img : images) {
        Mat normalizedImg;
        //��ÿ��ͼԤ����->�������Ϊ70���Ϊ160������Ϊ0
        normalizedImg = normalization(img);

        processedImgs.push_back(normalizedImg);

        //����
        string outputFilePath = processedPath + "//" + to_string(++idx) + ".jpg";
        cv::imwrite(outputFilePath, normalizedImg);
        cout << "Processed and saved image: " << outputFilePath << endl;

    }
    
    int idx1 = 0;
    vector<Mat> trees180 = floodFill3d(processedImgs);

    for (const auto& img : trees180) {
        string outputFilePath2 = processedPath2 + "//" + to_string(++idx) + ".jpg";
        cv::imwrite(outputFilePath2, img);
        cout << "Processed and saved image: " << outputFilePath2 << endl;

        Mat tree1_color = red_show(img);
        string outputFilePath3 = processedPath3 + "//" + to_string(++idx1) + ".jpg";
        cv::imwrite(outputFilePath3, tree1_color);
        cout << "Processed and saved image: " << outputFilePath3 << endl;
    }

    //��processedImgs����floodFill��Ѫ�����������˵�һ��

    return trees180;
}
