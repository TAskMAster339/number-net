#include "matrix.h"
#include <vector>
#include <iostream>


int main(){
    double k = 1;
    std::vector<std::vector<double>> vec (5, std::vector<double>(3));
    for (size_t i = 0; i != vec.size(); ++i){
        for (size_t j = 0; j != vec[i].size(); j++){
            vec[i][j] = k++;
        }
    }
    Matrix m1(vec);
    Matrix m4(vec);
    Matrix m2(3, 2);
    m2[0][0] = 1;
    m2[1][1] = 4;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2.print();
    std::cout << m2.getRows() << 'x' << m2.getColumns() << std::endl;
    std::cout << '\n';
    m1.print();
    std::cout << m1.getRows() << 'x' << m1.getColumns() << std::endl;
    std::cout << '\n';
    Matrix m3(1, 1);
    m2.transpose();
    m1.transpose();
    m3 = m2 * m1;
    m3.print();
    std::cout << m3.getRows() << 'x' << m3.getColumns() << std::endl;
    std::cout << '\n';
    m1.transpose();
    m1.print();
    std::cout << (m4 == m1) << std::endl;
    m2*=3;
    m2.print();
    std::cout << "m22222222222222222222222\n";
    m1+=m4;
    m1.print();
    return 0;
}
