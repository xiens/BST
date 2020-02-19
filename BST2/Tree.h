#include<iostream>
#include<iomanip> 
#include<memory>
#include<functional>

using namespace std;
#define width_unit 5

template <typename T>
class Tree
{
private:
	class Node
	{
	public:
		T key;
		shared_ptr<Node> left;
		shared_ptr<Node> right;
		Node(T d = 0) //constructor
			:key(d), left(NULL), right(NULL) {}
	};


	void trav(T, shared_ptr <Node> &, shared_ptr <Node> &);

	template <typename T>
	struct FunctionLess {
		inline bool operator()(const T& _Left, const T& _Right) const
		{	// apply operator< to operands
			return (_Left < _Right);
		}

	};
	shared_ptr <Node> root; 

	function<bool(const T&, const T&)> compareLess = FunctionLess<T>(); 


public:

	Tree(); //constructor
	~Tree(void); //destructor
	bool find(T);
	void insert(T);
	void erase(T);
	bool empty(void) const;
	T & min();
	T & max();

	shared_ptr<typename Tree<T>::Node> & getRoot();
	void print(ostream &, shared_ptr <Node>, int level) const; //should be private
	void print(shared_ptr <Node>, int level) const; //should be private

}; 



template <typename T>
Tree<T>::Tree()
{
	root = NULL;
}

template<typename T>
Tree<T>::~Tree(void)
{
}

template <typename T>
bool Tree<T>::empty(void) const
{
	return !root;
}

template <typename T>
T & Tree<T>::min()
{
	if (root != NULL) {
		shared_ptr <Node> currentNode = root;

		while (currentNode->left)
			currentNode = currentNode->left;

		return currentNode->key;
	}
}

template <typename T>
T & Tree<T>::max()
{
	if (root != NULL) {
		shared_ptr <Node> currentNode = root;

		while (currentNode->right)
			currentNode = currentNode->right;
		zxsdd
		return currentNode->key;
	}
}

template<typename T>
inline shared_ptr<typename Tree<T>::Node> & Tree<T>::getRoot()
{
	return root;
}

//traversing across the tree, returning the place for inserting new element, temp is the last occupied spot
template <typename T>
void Tree<T>::trav(T key, shared_ptr <Node> & temp, shared_ptr <Node> & currentNode)
{
	currentNode = root;
	temp = NULL;
	while(currentNode && (compareLess(currentNode->key, key)|| compareLess(key, currentNode->key)))
	{
		temp = currentNode;
		if(compareLess(key,currentNode->key))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}
}



template <typename T>
bool Tree<T>::find(T key)
{
	shared_ptr <Node> temp = NULL;
	shared_ptr <Node> currentNode = NULL;
	trav(key, temp, currentNode);
	
	if (currentNode) return true;
}

template <typename T>
void Tree<T>::insert(T key)
{
	shared_ptr <Node> temp = NULL;
	shared_ptr <Node> currentNode = NULL;
	trav(key, temp, currentNode);

	if (!currentNode) //no duplicates
	{
		currentNode = make_shared<Node>(key);

		if (!temp)
			root = currentNode;
		else if (compareLess(key, temp->key))
			temp->left = currentNode;
		else
			temp->right = currentNode;
	}
}
template <typename T>
void Tree<T>::erase(const T key)
{
	shared_ptr <Node> temp = NULL;
	shared_ptr <Node> currentNode = NULL;
	trav(key, temp, currentNode); 

	if (currentNode) //if it is not null then
	{
		if (currentNode->left && currentNode->right) //2 children case
		{
			shared_ptr <Node> tmp = currentNode;
			temp = currentNode;
			currentNode = currentNode->left;
			while (currentNode->right)
			{
				temp = currentNode;
				currentNode = currentNode->right;
			}
			tmp->key = currentNode->key;
		}

		//1 or 0 child case
		shared_ptr <Node> tmp = (currentNode->left ? currentNode->left : currentNode->right);

		if (!temp) {
			root = tmp;
		}
		else if (compareLess(temp->key, currentNode->key)) {
			temp->right = tmp;
		}
		else {
			temp->left = tmp;
		}
		//delete currentNode;
	}
}


//the recursive tree output
template <typename T>
void Tree<T>::print(ostream & ost, shared_ptr <Node> currentNode, int level) const
{
	if (currentNode) //if the currentNodeent node is not null then
	{
		print(ost, currentNode->right, level + 1); //try to go to right node
												   //output the node data w/ respect to its level
		ost << setw(level*width_unit) << currentNode->key << endl;
		print(ost, currentNode->left, level + 1); //try to go to left node
	}
}


//the recursive tree print
template <typename T>
void Tree<T>::print(shared_ptr <Node> currentNode, int level) const
{
	if (currentNode) //if the currentNodeent node is not null then
	{
		print(currentNode->right, level + 1); //try to go to right node
											  //print the node data w/ respect to its level
		cout << setw(level*width_unit) << currentNode->key << endl;
		print(currentNode->left, level + 1); //try to go to left node
	}
}

template <typename T>
ostream & operator<<(ostream &ost,  Tree<T> &t)
{
	t.print(ost, t.getRoot() , 1);

	return ost;
}