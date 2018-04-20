#pragma once
#include<iostream>
using namespace std;

template<class K, class V>
struct BSTNode
{
	BSTNode(K k,V v)
	{
		_key = k;
		_value = v;
		Lchild = NULL;
		Rchild = NULL;
	}

	K _key;
	V  _value;
	BSTNode<K,V>* Lchild;
	BSTNode<K, V>* Rchild;
};
template<class K,class V>
class SearchTree
{
	typedef  BSTNode<K, V> Node;
	typedef  BSTNode<K, V>* pNode;
public:
	SearchTree()          //无参构造
	{
		Root = NULL;
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
		return _Insert1(Root, k, v);
	}
	bool Insert2(K k,V v)    //插入节点（递归法）2
	{
		return _Insert2(Root,k, v);
	}

	bool Delete1(int key)         //删除节点（循环法） 1
	{
		return _Delete1(Root,key);
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
	
private:
	///////////////////////////////////////////////////////
	bool _Insert1(pNode& pRoot,K k, V v)           //插入元素（循环法）1
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
			cur->Lchild = newNode;
		else
			cur->Rchild = newNode;

		return true;
	}

	bool _Insert2(pNode& pRoot, K k, V v)         //插入元素（递归法）
	{
		if (pRoot == NULL)
		{
			pNode newNode = new Node(k, v);
			pRoot = newNode;
			return true;
		}
		if (pRoot->_key > k)
		{
			return _Insert2(pRoot->Lchild, k, v);
		}
		else if (pRoot->_key < k)
		{
			return _Insert2(pRoot->Rchild, k, v);
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
		ConvertNode(pRoot,lastNode);    //调整指针指向
		return head;
	}
	void ConvertNode(pNode pRoot,pNode& lastNode)    //调整指针指向函数
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
	bool _Delete1(pNode& pRoot,int key)         //删除节点（循环法）1
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
						if (pre->Rchild== cur)
						{
							pre->Rchild =cur->Rchild;
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
};

void Test()
{
	SearchTree<int, int> s;
	//int arr[] = { 2, 3, 1, 0, 4, 8, 5, 6, 7, 9 };
	int arr[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	//int arr[] = { 5, 3, 4, 1, 2, 0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < size; i++)
	{
		s.Insert1(arr[i], i);
	}
	s.InOrder();
	cout << endl;
	cout << s.MinNode()->_key << endl;
	cout << s.MaxNode()->_key << endl;

	s.Delete1(3);
	s.InOrder();
	//BSTNode<int, int>* Head = s.BSTswitchList();    //转换双向链表
	//while (Head)
	//{
	//	cout << Head->_key << ",";
	//	Head = Head->Rchild;
	//}
	//cout << endl;

	/*cout << endl;
	s.Delete2(5);
	s.InOrder();
	cout << endl;
	s.Delete2(8);
	s.InOrder();
	cout << endl;
	s.Delete2(2);
	s.InOrder();*/

}
