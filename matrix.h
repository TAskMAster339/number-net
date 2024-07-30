#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix{
    public:
        Matrix(int m, int n); //create a 0-Matrix
        Matrix(const std::vector<std::vector<double>>& nums);

        void rand(double start, double end); //fill random values into the matrix;
        void print() const;
        void transpose();

        double operator() (size_t i, size_t j) const;        
        const std::vector<double>& operator[] (size_t i) const { return data[i];};
        std::vector<double>& operator[] (size_t i) { return data[i];}; 
        
        Matrix operator* (const Matrix& other);
        Matrix& operator*= (double num);
        Matrix operator* (double num);
        
        Matrix& operator+= (const Matrix& other);
        Matrix operator+ (const Matrix& other);
        
        bool operator== (const Matrix& other);
        bool operator!= (const Matrix& other);

        size_t getRows() const;
        size_t getColumns() const;
    private:
        std::vector<std::vector<double>> data;
};

#endif // MATRIX_H
