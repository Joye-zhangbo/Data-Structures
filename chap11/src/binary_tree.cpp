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

//ʹ�ù�����������������Զ����ַ�(ref_element_)�������
template <typename T>
void BinaryTree<T>::create()
{
  create(root_);
}

//ǰ���������������(ǰ�������Ӧ��)����#��ʾ�ս��
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreOrder()
{
  createBinaryTreeByPreOrder(root_);
}

//ʹ����������������������������
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreAndInOrder(const char* pre, const char* in)
{
  int n = strlen(pre);
  createBinaryTreeByPreAndInOrder(root_, pre, in, n);
}

//ʹ�ú�������������������������
template <typename T>
void BinaryTree<T>::createBinaryTreeByPostAndInOrder(const char* post, const char* in)
{
  int n = strlen(post);
  createBinaryTreeByPostAndInOrder(root_, post, in, n);
}

//==========�������ı���==========//

//����������ݹ飩
template <typename T>
void BinaryTree<T>::preOrder()
{
  std::cout << "preorder traversal: ";
  preOrder(root_);
}

//�������(�ݹ�)
template <typename T>
void BinaryTree<T>::inOrder()
{
  std::cout << "mid-order traversal: ";
  inOrder(root_);
}

//����������ݹ飩
template <typename T>
void BinaryTree<T>::postOrder()
{
  std::cout << "post-order traversal: ";
  postOrder(root_);
}

//�������(�ǵݹ�)
template <typename T>
void BinaryTree<T>::preOrderNoRecurve()
{
  preOrderNoRecurve(root_);
}

//�������(�ǵݹ�)
template <typename T>
void BinaryTree<T>::inOrderNoRecurve()
{
  inOrderNoRecurve(root_);
}

//�������(�ǵݹ�)
template <typename T>
void BinaryTree<T>::postOrderNoRecurve()
{
  postOrderNoRecurve(root_);
}

//��α���(�ǵݹ�)
template <typename T>
void BinaryTree<T>::levelOrder()
{
  std::cout << "level-order traversal: ";
  levelOrder(root_);
}

//���ٺ���
template <typename T>
void BinaryTree<T>::destroy()
{
  destroy(root_);
}

//����������(ǰ�������Ӧ��)
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
  root_ = copy(s.getRoot());
}

//�ж����Ŷ������Ƿ����(ǰ�������Ӧ��)
template <typename T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& s)
{
  return (equal(this->getRoot(), s.getRoot()));
}

//����������Ľ��ĸ���(���������Ӧ��)
template <typename T>
int BinaryTree<T>::getSize()
{
  return getSize(root_);
}

//����������ĸ߶ȣ����������Ӧ�ã�
template <typename T>
int BinaryTree<T>::getHeight()
{
  return getHeight(root_);
}

//�ж϶������Ƿ�Ϊ��
template <typename T>
bool BinaryTree<T>::empty()
{
  return (root_ == NULL) ? true : false;
}

//�Թ�������ʽ���������(ǰ�������Ӧ��)
template <typename T>
void BinaryTree<T>::printBinaryTree()
{
  printBinaryTree(root_);
}

//ʹ�ù����������������,�����ԡ��ַ�������������,��'#'�ַ��������
template <typename T>
void BinaryTree<T>::create(BinaryTreeNode<T>*& BT)
{
  std::stack<BinaryTreeNode<T>*> s;
  BT = NULL;
  BinaryTreeNode<T>*p, *t;  // p������ס��ǰ�����Ľڵ㣬t������סջ����Ԫ��
  int k;                    // k�Ǵ������������ı��
  T ch;
  std::cin >> ch;

  while (ch != ref_element_)
  {
    switch (ch)
    {
      case '(':  //��(������
        s.push(p);
        k = 1;
        break;

      case ')':  //��)������
        s.pop();
        break;

      case ',':  //��,������
        k = 2;
        break;

      default:
        p = new BinaryTreeNode<T>(ch);  //����һ�����
        if (BT == NULL)                 //���ͷ�ڵ��ǿ�
        {
          BT = p;
        }
        else if (k == 1)  //����*t������
        {
          t = s.top();
          t->left_child_ = p;
        }
        else  //����*t���Һ���
        {
          t = s.top();
          t->right_child_ = p;
        }
    }
    std::cin >> ch;
  }
}

//����������(������֪�Ķ�������ǰ���������)��#��ʾ�ս��
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreOrder(BinaryTreeNode<T>*& subTree)
{
  T item;
  if (std::cin >> item)
  {
    if (item != ref_element_)
    {
      subTree = new BinaryTreeNode<T>(item);  //������
      if (subTree == NULL)
      {
        std::cout << "�ռ�������" << std::endl;
        // exit(1);
        return;
      }
      createBinaryTreeByPreOrder(subTree->left_child_);   //�ݹ鴴��������
      createBinaryTreeByPreOrder(subTree->right_child_);  //�ݹ鴴��������
    }
    else
    {
      subTree = NULL;
    }
  }
}

