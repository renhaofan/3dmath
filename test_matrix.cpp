#include "mymatrix.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>

using std::cout;
using std::endl;

int main() {
    scalar data[]{0.f, 1.f, 2.f, 3.f,
                  4.f, 5.f, 6.f, 7.f,
                  8.f, 9.f, 10.f, 11.f,
                  12.f, 13.f, 14.f, 15.f};

    Matrix4 m;
    m.scale(5, 2 ,32);
    cout << m << endl;
////    m.set(data);
////    cout << m << endl;
//    scalar row[] = {9, 2, 3, 1};
//    m.setRow(0, row);
//    m.setRow(1, row);
//    m.setRow(2, Vector4(0, 1, 2, 3));
//    m.setRow(3, Vector4(8, 9, 12, 4));
//    cout << m << endl;
//    m.setIdentity();
//    cout << m << endl;
//    m.setColumn(0, row);
//    m.setColumn(3, Vector4(8, 9, 12, 4));
//    cout << m << endl;


//    scalar* p = m.data();
//    p[2] = 25;
//    cout << m << endl;

//    for (int i = 0; i < 4; i++) {
//        cout << m.getRow(i) << endl;
//    }
//    for (int i = 0; i < 4; i++) {
//        cout << m.getColumn(i) << endl;
//    }


//    scalar src[]{4.f, 1.f, 2.f, 3.f,
//                  4.f, 5.f, 6.f, 7.f,
//                  8.f, 3.f, 1.f, 11.f,
//                  12.f, 13.f, 14.f, 15.f};
//    m.set(src);
//    Eigen::Matrix4f e_m(src);
//    cout << e_m.determinant() << endl;
//    cout << m.getDeterminant() << endl;

//    m.setIdentity();
//    Matrix3 r3;
//    r3.setRotationMatrix(Vector3(1.f, 1.f, 1.f), 25);
//    cout << r3 << endl;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            m(i, j) = r3(i, j);
//        }
//    }
//    m(0, 3) = 3.3;
//    m(1, 3) = 2.3;
//    cout << m << endl;
//    cout << m.isRotationMatrix() << endl;
//    cout << m.isEuclideanMatrix() << endl;
//    cout << m.isAffineMatrix() << endl;
//    cout << m / 2 << endl;

//    Matrix4 v(m);
//    float a = 5;
//    Eigen::Matrix4f e_v(v.data());
//    e_m = e_v;
//    cout << v.matmul(m) << endl;
//    cout << e_v * e_m << endl;

//    m.setIdentity();
//    cout << v << endl;
//    cout << v * m << endl;
//    v = m;
//    v[0] += MYEPSILON;
//    cout << v.equal(m) << endl;
//    cout << (v == m) << endl;
//    cout << (v != m) << endl;

//    v.set(src);
//    cout << v << endl;
//    v *= 5;
//    cout << v << endl;
//    cout << -v << endl;

//    cout << v * Vector4(1.f, 1.f, 1.f, 1.f) << endl;
//    cout << Vector4(1.f, 1.f, 1.f, 1.f) * v << endl;
//    v *= m;
//    cout << v << endl;
//    cout << v * 0.1 << endl;


/*  test Matrix3
    Matrix3 m;
    cout << m << endl;
    scalar src[] = {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};
    m = Matrix3(src);
    cout << m << endl;
    m = Matrix3(8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);
    cout << m << endl;

    Matrix3 v(m);
    cout << v << endl;
    printf("m %p\n", &m);
    printf("v %p\n", &v);
    printf("m data %p\n", m.data());
    printf("v data %p\n", v.data());

    scalar data[] = {2.5, 1.5, 0, 3, 2.5, 0, 0, 0, 1};
    Eigen::Matrix3f e_m(data);
    cout << e_m << endl;
    cout << e_m.inverse() << endl;
    m.set(data);
    cout << m << endl;
    cout << m.computeInverse() << endl;
    v = m;
    v[0] += MYEPSILON;
    cout << (v == m) << endl;
    cout << (v != m) << endl;
    cout << (v.equal(m)) << endl;
    m.set(src);
    cout << m << endl;
    cout << m.getColumn(0) << endl;
    cout << m.getColumn(1) << endl;
    cout << m.getColumn(2) << endl;
    cout << m.getRow(0) << endl;
    cout << m.getRow(1) << endl;
    cout << m.getRow(2) << endl;

    e_m = Eigen::Matrix3f(src);
    cout << e_m << endl;
    cout << m << endl;
    cout << e_m.determinant() << endl;
    cout << m.getDeterminant() << endl;

    scalar d[] = {1.2, 3.f, 3.8, 2, 3, 4, 1.3, 2.3, 4};
    e_m = Eigen::Matrix3f(d);
    m.set(d);
    cout << e_m << endl;
    cout << m << endl;
    cout << e_m.inverse() << endl;
    m.inverse();
    cout << m << endl;
    m.setRotationMatrix(Vector3(1.f, 1.f, 1.f), 30);
    cout << m << endl;
    cout << m.isRotationMatrix() << endl;
    Eigen::Matrix3f e_v(src);
    v.set(src);

    m = Matrix3(d);
    v = Matrix3(8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);
    cout << m << endl;
    cout << v << endl;
    scalar src_inv[] = {8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f};
    e_m = Eigen::Matrix3f(d);
    e_v = Eigen::Matrix3f(src_inv);
    cout << e_m << endl;
    cout << e_v << endl;

    const Matrix3 ret = m.matmul(v);
    cout << ret << endl;
    cout << e_m * e_v << endl;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cout << ret(i, j) << " ";
    cout << endl;
    m.set(src);
    cout << m << endl;
    cout << m * 5 << endl;
    cout << m / 0.1 << endl;
    v.set(src);
    cout << m * v << endl;
    cout << m * Vector3(1.f, 1.f, 1.f) << endl;

    m *= v;
    cout << m << endl;
    m += v;
    cout << m << endl;
    m -= v;
    cout << m << endl;

    cout << v << endl;
    v = m;
    cout << v << endl;

    scalar xx[]{9, 2, 6};

    m.setColumn(0, xx);
    m.setColumn(1, xx);
    m.setColumn(2, Vector3(1,2,3));
    cout << m << endl;
    m.setRow(0, xx);
    m.setRow(1, Vector3(4,5,6));
    m.setRow(2, Vector3(7,8,9));
    cout << m << endl;
    cout << m.toHomogenous() << endl;
    m.transpose();
    cout << m << endl;

    cout << m.transposed() << endl;
    cout << m << endl;

    cout << 1.f * m << endl;
    cout << 2.f * m << endl;
    cout << Vector3(1.f, 1.f, 1.f) * m << endl;
    cout << -m << endl;
*/

/*    test Matrix2
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
*/

    return 0;
}
