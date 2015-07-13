#ifndef OCTREE
#define OCTREE

#endif // OCTREE

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

struct Octree {
    vector<Vec3d> samples;
    int level;
    Vec3d centroid;
    vector<Octree> children;
};

