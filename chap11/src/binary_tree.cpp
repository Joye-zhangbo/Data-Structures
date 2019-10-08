#include <../include/binary_tree.h>
#include <string.h>
#include <cstdio>
#include <stack>
#include <queue>

template <typename T>
BinaryTree<T>::BinaryTree() : root_(NULL)
{
}

template <typename T>
BinaryTree<T>::BinaryTree(const T value) : ref_element_(value), root_(NULL)
{
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
  destroy(root_);
}

//使用广义表创建二叉树，以自定义字符(ref_element_)代表结束
template <typename T>
void BinaryTree<T>::create()
{
  create(root_);
}

//前序遍历创建二叉树(前序遍历的应用)，用#表示空结点
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreOrder()
{
  createBinaryTreeByPreOrder(root_);
}

//使用先序遍历和中序遍历创建二叉树
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreAndInOrder(const char* pre, const char* in)
{
  int n = strlen(pre);
  createBinaryTreeByPreAndInOrder(root_, pre, in, n);
}

//使用后序遍历和中序遍历创建二叉树
template <typename T>
void BinaryTree<T>::createBinaryTreeByPostAndInOrder(const char* post, const char* in)
{
  int n = strlen(post);
  createBinaryTreeByPostAndInOrder(root_, post, in, n);
}

//==========二叉树的遍历==========//

//先序遍历（递归）
template <typename T>
void BinaryTree<T>::preOrder()
{
  std::cout << "preorder traversal: ";
  preOrder(root_);
}

//中序遍历(递归)
template <typename T>
void BinaryTree<T>::inOrder()
{
  std::cout << "mid-order traversal: ";
  inOrder(root_);
}

//后序遍历（递归）
template <typename T>
void BinaryTree<T>::postOrder()
{
  std::cout << "post-order traversal: ";
  postOrder(root_);
}

//先序遍历(非递归)
template <typename T>
void BinaryTree<T>::preOrderNoRecurve()
{
  preOrderNoRecurve(root_);
}

//中序遍历(非递归)
template <typename T>
void BinaryTree<T>::inOrderNoRecurve()
{
  inOrderNoRecurve(root_);
}

//后序遍历(非递归)
template <typename T>
void BinaryTree<T>::postOrderNoRecurve()
{
  postOrderNoRecurve(root_);
}

//层次遍历(非递归)
template <typename T>
void BinaryTree<T>::levelOrder()
{
  std::cout << "level-order traversal: ";
  levelOrder(root_);
}

//销毁函数
template <typename T>
void BinaryTree<T>::destroy()
{
  destroy(root_);
}

//拷贝二叉树(前序遍历的应用)
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
  root_ = copy(s.getRoot());
}

//判断两颗二叉树是否相等(前序遍历的应用)
template <typename T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& s)
{
  return (equal(this->getRoot(), s.getRoot()));
}

//计算二叉树的结点的个数(后序遍历的应用)
template <typename T>
int BinaryTree<T>::getSize()
{
  return getSize(root_);
}

//计算二叉树的高度（后序遍历的应用）
template <typename T>
int BinaryTree<T>::getHeight()
{
  return getHeight(root_);
}

//判断二叉树是否为空
template <typename T>
bool BinaryTree<T>::empty()
{
  return (root_ == NULL) ? true : false;
}

//以广义表的形式输出二叉树(前序遍历的应用)
template <typename T>
void BinaryTree<T>::printBinaryTree()
{
  printBinaryTree(root_);
}

//使用广义表创建二叉树函数,这里以“字符”创建二叉树,以'#'字符代表结束
template <typename T>
void BinaryTree<T>::create(BinaryTreeNode<T>*& BT)
{
  std::stack<BinaryTreeNode<T>*> s;
  BT = NULL;
  BinaryTreeNode<T>*p, *t;  // p用来记住当前创建的节点，t用来记住栈顶的元素
  int k;                    // k是处理左、右子树的标记
  T ch;
  std::cin >> ch;

  while (ch != ref_element_)
  {
    switch (ch)
    {
      case '(':  //对(做处理
        s.push(p);
        k = 1;
        break;

      case ')':  //对)做处理
        s.pop();
        break;

      case ',':  //对,做处理
        k = 2;
        break;

      default:
        p = new BinaryTreeNode<T>(ch);  //构造一个结点
        if (BT == NULL)                 //如果头节点是空
        {
          BT = p;
        }
        else if (k == 1)  //链入*t的左孩子
        {
          t = s.top();
          t->left_child_ = p;
        }
        else  //链入*t的右孩子
        {
          t = s.top();
          t->right_child_ = p;
        }
    }
    std::cin >> ch;
  }
}

