//#include <iostream>    
//#include <opencv2/opencv.hpp>
//#include <filesystem>
//#include "utils.h"
//
//using namespace cv;
//using namespace std;
//namespace fs = std::filesystem;
//vector<Mat> readAndProcess(string path) {
//    //先读入所有非空的图片 -> images
//    vector<Mat> images;
//
//    // 1. 获取图片
//    // 设置图像文件夹路径
//    string folderPath = path;
//    // 设置处理后的图像文件夹路径
//    string processedPath = "C://files6//tree";
//    string processedPath2 = "C://files6//tree_c";
//    string processedPath3 = "C://files6//tree_color";
//    // 获取文件夹中的所有图像文件
//    vector<string> imageFiles;
//    for (const auto& entry : fs::directory_iterator(folderPath)) {
//        if (entry.is_regular_file() && (entry.path().extension() == ".jpg" || entry.path().extension() == ".png")) {
//            imageFiles.push_back(entry.path().string());
//        }
//    }
//    vector<Mat> processedImgs; //预处理后的图像集
//    // 检查是否有图像文件
//    if (imageFiles.empty()) {
//        cerr << "No image files found in the specified directory!" << endl;
//        return processedImgs;
//    }
//
//    // 2. 遍历全部图像，应用func => 新的图像集
//    for (const auto& filePath : imageFiles) {
//        // 读取图像
//        cv::Mat image = cv::imread(filePath, 0);
//        if (image.empty()) {
//            cerr << "Could not open or find the image: " << filePath << endl;
//            continue;
//        }
//
//        //检查图像是否为全黑，若是，跳过
//        if (!areAllPixelsBelowThreshold(image, 30))
//            images.push_back(image);
//    }
//
//    
//    int idx = 0;
//    //int idx1 = 0;
//    for (const auto& img : images) {
//        Mat processedImg, normalizedImg, processedImg_root1;
//        //给每张图预处理->肺内最低为70最高为160，肺外为0
//        normalizedImg = normalization(img);
//
//        //将中间70%的图片的中间纵隔区改为180，然后找连通域树根一遍
//        int size = images.size();
//        if (idx > (int)size / 16 && idx < (int)4 * size / 5) {
//            processedImg = lung_and_media_make(normalizedImg);
//            processedImg_root1 = tree_seed1_make(processedImg);//同一个条件，两个步骤
//        }
//        else {
//            processedImg = normalizedImg;
//            processedImg_root1 = processedImg;
//        }
//        //
//        processedImgs.push_back(processedImg_root1);
//
//        //导出
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
//    //在processedImgs里用floodFill找血管树，已做了第一步
//
//    return right_tree2s;
//}
