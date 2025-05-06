#include "Matrices.h"

namespace Matrices
{

    Matrix::Matrix (int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        a.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            a.at(i).resize(cols);
        }
    }

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: dimensions must agree");
        } else
        {
            Matrix c = a;

            for (int i = 0; i < a.getRows(); i++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    c(i,j) = c(i,j) + b(i,j);
                }
            }   

            return c;         
        }
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        } else
        {
            Matrix c(a.getRows(), b.getCols());

            for (int k = 0; k < b.getCols(); k++)
            {
                for (int i = 0; i < a.getRows(); i++)
                {
                    for (int j = 0; j < b.getRows(); j++)
                    {
                        c(i,k)  += a(i,j) * b(j,k);
                    }
                }
            }

            return c;
        }
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        } else
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    if(abs(a(i,j) - b(i,j)) >= 0.001) 
                    {
                        return false;
                    }
                }
            }   
        }

        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a==b);
    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << a(i,j) << ' ';
            }

            os << '\n';
        }   

        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        (*this)(0,0) = cos(theta);
        (*this)(1,0) = sin(theta);
        (*this)(0,1) = (-1.0) * sin(theta);
        (*this)(1,1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0,0) = scale;
        (*this)(1,0) = 0;
        (*this)(0,1) = 0;
        (*this)(1,1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (size_t i = 0; i < nCols; i++)
        {
            (*this)(0, i) = xShift;
            (*this)(1, i) = yShift;
        }
    }
}