#include <../include/array_list.h>
#include "boost/array.hpp"

template <class T>
arrayList<T>::arrayList(int initialCapacity) : arrayLength_(initialCapacity)  // constructor function
{
  if (initialCapacity < 1)
  {
    std::ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    std::cout << s.str() << std::endl;
  }
  element_ = new T[arrayLength_];
  listSize_ = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList)  // copy constructor function
{
  arrayLength_ = theList.arrayLength_;
  listSize_ = theList.listSize_;
  element_ = new T[arrayLength_];
  std::copy(theList.element_, theList.element_ + listSize_, element_);
}

template <class T>
bool arrayList<T>::checkIndex(int theIndex) const
{
  if (theIndex < 0 || theIndex >= listSize_)
  {
    std::ostringstream s;
    s << "index = " << theIndex << " size = " << listSize_;
    std::cout << s.str() << std::endl;
    // throw illegalIndex(s.str());
    return false;
  }
  return true;
}

template <class T>
T& arrayList<T>::get(int theIndex) const
{
  if (!checkIndex(theIndex))
  {
    std::cerr << "index error!" << std::endl;
  }
  return element_[theIndex];
}

template <class T>
int arrayList<T>::indexOf(const T& theElement) const
{
  int theIndex;
  theIndex = (int)(std::find(element_, element_ + listSize_, theElement) - element_);

  if (theIndex == listSize_)
  {
    return -1;
  }
  else
    return theIndex;
}

template <class T>
void arrayList<T>::erase(int theIndex)
{
  if (!checkIndex(theIndex))
  {
    return;
  }
  std::copy(element_ + theIndex + 1, element_ + listSize_, element_ + theIndex);
  element_[--listSize_].~T();
}

template <class T>
void arrayList<T>::insert(int theIndex, const T& theELement)
{
  if (theIndex < 0 || theIndex > listSize_)
  {
    std::ostringstream s;
    s << "index = " << theIndex << " size = " << listSize_;
    std::cout << s.str() << std::endl;
  }
  if (listSize_ == arrayLength_)
  {
    std::cout << "The index out of range." << std::endl;
  }
  for (int i = listSize_ - 1; i >= theIndex; i--)
    element_[i + 1] = element_[i];
  element_[theIndex] = theELement;

  listSize_++;
  // return *this;
}

template <class T>
void arrayList<T>::output(std::ostream& out) const
{
  for (int i = 0; i < listSize_; i++)
    out << element_[i] << "  ";
}

template <class T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
  x.output(out);
  return out;
}

int main(int argc, const char** argv)
{
  const int array_size = 20;
  const int RAND_MAX_VALUE = 100;
  const int RAND_MIN_VALUE = 1;
  arrayList<int> array_(array_size);

  for (size_t i = 0; i < array_size; i++)
  {
    array_.insert(i, (std::rand() % (RAND_MAX_VALUE - RAND_MIN_VALUE)) + RAND_MIN_VALUE);
  }

  // test output
  std::cout << "init array is: ";
  array_.output(std::cout);
  std::cout << std::endl;
  std::cout << "init array size is: " << array_.size() << std::endl;

  printf("index of array: %d\n", array_.indexOf(24));

  array_.erase(0);

  printf("index of array: %d\n", array_.indexOf(24));

  array_.erase(6);

  printf("get value from array: %d\n", array_.get(0));

  printf("get capacity: %d\n", array_.capacity());

  printf("get size: %d\n", array_.size());

  return 0;
}
