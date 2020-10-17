

#include <iostream>
using namespace std;

// the class is using for matirx computation for N*N 2D matrix

class matrix_fun{

    friend ostream& operator<<(ostream&, const matrix_fun&);
    friend istream& operator>>(istream&, matrix_fun&);
    friend double get_determinant(const matrix_fun&);
    friend double compute_coeff(int, int, double);
    friend double* expand_det_array_from_cof(const matrix_fun&, double*);


    private:
        int N; // declare for N*N size
        double** A;
    public:
        // constructor
        matrix_fun(int, double**);
        matrix_fun(int);
        matrix_fun();
        void get_size(int);
        void set_ele();
        void get_ele(int, double**);

        void print_matrix();

        

        // some operation including inverse matrix
        matrix_fun transpose();
        matrix_fun get_cofactor_matix();
        matrix_fun get_inverse();

        // operator overloading
        // support coefficient multiplication, mapping product ,and matrix product
        matrix_fun& operator=(const matrix_fun&); 
        matrix_fun operator+(const matrix_fun&);
        matrix_fun operator-(const matrix_fun&);
        matrix_fun& operator*=(const double&); // coeff 
        matrix_fun operator*=(const matrix_fun&); // elementwise muliplication
        matrix_fun& operator/=(const double&);
        matrix_fun operator/(const matrix_fun&); // for elewise divide
        matrix_fun operator*(const matrix_fun&); // matrix product

        // destructor for del A C
        ~matrix_fun();
};
