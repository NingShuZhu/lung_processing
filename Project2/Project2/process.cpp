//#include <iostream>    
//#include <opencv2/opencv.hpp>
//#include <filesystem>
//#include "utils.h"
//
//using namespace cv;
//using namespace std;
//namespace fs = std::filesystem;
//vector<Mat> readAndProcess(string path) {
//    //�ȶ������зǿյ�ͼƬ -> images
//    vector<Mat> images;
//
//    // 1. ��ȡͼƬ
//    // ����ͼ���ļ���·��
//    string folderPath = path;
//    // ���ô�����ͼ���ļ���·��
//    string processedPath = "C://files6//tree";
//    string processedPath2 = "C://files6//tree_c";
//    string processedPath3 = "C://files6//tree_color";
//    // ��ȡ�ļ����е�����ͼ���ļ�
//    vector<string> imageFiles;
//    for (const auto& entry : fs::directory_iterator(folderPath)) {
//        if (entry.is_regular_file() && (entry.path().extension() == ".jpg" || entry.path().extension() == ".png")) {
//            imageFiles.push_back(entry.path().string());
//        }
//    }
//    vector<Mat> processedImgs; //Ԥ������ͼ��
//    // ����Ƿ���ͼ���ļ�
//    if (imageFiles.empty()) {
//        cerr << "No image files found in the specified directory!" << endl;
//        return processedImgs;
//    }
//
//    // 2. ����ȫ��ͼ��Ӧ��func => �µ�ͼ��
//    for (const auto& filePath : imageFiles) {
//        // ��ȡͼ��
//        cv::Mat image = cv::imread(filePath, 0);
//        if (image.empty()) {
//            cerr << "Could not open or find the image: " << filePath << endl;
//            continue;
//        }
//
//        //���ͼ���Ƿ�Ϊȫ�ڣ����ǣ�����
//        if (!areAllPixelsBelowThreshold(image, 30))
//            images.push_back(image);
//    }
//
//    
//    int idx = 0;
//    //int idx1 = 0;
//    for (const auto& img : images) {
//        Mat processedImg, normalizedImg, processedImg_root1;
//        //��ÿ��ͼԤ����->�������Ϊ70���Ϊ160������Ϊ0
//        normalizedImg = normalization(img);
//
//        //���м�70%��ͼƬ���м��ݸ�����Ϊ180��Ȼ������ͨ������һ��
//        int size = images.size();
//        if (idx > (int)size / 16 && idx < (int)4 * size / 5) {
//            processedImg = lung_and_media_make(normalizedImg);
//            processedImg_root1 = tree_seed1_make(processedImg);//ͬһ����������������
//        }
//        else {
//            processedImg = normalizedImg;
//            processedImg_root1 = processedImg;
//        }
//        //
//        processedImgs.push_back(processedImg_root1);
//
//        //����
//        string outputFilePath = processedPath + "//" + to_string(++idx) + ".jpg";
//        cv::imwrite(outputFilePath, processedImg_root1);
//        cout << "Processed and saved image: " << outputFilePath << endl;
//
//
//        /*Mat tree1_color = red_show(processedImg_root1);
//        string outputFilePath3 = processedPath3 + "//" + to_string(++idx1) + ".jpg";
//        cv::imwrite(outputFilePath3, tree1_color);
//        cout << "Processed and saved image: " << outputFilePath3 << endl;*/
//    }
//    //idx = 0;
//    int idx1 = 0;
//    //vector<Mat> right_tree2s = right_lung_tree(images_extend(processedImgs));
//    vector<Mat> right_tree2s = images_extend(processedImgs);
//
//    for (const auto& img : right_tree2s) {
//        /*string outputFilePath2 = processedPath2 + "//" + to_string(++idx) + ".jpg";
//        cv::imwrite(outputFilePath2, img);
//        cout << "Processed and saved image: " << outputFilePath2 << endl;*/
//
//        Mat tree1_color = red_show(img);
//        string outputFilePath3 = processedPath3 + "//" + to_string(++idx1) + ".jpg";
//        cv::imwrite(outputFilePath3, tree1_color);
//        cout << "Processed and saved image: " << outputFilePath3 << endl;
//    }
//
//    //��processedImgs����floodFill��Ѫ�����������˵�һ��
//
//    return right_tree2s;
//}
