#include <iostream>

using namespace std;

class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
public:
    Matrix(int s = 5);

    Matrix(const Matrix &);// copy constructor

    ~Matrix() {
        delete [] matrix;
        delete [] buf;
    }

    Matrix &operator=(const Matrix &a);

    Matrix &clockwise90(){
        int tmp[size*size];
        int num = 0;
        for(int i=0;i<this->size;i++){
            for(int j = 0;j<this->size;j++){
                tmp[num] = this->matrix[i][j];
                num++;
            }
        }
        num=0;
        for(int i=size-1; i>=0; i--){
            for(int j=0; j<size; j++){
                matrix[j][i] = tmp[num];
                num++;
            }
        }
        return *this;
    }
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix

using namespace std;

int main()
{
    int matrix_size;
    cin>>matrix_size;
    Matrix a(matrix_size);
    cin>>a;

    cout<<endl;
    
    cout<<a.clockwise90().clockwise90()<<endl;
    cout<<a<<endl;

    return 0;
} // end main


Matrix::Matrix(int s){
    size=s;
    matrix = new int*[s];
    buf = new int[s*s];
    for(int i=0;i<s;i++){
        matrix[i] = &buf[i*s];
    }
    
}

Matrix::Matrix(const Matrix &m){
    size = m.size;
    matrix = new int*[size];
    buf = new int[size*size];
    for(int i=0;i<size;i++){
        matrix[i] = &buf[i*size];
    }
    for(int i=0;i<size*size;i++){
        buf[i] = m.buf[i];
    }
}

std::ostream &operator<<(std::ostream &output, const Matrix &m){
    for(int i=0;i<m.size;i++){
        output<<m.matrix[i][0];
        for(int j=1;j<m.size;j++){
            output<<" "<<m.matrix[i][j];
        }
        output<<std::endl;
    }
    return output;
}

std::istream &operator>>(std::istream &input, Matrix &m){
    for(int i=0;i<m.size;i++){
        for(int j=0;j<m.size;j++){
            input>>m.matrix[i][j];
        }
    }
    return input;
}

Matrix& Matrix::operator=(const Matrix &a){
    for(int i=0;i<a.size*a.size;i++){
        buf[i]  = a.buf[i];
    }
    return *this;
}
