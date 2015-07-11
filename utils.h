#ifndef UTILS
#define UTILS

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

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


#endif // UTILS

