#include <../include/chain_list.h>
#include "boost/array.hpp"

template <class T>
ChainList<T>::ChainList(int initialCapacity)  // constructor function
{
  if (initialCapacity < 1)
  {
    std::ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    std::cout << s.str() << std::endl;
  }
  first_node_ = NULL;
  list_size_ = 0;
}

template <class T>
ChainList<T>::ChainList(const ChainList<T>& theList)  // copy constructor function
{
  list_size_ = theList.list_size_;
  if (list_size_ == 0)
  {
    first_node_ = NULL;
    return;
  }
  ChainNode<T>* source_node = theList.first_node_;
  first_node_ = new ChainList<T>(source_node->element);
  source_node = source_node->next;
  ChainNode<T>* target_node = first_node_;
  while (source_node != NULL)
  {
    target_node->next = new ChainNode<T>(source_node->element);
    target_node = target_node->next;
    source_node = source_node->next;
  }
  target_node->next = NULL;
}

template <class T>
ChainList<T>& ChainList<T>::operator=(const ChainList<T>& chain_node)
{
  ChainNode<T>* new_first_node = new ChainNode<T>(chain_node->first_node_);
  delete first_node_;
  first_node_ = new_first_node;
  this->list_size_ = chain_node.list_size_;
  return *this;
}

template <class T>
ChainList<T>::~ChainList()
{
  while (first_node_ != NULL)
  {
    ChainNode<T>* next_node = first_node_->next;
    delete first_node_;
    first_node_ = next_node;
  }
}

template <class T>
bool ChainList<T>::checkIndex(int theIndex) const
{
  if (theIndex < 0 || theIndex >= list_size_)
  {
    std::ostringstream s;
    s << "index = " << theIndex << " size = " << list_size_;
    std::cout << s.str() << std::endl;
    // throw illegalIndex(s.str());
    return false;
  }
  return true;
}

template <class T>
T& ChainList<T>::get(int theIndex) const
{
  if (!checkIndex(theIndex))
  {
    std::cerr << "index error!" << std::endl;
  }
  ChainNode<T>* current_node = first_node_;
  for (size_t i = 0; i < theIndex; i++)
  {
    current_node = current_node->next;
  }
  return current_node->element;
}

template <class T>
int ChainList<T>::indexOf(const T& theElement) const
{
  ChainNode<T>* current_node = first_node_;
  int index = 0;
  while (current_node != NULL && current_node->element != theElement)
  {
    current_node = current_node->next;
    index++;
  }
  if (current_node == NULL)
  {
    return -1;
  }
  else
  {
    return index;
  }
}

template <class T>
void ChainList<T>::erase(int theIndex)
{
  if (!checkIndex(theIndex))
  {
    return;
  }
  ChainNode<T>* delete_node;
  if (theIndex == 0)
  {
    delete_node = first_node_;
    first_node_ = first_node_->next;
  }
  else
  {
    ChainNode<T>* ptr = first_node_;
    for (int i = 0; i < theIndex; i++)
    {
      ptr = ptr->next;
    }
    delete_node = ptr->next->next;
    ptr->next = ptr->next->next;
  }
  list_size_--;
  delete delete_node;
}

template <class T>
void ChainList<T>::insert(int theIndex, const T& theElement)
{
  if (theIndex < 0 || theIndex > list_size_)
  {
    std::ostringstream s;
    s << "index = " << theIndex << " size = " << list_size_;
    std::cout << s.str() << std::endl;
  }
  if (theIndex == 0)
  {
    first_node_ = new ChainNode<T>(theElement, first_node_);
  }
  else
  {
    ChainNode<T>* ptr = first_node_;
    for (int i = 0; i < theIndex - 1; i++)
    {
      ptr = ptr->next;
    }
    ptr->next = new ChainNode<T>(theElement, ptr->next);
  }

  list_size_++;
}

template <class T>
void ChainList<T>::output(std::ostream& out) const
{
  for (ChainNode<T>* current_node = first_node_; current_node != NULL; current_node = current_node->next)
    out << current_node->element << "  ";
}

template <class T>
std::ostream& operator<<(std::ostream& out, const ChainList<T>& x)
{
  x.output(out);
  return out;
}

int main(int argc, const char** argv)
{
  const int array_size = 80;
  const int RAND_MAX_VALUE = 100;
  const int RAND_MIN_VALUE = 1;
  ChainList<int> array_(array_size);

  for (size_t i = 0; i < array_size; i++)
  {
    array_.insert(i, (std::rand() % (RAND_MAX_VALUE - RAND_MIN_VALUE)) + RAND_MIN_VALUE);
  }

  // test output
  std::cout << "init array is: ";
  array_.output(std::cout);
  std::cout << std::endl;
  std::cout << "init array size is: " << array_.size() << std::endl;

  printf("index of array: %d\n", array_.indexOf(42));

  array_.erase(0);

  printf("index of array: %d\n", array_.indexOf(42));

  array_.erase(6);

  printf("get value from array: %d\n", array_.get(37));

  printf("get size: %d\n", array_.size());

  // getchar();
  return 0;
}
