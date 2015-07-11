#include <iostream>
#include <settings.h>
#include <utils.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    cout << "Reading file... ";
    vector<Vec3d> points = readFile(FILENAME);
    cout << "done!" << endl;
    cout << "Hello World!" << endl;
    return 0;
}

