#pragma once
#include<iostream>
using namespace std;

template<class K, class V>
struct BSTNode2
{
	BSTNode2()
	{
		Lchild = NULL;
		Rchild = NULL;
		_parent = NULL;
	}
	BSTNode2(K k, V v)
	{
		_key = k;
		_value = v;
		Lchild = NULL;
		Rchild = NULL;
		_parent = NULL;
	}

	K _key;
	V  _value;
	BSTNode2<K, V>* Lchild;
	BSTNode2<K, V>* Rchild;
	BSTNode2<K, V>* _parent;
};

template<class K,class V>
struct BSTIterator
{
	typedef BSTNode2<K, V>* PNode;
	typedef BSTIterator<K, V> Iter;
public:
	BSTIterator()
		:_pNode(NULL)
		, _pHead(NULL)
	{ }
	BSTIterator(PNode pPNode)
		:_pNode(pPNode)
		,_pHead(pPNode)
	{ }
	BSTIterator(PNode pPNode, PNode Head)
		:_pNode(pPNode)
		, _pHead(Head)
	{ }
	BSTIterator(Iter& s)
		:_pNode(s._pNode)
		, _pHead(s._pHead)
	{ }

	Iter& operator++()            //前置++
	{
		Increase();
		return *this;
	}
	Iter operator++(int)           //后置++
	{
		Iter temp(*this);
		Increase();
		return temp;
	}
	Iter& operator--()
	{
		Decrease();
		return *this;
	}
	Iter operator--(int)
	{
		Iter temp(*this);
		Decrease();
		return temp;
	}
	bool operator!=(Iter& s)
	{
		return  _pNode != s._pNode;
	}
	bool operator==(Iter& s)
	{
		return _pNode == s._pNode;
	}
	K& operator*()
	{
		return _pNode->_key;
	}
	PNode operator->()
	{
		return _pNode;
	}
	void Increase()
	{
		if (_pNode->Rchild)
		{
			_pNode = _pNode->Rchild;
			while (_pNode->Lchild)
				_pNode = _pNode->Lchild;
		}
		else
		{
			PNode pParent = _pNode->_parent;
			while (_pNode == pParent->Rchild)
			{
				_pNode = _pNode->_parent;
				pParent = _pNode->_parent;
			}
			// _pNode在pRoot且pRoot没有右子树
			if (_pNode->Rchild != pParent)
				_pNode = pParent;
		}
	}
	void Decrease()
	{
		if (_pNode == _pHead)
			_pNode = _pHead->Rchild;
		else if (_pNode->Lchild)      
		{
			//到做子树中找最大的节点
			_pNode = _pNode->Lchild;
			while (_pNode->Rchild)
				_pNode = _pNode->Rchild;
		}
		else
		{
			PNode pParent = _pNode->_parent;
			while (_pNode == pParent->Lchild)
			{
				_pNode = _pNode->_parent;
				pParent = _pNode->_parent;
			}
				_pNode = pParent;
		}
	}

private:
	PNode _pNode;
	PNode _pHead;
};


template<class K, class V>
class SearchTree
{
	typedef  BSTNode2<K, V> Node;
	typedef  BSTNode2<K, V>* pNode;
	typedef  BSTIterator<K, V> Iterator;
public:
	SearchTree()          //无参构造
	{
		Root = NULL;
		_Head = new Node;
		_Head->_parent = Root;
	}
	SearchTree(K* arr,int size)          //有参构造
	{
		_Head = new Node;
		for (int i = 0; i < size;i++)
		{
			Insert2(arr[i], i);
		}
		_Head->_parent = Root;
		_Head->Lchild = MinNode();
		_Head->Rchild = MaxNode();
		Root->_parent = _Head;
	}
	Node* MinNode()          //序号最小的点
	{
		Node*cur = Root;
		while (cur->Lchild)
		{
			cur = cur->Lchild;
		}
		return cur;
	}
	Node* MaxNode()       //序号最大的点
	{
		Node* cur = Root;
		while (cur->Rchild)
		{
			cur = cur->Rchild;
		}
		return cur;
	}

