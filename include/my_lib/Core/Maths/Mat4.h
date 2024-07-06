
#if !defined(MAT4_H)
#define MAT4_H
#include <vector>
#include "Vec4.h"
#include "Matrix.h"

# define M_PI           3.14159265358979323846

class Mat4 : public Matrix
{
public:

    Mat4();
    Mat4(const Matrix&);
    ~Mat4();
    Vec4 operator*(const Vec4&) const;
    Mat4 operator*(const Mat4&) const;
    Matrix operator*(const Matrix&) const;
    static  float* MatToGlfloatConversion(const Mat4&);
    static  Mat4 CreateScaleMatrix(const Vec3&);
    static  Mat4 CreateTranslationMatrix(const Vec3&);
    static  Mat4 CreateXRotationMatrix(float);
    static  Mat4 CreateYRotationMatrix(float);
    static  Mat4 CreateZRotationMatrix(float);
    static  Mat4 CreateRotationMatrix(const Vec3&);
    static  Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);
    void Print();
};

inline Mat4::Mat4()
{
    nbLine = 4;
    nbCol  = 4;
    matrix.resize(nbCol * nbLine);
}

inline Mat4::Mat4(const Matrix& m)
{
    nbLine  = m.nbLine;
    nbCol   = m.nbCol;

    for (float v : m.matrix)
    {
        matrix.push_back(v);
    }
}

inline Matrix Mat4::operator*(const Matrix& m) const
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

inline Mat4 Mat4::operator*(const Mat4& m) const
{
    Matrix a(*this);
    Matrix b(m);

    return a * b;
}

inline Vec4 Mat4::operator*(const Vec4& vec4) const
{
    Matrix vec4_m(4,1);
    vec4_m.Accessor(0, 0) = vec4.x;
    vec4_m.Accessor(1, 0) = vec4.y;
    vec4_m.Accessor(2, 0) = vec4.z;
    vec4_m.Accessor(3, 0) = vec4.w;
    vec4_m = *this * vec4_m;

    Vec4 v(vec4_m.Accessor(0, 0), vec4_m.Accessor(1, 0), vec4_m.Accessor(2, 0), vec4_m.Accessor(3, 0)); 
    return v;
}

inline Mat4 Mat4::CreateScaleMatrix(const Vec3& scale)
{
    Mat4 scaleMat;

    scaleMat.Accessor(0, 0) = scale.x;
    scaleMat.Accessor(1, 1) = scale.y;
    scaleMat.Accessor(2, 2) = scale.z;
    scaleMat.Accessor(3, 3) = 1;

    return scaleMat;
}

inline Mat4 Mat4::CreateTranslationMatrix(const Vec3& translation)
{
    Mat4 translationMat;

    translationMat.Accessor(0, 0) = 1;
    translationMat.Accessor(1, 1) = 1;
    translationMat.Accessor(2, 2) = 1;
    translationMat.Accessor(3, 3) = 1;
    translationMat.Accessor(0, 3) = translation.x;
    translationMat.Accessor(1, 3) = translation.y;
    translationMat.Accessor(2, 3) = translation.z;

    return translationMat;
}

inline Mat4 Mat4::CreateXRotationMatrix(float angle)
{
    Mat4 rotationMat;

    rotationMat.Accessor(0, 0) = 1;
    rotationMat.Accessor(3, 3) = 1;
    rotationMat.Accessor(1, 1) = cos(angle);
    rotationMat.Accessor(1, 2) = -sin(angle);
    rotationMat.Accessor(2, 1) = sin(angle);
    rotationMat.Accessor(2, 2) = cos(angle);

    return rotationMat;    
}

inline Mat4 Mat4::CreateYRotationMatrix(float angle)
{
    Mat4 rotationMat;

    rotationMat.Accessor(1, 1) = 1;
    rotationMat.Accessor(3, 3) = 1;
    rotationMat.Accessor(0, 0) = cos(angle);
    rotationMat.Accessor(0, 2) = sin(angle);
    rotationMat.Accessor(2, 0) = -sin(angle);
    rotationMat.Accessor(2, 2) = cos(angle);

    return rotationMat;    
}

inline Mat4 Mat4::CreateZRotationMatrix(float angle)
{
    Mat4 rotationMat;

    rotationMat.Accessor(2, 2) = 1;
    rotationMat.Accessor(3, 3) = 1;
    rotationMat.Accessor(0, 0) = cos(angle);
    rotationMat.Accessor(0, 1) = -sin(angle);
    rotationMat.Accessor(1, 0) = sin(angle);
    rotationMat.Accessor(1, 1) = cos(angle);

    return rotationMat;    
}

inline Mat4 Mat4::CreateRotationMatrix(const Vec3& angle)
{
    return  Mat4::CreateXRotationMatrix(angle.x) *
            Mat4::CreateYRotationMatrix(angle.y) * 
            Mat4::CreateZRotationMatrix(angle.z);    
}

inline Mat4 Mat4::CreateTransformMatrix(const Vec3& position, const Vec3& rotation, const Vec3& scale)
{
    return CreateRotationMatrix(rotation) *                //exchange rotation and translation to swap between 1st and 3rd person camera
           CreateTranslationMatrix(position) *             // Here set on 1st person 
           CreateScaleMatrix(scale);
}

inline Mat4::~Mat4()
{

}

inline float* Mat4::MatToGlfloatConversion(const Mat4& matrix)
{
    float* list = new float[16];
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
            list[(4*i)+j] = matrix.Accessor(i,j);
    }

    return list;
}

inline void  Mat4::Print()
{
    for( int i = 0;  i < this->nbLine ; i++)
    {
        for (int j = 0; j < this->nbCol ; j++)
        {
            std::cout << "|" << this->matrix[i * 4 + j] << "|";
        }
        std::cout << std::endl;
    }
}

#endif // MAT4_H