//ʹ����������������������������
template <typename T>
void BinaryTree<T>::createBinaryTreeByPreAndInOrder(BinaryTreeNode<T>*& cur, const char* pre, const char* in, int n)
{
  if (n <= 0)
  {
    cur = NULL;
    return;
  }
  int k = 0;
  while (pre[0] != in[k])  //���������ҵ�pre[0]��ֵ
  {
    k++;
  }
  cur = new BinaryTreeNode<T>(in[k]);  //�������
  createBinaryTreeByPreAndInOrder(cur->left_child_, pre + 1, in, k);
  createBinaryTreeByPreAndInOrder(cur->right_child_, pre + k + 1, in + k + 1, n - k - 1);
}
//ʹ�ú�������������������������
template <typename T>
void BinaryTree<T>::createBinaryTreeByPostAndInOrder(BinaryTreeNode<T>*& cur, const char* post, const char* in, int n)
{
  if (n == 0)
  {
    cur = NULL;
    return;
  }

  char r = *(post + n - 1);        //�����ֵ
  cur = new BinaryTreeNode<T>(r);  //���쵱ǰ���

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

//�������(�ݹ�)
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

//�������(�ݹ�)
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

//�������(�ݹ�)
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

//����������ǵݹ飩
template <typename T>
void BinaryTree<T>::preOrderNoRecurve(BinaryTreeNode<T>* p)
{
  std::stack<BinaryTreeNode<T>*> stack_binary;
  BinaryTreeNode<T>* t;
  stack_binary.push(p);          //���ڵ��ջ
  while (!stack_binary.empty())  //��ջ��Ϊ��
  {
    t = stack_binary.top();  // p�ȼ�סջ��Ԫ�أ�Ȼ��ջ����ջ
    stack_binary.pop();
    std::cout << t->element_ << " ";  //����Ԫ��
    if (t->right_child_ != NULL)      //�Һ��Ӳ�Ϊ�գ��Һ��ӽ�ջ
    {
      stack_binary.push(t->right_child_);
    }
    if (t->left_child_ != NULL)  //���Ӳ�Ϊ�գ����ӽ�ջ
    {
      stack_binary.push(t->left_child_);
    }
  }
}

//�������(�ǵݹ�)
template <typename T>
void BinaryTree<T>::inOrderNoRecurve(BinaryTreeNode<T>* root_)
{
  if (root_ == NULL)
    return;
  std::stack<BinaryTreeNode<T>*> s;
  s.push(root_);
  while (!s.empty())
  {
    while (s.top()->left_child_ != NULL)  //������������ջ
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

//�������(�ǵݹ�)
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
      //��Ҷ�ӽ�� || û���ҽ��
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

//��α���(�ǵݹ�)
template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* p)
{
  std::queue<BinaryTreeNode<T>*> Q;
  Q.push(p);  //���ڵ����
  BinaryTreeNode<T>* t;
  while (!Q.empty())
  {
    t = Q.front();  // t�ȼ�ס��ͷ,�ٽ���ͷ����
    Q.pop();
    std::cout << t->element_ << " ";  //���ʶ�ͷԪ�ص�����

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

//�ӽ��subTree��ʼ���������current�ĸ��ڵ�,�ҵ����ظ��ڵ�ĵ�ַ���Ҳ�������NULL
template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::getParent(BinaryTreeNode<T>* subTree, BinaryTreeNode<T>* current)
{
  if (subTree == NULL)
  {
    return NULL;
  }
  if (subTree->left_child_ == current || subTree->right_child_ == current)  //����ҵ������ظ��ڵ�subTree
  {
    return subTree;
  }
  BinaryTreeNode<T>* p;
  if ((p = getParent(subTree->left_child_, current)) != NULL)  //�ݹ���������������
  {
    return p;
  }
  else
  {
    return getParent(subTree->right_child_, current);  //�ݹ�������������
  }
}

//������������
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

//���ƶ���������������һ��ָ�룬����һ����originNodeΪ�����ƵĶ������ĸ���
template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::copy(BinaryTreeNode<T>* originNode)
{
  if (originNode == NULL)
  {
    return NULL;
  }
  BinaryTreeNode<T>* temp = new BinaryTreeNode<T>;  //���������
  temp->element_ = originNode->element_;
  temp->left_child_ = copy(originNode->left_child_);
  temp->right_child_ = copy(originNode->right_child_);
  return temp;
}

//�ж����Ŷ������Ƿ����
template <typename T>
bool BinaryTree<T>::equal(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b)
{
  if (a == NULL && b == NULL)  //���߶�Ϊ��
  {
    return true;
  }
  if (a != NULL && b != NULL && a->element_ == b->element_ && equal(a->left_child_, b->left_child_) &&
      equal(a->right_child_, b->right_child_))  //���߶���Ϊ�գ������ߵĽ��������ȣ������ߵ����������Ľ�㶼���
  {
    return true;
  }
  return false;
}

//�����������subTreeΪ���ĸ߶�
template <typename T>
int BinaryTree<T>::getHeight(BinaryTreeNode<T>* subTree)
{
  if (subTree == NULL)  //�ݹ�����������߶�Ϊ0
  {
    return 0;
  }
  int i = getHeight(subTree->left_child_);
  int j = getHeight(subTree->right_child_);
  return i < j ? j + 1 : i + 1;
}

//�Թ�������ʽ���������
template <typename T>
void BinaryTree<T>::printBinaryTree(BinaryTreeNode<T>* BT)
{
  if (BT != NULL)  //��Ϊ��ʱ�����ݹ�
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
