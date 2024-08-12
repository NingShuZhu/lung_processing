//#include <opencv2/opencv.hpp>
//#include <vtkSmartPointer.h>
//#include <vtkImageData.h>
//#include <vtkMarchingCubes.h>
//#include <vtkPolyData.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <iostream> 
//#include <vtkCamera.h>
//#include <vtkProperty.h>
//#include "utils.h"
//
//#include <vtkAutoInit.h>
//#include <vtkImageConnectivityFilter.h>
//#include <vtkImageDataGeometryFilter.h>
//#include <vtkInteractorStyleImage.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//
//#define DEPTH 300
//
//using namespace std;
//using namespace cv;
//
//// 读取切面图像中的血管像素（180）至3D矩阵volume
//cv::Mat readTrees(vector<Mat> images) {
//
//    // 构建3D矩阵
//    int rows = images[0].rows;
//    int cols = images[0].cols;
//    cv::Mat volume = cv::Mat::zeros(rows, cols, CV_8U(DEPTH));
//
//    // 设最大立体高度为300
//    for (int i = 0; i < DEPTH; ++i) {
//        if (i < images.size()) {
//            for (int y = 0; y < images[0].rows; y++) {
//                for (int x = 0; x < images[0].cols; x++) {
//                    if (images[i].at<uchar>(y, x) == 180) {
//                        volume.at<Vec<uchar, DEPTH>>(y, x)[i] = 180;
//                    }
//                }
//            }
//        }
//    }
//
//    return volume;
//}
//
////// 使用 VTK 查找三维连通域
////void findAndVisualizeConnectedComponents(const vtkSmartPointer<vtkImageData>& vtkVolume) {
////    vtkSmartPointer<vtkImageConnectivityFilter> connectivityFilter = vtkSmartPointer<vtkImageConnectivityFilter>::New();
////    connectivityFilter->SetInputData(vtkVolume);
////    connectivityFilter->SetExtractionModeToLargestRegion();
////    connectivityFilter->Update();
////
////    vtkSmartPointer<vtkImageDataGeometryFilter> geometryFilter = vtkSmartPointer<vtkImageDataGeometryFilter>::New();
////    geometryFilter->SetInputConnection(connectivityFilter->GetOutputPort());
////    geometryFilter->Update();
////
////    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
////    mapper->SetInputConnection(geometryFilter->GetOutputPort());
////
////    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
////    actor->SetMapper(mapper);
////
////    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
////    renderer->AddActor(actor);
////    renderer->SetBackground(0.1, 0.2, 0.3);
////
////    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
////    renderWindow->AddRenderer(renderer);
////    renderWindow->SetSize(800, 600);
////
////    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
////    renderWindowInteractor->SetRenderWindow(renderWindow);
////
////    renderWindow->Render();
////    renderWindowInteractor->Start();
////}
//
//int main() {
//    string path = "C:\\files6\\processed3";
//
//    //再对此vector进行处理、提取、输出
//    vector<Mat> images = readAndProcess(path);
//
//    // 读取切面图像
//    //cv::Mat volume = readTrees(images);  // 替换为实际路径和切片数量
//
//    // 将OpenCV的cv::Mat转换为VTK的vtkImageData
//    vtkSmartPointer<vtkImageData> vtkVolume = vtkSmartPointer<vtkImageData>::New();
//    int dims[3] = {images[0].rows, images[0].cols, images.size()};
//    vtkVolume->SetDimensions(dims);
//    vtkVolume->AllocateScalars(VTK_UNSIGNED_CHAR, 1);
//
//    for (int z = 0; z < images.size(); ++z) {
//        for (int y = 0; y < images[0].rows; ++y) {
//            for (int x = 0; x < images[0].cols; ++x) {
//                unsigned char* pixel = static_cast<unsigned char*>(vtkVolume->GetScalarPointer(y, x, z));
//                if (images[z].at<uchar>(y, x) == 180) {
//                    pixel[0] = 180;
//                }
//                else {
//                    pixel[0] = 0;
//                }
//            }
//        }
//    }
//
//    //findAndVisualizeConnectedComponents(vtkVolume);
//
//    // 提取等值面
//    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
//    marchingCubes->SetInputData(vtkVolume);
//    marchingCubes->SetValue(0, 127);  // 设置等值面值
//
//    // 映射等值面
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(marchingCubes->GetOutputPort());
//
//    // 创建演员
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    
//    // 设置演员的颜色
//    actor->GetProperty()->SetColor(1.0, 1.0, 1.0); // 红色
//   
//    // 创建渲染器
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(actor);
//
//    // 创建渲染窗口
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//
//    // 创建交互器
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//
//    // 开始渲染和交互
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//
//    return 0;
//}
