#include <iostream>
#include <type_traits>


#include "myvector.hpp"
using namespace std;


//https://www.zhihu.com/question/36814207/answer/2431162249
//template <typename T>
//struct vec2 {
//    using value_type = std::decay_t<T>;
//    using reference = value_type &;
//    using const_reference = const value_type &;
//    using pointer = value_type *;

//    reference operator[](int index) {
//        return data[index];
//    }

//    const_reference operator[](int index) const {
//        return data[index];
//    }

//    union {
//        T data[2];
//        struct {
//            T x, y;
//        };
//    };
//    //    vec2<int> v{1, 2};
//    //    std::cout << "v[0] = "<< v[0] <<", v[1] = "<< v[1]<<std::endl;
//    //    std::cout << "v[0] = "<< v.x <<", v[1] = "<< v.y<<std::endl;
//};

void test(const float a[4]) {
    cout << a[0] << endl;
    cout << a[1] << endl;
    cout << a[2] << endl;
    cout << a[3] << endl;
}

int main(int argc, char** argv) {

//    Vector2 w;
//    Vector2 v(w);
//    w.x = 5;
//    cout << w << endl;
//    cout << v << endl;
    float a[4]{1, 2, 3, 4};

    float b = 4;
    float* point_b = &b;

    //cout << sizeof(a) / sizeof(float) << endl;
    //cout << sizeof(point_b) / sizeof(float) << endl;

    return 0;
}
