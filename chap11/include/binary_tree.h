#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <iostream>

//结点类型
template <typename T>
struct BinaryTreeNode
{
  T element_;                                    //结点中存储的数据
  BinaryTreeNode<T>*left_child_, *right_child_;  //左子树和右子树
  BinaryTreeNode() : left_child_(NULL), right_child_(NULL)
  {
  }  //无参构造函数
  BinaryTreeNode(T element, BinaryTreeNode<T>* left_child = NULL, BinaryTreeNode<T>* right_child = NULL)
    : element_(element), left_child_(left_child), right_child_(right_child)
  {
  }  //带默认值的有参构造参数
};

//二叉树类
template <typename T>
class BinaryTree
{
public:
  BinaryTree();
  BinaryTree(const T value);
  BinaryTree(const BinaryTree<T>& s);
  bool operator==(const BinaryTree<T>& s);
  ~BinaryTree();
  void create();
  void createBinaryTreeByPreOrder();
  void createBinaryTreeByPreAndInOrder(const char* pre, const char* in);
  void createBinaryTreeByPostAndInOrder(const char* post, const char* in);
  void preOrder();
  void inOrder();
  void postOrder();
  void preOrderNoRecurve();
  void inOrderNoRecurve();
  void postOrderNoRecurve();
  void levelOrder();
  void destroy();
  int getSize();
  int getHeight();
  bool empty();
  BinaryTreeNode<T>* getRoot() const
  {
    return root_;
  }
  void printBinaryTree();

protected:
  BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current) const
  {
    // 如果没有根节点或current结点就是root结点，就没有父节点
    return (root_ == NULL || root_ == current) ? NULL : getParent(root_, current);
  }
  BinaryTreeNode<T>* getLeftChild(BinaryTreeNode<T>* current) const
  {
    return (current != NULL) ? current->left_child_ : NULL;
  }
  BinaryTreeNode<T>* getRightChild(BinaryTreeNode<T>* current) const
  {
    return (current != NULL) ? current->right_child_ : NULL;
  }
  void create(BinaryTreeNode<T>*& BT);
  void createBinaryTreeByPreOrder(BinaryTreeNode<T>*& subTree);
  void createBinaryTreeByPreAndInOrder(BinaryTreeNode<T>*& cur, const char* pre, const char* in, int n);
  void createBinaryTreeByPostAndInOrder(BinaryTreeNode<T>*& cur, const char* post, const char* in, int n);
  void preOrder(BinaryTreeNode<T>*& subTree);
  void postOrder(BinaryTreeNode<T>*& subTree);
  void inOrder(BinaryTreeNode<T>*& subTree);
  void preOrderNoRecurve(BinaryTreeNode<T>* p);
  void inOrderNoRecurve(BinaryTreeNode<T>* root_);
  void postOrderNoRecurve(BinaryTreeNode<T>* p);
  void levelOrder(BinaryTreeNode<T>* p);
  BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* subTree, BinaryTreeNode<T>* current);
  void destroy(BinaryTreeNode<T>*& subTree);
  BinaryTreeNode<T>* copy(BinaryTreeNode<T>* originNode);
  bool equal(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b);
  int getSize(BinaryTreeNode<T>* subTree)
  {
    if (subTree == NULL)  //递归结束，空树结点个数为0
    {
      return 0;
    }
    return 1 + getSize(subTree->left_child_) + getSize(subTree->right_child_);
  }
  int getHeight(BinaryTreeNode<T>* subTree);
  void printBinaryTree(BinaryTreeNode<T>* BT);

private:
  BinaryTreeNode<T>* root_;  //根节点
  T ref_element_;            //数据输入停止的标志，需要一个构造函数
};
#endif  // !_BINARY_TREE_H_