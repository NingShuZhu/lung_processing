#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

int main()
{
    string path = "C:\\files6\\processed3";
    
    //再对此vector进行处理、提取、输出
    readAndProcess(path);

    return 0;
}