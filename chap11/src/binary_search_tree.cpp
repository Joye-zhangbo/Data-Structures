#include <../include/binary_search_tree.h>
#include <iostream>
#include <cstdio>
#include <algorithm>

template <class K, class V>
BinarySearchTree<K, V>::BinarySearchTree() : root_(NULL)
{
}

// BST find
template <class K, class V>
BinarySearchTreeNode<K, V>* BinarySearchTree<K, V>::find(const K& key)
{
  return find(root_, key);
}

template <class K, class V>
BinarySearchTreeNode<K, V>* BinarySearchTree<K, V>::find(BinarySearchTreeNode<K, V>* root, const K& key)
{
  if (root == NULL)
  {
    return NULL;
  }

  if (root->key_ > key)  // find in leftchild
  {
    return find(root->left_child_, key);
  }
  else if (root->key_ < key)  // find in rightchild
  {
    return find(root->right_child_, key);
  }
  else
  {
    return root;
  }
}

// BST insert
// find the node and insert
template <class K, class V>
bool BinarySearchTree<K, V>::insert(const K& key, const V& value)
{
  return insert(root_, key, value);
}

template <class K, class V>
bool BinarySearchTree<K, V>::insert(BinarySearchTreeNode<K, V>*& root, const K& key, const V& value)
{
  if (root == NULL)
  {
    root = new BinarySearchTreeNode<K, V>(key, value);
    return true;
  }

  if (root->key_ > key)
  {
    return insert(root->left_child_, key, value);
  }
  else if (root->key_ < key)
  {
    return insert(root->right_child_, key, value);
  }
  else
  {
    return false;
  }
}

// BST erase
template <class K, class V>
bool BinarySearchTree<K, V>::erase(const K& key)
{
  return erase(root_, key);
}

template <class K, class V>
bool BinarySearchTree<K, V>::erase(BinarySearchTreeNode<K, V>*& root, const K& key)
{
  // There is no such node
  if (root == NULL)
  {
    return false;
  }
  // only one node
  if (root->left_child_ == NULL && root->right_child_ == NULL)
  {
    if (root->key_ == key)
    {
      delete root;
      root = NULL;
      return true;
    }
    else
    {
      return false;
    }
  }

  if (root->key_ > key)
  {
    erase(root->left_child_, key);
  }
  else if (root->key_ < key)
  {
    erase(root->right_child_, key);
  }
  else
  {
    BinarySearchTreeNode<K, V>* del = NULL;

    if (root->left_child_ == NULL)  // just has rightchild
    {
      del = root;
      root = root->right_child_;
      delete del;
      del = NULL;
      return true;
    }
    else if (root->right_child_ == NULL)  // just has leftchild
    {
      del = root;
      root = root->left_child_;
      delete del;
      del = NULL;
      return true;
    }
    else
    {
      BinarySearchTreeNode<K, V>* RightFirst = root->right_child_;
      // find the first In order node
      while (RightFirst->left_child_)
      {
        RightFirst = RightFirst->left_child_;
      }

      // swap RightFirst node with cur node
      std::swap(root->key_, RightFirst->key_);
      std::swap(root->value_, RightFirst->value_);

      erase(root->right_child_, key);
      return true;
    }
  }
}

// BST print In Order
template <class K, class V>
void BinarySearchTree<K, V>::output()
{
  output(root_);
  std::cout << std::endl;
}

template <class K, class V>
void BinarySearchTree<K, V>::output(BinarySearchTreeNode<K, V>* root)
{
  if (root == NULL)
  {
    return;
  }

  output(root->left_child_);
  std::cout << root->key_ << " ";
  output(root->right_child_);
}

//计算二叉数以subTree为根的高度
template <class K, class V>
int BinarySearchTree<K, V>::getHeight(BinarySearchTreeNode<K, V>* root)
{
  if (root == NULL)  //递归结束，空树高度为0
  {
    return 0;
  }
  int i = getHeight(root->left_child_);
  int j = getHeight(root->right_child_);
  return i < j ? j + 1 : i + 1;
}

template <class K, class V>
int BinarySearchTree<K, V>::getHeight()
{
  return getHeight(root_);
}

int main()
{
  const int array_size = 20;
  const int RAND_MAX_VALUE = 100;
  const int RAND_MIN_VALUE = 1;
  BinarySearchTree<int, int> tree_list_;

  std::cout << "origin data: " << std::endl;
  for (size_t i = 0; i < array_size; i++)
  {
    int the_element = (std::rand() % (RAND_MAX_VALUE - RAND_MIN_VALUE)) + RAND_MIN_VALUE;
    std::cout << the_element << " ";
    tree_list_.insert(the_element, 1);
  }
  std::cout << std::endl;

  //二叉搜索树按中序输出是有序的
  std::cout << "binary search tree: " << std::endl;
  tree_list_.output();

  //测试查找
  std::cout << "search for specific the element : " << std::endl;
  std::cout << tree_list_.find(5)->key_ << std::endl;
  std::cout << tree_list_.find(5)->value_ << std::endl;

  std::cout << "binary tree after removing some elements : " << std::endl;

  std::cout << "Height: " << tree_list_.getHeight() << std::endl;

  //测试删除
  tree_list_.erase(4);
  tree_list_.erase(6);
  tree_list_.erase(3);
  tree_list_.erase(1);
  tree_list_.erase(2);
  tree_list_.erase(29);

  //再次打印删除后的结果
  tree_list_.output();

  std::cout << "Height: " << tree_list_.getHeight() << std::endl;

  // the root element
  std::cout << "the root element is: " << std::endl;
  std::cout << (tree_list_.getRoot())->key_ << std::endl;

  return 0;
}