//创建二叉树(利用已知的二叉树的前序遍历创建)用#表示空结点
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreOrder(BinaryTreeNode<T>*& subTree)
{
  T item;
  if (std::cin >> item)
  {
    if (item != ref_element_)
    {
      subTree = new BinaryTreeNode<T>(item);  //构造结点
      if (subTree == NULL)
      {
        std::cout << "空间分配错误！" << std::endl;
        // exit(1);
        return;
      }
      createBinaryTreeByPreOrder(subTree->left_child_);   //递归创建左子树
      createBinaryTreeByPreOrder(subTree->right_child_);  //递归创建右子树
    }
    else
    {
      subTree = NULL;
    }
  }
}

//使用先序遍历和中序遍历创建二叉树
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreAndInOrder(BinaryTreeNode<T>*& cur, const char* pre, const char* in, int n)
{
  if (n <= 0)
  {
    cur = NULL;
    return;
  }
  int k = 0;
  while (pre[0] != in[k])  //再中序中找到pre[0]的值
  {
    k++;
  }
  cur = new BinaryTreeNode<T>(in[k]);  //创建结点
  createBinaryTreeByPreAndInOrder(cur->left_child_, pre + 1, in, k);
  createBinaryTreeByPreAndInOrder(cur->right_child_, pre + k + 1, in + k + 1, n - k - 1);
}
//使用后序遍历和中序遍历创建二叉树
template <typename T>
void BinaryTree<T>::createBinaryTreeByPostAndInOrder(BinaryTreeNode<T>*& cur, const char* post, const char* in, int n)
{
  if (n == 0)
  {
    cur = NULL;
    return;
  }

  char r = *(post + n - 1);        //根结点值
  cur = new BinaryTreeNode<T>(r);  //构造当前结点

  int k = 0;
  const char* p = in;
  while (*p != r)
  {
    k++;
    p++;
  }
  createBinaryTreeByPostAndInOrder(cur->left_child_, post, in, k);
  createBinaryTreeByPostAndInOrder(cur->right_child_, post + k, p + 1, n - k - 1);
}

//先序遍历(递归)
template <typename T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T>*& subTree)
{
  if (subTree != NULL)
  {
    std::cout << subTree->element_ << " ";
    preOrder(subTree->left_child_);
    preOrder(subTree->right_child_);
  }
}

//中序遍历(递归)
template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>*& subTree)
{
  if (subTree != NULL)
  {
    inOrder(subTree->left_child_);
    std::cout << subTree->element_ << " ";
    inOrder(subTree->right_child_);
  }
}

//后序遍历(递归)
template <typename T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T>*& subTree)
{
  if (subTree != NULL)
  {
    postOrder(subTree->left_child_);
    postOrder(subTree->right_child_);
    std::cout << subTree->element_ << " ";
  }
}

//先序遍历（非递归）
template <typename T>
void BinaryTree<T>::preOrderNoRecurve(BinaryTreeNode<T>* p)
{
  std::stack<BinaryTreeNode<T>*> stack_binary;
  BinaryTreeNode<T>* t;
  stack_binary.push(p);          //根节点进栈
  while (!stack_binary.empty())  //当栈不为空
  {
    t = stack_binary.top();  // p先记住栈顶元素，然后栈顶出栈
    stack_binary.pop();
    std::cout << t->element_ << " ";  //访问元素
    if (t->right_child_ != NULL)      //右孩子不为空，右孩子进栈
    {
      stack_binary.push(t->right_child_);
    }
    if (t->left_child_ != NULL)  //左孩子不为空，左孩子进栈
    {
      stack_binary.push(t->left_child_);
    }
  }
}

//中序遍历(非递归)
template <typename T>
void BinaryTree<T>::inOrderNoRecurve(BinaryTreeNode<T>* root_)
{
  if (root_ == NULL)
    return;
  std::stack<BinaryTreeNode<T>*> s;
  s.push(root_);
  while (!s.empty())
  {
    while (s.top()->left_child_ != NULL)  //将左结点依次入栈
    {
      s.push(s.top()->left_child_);
    }
    while (!s.empty())
    {
      BinaryTreeNode<T>* cur = s.top();
      std::cout << cur->element_ << " ";
      s.pop();
      if (cur->right_child_ != NULL)
      {
        s.push(cur->right_child_);
        break;
      }
    }
  }
}

//后序遍历(非递归)
template <typename T>
void BinaryTree<T>::postOrderNoRecurve(BinaryTreeNode<T>* p)
{
  if (root_ == NULL)
    return;
  std::stack<BinaryTreeNode<T>*> s;
  s.push(p);
  BinaryTreeNode<T>* lastPop = NULL;
  while (!s.empty())
  {
    while (s.top()->left_child_ != NULL)
      s.push(s.top()->left_child_);
    while (!s.empty())
    {
      //右叶子结点 || 没有右结点
      if (lastPop == s.top()->right_child_ || s.top()->right_child_ == NULL)
      {
        std::cout << s.top()->element_ << " ";
        lastPop = s.top();
        s.pop();
      }
      else if (s.top()->right_child_ != NULL)
      {
        s.push(s.top()->right_child_);
        break;
      }
    }
  }
}

