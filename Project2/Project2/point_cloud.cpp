//#include <vtkSmartPointer.h>
//#include <vtkPoints.h>
//#include <vtkPolyData.h>
//#include <vtkVertexGlyphFilter.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <iostream> 
//#include "utils.h"
//
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//
//int main(int argc, char* argv[])
//{
//    string path = "C:\\files6\\processed3";
//    string processedPath3 = "C://files6//tree_color";
//
//    //再对此vector进行处理、提取、输出
//    vector<Mat> images = readAndProcess(path);
//   /* int idx1 = 0;
//    for (const auto& img : images) {
//        Mat coloredImg = red_show(img);
//        string outputFilePath3 = processedPath3 + "//" + to_string(++idx1) + ".jpg";
//        cv::imwrite(outputFilePath3, coloredImg);
//        cout << "Processed and saved image: " << outputFilePath3 << endl;
//    }*/
//    
//    // 创建点云数据
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    // 添加更多点...    
//    for (int z = 0; z < images.size(); ++z) {
//        for (int y = 0; y < images[0].rows; ++y) {
//            for (int x = 0; x < images[0].cols; ++x) {
//                if (images[z].at<uchar>(y, x) == 180) {
//                    cout << "+1" << endl;
//                    points->InsertNextPoint(y, x, z);
//                }
//            }
//        }
//    }
//
//    /*vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    points->InsertNextPoint(1.0, 2.0, 3.0);
//    points->InsertNextPoint(2.0, 3.0, 4.0);
//    points->InsertNextPoint(3.0, 4.0, 5.0);*/
//
//    // 创建一个 PolyData 存储点云数据
//    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
//    polyData->SetPoints(points);
//
//    // 创建一个 VertexGlyphFilter 以将点显示为顶点
//    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
//    vertexFilter->SetInputData(polyData);
//    vertexFilter->Update();
//
//    // 创建一个 PolyDataMapper 映射点云数据
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(vertexFilter->GetOutputPort());
//
//    // 创建一个 Actor 用于渲染点云数据
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//
//    // 创建一个 Renderer 并添加 Actor
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(actor);
//    renderer->SetBackground(0.1, 0.2, 0.3); // 设置背景颜色
//
//    // 创建一个 RenderWindow 并添加 Renderer
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//    renderWindow->SetSize(800, 600);
//
//    // 创建一个 RenderWindowInteractor 用于交互
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//
//    // 开始渲染和交互
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//
//    return EXIT_SUCCESS;
//}
