#include <iostream>
#include <settings.h>
#include <utils.h>
#include <octree.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace Octree;

int main() {
    cout << "Reading file... ";
    vector<Vec3d> pointsFile = readFile(FILENAME);
    cout << "done!" << endl;

    cout << "Building octree... ";
    nodes.clear();
    Node *root = new Node();
    root->level = 0;
    for (int i = 0; i < pointsFile.size(); i++) {
        root->append(&pointsFile[i]);
    }
    build(root);
    cout << "done!" << endl;
    cout << nodes.size() << " nodes generated." << endl;

    return 0;
}

