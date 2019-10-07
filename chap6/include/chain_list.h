#ifndef __CHAIN_LIST_H
#define __CHAIN_LIST_H

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

template <typename T>
struct ChainNode
{
  T element;
  ChainNode<T>* next;

  ChainNode()
  {
  }
  ChainNode(const T& element)
  {
    this->element = element;
  }
  ChainNode(const T& element, ChainNode<T>* next)
  {
    this->element = element;
    this->next = next;
  }
};

template <class T>
class ChainList : public linearList<T>
{
public:
  ChainList(int initialCapacity = 10);
  ChainList(const ChainList<T>&);
  ChainList<T>& operator=(const ChainList<T>& chain_node);
  ~ChainList();

  // ADT
  bool empty() const
  {
    return list_size_ == 0;
  }
  int size() const
  {
    return list_size_;
  }
  T& get(int theIndex) const;
  int indexOf(const T& theElement) const;
  void erase(int theIndex);
  void insert(int theIndex, const T& theELement);
  void output(std::ostream& out) const;

private:
  bool checkIndex(int theIndex) const;
  int list_size_;
  ChainNode<T>* first_node_;
};
#endif  //
