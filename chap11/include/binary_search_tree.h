#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include <ostream>
#include <cstdio>

// the struct of BST
// K: the type of key
// V: the type of value
// K and V need overload operators < and > and ==
template <class K, class V>
struct BinarySearchTreeNode
{
  BinarySearchTreeNode* left_child_;   // left child;
  BinarySearchTreeNode* right_child_;  // right child;
  K key_;                              // key
  V value_;                            // value

  BinarySearchTreeNode(const K& key, const V& value)  // init
    : left_child_(NULL), right_child_(NULL), key_(key), value_(value)
  {
  }
};

template <class K, class V>
class BinarySearchTree
{
public:
  BinarySearchTree();
  ~BinarySearchTree() = default;
  BinarySearchTreeNode<K, V>* find(const K& key);
  bool insert(const K& key, const V& value);
  bool erase(const K& key);
  void output();
  BinarySearchTreeNode<K, V>* getRoot()
  {
    return root_;
  }
  int getHeight();

private:
  BinarySearchTreeNode<K, V>* find(BinarySearchTreeNode<K, V>* root, const K& key);
  bool insert(BinarySearchTreeNode<K, V>*& root, const K& key, const V& value);
  bool erase(BinarySearchTreeNode<K, V>*& root, const K& key);
  void output(BinarySearchTreeNode<K, V>* root);
  int getHeight(BinarySearchTreeNode<K, V>* root);
  BinarySearchTreeNode<K, V>* root_;
};

#endif  // !__BINARY_SEARCH_TREE_H_