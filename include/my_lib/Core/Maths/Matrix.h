
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "../Debug/Assertion.h"

class Matrix
{

    public:
        Matrix();
        Matrix(int, int);
        Matrix(const Matrix&);
        ~Matrix();
        static Matrix Identity();
        Matrix operator*(const Matrix&) const;
        float Accessor(int, int) const;
        float& Accessor(int, int);
        Matrix Transpose();
        Matrix GetSubMatrix(int, int);
        float Det();
        float MinorValue(int, int);
        float Cof(int, int);
        Matrix CoMat();
        Matrix Adjunct();
        Matrix Reverse();

        int                 nbLine;
        int                 nbCol;
        std::vector<float>  matrix;
};

inline Matrix::Matrix()
{
    nbLine  = 0;
    nbCol   = 0;
}

inline Matrix::Matrix(int n, int m)
{
    nbLine  = n;
    nbCol   = m;
    matrix.resize(nbCol * nbLine); 
}

inline Matrix::Matrix(const Matrix& m)
{
    nbLine  = m.nbLine;
    nbCol   = m.nbCol;

    for(float v : m.matrix)
    {
        matrix.push_back(v);
    }
}

inline Matrix::~Matrix()
{

}

inline Matrix Matrix::Identity()
{
    Matrix identity;
    identity.nbLine     = 4;
    identity.nbCol      = 4;
    
    identity.matrix.resize(16);
    identity.matrix[0]  = 1;
    identity.matrix[5]  = 1;
    identity.matrix[10] = 1;
    identity.matrix[15] = 1;

    return identity;
}

inline float Matrix::Accessor(int indexLine, int indexCol) const
{
    return matrix[indexLine + indexCol * nbLine];
}

inline float& Matrix::Accessor(int indexLine, int indexCol)
{
    return matrix[indexLine + indexCol * nbLine];
}

inline Matrix Matrix::operator*(const Matrix& m) const
{   
    Matrix result(this->nbLine, m.nbCol);

    for (int i = 0; i < result.nbLine; i++)
    {
        for (int j = 0; j < result.nbCol; j++)
        {
            for (int k = 0; k < this->nbCol; k++)
            {
                result.Accessor(i, j) += this->Accessor(i, k) * m.Accessor(k, j);
            }
        }
    }

    return result;
}

inline Matrix Matrix::Transpose()
{
    Matrix tempMatrix(this->nbCol, this->nbLine);

    for (int i = 0; i < nbLine; i++)
    {
        for (int j = 0; j < nbCol; j++)
            tempMatrix.Accessor(j, i) = this->Accessor(i, j);
    }

    return tempMatrix;
}

inline Matrix Matrix::GetSubMatrix(int excludedColumnIndex, int excludedLineIndex)
{
    Matrix newMatrix(this->nbLine - 1, this->nbCol - 1);
    bool ColIndexPassed  = false;
    bool LineIndexPassed = false;

    for (int i = 0; i < this->nbLine; i++)
    {
        if (i == excludedLineIndex)
        {
            LineIndexPassed = true;
            continue;
        }

        for (int j = 0; j < this->nbCol; j++)
        {
            if (j == excludedColumnIndex)
            {
                ColIndexPassed = true;
                continue;
            }

            newMatrix.Accessor(i - LineIndexPassed, j - ColIndexPassed) = this->Accessor(i, j);
        }
        ColIndexPassed = false;
    }

    return newMatrix;
}

inline float Matrix::Det()
{
    myAssert(nbLine == nbCol);
    
    if (nbLine == 1)
        return matrix[0];

    if (nbLine == 2)
        return matrix[0] * matrix[3] - matrix[2] * matrix[1];
    
    if (nbLine == 3)
    {
        return matrix[0] * (matrix[4] * matrix[8] - matrix[7] * matrix[5]) 
             - matrix[1] * (matrix[3] * matrix[8] - matrix[6] * matrix[5]) 
             + matrix[2] * (matrix[3] * matrix[7] - matrix[6] * matrix[4]);
    }

    if (nbLine == 4)
    {
        return matrix[0] * (
                    matrix[5] * (matrix[10] * matrix[15] - matrix[14] * matrix[11]) 
                  - matrix[6] * (matrix[9] * matrix[15] - matrix[13] * matrix[11]) 
                  + matrix[7] * (matrix[9] * matrix[14] - matrix[13] * matrix[10]))
             - matrix[1] * (
                    matrix[4] * (matrix[10] * matrix[15] - matrix[14] * matrix[11])
                  - matrix[6] * (matrix[8] * matrix[15] - matrix[12] * matrix[11])
                  + matrix[7] * (matrix[8] * matrix[14] - matrix[12] * matrix[10]))
             + matrix[2] * (
                    matrix[4] * (matrix[9] * matrix[15] - matrix[13] * matrix[11])
                  - matrix[5] * (matrix[8] * matrix[15] - matrix[12] * matrix[11])
                  + matrix[7] * (matrix[8] * matrix[13] - matrix[12] * matrix[9]))
             - matrix[3] * (
                    matrix[4] * (matrix[9] * matrix[14] - matrix[13] * matrix[10])
                  - matrix[5] * (matrix[8] * matrix[14] - matrix[12] * matrix[10])
                  + matrix[6] * (matrix[8] * matrix[13] - matrix[12] * matrix[9]));
    }

    else 
    {
        float toReturn = 0;

        for (int i = 0; i < nbLine; i++)
        {
            toReturn += GetSubMatrix(i, 0).Det() * matrix[i] * ((i % 2) ? -1 : 1);
        }

        return toReturn;
    }
}

inline float Matrix::MinorValue(int indexLine, int indexCol)
{
    return GetSubMatrix(indexCol, indexLine).Det();
}

inline float Matrix::Cof(int indexLine, int indexCol)
{
    return pow(-1, indexLine + indexCol + 2) * MinorValue(indexLine, indexCol);
}

inline Matrix Matrix::CoMat()
{
    myAssert(nbLine == nbCol);

    Matrix cofMat(nbLine, nbCol);
    for (int i = 0; i < nbLine; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            cofMat.Accessor(i, j) = this->Cof(i, j);
        }
    }

    return cofMat;
}

inline Matrix Matrix::Adjunct()
{
    myAssert(nbLine == nbCol);

    return this->CoMat().Transpose();
}

inline Matrix Matrix::Reverse()
{
    myAssert(nbLine == nbCol || this->Det() != 0);

    Matrix reverse(this->Adjunct());
    float det = this->Det();
    for (int i = 0; i < nbLine; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            reverse.Accessor(i, j) /= det;
        }
    }

    return reverse;
}

#endif