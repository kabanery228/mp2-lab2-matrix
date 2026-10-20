// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v):size(v.size), pMem(new T[size]){
      for (int i = 0;i < size;pMem[i] = v.pMem[i++]);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      size = v.size;
      pMem = v.pMem;
      delete v.pMem;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          size = v.size;
          pMem = new T[size];
          std::memcpy(pMem, v.pMem, size);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          size = v.size;
          pMem = v.pMem;
          delete v.pMem;
          //std::memcpy(pMem, v.pMem, size);
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0) throw out_of_range("Index must be greater than zero and lowwer than vector size");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) throw out_of_range("Index must be greater than zero and lowwer than vector size");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (size != v.size) {
          return false;
      }
      for (int i = 0;i < size;i++)
          if (pMem[i] != v[i]) 
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < size;tmp[i++] += val);
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < size;tmp[i++] -= val);
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < size;tmp[i++] *= val);
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (size != v.size) {
          throw "different size";
      }
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < size;tmp[i] += v[i++]);
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (size != v.size) {
          throw "different size";
      }
      TDynamicVector tmp(*this);
      for (int i = 0;i < size;tmp[i] -= v[i++]);
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (size != v.size) {
          throw "different size";
      }
      T tmp = 0;
      for (int i = 0;i < size;tmp += *this[i] * v[i++]);
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  
  friend istream& operator>>(istream& istr, TDynamicVector<T>& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      for (int i = 0; i < sz;i++)
          if (pMem[i] != m[i]) return false;
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0;i < sz;++i)
          tmp[i] = (*this)[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(sz);
      for (int i = 0;i < sz;++i) 
          tmp[i] = (*this)[i] * v;
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0;i < sz;++i)
          tmp[i] = (*this)[i] + m[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0;i < sz;++i)
          tmp[i] = (*this)[i] - m[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0;i < sz;++i) 
          for (int j = 0;j < sz;++j) 
              for (int k = 0;k < sz;++k) 
                  tmp[i][j] += (*this)[i][k] * m[k][j];
              
          
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0;i < sz;++i)
          istr >> v[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0;i < sz;++i) 
          ostr << v[i]<<std::endl;
      return ostr;
  }
};

#endif
