#include <iostream>    
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

int main()
{
    string path = "C:\\files6\\processed3";
    
    //�ٶԴ�vector���д�����ȡ�����
    readAndProcess(path);

    return 0;
}