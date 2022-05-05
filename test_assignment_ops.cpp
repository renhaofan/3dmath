/**
 * test assignemnt operator= in Eigen and OpenCV
 * OpenCV soft copy
 * Eigen hard copy
 */


#include <iostream>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main() {
    Eigen::Vector2f u(1.f, 2.f);
    Eigen::Vector2f v(3.f, 4.f);
    //! eigen hard copy
    v = u;
    cout << "u :" << u.x() << ", " << u.y() << endl;
    cout << "v :" << v.x() << ", " << v.y() << endl;
    cout << "----------" << endl;
    cout << "u address:" << u.data() << endl;
    cout << "v address:" << v.data() << endl;
    printf("u address %p\n", u.data());
    printf("v address %p\n", v.data());

    cv::Mat mu(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat mv(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
    //! OpenCV soft copy
    mv = mu;
    cout << "----------" << endl;
    printf("mu address %p\n", mu.data);
    printf("mv address %p\n", mv.data);

    return 0;
}
