#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "myvector.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

// The following code can show the binary presentation of a float in some
// mainstream architecture.
void printFloat(float num) {
    int inum = *(int*)&num;
    for (int i = 0; i < 32; ++i) {
        cout << ((inum&0x80000000) ? 1 : 0);
        if (i == 0 || i == 8)
            cout << " ";
        inum <<= 1;
    }
    cout << endl;
}


int main() {
    /* initialize random seed: */
    srand(time(NULL));
    /* generate secret number between 1 and 10: */
    const int N = 6;
    scalar random[N];
    for (int i = 0; i < N; i++) {
        random[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        random[i] *= 10;
    }

    ofstream myfile, eigenfile;
    myfile.open("myvector.txt");
    eigenfile.open("eigenvector.txt");

    // Vector2
    Vector2 mu(random[0], random[1]);
    Vector2 mv(random[2], random[3]);
    Eigen::Vector2f eu(random[0], random[1]);
    Eigen::Vector2f ev(random[2], random[3]);

    // basic utils
    myfile << mu.x << "," << mu.y << endl;
    myfile << mv.x << "," << mv.y << endl;
    eigenfile << eu.x() << "," << eu.y() << endl;
    eigenfile << ev.x() << "," << ev.y() << endl;

    myfile << mu + mv << endl;
    eigenfile << "(" << (eu + ev).x() << ", " << (eu + ev).y() << ")" << endl;

    myfile << mu.norm() << endl;
    eigenfile << eu.norm() << endl;

    myfile << mu.normalized() << endl;
    eigenfile << "(" << (eu.normalized()).x() << ", " << (eu.normalized()).y() << ")" << endl;

    myfile << mu.dot(mv) << endl;
    eigenfile << eu.dot(ev) << endl;

    myfile << -mu << endl;
    eigenfile << "(" << (-eu).x() << ", " << (-eu).y() << ")" << endl;

    myfile << mu - mv << endl;
    eigenfile << "(" << (eu - ev).x() << ", " << (eu - ev).y() << ")" << endl;

    mu += mv;
    eu += ev;

    mu *= 2.5f;
    eu *= 2.5f;

    mu /= 1.5f;
    eu /= 1.5f;

    myfile << mu.distance(mv) << endl;
    eigenfile << (eu - ev).norm() << endl;

    myfile << mu.x << "," << mu.y << endl;
    eigenfile << eu.x() << "," << eu.y() << endl;


    myfile << mu[0] << endl;
    myfile << mu[1] << endl;
    eigenfile << eu[0] << endl;
    eigenfile << eu[1] << endl;

    myfile << "------" << endl;
    eigenfile << "------" << endl;


    myfile << mu.equal(mu) << endl;
    eigenfile << (eu - eu).isMuchSmallerThan(MYEPSILON) << endl;
    mv.set(mu.x + MYEPSILON, mu.y + MYEPSILON);
    ev.x() = eu.x() + MYEPSILON;
    ev.y() = eu.y() + MYEPSILON;
    myfile << (mv == mu) << endl;
    eigenfile << (ev == eu) << endl;

    myfile << "------" << endl;
    eigenfile << "------" << endl;



    myfile.close();
    eigenfile.close();

    //    ofstream myfile;
    //    myfile.open("example.txt");
    //    if (myfile.is_open()) {
    //        myfile << "1" << endl;
    //        myfile << "2" << endl;

    //        myfile.close();
    //    } else
    //        cout << "Unable to open file";

    return 0;
}
