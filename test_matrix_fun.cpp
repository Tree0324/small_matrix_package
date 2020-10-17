
#include "matrix_fun.h"

int main(){

    double A_tmp[3][3] = {{1, 2, 3},
                      {3, 4, 6},
                      {7, 8, 9}};
    double B_tmp[3][3] = {{5, 6, 7},
                      {9, 10, 12},
                      {13, 15, 18}};
    
    double C_tmp[2][2] = {{1, 2},
                            {4, 6}};

    double D_tmp[4][4] = {{1, 2, 3, 4},
                            {5, 6, 8, 12},
                            {15, 16, 25, 22},
                            {7, 4, 7, 9}};
                            
    double E_tmp[5][5] = {{1, 2, 1, 4, 5},
                            {2, 1, 4, 5, 6},
                            {1, 8, 8 ,10, 11},
                            {9, 10, 2, 12, 13},
                            {14, 2, 16, 17, 18}};

    double F_tmp[6][6] = {{1, 2, 5, 8, 1, 2},
                            {9, 10, 15, 16, 25, 30},
                            {14, 15, 16, 18, 45, 50},
                            {20, 22, 23, 25, 27, 20},
                            {12, 12, 25, 88, 99, 100},
                            {12, 25, 14, 1, 2, 0}};


    int N = 3;
    double** A = new double*[N];
    double** B = new double*[N];
    for (int i=0;i<N;i++){
        A[i] = new double[N];
        B[i] = new double[N];
    }
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++){
            A[i][j] = A_tmp[i][j];
            B[i][j] = B_tmp[i][j];
        }

    
    double** C = new double*[2];
    for (int i=0;i<2;i++)
        C[i] = new double[2];

    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++)
            C[i][j] = C_tmp[i][j];
    

    double** D = new double*[4];
    for (int i=0;i<4;i++)
        D[i] = new double[4];

    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            D[i][j] = D_tmp[i][j];
    
    
    double** E = new double*[5];
    for (int i=0;i<5;i++)
        E[i] = new double[5];

    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            E[i][j] = E_tmp[i][j];
    
    double** F = new double*[6];
    for (int i=0;i<6;i++)
        F[i] = new double[6];

    for (int i=0;i<6;i++)
        for (int j=0;j<6;j++)
            F[i][j] = F_tmp[i][j];
    




    // test for constructor
    cout << "test for constructor" << endl;
    matrix_fun test(N, A), test_size(5);
    //cout << test.N;
    test.print_matrix();

    // check pointer or value
    matrix_fun a1(N,A);
    matrix_fun a2(N,A);
    a1 = a1 + test;
    a1.print_matrix();
    a2.print_matrix();

    // test for transpose   
    cout << "test for transpose" << endl; 
    test.transpose().print_matrix();
    cout << "test is " << test << endl;
    test_size.print_matrix();

    cout << endl;
    matrix_fun test_trans(N);
    test_trans = test;
    test.print_matrix();
    test_trans.print_matrix();

    cout << endl;
    // test for operator + - * / mapping operator
    cout << "test for operator" << endl;
    matrix_fun test_oper_1(N, A), test_oper_2(N, B), test_oper_3(N), test_oper_4(N);
    cout << "test for +" << endl;
    test_oper_3 = test_oper_1 + test_oper_2;
    test_oper_3.print_matrix();
    test_oper_1.print_matrix();
    cout << "test for -" << endl;
    test_oper_4 = test_oper_1 - test_oper_2;
    test_oper_4.print_matrix();
    cout << "test for a = a + b" << endl;
    test_oper_4 = test_oper_4 + test_oper_3;
    test_oper_4.print_matrix();
    cout << "test for a *= coeff" << endl;
    test_oper_1 *= 50;
    test_oper_1.print_matrix();
    test_oper_1 /= 50;
    cout << "test for divide" << endl;
    test_oper_4 = test_oper_1 / test_oper_2;
    cout << test_oper_4 << endl;
    cout << "test for matrix product" << endl;
    test_oper_4 = test_oper_1 * test_oper_2;
    
    cout <<test_oper_4 << endl << test_oper_1 << test_oper_2 << endl; 
    cout << "test bitwise muliplication" << endl;
    test_oper_4 = (test_oper_1 *= test_oper_2);

    cout <<test_oper_4 << endl << test_oper_1 << test_oper_2 << endl; 
    // test for iostream
    cout << "test for isotream" << endl;

    cout << test_oper_1 << endl;        
    matrix_fun cin_test(N);
    // cin >> cin_test;
    // cout << cin_test;

    // detetminant cofator inverse test
    cout << "determinant test" << endl;
    matrix_fun test_det(N, A), test_inv(N, B);
    cout << "the determinant of A is ";
    cout << get_determinant(test_det) << endl;
    cout << "inverse test" << endl;
 
    cout << "test for 2*2 " << endl;
    matrix_fun inv_2(2,C);
    cout << "det is " << get_determinant(inv_2) << endl;
    cout << "matrix is " << endl;
    cout << inv_2 << endl;

    cout << "the inverse is " << endl;
    cout << inv_2.get_inverse();
  
    cout << "test for 3*3" << endl;
    cout << "the matrix is " << endl;
    cout << test_inv;
    cout << "the determinant is " << get_determinant(test_inv);
    cout << test_inv << endl;
    cout << "get cofator matix is " << endl;
    cout << test_inv.get_cofactor_matix() << endl;
    cout << "inverse matrix is " << endl;
    cout << test_inv.get_inverse() << endl;

    cout << "test for det 4*4" << endl;
    matrix_fun test_det4D(4, D);
    cout << "cofator matrix for 4D is" << endl;

    //cout << test_det4D << endl;
    cout << "det is " << get_determinant(test_det4D) << endl;
    cout <<  "inverse is\n" << test_det4D.get_inverse() << endl;
    cout << "test for 5*5 " << endl;
    matrix_fun test_5D(5, E);
    cout << "det is " << get_determinant(test_5D) << endl;
    cout << "inv is" << test_5D.get_inverse() << endl; 
    // cout << test_5D; 
    cout << "test for 6*6" << endl;
    matrix_fun test_6D(6, F);
    cout << "det is " << get_determinant(test_6D) << endl;
    cout << "inv is " << test_6D.get_inverse() << endl;


    cout << "congradulation~\nend of test !!!!" << endl;
    return 0;

}