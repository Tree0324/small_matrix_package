
#include "matrix_fun.h"

double compute_coeff(int, int , double);


// constructor
matrix_fun::matrix_fun(int N_in, double** A_in){
    get_size(N_in);
    set_ele();
    get_ele(N_in, A_in);
}

// u can only enter size
matrix_fun::matrix_fun(int N_in){
    get_size(N_in);
    set_ele();
}

// default 2*2
matrix_fun::matrix_fun(){
    get_size(2);
    set_ele();
}

void matrix_fun::get_size(int N_in){
    N = N_in;
}
void matrix_fun::set_ele(){
    A = new double*[N];
    for (int i=0;i<N;i++)
        A[i] = new double[N];

    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            A[i][j] = 0;    
}
void matrix_fun::get_ele(int N_in, double** A_in){
    for (int i=0;i<N_in;i++)
        for (int j=0;j<N_in;j++)
            A[i][j] = A_in[i][j];
}



void matrix_fun::print_matrix(){
    for (int i=0;i<N;i++){
        cout << endl;
        for (int j=0;j<N;j++)
            cout << A[i][j] << " ";
    }
    cout << endl;
}


matrix_fun& matrix_fun::operator=(const matrix_fun& B_in){
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            A[i][j] = B_in.A[i][j];
    this->N = B_in.N;
    return *this;
}
matrix_fun matrix_fun::operator+(const matrix_fun& B_in){
    matrix_fun tmp(N, A);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            tmp.A[i][j] = A[i][j] + B_in.A[i][j];
      
    return tmp;
}

matrix_fun matrix_fun::operator-(const matrix_fun& B_in){
    matrix_fun tmp(N, A);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            tmp.A[i][j] = this->A[i][j] - B_in.A[i][j];   
    return tmp;
}

