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
//    //�ٶԴ�vector���д�����ȡ�����
//    vector<Mat> images = readAndProcess(path);
//   /* int idx1 = 0;
//    for (const auto& img : images) {
//        Mat coloredImg = red_show(img);
//        string outputFilePath3 = processedPath3 + "//" + to_string(++idx1) + ".jpg";
//        cv::imwrite(outputFilePath3, coloredImg);
//        cout << "Processed and saved image: " << outputFilePath3 << endl;
//    }*/
//    
//    // ������������
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    // ��Ӹ����...    
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
//    // ����һ�� PolyData �洢��������
//    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
//    polyData->SetPoints(points);
//
//    // ����һ�� VertexGlyphFilter �Խ�����ʾΪ����
//    vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
//    vertexFilter->SetInputData(polyData);
//    vertexFilter->Update();
//
//    // ����һ�� PolyDataMapper ӳ���������
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(vertexFilter->GetOutputPort());
//
//    // ����һ�� Actor ������Ⱦ��������
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//
//    // ����һ�� Renderer ����� Actor
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(actor);
//    renderer->SetBackground(0.1, 0.2, 0.3); // ���ñ�����ɫ
//
//    // ����һ�� RenderWindow ����� Renderer
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//    renderWindow->SetSize(800, 600);
//
//    // ����һ�� RenderWindowInteractor ���ڽ���
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//
//    // ��ʼ��Ⱦ�ͽ���
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//
//    return EXIT_SUCCESS;
//}
