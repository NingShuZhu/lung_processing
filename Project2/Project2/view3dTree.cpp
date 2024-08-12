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
//// ��ȡ����ͼ���е�Ѫ�����أ�180����3D����volume
//cv::Mat readTrees(vector<Mat> images) {
//
//    // ����3D����
//    int rows = images[0].rows;
//    int cols = images[0].cols;
//    cv::Mat volume = cv::Mat::zeros(rows, cols, CV_8U(DEPTH));
//
//    // ���������߶�Ϊ300
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
////// ʹ�� VTK ������ά��ͨ��
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
//    //�ٶԴ�vector���д�����ȡ�����
//    vector<Mat> images = readAndProcess(path);
//
//    // ��ȡ����ͼ��
//    //cv::Mat volume = readTrees(images);  // �滻Ϊʵ��·������Ƭ����
//
//    // ��OpenCV��cv::Matת��ΪVTK��vtkImageData
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
//    // ��ȡ��ֵ��
//    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
//    marchingCubes->SetInputData(vtkVolume);
//    marchingCubes->SetValue(0, 127);  // ���õ�ֵ��ֵ
//
//    // ӳ���ֵ��
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(marchingCubes->GetOutputPort());
//
//    // ������Ա
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    
//    // ������Ա����ɫ
//    actor->GetProperty()->SetColor(1.0, 1.0, 1.0); // ��ɫ
//   
//    // ������Ⱦ��
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(actor);
//
//    // ������Ⱦ����
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//
//    // ����������
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//
//    // ��ʼ��Ⱦ�ͽ���
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//
//    return 0;
//}
