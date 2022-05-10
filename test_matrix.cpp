#include "mymatrix.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

using std::cout;
using std::endl;

int main() {
    cout << "ctors test" << endl;
    Matrix2 m(1, 2, 4, 5);
    Matrix2 v;
    cout << m << endl;
    cout << v << endl;

    scalar data[] = {1.f, 2.f, 3.f, 4.f};
    v = Matrix2(data);
    cout << v << endl;
    v = Matrix2(22.f, 32.f, 45.f, 1.f);
    cout << v << endl;
    v = Matrix2(m);
    cout << v << endl;

    std::cout << "----------" << std::endl;
    cout << "set fucntion test" << endl;
    v.set(data);
    cout << v << endl;
    v.set(4.f, 3.f, 2.f, 1.f);
    cout << v << endl;
    float rdata[] = {8, 9};
    v.setRow(0, rdata);
    cout << v << endl;
    v.setRow(1, rdata);
    cout << v << endl;
//    v.setRow(2, rdata);
    v = m;
    cout << v << endl;
    float cdata[] = {6, 22};
    v.setColumn(0, cdata);
    cout << v << endl;
    v.setColumn(1, cdata);
    cout << v << endl;
    v.setColumn(0.1, rdata);
    cout << v << endl;

    std::cout << "----------" << std::endl;
    cout << "pointer function test" << endl;
    scalar* raw_data = v.data();
    for (int i = 0; i < 4; i++) {
        cout << raw_data[i] << " ";
    }
    cout << endl;
    raw_data[0] = 888.f;
    raw_data[3] = 333.f;
    cout << v << endl;

    for (int i = 0; i < 4; i++) {
        cout << raw_data[i] << " ";
    }
    cout << endl;
    raw_data[0] = 1.f;
    cout << v << endl;

    const scalar* const_data = v.constData();
    for (int i = 0; i < 4; i++) {
        cout << const_data[i] << " ";
    }
    cout << endl;

    std::cout << "----------" << std::endl;
    cout << "get function test" << endl;

    for (int i = 0; i < 2; ++i) {
        cout << v.getRow(i) << endl;
    }
    for (int i = 0; i < 2; ++i) {
        cout << v.getColumn(i) << endl;
    }
    cout << "v.determinant: " << v.getDeterminant() << endl;
//    cout << "v.angle: " << v.getAngle() << endl;
    if (v.isRotationMatrix()) {
        cout << "v.angle: " << v.getAngle() << endl;
    }

    std::cout << "----------" << std::endl;
    cout << "in-place concerned function test" << endl;
    v.setIdentity();
    cout << v << endl;
    v.setRotatonMatrix(2.f, RAD);
    cout << v << endl;
    if (v.isRotationMatrix()) {
        cout << "v.angle: " << v.getAngle(RAD) << endl;
    }
    v.transpose();
    cout << v << endl;
    cout << v.transposed() << endl;
    cout << v << endl;
    v.inverse();
    cout << v << endl;
    cout << v.computeInverse() << endl;
    cout << v << endl;
    std::cout << "----------" << std::endl;
    cout << "operator test" << endl;
    v.set(1, 2, 3, 4);
    cout <<"m: " << m;
    cout <<"v: " << v;
    cout <<"m+v: " << m+v;
    m += v;
    cout <<"m: " << m;

    cout <<"m-v: " << m-v << endl;
    m -= Matrix2();
    cout << m << endl;
    cout << v << endl;
    cout << m.matmul(v) << endl;
    cout << v.matmul(m) << endl;
    cout << m * v << endl;
    cout << v * m << endl;
    m *= v;
    cout << m << endl;
    cout << m / 2 << endl;
    cout << m << endl;
    m /= 2;
    cout << m << endl;

    v.set(1,2,3,4);
    cout << v * 3 << endl;
    v *= 3;
    cout << v << endl;
    m = v;
    cout << m << endl;
    v[0] += MYEPSILON;
    cout << v.equal(m) << endl;
    cout << (v == m) << endl;

    const Matrix2 tt;
    for (int i = 0; i < 4; i++) {
        cout << tt[i] << " ";
    }
    cout << endl;
    cout << tt(0, 0) << endl;
    for (int i = 0; i < 4; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << v(1, 0) << endl;
    cout << -v << endl;

    cout << Vector2(2, 3) * v << endl;

    std::cout << "----------" << std::endl;
    cout << "deep/shadow copy test" << endl;
    m = v;
    printf("m: %p\n", &m);
    printf("v: %p\n", &v);
    printf("m data: %p\n", m.data());
    printf("v data: %p\n", v.data());

    Matrix2 mm(m);
    printf("m: %p\n", &m);
    printf("mm: %p\n", &mm);
    printf("m data: %p\n", m.data());
    printf("mm data: %p\n", mm.data());


    return 0;
}