	bool Insert1(K k, V v)           //插入元素 (循环法)1
	{
		bool ret=_Insert1(Root, k, v);
		_Head->_parent = Root;
		_Head->Lchild = MinNode();
		_Head->Rchild = MaxNode();
		Root->_parent = _Head;
		return ret;
	}
	bool Insert2(K k, V v)    //插入节点（递归法）2
	{
		pNode pre = NULL;
		bool ret=_Insert2(Root, pre, k, v);
		_Head->_parent = Root;
		_Head->Lchild = MinNode();
		_Head->Rchild = MaxNode();
		Root->_parent = _Head;
		return ret;
	}

	bool Delete1(int key)         //删除节点（循环法） 1
	{
		return _Delete1(Root, key);
	}

	bool Delete2(K key)       //删除节点（递归法） 2
	{
		return _Delete2(Root, key);
	}
	void InOrder()       //中序遍历
	{
		_InOrder(Root);
	}
	pNode BSTswitchList()     //转换为双向链表
	{
		return _BSTswitchList(Root);
	}
	///////////////////////////////////////////////////////////////
	//迭代器
	Iterator Begin()
	{
		return _Head->Lchild;
	}
	Iterator End()
	{
		return _Head;
	}
	void Display()
	{
		/*Iterator It=Begin();
		while (It != End())
		{
			cout << It->_key << ",";
			It++;
		}*/
		Iterator It = End();
		while (It != Begin())
		{
			It--;
			cout << It->_key << ",";
		}
	}

private:
	///////////////////////////////////////////////////////
	bool _Insert1(pNode& pRoot, K k, V v)           //插入元素（循环法）1
	{
		Node* newNode = new Node(k, v);
		if (pRoot == NULL)
		{
			pRoot = newNode;
			return true;
		}
		Node* temp = pRoot;
		Node* cur = NULL;
		while (temp)
		{
			cur = temp;
			if (temp->_key > k)
				temp = temp->Lchild;
			else if (temp->_key < k)
				temp = temp->Rchild;
			else
				return false;     //k已存在
		}

		if (cur->_key>k)
		{
			cur->Lchild = newNode;
			newNode->_parent = cur;
		}
		else
		{
			cur->Rchild = newNode;
			newNode->_parent = cur;
		}

		return true;
	}

	bool _Insert2(pNode& pRoot,pNode& pre, K k, V v)         //插入元素（递归法）
	{
		if (pRoot == NULL)
		{
			pNode newNode = new Node(k, v);
			pRoot = newNode;
			newNode->_parent = pre;
			return true;
		}
		if (pRoot->_key > k)
		{
			pre = pRoot;
			return _Insert2(pRoot->Lchild,pre, k, v);
		}
		else if (pRoot->_key < k)
		{
			pre = pRoot;
			return _Insert2(pRoot->Rchild,pre, k, v);
		}
		else
			return false;     //该节点已存在
	}

	///////////////////////////////////////////////////////////////////////

