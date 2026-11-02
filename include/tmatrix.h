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
    if (sz == 0 || sz>MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]{};// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v):sz(v.sz), pMem(new T[sz]){
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
          for (int i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.pMem = nullptr;
          v.sz = 0;
          //std::memcpy(pMem, v.pMem, size);
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация

  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz || ind < 0 || ind > MAX_VECTOR_SIZE) throw out_of_range("Index must be greater than zero and lowwer than vector size");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0 || ind > MAX_VECTOR_SIZE) throw out_of_range("Index must be greater than zero and lowwer than vector size");
      return pMem[ind];
  }
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) {
          return false;
      }
      for (int i = 0;i < sz;i++)
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
      for (int i = 0;i < sz;tmp[i++] += val);
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < sz;tmp[i++] -= val);
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < sz;tmp[i++] *= val);
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw "different size";
      }
      TDynamicVector<T> tmp(*this);
      for (int i = 0;i < sz;tmp[i] += v[i++]);
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw "different size";
      }
      TDynamicVector tmp(*this);
      for (int i = 0;i < sz;tmp[i] -= v[i++]);
      return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw "different size";
      }
      T tmp = 0;
      for (int i = 0;i < sz;tmp += (*this)[i] * v[i++]);
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
      if (s > MAX_MATRIX_SIZE || s <= 0)
          throw std::out_of_range("out of range");

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicMatrix& m) :TDynamicMatrix(m.sz){
      for (int i = 0; i < sz; ++i)
          pMem[i] = m.pMem[i];
  }
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;
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
      for (int i = 0;i < v.size();++i)
          istr >> v[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0;i < v.size();++i) 
          ostr << v[i]<<std::endl;
      return ostr;
  }
};

#endif
