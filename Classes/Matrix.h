#pragma once

template<class T>
class Matrix
{
private:
    int m_rows;
    int m_cols;
    T** m_matrix;

public:
    Matrix(int rows, int cols);
    ~Matrix();
    //
    void SetSize(int rows, int cols);
    void Create();
    //
    int rows();
    int cols();
};

template<class T>
Matrix<T>::Matrix(int rows, int cols)
    :m_rows(rows), m_cols(cols)
{
    m_matrix = new T* [m_rows];
    for (int i = 0; i < m_rows; i++)
        m_matrix[i] = new T[m_cols];
}

template<class T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < m_rows; i++)
        delete[] m_matrix[i];

    delete[] m_matrix;
}

template<class T>
void Matrix<T>::SetSize(int rows, int cols)
{
}

template<class T>
void Matrix<T>::Create()
{
}

template<class T>
int Matrix<T>::rows()
{
    return m_rows;
}

template<class T>
int Matrix<T>::cols()
{
    return m_cols;
}
