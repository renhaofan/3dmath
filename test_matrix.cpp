#include "mymatrix.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

int main() {
    Matrix2 mm(1, 2, 4, 5);
    std::cout << mm << std::endl;
    scalar* t = mm.data();
    t[0] = mm(1,0);
    std::cout << mm << std::endl;
    std::cout << "----------" << std::endl;
    scalar dd[4]{33, 22, 7, 8};
    mm.set(dd);
    std::cout << mm << std::endl;


    std::cout << "----------" << std::endl;
    Matrix2 vv(mm);
    std::cout << vv << std::endl;
    printf("%p\n", &mm);
    printf("%p\n", &vv);

//    std::cout << "----------" << std::endl;
//    Matrix2 vvv(2, 3, 5, 6);
//    vvv = vv;
//    printf("%p\n", &vv);
//    printf("%p\n", &vvv);
//    Matrix2 mm(3, 2, 1, 2);
//    Matrix2 vv(1, 2, 4, 5);
//    std::cout << mm << std::endl;
//    std::cout << vv << std::endl;
//    std::cout << "----------" << std::endl;
//    std::cout << mm.matmul(vv) << std::endl;

    return 0;
}
