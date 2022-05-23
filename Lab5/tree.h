#include <iostream>
#include <string>
using namespace std;
enum RBTColor { Black, Red };
template<class KeyType,class DataType >
struct  RBTNode
{
	KeyType key;
	DataType data;
	RBTColor color;
	RBTNode<KeyType,DataType>* left;
	RBTNode<KeyType, DataType>* right;
	RBTNode<KeyType, DataType>* parent;
	RBTNode(KeyType k, DataType d, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
		key(k), data(d), color(c), parent(p), left(l), right(r) { };
};
template<class T,class V>
class  RBTree
{private:
	RBTNode<T, V>* root;
public:
	int count_s;
	int count_i;
	int count_d;
	RBTree() ;
	~RBTree();
	void insert(T key,V data);    
	void remove(T key); 
	RBTNode<T, V>* search(T key);	
	void leftRotate(RBTNode<T, V>*& root, RBTNode<T, V>* x);
	void rightRotate(RBTNode<T, V>*& root, RBTNode<T, V>* y);

	void insert(RBTNode<T, V>*& root, RBTNode<T, V>* node);
	void InsertBalance(RBTNode<T, V>*& root, RBTNode<T, V>* node);
	void destory(RBTNode<T, V>*& node);
	void remove(RBTNode<T, V>*& root, RBTNode<T, V>* node);
	void removeBalance(RBTNode<T, V>*& root, RBTNode<T, V>* node, RBTNode<T, V>* parent);
	RBTNode<T, V>* search(RBTNode<T, V>* node, T key) ;

};
template<class T, class V>	
RBTree<T, V>::RBTree() :root(NULL) {
	count_s = 0;
	count_d = 0;
	count_i = 0;
	root = nullptr;
}
template<class T, class V>		
RBTree<T, V>::~RBTree() {
	destory(root);
}
template<class T, class V>	
void RBTree<T, V>::leftRotate(RBTNode<T, V>*& root, RBTNode<T, V>* x) {
	RBTNode<T, V>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL)
	{
		root = y;
	}
	else {
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
};
template<class T, class V>	
void RBTree<T, V>::rightRotate(RBTNode<T, V>*& root, RBTNode<T, V>* y) {
	RBTNode<T, V>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
	{
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == NULL)
	{
		root = x;
	}
	else {
		if (y == y->parent->right)
		{
			y->parent->right = x;
		}
		else
		{
			y->parent->left = x;
		}
	}
	x->right = y;
	y->parent = x;
};
template<class T, class V>	
void RBTree<T, V>::insert(T key,V data)
{
	 count_i=0;
	RBTNode<T, V>* n = new RBTNode<T, V>(key,data, Red, NULL, NULL, NULL);
	insert(root, n);
};
template<class T, class V>
void RBTree<T, V>::insert(RBTNode<T, V>*& root, RBTNode<T, V>* node)
{
	
	RBTNode<T, V>* x = root;
	RBTNode<T, V>* y = NULL;
	while (x != NULL)
	{
		count_i++;
		y = x;
		if (node->key > x->key)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
		
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
		{
			y->right = node;
		}
		else
		{
			y->left = node;
		}
	}
	else
	{
		root = node;
	}
	node->color = Red;
	count_i++;
	InsertBalance(root, node);
};
template<class T, class V>
void RBTree<T, V>::InsertBalance(RBTNode<T, V>*& root, RBTNode<T, V>* node)
{
	RBTNode<T, V>* parent;
	parent = node->parent;
	while (node != RBTree::root && parent->color == Red)
	{
		count_i++;
		RBTNode<T, V>* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTNode<T, V>* uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RBTNode<T, V>* uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	count_i++;
	root->color = Black;
}
template<class T, class V>
void RBTree<T, V>::destory(RBTNode<T, V>*& node)
{
	if (node == NULL)
	{
		return;
	}
	destory(node->left);
	destory(node->right);
	delete node;
	node = nullptr;
}
template<class T, class V>
void RBTree<T, V>::remove(T key)
{
	count_d = 0;
	RBTNode<T,V>* deletenode = search(root, key);
	count_d+=count_s;
	if (deletenode != NULL)
	{
		remove(root, deletenode);
	}
}
template<class T, class V>
void RBTree<T, V>::remove(RBTNode<T, V>*& root, RBTNode<T, V>* node)
{
	
	RBTNode<T, V>* child, * parent;
	RBTColor color;
	if (node->left != NULL && node->right != NULL)
	{
		RBTNode<T, V>* replace = node;
		replace = node->right;
		while (replace->left != NULL)
		{
			count_d++;
			replace = replace->left;
		}
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
			{
				node->parent->left = replace;
			}
			else
			{
				node->parent->right = replace;
			}
		}
		else
		{
			root = replace;
		}
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if (child != NULL)
			{
				child->parent = parent;
			}
			parent->left = child;
			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
		{
			removeBalance(root, child, parent);
		}

		delete node;
		return;
	}
	if (node->left != NULL)
	{
		child = node->left;
	}
	else
	{
		child = node->right;
	}
	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	if (parent)
	{
		if (node == parent->left)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}
	}
	else
	{
		RBTree::root = child;
	}
	if (color == Black )
	{
		removeBalance(root, child, parent);
	}
	count_d++;
	delete node;
}
template<class T, class V>
void RBTree<T, V>::removeBalance(RBTNode<T, V>*& root, RBTNode<T, V>* node, RBTNode<T, V>* parent)
{
	RBTNode<T, V>* tmp;
	if (node == NULL&& node == RBTree::root) {
		return;
	}
	while ((!node) || (node->color == Black && node != RBTree::root))
	{
		count_d++;
		if (parent->left == node)
		{
			tmp = parent->right;
			if (tmp->color == Red)
			{
				tmp->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				tmp = parent->right;
			}
			else
			{
				if (!(tmp->right) || tmp->right->color == Black)
				{
					tmp->left->color = Black;
					tmp->color = Red;
					rightRotate(root, tmp);
					tmp = parent->right;
				}
				tmp->color = parent->color;
				parent->color = Black;
				tmp->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			tmp = parent->left;
			if (tmp->color == Red)
			{
				tmp->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				tmp = parent->left;
			}
			if ((!tmp->left || tmp->left->color == Black) && (!tmp->right || tmp->right->color == Black))
			{
				tmp->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(tmp->left) || tmp->left->color == Black)
				{
					tmp->right->color = Black;
					tmp->color = Red;
					leftRotate(root, tmp);
					tmp = parent->left;
				}
				tmp->color = parent->color;
				parent->color = Black;
				tmp->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
	{
		node->color = Black;
	}
}
template<class T, class V>
RBTNode<T, V>* RBTree<T, V>::search(T key)
{
	count_s = 0;
	return search(root, key);
}
template<class T, class V>
RBTNode<T, V>* RBTree<T, V>::search(RBTNode<T, V>* node, T key) 
{
	
	if (node == NULL || node->key == key)
	{
		count_s++;
		return node;
	}
	else
	{
		if (key > node->key)
		{
			count_s++;
			return search(node->right, key);
		}
		else
		{
			count_s++;
			return search(node->left, key);
		}
	}
}
	

