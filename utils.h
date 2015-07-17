#ifndef UTILS
#define UTILS

#include <iostream>
#include <opencv2/opencv.hpp>
//#include <octree.h>
#include <fstream>

using namespace std;
using namespace cv;
using namespace Octree;

void split(vector<string> &tokens, const string &text, string sep) {
    tokens.clear();
    int start = 0, end = 0;
    while ((end = static_cast<int>(text.find(sep, start))) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
}

vector<Vec3d> readFile(string filename) {
    vector<Vec3d> points;
    ifstream infile(filename);
    string line;
    vector<string> tokens;
    while (getline(infile, line)) {
        split(tokens, line, " ");
        if (tokens[0] == "OFF") {
            continue;
        }
        points.push_back(Vec3d(stof(tokens[0]), stof(tokens[1]), stof(tokens[2])));
        tokens.empty();
    }
    return points;
}

void writeToFile(string filename, vector<Node*> nodes, vector<Vec3d> normals) {
    string content;
    int count_samples = 0;
    for (int k = 0; k < nodes.size(); k++) {
        vector<Vec3d*> points = nodes[k]->samples;
        count_samples += static_cast<int>(points.size());
        cv::Vec3d color = 255 * Vec3d(1, 1, 1);
        for (int i = 0; i < points.size(); i++) {
            content += to_string((*points[i])[0]) + " " + to_string((*points[i])[1]) + " " + to_string((*points[i])[2]) + " " + to_string(abs(color[0])) + " " + to_string(abs(color[1]))+ " " + to_string(abs(color[2])) + "\n";
        }
    }

    string header = "COFF " + to_string(count_samples) + " 0 0\n";

    ofstream output;
    output.open(filename);
    output << header << content;
    output.close();

}

#endif // UTILS

