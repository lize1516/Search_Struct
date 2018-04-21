#incldue<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};
template<class K,class V>
struct RBNode
{
	RBNode()
	:_Lchild(NULL)
	,_Rchild(NULL)
	,_Parent(NULL)
	, _color(RED)
	{ }
	RBNode(K key,V value,Color color=RED)
		:_Lchild(NULL)
		, _Rchild(NULL)
		, _Parent(NULL)
		, _key(key)
		, _value(value)
		, _color(color)
	{ }
	RBNode<K, V>* _Lchild;
	RBNode<K, V>* _Rchild;
	RBNode<K, V>* _Parent;
	K _key;
	V _value;
	Color _color;
};

template<class K, class V>
class RBTree
{
	typedef RBNode<K, V> Node;
	typedef RBNode<K, V>* pNode;
public:
	RBTree()
	{
		Root = NULL;
	}
	bool Insert(K k,V v)
	{
		return _Insert(Root,k,v);
	}
	void InOrder()
	{
		_InOrder(Root);
	}
	bool CheckRBT()
	{
		int blackcount = 0;
		int k = 0;
		pNode cur = Root;
		while (cur)
		{
			if (cur->_color == BLACK)
				blackcount++;
			cur = cur->_Lchild;
		}
		return _CheckRBT(Root,blackcount,k);
	}
private:
	bool _CheckRBT(pNode pRoot,int blackcount,int k)
	{
		if (pRoot == NULL)
		{
			if (blackcount == k)
				return true;
			else
				return false;
		}
		if (pRoot->_color == RED&&pRoot->_Parent->_color == RED)
			return false;
		if (pRoot->_color == BLACK)
			k++;
		return _CheckRBT(pRoot->_Lchild,blackcount,k);
		return _CheckRBT(pRoot->_Rchild, blackcount, k);

	}
	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_Lchild);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
			_InOrder(pRoot->_Rchild);
		}
	}
	bool _Insert(pNode& pRoot,K k,V v)
	{
		pNode newNode = new Node(k, v);
		if (pRoot == NULL)          //情况一
		{
			pRoot = newNode;
			newNode->_color = BLACK;
		}
		pNode cur = pRoot;
		pNode pParent = NULL;
		while (cur)                 
		{                           //查找要插入的位置
			pParent = cur;
			if (cur->_key > k)
				cur = cur->_Lchild;
			else if (cur->_key < k)
				cur = cur->_Rchild;
			else
				return false;     //k已存在
		}
		if (pParent->_key>k)
		{
			pParent->_Lchild = newNode;
			newNode->_Parent = pParent;
		}
		else
		{
			pParent->_Rchild = newNode;
			newNode->_Parent = pParent;
		}
		cur = newNode;
		
		pNode u = NULL;
		pNode p = pParent;
		while (cur!=Root&&p->_color==RED)
		{
			pNode g = p->_Parent;
			if (p== g->_Lchild)
				u = g->_Rchild;
			else
				u = g->_Lchild;

			if (p->_color == BLACK)        //情况二
				return true;
			else if (cur->_color==RED&&u->_color==RED)   //情况三
			{
				p->_color = BLACK;
				u->_color = BLACK;
				if (g!=Root)
				g->_color = RED;

				cur = g;
				p = cur->_Parent;
			}
			else if (cur->_color == RED&&g->_color == BLACK&&(u->_color==BLACK||u==NULL))   //情况四
			{
				p->_color = BLACK;
				g->_color = RED;
				if (cur == p->_Lchild&&p == g->_Lchild)
				{
					//右单旋
					RotateRight(g);
				}
				else if (cur == p->_Rchild&&p == g->_Rchild)
				{
					//左单旋
					RotateLeft(g);
				}
			}
			else if (cur->_color == RED&&g->_color == BLACK && (u->_color == BLACK || u == NULL))
			{
				if (p == g->_Lchild&&cur == p->_Rchild)
				{
					//左单旋
					RotateLeft(p);
					swap(cur, p);
				}
				else if (p == g->_Rchild&&cur == p->_Lchild)
				{
					//右单旋
					RotateRight(p);
					swap(cur, p);
				}
			}
			if (g == Root)
				g->_color = BLACK;
		}
		return true;
	}
	void RotateLeft(pNode g)
	{
		pNode pSubR = g->_Rchild;
		pNode pSubRL = pSubR->_Lchild;
		pNode pParent = g->_Parent;

		g->_Rchild = pSubRL;
		if (pSubRL != NULL)
			pSubRL->_Parent = g;
		pSubR->_Lchild = g;
		g->_Parent = pSubR;
		if (pParent == NULL)
			Root = pSubR;
		else if (pParent != NULL&&g == pParent->_Lchild)
		{
			pParent->_Lchild = g;
			g->_Parent = pParent;
		}
		else if (pParent != NULL&&g == pParent->_Rchild)
		{
			pParent->_Rchild = g;
			g->_Parent = pParent;
		}
	}
	void RotateRight(pNode g)
	{
		pNode pSubL = g->_Lchild;
		pNode pSubLR = pSubL->_Rchild;
		pNode pParent = g->_Parent;
	    
		g->_Lchild = pSubLR;
		if (pSubLR)
			pSubLR->_Parent = g;
		pSubL->_Rchild = g;
		g->_Parent = pSubL;
		if (pParent == NULL)
			Root = pSubL;
		else if (pParent != NULL&&g == pParent->_Lchild)
		{
			pParent->_Lchild = pSubL;
			pSubL->_Parent = pParent;
		}
		else if (pParent != NULL&&g == pParent->_Rchild)
		{
			pParent->_Rchild = pSubL;
			pSubL->_Parent = pParent;
		}

	}
	
private:
	pNode Root;
};
void Test()
{
	RBTree<int, int> t;
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int size = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < size; i++)
	{
		t.Insert(arr[i], i);
	}
	t.InOrder();
	if (t.CheckRBT() == true)
		cout << "是红黑树" << endl;
	else
		cout << "不是红黑树" << endl;
}
