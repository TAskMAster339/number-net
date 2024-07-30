#include "matrix.h"
#include <random>
#include <iostream>
#include <stdexcept>

Matrix::Matrix(int m, int n){
    data.resize(m);
    for (size_t i = 0; i != m; ++i){
        data[i].resize(n);
    }      
}
Matrix::Matrix(const std::vector<std::vector<double>>& nums){
    data.resize(nums.size());
    for (size_t i = 0; i != nums.size(); ++i){
        data[i] = nums[i];
    }
}
size_t Matrix::getRows() const{
    return data.size();
}
size_t Matrix::getColumns() const{
    if (data.size() == 0)
        return 0;
    return data[0].size();
}
void Matrix::rand(double start, double end){
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distrib(start, end);

    for (size_t i = 0; i < data.size(); ++i){
        for (size_t j = 0; j < data[i].size(); ++j){
            data[i][j] = distrib(gen);
        }
    }
}
void Matrix::print() const{
    for (size_t i = 0; i < data.size(); ++i){
        for (size_t j = 0; j < data[i].size(); ++j){
            std::cout << data[i][j] << '\t';
        }
        std::cout << '\n';
    }
}
double Matrix::operator() (size_t i, size_t j) const {
    return data[i][j];
}
void Matrix::transpose(){
    std::vector<std::vector<double>> new_data(data[0].size(), std::vector<double>(data.size()));
    for (size_t i = 0; i != data.size(); ++i){
        for (size_t j = 0; j != data[i].size(); ++j){
            new_data[j][i] = data[i][j];
        }
    }
    data = new_data;
}
Matrix Matrix::operator* (const Matrix& other){
    if (getColumns() != other.getRows()){
        throw std::logic_error("Incorrect matrix sizes");
    }
    size_t n_row = getRows(), n_column = other.getColumns(); 
    std::cout << getRows() << 'x' << getColumns() << '\t' << other.getRows() << 'x' << other.getColumns() << std::endl;
    Matrix n_m(n_row, n_column);
    for (size_t i = 0; i < n_row; ++i){
        for (size_t j = 0; j < n_column; ++j){
           double sum = 0;
           for (size_t k = 0; k < data[i].size(); ++k){
               sum += (data[i][k] * other[k][j]);
           }
            n_m[i][j] = sum;
        }
    }
    return n_m;
}
Matrix& Matrix::operator*= (double num){
    for (size_t i = 0; i < getRows(); ++i){
        for (size_t j = 0; j < getColumns(); ++j){
            data[i][j]*=num;
        }
    }
    return *this;
}
Matrix Matrix::operator* (double num){
    Matrix n_m(getRows(), getColumns());
    n_m*=num;
    return n_m;
}
Matrix& Matrix::operator+= (const Matrix& other){
    if (getRows() != other.getRows() || getColumns() != other.getColumns()){
        throw std::logic_error("Incorrect matrix sizes");
    }
    for (size_t i = 0; i < getRows(); ++i){
        for (size_t j = 0; j < getColumns(); ++j){
            data[i][j]+=other[i][j];
        }
    }
    return *this;
       
}
Matrix Matrix::operator+ (const Matrix& other){
    if (getRows() != other.getRows() || getColumns() != other.getColumns()){
        throw std::logic_error("Incorrect matrix sizes");
    }
    auto tmp = *this;
    tmp+=other;
    return tmp;

}
bool Matrix::operator== (const Matrix& other){
    if (getRows() != other.getRows() || getColumns() != other.getColumns()){
        throw std::logic_error("Incorrect matrix sizes");
    }
    for (size_t i = 0; i < getRows(); ++i){
        for (size_t j = 0; j < getColumns(); ++j){
            if (data[i][j] != other[i][j]){
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!= (const Matrix& other){
    return !(*this==other);
}
