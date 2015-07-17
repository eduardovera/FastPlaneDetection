#ifndef OCTREE
#define OCTREE

#endif // OCTREE

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

namespace Octree {

    struct Node {
        vector<Vec3d*> samples;
        int level;
        Vec3d centroid;
        vector<Node*> children;
        Mat1d covariance;
        Mat1d eigenvalues;
        Mat1d eigenvectors;
        bool isCoplanar;

        Node() {
            this->isCoplanar = false;
            this->covariance = Mat1d::zeros(3, 3);
            this->centroid = Vec3d(0.0, 0.0, 0.0);
        }

        void append(Vec3d *point) {
            int sample_size = static_cast<int>(this->samples.size());
            centroid = (sample_size * centroid) + *point;
            this->samples.push_back(point);
            centroid /= (sample_size + 1);
        }

        void computeCovariance() {
            Vec3d sd;
            for (int i = 0; i < this->samples.size(); i++) {
                sd = *this->samples[i] - this->centroid;
                covariance(0, 0) += sd[0] * sd[0];
                covariance(0, 1) += sd[0] * sd[1];
                covariance(0, 2) += sd[0] * sd[2];
                covariance(1, 1) += sd[1] * sd[1];
                covariance(1, 2) += sd[1] * sd[2];
                covariance(2, 2) += sd[2] * sd[2];
            }
            covariance(1, 0) = covariance(0, 1);
            covariance(2, 0) = covariance(0, 2);
            covariance(2, 1) = covariance(1, 2);

            covariance /= samples.size() - 1.0;

        }

        void subdivide() {
            double minX = DBL_MAX;
            double maxX = -DBL_MAX;

            double minY = DBL_MAX;
            double maxY = -DBL_MAX;

            double minZ = DBL_MAX;
            double maxZ = -DBL_MAX;

            Vec3d point;
            for (int i = 0; i < this->samples.size(); i++) {
                point = *this->samples[i];
                if (point[0] < minX) {
                    minX = point[0];
                }
                if (point[0] > maxX) {
                    maxX = point[0];
                }

                if (point[1] < minY) {
                    minY = point[1];
                }
                if (point[1] > maxY) {
                    maxY = point[1];
                }

                if (point[2] < minZ) {
                    minZ = point[2];
                }
                if (point[0] > maxZ) {
                    maxZ = point[2];
                }
            }

            double midX = .5 * (maxX + minX);
            double midY = .5 * (maxY + minY);
            double midZ = .5 * (maxZ + minZ);

            int x, y, z;
            Node* child1 = new Node();
            Node* child2 = new Node();
            Node* child3 = new Node();
            Node* child4 = new Node();
            Node* child5 = new Node();
            Node* child6 = new Node();
            Node* child7 = new Node();
            Node* child8 = new Node();


            for (int i = 0 ; i < this->samples.size(); i++) {
                point = *this->samples[i];
                if (point[0] >= midX) {
                    x = +1;
                } else {
                    x = -1;
                }
                if (point[1] >= midY) {
                    y = +1;
                } else {
                    y = -1;
                }
                if (point[2] >= midZ) {
                    z = +1;
                } else {
                    z = -1;
                }

                if (x == +1 && y == +1 && z == +1) {
                    child1->append(this->samples[i]);
                } else if (x == +1 && y == +1 && z == -1) {
                    child2->append(this->samples[i]);
                } else if (x == +1 && y == -1 && z == +1) {
                    child3->append(this->samples[i]);
                } else if (x == +1 && y == -1 && z == -1) {
                    child4->append(this->samples[i]);
                } else if (x == -1 && y == +1 && z == +1) {
                    child5->append(this->samples[i]);
                } else if (x == -1 && y == +1 && z == -1) {
                    child6->append(this->samples[i]);
                } else if (x == -1 && y == -1 && z == +1) {
                    child7->append(this->samples[i]);
                } else if (x == -1 && y == -1 && z == -1) {
                    child8->append(this->samples[i]);
                }
            }

            this->children.push_back(child1);
            this->children.push_back(child2);
            this->children.push_back(child3);
            this->children.push_back(child4);
            this->children.push_back(child5);
            this->children.push_back(child6);
            this->children.push_back(child7);
            this->children.push_back(child8);

        }
    };

    vector<Node*> nodes;

    void build(Node* node) {
        if (node->samples.size() < SMS) {
            return;
        }

        if (node->level >= SLEVEL) {
            node->computeCovariance();
            eigen(node->covariance, true, node->eigenvalues, node->eigenvectors);
            if ((node->eigenvalues(1) > (THICKNESS * node->eigenvalues(2))) && (node->eigenvalues(0) < (ISOTROPY * node->eigenvalues(1)))) {
                node->isCoplanar = true;
                nodes.push_back(node);
                return;
            }
        }

        node->subdivide();
        for (int i = 0; i < node->children.size(); i++) {
            Node *n = node->children[i];
            n->level = node->level + 1;
            build(n);
        }
    }

}
