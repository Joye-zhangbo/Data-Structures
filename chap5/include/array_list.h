#ifndef __ARRAY_LIST_H
#define __ARRAY_LIST_H

#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>
#include <ostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <cstring>

template <class T>
class linearList
{
public:
  virtual ~linearList(){};
  virtual bool empty() const = 0;
  virtual int size() const = 0;
  virtual T& get(int theIndex) const = 0;
  virtual int indexOf(const T& theElement) const = 0;
  virtual void erase(int theIndex) = 0;
  virtual void insert(int theIndex, const T& theELement) = 0;
  virtual void output(std::ostream& out) const = 0;
};

template <class T>
class arrayList : public linearList<T>
{
public:
  arrayList(int initialCapacity);
  arrayList(const arrayList<T>&);
  ~arrayList()
  {
    delete[] element_;
  }

  // ADT
  bool empty() const
  {
    return listSize_ == 0;
  }
  int size() const
  {
    return listSize_;
  }
  T& get(int theIndex) const;
  int indexOf(const T& theElement) const;
  void erase(int theIndex);
  void insert(int theIndex, const T& theELement);
  void output(std::ostream& out) const;
  int capacity() const
  {
    return arrayLength_;
  }

private:
  bool checkIndex(int theIndex) const;
  int listSize_;
  int arrayLength_;
  T* element_;
};
#endif  //