//层次遍历(非递归)
template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* p)
{
  std::queue<BinaryTreeNode<T>*> Q;
  Q.push(p);  //根节点进队
  BinaryTreeNode<T>* t;
  while (!Q.empty())
  {
    t = Q.front();  // t先记住队头,再将队头出队
    Q.pop();
    std::cout << t->element_ << " ";  //访问队头元素的数据

    if (t->left_child_ != NULL)
    {
      Q.push(t->left_child_);
    }

    if (t->right_child_ != NULL)
    {
      Q.push(t->right_child_);
    }
  }
}

//从结点subTree开始，搜索结点current的父节点,找到返回父节点的地址，找不到返回NULL
template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::getParent(BinaryTreeNode<T>* subTree, BinaryTreeNode<T>* current)
{
  if (subTree == NULL)
  {
    return NULL;
  }
  if (subTree->left_child_ == current || subTree->right_child_ == current)  //如果找到，返回父节点subTree
  {
    return subTree;
  }
  BinaryTreeNode<T>* p;
  if ((p = getParent(subTree->left_child_, current)) != NULL)  //递归在左子树中搜索
  {
    return p;
  }
  else
  {
    return getParent(subTree->right_child_, current);  //递归右子树中搜索
  }
}

//二叉树的销毁
template <typename T>
void BinaryTree<T>::destroy(BinaryTreeNode<T>*& subTree)
{
  if (subTree != NULL)
  {
    destroy(subTree->left_child_);
    destroy(subTree->right_child_);
    delete subTree;
    subTree = NULL;
  }
}

//复制二叉树函数，返回一个指针，给出一个以originNode为根复制的二叉树的副本
template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::copy(BinaryTreeNode<T>* originNode)
{
  if (originNode == NULL)
  {
    return NULL;
  }
  BinaryTreeNode<T>* temp = new BinaryTreeNode<T>;  //创建根结点
  temp->element_ = originNode->element_;
  temp->left_child_ = copy(originNode->left_child_);
  temp->right_child_ = copy(originNode->right_child_);
  return temp;
}

//判断两颗二叉树是否相等
template <typename T>
bool BinaryTree<T>::equal(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b)
{
  if (a == NULL && b == NULL)  //两者都为空
  {
    return true;
  }
  if (a != NULL && b != NULL && a->element_ == b->element_ && equal(a->left_child_, b->left_child_) &&
      equal(a->right_child_, b->right_child_))  //两者都不为空，且两者的结点数据相等，且两者的左右子树的结点都相等
  {
    return true;
  }
  return false;
}

//计算二叉数以subTree为根的高度
template <typename T>
int BinaryTree<T>::getHeight(BinaryTreeNode<T>* subTree)
{
  if (subTree == NULL)  //递归结束，空树高度为0
  {
    return 0;
  }
  int i = getHeight(subTree->left_child_);
  int j = getHeight(subTree->right_child_);
  return i < j ? j + 1 : i + 1;
}

//以广义表的形式输出二叉树
template <typename T>
void BinaryTree<T>::printBinaryTree(BinaryTreeNode<T>* BT)
{
  if (BT != NULL)  //树为空时结束递归
  {
    std::cout << BT->element_;
    if (BT->left_child_ != NULL || BT->right_child_ != NULL)
    {
      std::cout << '(';
      if (BT->left_child_ != NULL)
      {
        printBinaryTree(BT->left_child_);
      }
      std::cout << ',';
      if (BT->right_child_ != NULL)
      {
        printBinaryTree(BT->right_child_);
      }
      std::cout << ')';
    }
  }
}

int main(int argc, char** argv)
{
  BinaryTree<char> binary_tree_('#');
  std::cout << "Please input character: ";
  binary_tree_.createBinaryTreeByPreOrder();  // ABC#D##EF#G#HI###J###
  binary_tree_.printBinaryTree();
  std::cout << std::endl;
  std::cout << "Size: " << binary_tree_.getSize() << std::endl;
  std::cout << "Height: " << binary_tree_.getHeight() << std::endl;
  // pre order
  binary_tree_.preOrder();
  std::cout << std::endl;
  // in order
  binary_tree_.inOrder();
  std::cout << std::endl;
  // post order
  binary_tree_.postOrder();
  std::cout << std::endl;
  // level order
  binary_tree_.levelOrder();
  std::cout << std::endl;
  // the root element
  std::cout << "The root element is: " << (binary_tree_.getRoot())->element_ << std::endl;

  // is empty
  std::cout << "Is the tree empty? ---> " << binary_tree_.empty() << std::endl;
  // destory
  binary_tree_.destroy();
  // is empty
  std::cout << "Is the tree empty? ---> " << binary_tree_.empty() << std::endl;

  int i = 0;
  while (1)
  {
    std::cout << "loop count: " << i++ << std::endl;
    if (i > 1000)
      i = 0;
  }

  return 0;
}