	//转化为双向链表
	pNode _BSTswitchList(pNode& pRoot)
	{
		if (pRoot == NULL)
			return NULL;
		pNode head = MinNode();    //最左边的节点
		pNode lastNode = NULL;
		ConvertNode(pRoot, lastNode);    //调整指针指向
		return head;
	}
	void ConvertNode(pNode pRoot, pNode& lastNode)    //调整指针指向函数
	{
		//lastNode是转换后链表的最后一个节点的指针
		if (pRoot->Lchild != NULL)
			ConvertNode(pRoot->Lchild, lastNode);           	//调整pRoot的left指针，指向指向上一个节点

		pRoot->Lchild = lastNode;                 	//调整指向最后一个节点，right指向下一个节点
		if (lastNode != NULL)
			lastNode->Rchild = pRoot;        //调整指向链表最后一个节点的指针   

		lastNode = pRoot;                    //对tree的右字树进行转换，lastNode是转化后链表最后一个节点的指针
		if (pRoot->Rchild != NULL)
			ConvertNode(pRoot->Rchild, lastNode);
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	void _InOrder(Node* _Root)       //中序遍历
	{
		if (_Root != NULL)
		{
			_InOrder(_Root->Lchild);
			cout << "<" << _Root->_key << "," << _Root->_value << ">" << endl;
			_InOrder(_Root->Rchild);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	bool _Delete1(pNode& pRoot, int key)         //删除节点（循环法）1
	{
		//空树，直接返回
		if (pRoot == NULL)
			return false;
		if (pRoot->_key == key&&pRoot->Lchild == NULL&&pRoot->Rchild == NULL)
		{
			delete pRoot;
			return true;
		}
		////////////////////////////////////////////////////
		Node* cur = pRoot;
		Node* pre = NULL;
		Node* temp = NULL;
		pNode pDel = NULL;

		while (cur)
		{
			pre = cur;
			if (cur->_key > key)
				cur = cur->Lchild;
			else if (cur->_key < key)
				cur = cur->Rchild;

			if (cur->_key == key)
			{
				pDel = cur->Rchild;
				if (cur == pRoot)                 //删除的节点为根节点
				{
					temp = cur;
					if (pDel != NULL)           //根节点右字树非空
					{
						while (pDel->Lchild)
						{
							temp = pDel;
							pDel = pDel->Lchild;
						}
						cur->_key = pDel->_key;
						cur->_value = pDel->_value;
						if (temp == cur)
							temp->Rchild = pDel->Rchild;
						else
							temp->Lchild = pDel->Rchild;

						delete pDel;
						return true;
					}
					else                          //根节点右字树节点为空
					{
						pDel = pRoot;
						pRoot = pRoot->Lchild;
						delete pDel;
						return true;
					}
				}
				else
				{
					temp = cur;
					if (pDel != NULL)
					{
						while (pDel->Lchild)
						{
							temp = pDel;
							pDel = pDel->Lchild;
						}
						cur->_key = pDel->_key;
						cur->_value = pDel->_value;
						if (temp == cur)
							temp->Rchild = pDel->Rchild;
						else
							temp->Lchild = pDel->Rchild;

						delete pDel;
						return true;
					}
					else                           //pDel为空（待删除节点的右字树为空）
					{
						if (pre->Rchild == cur)
						{
							pre->Rchild = cur->Rchild;
							delete cur;
							return true;
						}
						if (pre->Lchild == cur)
						{
							pre->Lchild = cur->Lchild;
							delete cur;
							return true;
						}
					}
				}
			}

		}
		return false;
	}

	bool _Delete2(pNode& pRoot, K key)                   //删除节点（递归法）
	{
		if (pRoot == NULL)
			return false;
		if (key < pRoot->_key)
			return _Delete(pRoot->Lchild, key);
		else if (key>pRoot->_key)
			return _Delete(pRoot->Rchild, key);
		else
		{
			if (pRoot->Lchild == NULL&&pRoot->Rchild == NULL)
			{
				delete pRoot;
				pRoot = NULL;
				return true;
			}
			else if (pRoot->Rchild == NULL)
			{
				pNode pDel = pRoot;
				pRoot = pRoot->Lchild;
				delete pDel;
				return true;
			}
			else if (pRoot->Lchild == NULL)
			{
				pNode pDel = pRoot;
				pRoot = pRoot->Rchild;
				delete pDel;
				return true;
			}
			else
			{
				pNode firstOfIn = pRoot->Rchild;
				while (firstOfIn->Lchild)
					firstOfIn = firstOfIn->Lchild;

				pRoot->_key = firstOfIn->_key;
				pRoot->_value = firstOfIn->_value;
				return _Delete(pRoot->Rchild, firstOfIn->_key);
			}
		}
	}
private:
	Node* Root;
	Node* _Head;
};
void IteratorTest2()    
{
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	SearchTree<int, int> s(arr, size);                 //有参构造创建节点
	s.InOrder();
	cout << endl;
	s.Display();
}
void IteratorTest()
{
	SearchTree<int, int> s;          //无参构造
	//int arr[] = { 2, 3, 1, 0, 4, 8, 5, 6, 7, 9 };
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	//int arr[] = { 5, 3, 4, 1, 2, 0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < size; i++)
	{
		s.Insert2(arr[i], i);
	}
	s.InOrder();
	cout << endl;
	cout << s.MinNode()->_key << endl;
	cout << s.MaxNode()->_key << endl;
	s.Display();
}