matrix_fun& matrix_fun::operator*=(const double& coeff){
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            A[i][j] = A[i][j] * coeff;
    return *this;
}
matrix_fun matrix_fun::operator*=(const matrix_fun& B_in){
    matrix_fun tmp(N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            tmp.A[i][j] = this->A[i][j] * B_in.A[i][j];  
    return tmp;
}
matrix_fun& matrix_fun::operator/=(const double& coeff){
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            A[i][j] = A[i][j] / coeff;
    return *this;
}
matrix_fun matrix_fun::operator/(const matrix_fun& B_in){
    matrix_fun tmp(N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            tmp.A[i][j] = this->A[i][j] / B_in.A[i][j];  
    return tmp;
}
matrix_fun matrix_fun::operator*(const matrix_fun& B_in){
    matrix_fun tmp(N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            for (int k=0;k<N;k++)
                tmp.A[i][j] += this->A[i][k] * B_in.A[k][j];  
    return tmp;
}

// transpose, cofactor, determinant, inverse implementation 
matrix_fun matrix_fun::transpose(){
    // copy a new matrix
    matrix_fun tmp(N);
    double**C = new double*[N];
    for (int i=0;i<N;i++)
        C[i] = new double[N];
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            C[i][j] = A[i][j];
    // paste for A
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++)
            tmp.A[j][i] = C[i][j];
    delete [] C;
    return tmp;
}

matrix_fun matrix_fun::get_cofactor_matix(){
    matrix_fun tmp(N);
    double coeff = 1;
    
    // save for det
    int target_i = 0, target_j = 0;
    int k = 0; // index for det
    double det_array[N*N] = {0};


    for (target_i=0;target_i<N;target_i++){
        for (target_j=0;target_j<N;target_j++){
            matrix_fun tmp_cofator(N-1);
            for (int ii=0,i=0;ii<N;i++,ii++){
                for (int jj=0,j=0;jj<N;j++,jj++){
                    if (target_i == ii || target_j == jj){
                        j--;
                    }
                    else{
                        tmp_cofator.A[i][j] = this->A[ii][jj];
                    }
                }
                if (target_i == ii )
                    i--;      
            }

            det_array[k] = (get_determinant(tmp_cofator));
            tmp.A[k/N][k%N] = det_array[k] * compute_coeff(k / N, k % N, coeff);
            k++;
 
        }    
    }
    
    return tmp;
}

matrix_fun matrix_fun::get_inverse(){
    matrix_fun tmp(N);
    double det = get_determinant(*this);
    if (det == 0){
        cout <<"the matrix is singular, no inverse exists" << endl; 
    }
    // special case with N=2
    if (N==2){
        tmp = *this;
        double tmp_val;
        tmp_val = A[0][0];
        tmp.A[0][0] = tmp.A[1][1];
        tmp.A[1][1] = tmp_val;
        tmp.A[0][1] = -tmp.A[0][1];
        tmp.A[1][0] = -tmp.A[1][0];
        tmp /= get_determinant(*this);
    }
    else{
            tmp = ((this->get_cofactor_matix()).transpose() /= det);
    }
    return tmp;
}

matrix_fun::~matrix_fun(){
    delete [] A;
}


// friend of the class
// firend of the class in iostream
ostream& operator<<(ostream& out, const matrix_fun& obj){
    for (int i=0;i<obj.N;i++){
        cout << endl;
        for (int j=0;j<obj.N;j++)
            cout << obj.A[i][j] << " ";
    }
    cout << endl;
    return out;
}
istream& operator>>(istream& in, matrix_fun& obj){
    for (int i=0;i<obj.N;i++)
        for (int j=0;j<obj.N;j++)
            cin >> obj.A[i][j];
    return in;
}

// function
double get_determinant(const matrix_fun& B_in){
    if (B_in.N==2){
            return B_in.A[0][0] * B_in.A[1][1] - B_in.A[0][1] * B_in.A[1][0];
    }
    else if (B_in.N == 3){
        double sum_plus = 0, sum_minus = 0;
        double plus[B_in.N] = {0};
        double minus[B_in.N] = {0};
        for (int i=0;i<B_in.N;i++){
            plus[i] = 1;
            minus[i] = 1;
        }
        for (int k=0,j=0;k<B_in.N;k++,j++){
            int times = 0;
            int tmp = j;
            int i = 0;
            while (times <  B_in.N){
                plus[k] *= B_in.A[i][j];
                i = i + 1 > B_in.N - 1 ? i + 1 - B_in.N : i + 1;
                j = j + 1 > B_in.N - 1 ? j + 1 - B_in.N : j + 1;
                times++;
            }
            j = tmp;
        }   

        for (int k=0, j=B_in.N-1;k<B_in.N;k++,j--){
            int times = 0;
            int i = 0;
            int tmp = j;
            while (times <  B_in.N){
                minus[k] *= B_in.A[i][j];
                j = j - 1 < 0 ? j + B_in.N - 1  : j - 1;
                i = i + 1 > B_in.N - 1 ? i + 1 - B_in.N : i + 1;
                times++;
            }
            j = tmp;
        }
        // algorithm for compute determinant
        for (int i=0;i<B_in.N;i++){
            sum_minus += minus[i];
            sum_plus += plus[i];
        }
        return sum_plus - sum_minus;
    }
    else{ 
        // recursive
        double det_recursive = 0;
        double coeff = 1;
        double* det_array = new double[B_in.N];
        for (int i=0;i<B_in.N;i++)
            det_array[i] = 0;

        expand_det_array_from_cof(B_in, det_array);
        for (int i=0;i<B_in.N;i++)
            det_recursive += compute_coeff(i,0,coeff) * (B_in.A[0][i] * det_array[i]);
        
        delete [] det_array;    
        return det_recursive;

    }
}

// other 
double compute_coeff(int i, int j , double coeff){
    int times = 0;
    if (i == 0 && j == 0)
        return coeff;
    else{
        while (times < i){
            coeff *= -1;
            times++;
        }
        times = 0;
        while (times < j){
            coeff *= -1;
            times++;
        }
        return coeff;
    }
}

double* expand_det_array_from_cof(const matrix_fun& B_in, double* det_array){
    double coeff = 1;
    int target_i = 0, target_j = 0;
    int k = 0; 
    target_i = 0;
        for (target_j=0;target_j<B_in.N;target_j++){
            matrix_fun tmp_cofator(B_in.N-1);
            for (int ii=0,i=0;ii<B_in.N;i++,ii++){
                for (int jj=0,j=0;jj<B_in.N;j++,jj++){
                    if (target_i == ii || target_j == jj){
                        j--;
                    }
                    else{
                        tmp_cofator.A[i][j] = B_in.A[ii][jj];
                    }
                }
                if (target_i == ii ){
                    i--;
                }
            }
            det_array[k] = get_determinant(tmp_cofator);
            k++;
        }
    return det_array;
}