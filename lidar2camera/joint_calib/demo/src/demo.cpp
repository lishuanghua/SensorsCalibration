#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

int main()
{
    double r_vec[3] = {-2.100418, -2.167796, 0.273330};
    cv::Mat pr_vec(1, 3, CV_64FC1, r_vec);
    std::cout << "pr_vec = " << pr_vec << std::endl;
    cv::Mat pR_matrix;
    cv::Rodrigues(pr_vec, pR_matrix);
    std::cout << "pR_matrix = " << pR_matrix << std::endl;
    // system("pause");

    // 旋转向量  模代表旋转角度
    cout << "旋转向量到旋转矩阵的转换" << endl;
    Mat src = (Mat_<double>(3, 1) << 0, 0, CV_PI / 2);
    cout << "src : \n"
         << src << endl;
    Mat dst;
    // 转化成旋转矩阵
    Rodrigues(src, dst);
    cout << "dst : \n"
         << dst << endl;

    Mat vec = (Mat_<double>(3, 1) << 1, 0, 0);
    cout << "vec : \n"
         << vec << endl;
    Mat result = dst * vec;
    cout << "result : \n"
         << result << endl;

    // 旋转矩阵
    cout << "旋转矩阵转化为旋转向量" << endl;
    Mat src1 = (Mat_<double>(3, 3) << 0, -1, 0, 1, 0, 0, 0, 0, 1);
    cout << "src1 : \n"
         << src1 << endl;
    Mat out;
    Rodrigues(src1, out);
    cout << "out : \n"
         << out << endl;

    return 0;
}