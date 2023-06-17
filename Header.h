#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <mutex>
using namespace std;

int countChar(string s, char c)
{
	int count = 0;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c)
		{
			count++;
		}
	}
	return count;
}

string strip(string s)
{
	string out;
	if (countChar(s, ' ') == s.length()) { return ""; }
	out = s.substr(s.find_first_not_of(' '), -1);
	out = out.substr(0, s.find_last_not_of(' ') + 1);
	return out;
}

string upperStr(string s)
{
	string out = "";
	for (int i = 0; s[i]; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			out.push_back(s[i] - 32);
		}
		else
		{
			out.push_back(s[i]);
		}
	}
	return out;
}

string lowerStr(string s)
{
	string out = "";
	for (int i = 0; s[i]; i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			out.push_back(s[i] + 32);
		}
		else
		{
			out.push_back(s[i]);
		}
	}
	return out;
}

bool isAlNum(string s)
{
	s = lowerStr(s);
	bool contNum = false;
	bool contChar = false;
	for (int i = 0; s[i]; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			contNum = true;
		}
		else if (s[i] >= 'a' && s[i] <= 'z')
		{
			contChar = true;
		}
		else
		{
			return false;
		}
	}
	return contNum && contChar;
}

bool isNumber(string s)
{
	if (s.length() == 0) { return false; }
	for (int i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i]>'9')
		{
			return false;
		}
	}
	return true;
}

template<typename T>
struct ListNode {
	T value = T();
	ListNode* next = nullptr;
};

template<typename T>
class List {
protected:
	ListNode<T>* start; //saves address of starting node of List
	ListNode<T>* end;	//saves address of ending node of List
	int len;
public:
	List() :start(nullptr), end(nullptr), len(0) {} //default constructor to initialize empty List
	~List() //Destructor. Empties Linked List
	{
		clear();
	}
	List(const List<T>& li) :start(nullptr), end(nullptr), len(0) //copy constructor which ensures deep copy
	{
		(*this) = li;
	}
	List<T>& operator=(const List<T>& li) //overloaded = operator for deep copy
	{
		ListNode<T>* ptr = li.start;
		while (!this->isEmpty())
		{
			this->removeAt(0);
		}
		while (ptr)
		{
			this->insertAt(-1, ptr->value);
			ptr = ptr->next;
		}
		return *this;
	}
	bool operator==(const List<T>& li) = delete;
	void clear()
	{
		while (!isEmpty())
		{
			removeAt(0);
		}
	}
	bool isEmpty() { return !bool(start); }	//returns true if List is empty
	int getLen() { return len; }
	ListNode<T>* getStart() { return start; }
	T Start()
	{
		if (start)
		{
			return start->value;
		}
		else
		{
			cout << "Linked List is Empty. Null Value returned as Start()\n";
			return T();
		}
	}
	ListNode<T>* getLast() { return end; }
	T Last()
	{
		if (end)
		{
			return end->value;
		}
		else
		{
			cout << "Linked List is Empty. Null Value returned as Last()\n";
			return T();
		}
	}
	void insert(const T& ele)
	{
		insertAt(-1, ele);
	}
	void insertAt(int pos, const T& ele)	//Inserts an element so that its index will be pos when added to List
	{
		ListNode<T>* newNode = new ListNode<T>;
		ListNode<T>* temp = nullptr;
		newNode->value = ele;
		if (pos<0 || pos>len) //if pos is less than 0 or more than length then insert ele at end
		{
			pos = len;
		}
		if (pos == 0)	//insert at start
		{
			newNode->next = start;
			start = newNode;
			if (len == 0)		//if List was empty before, point end to the new node as well
			{
				end = start;
			}
		}
		else if (pos == len)	//insert at end if position if one more than length(using pointer to end)
		{
			end->next = newNode;
			newNode->next = nullptr;
			end = end->next;
		}
		else //insert at a middle node by traversing to the required node from starting node
		{
			ListNode<T>* ptr = start;
			for (int i = 0; i < pos - 1; i++)
			{
				ptr = ptr->next;
			}
			temp = ptr->next;
			ptr->next = newNode;
			newNode->next = temp;
		}
		len++;
	}
	void removeAt(int pos)
	{
		ListNode<T>* temp = nullptr;
		if (isEmpty()) //end function if List already empty
		{
			cout << "CANT REMOVE as List is already empty!\n";
			return;
		}
		if (pos < 0 || pos >= len) //if pos is less than 0 or more than length then remove the last element
		{
			pos = len - 1;
		}
		if (pos == 0) //remove first element and change start if pos is 0
		{
			temp = start;
			start = start->next;
			delete temp;
			if (len == 1) //change end if length of List was only 1
			{
				end = nullptr;
			}
		}
		else	//remove any element other than first
		{
			ListNode<T>* ptr = start;
			for (int i = 0; i < pos - 1; i++)
			{
				ptr = ptr->next;
			}
			temp = ptr->next;
			ptr->next = temp->next;
			delete temp;
			if (len == pos + 1) //Change end if the last element was removed
			{
				end = ptr;
			}
		}
		len--;
	}
	bool removeEle(const T& val)
	{
		ListNode<T>* temp = nullptr;
		if (len == 0)
		{ 
			cout << "Can't Remove as List is already Empty! ~removeEle().\n";
			return false; 
		}
		if (start->value == val)
		{
			temp = start;
			start = start->next;
			delete temp;
			len--;
			if (!len) { end = nullptr; }
			return true;
		}
		ListNode<T>* ptr = start;
		while (ptr)
		{
			if (ptr->next && ptr->next->value == val)
			{
				temp = ptr->next;
				ptr->next = ptr->next->next;
				delete temp;
				len--;
				if (!len) { end = nullptr; }
				return true;
			}
			ptr = ptr->next;
		}
		cout << "Can't remove from List as element not found! ~removeEle().\n";
		return false;
	}
	void printList() //prints List(used for debugging)
	{
		ListNode<T>* ptr = start;
		cout << '[';
		while (ptr)
		{
			cout << ptr->value;
			ptr = ptr->next;
			if (ptr)
			{
				cout << ',';
			}
		}
		cout << "]\n";
	}
	bool search(const T& val)
	{
		ListNode<T>* iter = start;
		while (iter)
		{
			if (iter->value == val)
			{
				return true;
			}
			iter = iter->next;
		}
		return false;
	}
};

template<class T>
class Queue:private List<T>
{
public:
	Queue() :List<T>() {}
	void clear() { List<T>::clear(); }
	void enqueue(const T& val)
	{
		List<T>::insertAt(0, val);
	}
	T dequeue()
	{
		T temp;
		temp = List<T>::Start();
		List<T>::removeAt(0);
		return temp;
	}
	bool isEmpty() { return List<T>::isEmpty();  }
	T Front()
	{
		return List<T>::Start();
	}
};

template <typename T>
struct queuenode
{
	T data;
	int priority;
};

template <typename T>
class PriorityQueue
{
	queuenode<T>** heaparray;
	//curindex specifies present index till which array is filled.
	int curindex, size;
	void insertsort()
	{

		int pindex, tempindex = curindex;

		queuenode<T>* parent, * child;

		do
		{

			child = heaparray[tempindex];

			pindex = Parent(tempindex);

			//cout << endl << pindex;

			parent = heaparray[pindex];

			if (parent->priority < child->priority)
			{
				heaparray[pindex] = child;
				heaparray[tempindex] = parent;
			}

			tempindex = pindex;

		} while (parent->priority < child->priority && tempindex != 1);

	}
	void deletesort()
	{

		int maxchildindex = 0, pindex = 1, tempindex = curindex;

		queuenode<T>* parent, * child;

		do
		{
			parent = heaparray[pindex];

			maxchildindex = maxChild(Left(pindex), Right(pindex));

			if (maxchildindex == -1) { break; }

			child = heaparray[maxchildindex];

			if (parent->priority < child->priority)
			{
				heaparray[pindex] = child;
				heaparray[maxchildindex] = parent;
			}

			pindex = maxchildindex;

		} while (parent->priority < child->priority);

	}
	int maxChild(int index1, int index2)
	{
		if ((!heaparray[index1] && !heaparray[index2]) || index1 >= curindex) { return -1; }
		if (!heaparray[index2] || index2 >= curindex) { return index1; }
		if (heaparray[index1]->priority > heaparray[index2]->priority)
		{
			return index1;
		}
		else
		{
			return index2;
		}
	}
	int Parent(int i)
	{
		return (i / 2);
	}
	// to get index of left child of node at index i
	int Left(int i)
	{
		return (2 * i);
	}
	// to get index of right child of node at index i
	int Right(int i)
	{
		return (2 * i + 1);
	}
public:
	PriorityQueue(int size=100):heaparray(nullptr)//constructor with default size 100
	{
		this->size = size;
		curindex = 1;
		heaparray = new queuenode<T>*[size];
		for (int i = 0; i < size; i++)
		{
			heaparray[i] = nullptr;
		}
	}
	PriorityQueue(const PriorityQueue& obj):heaparray(nullptr)
	{
		(*this) = obj;
	}
	PriorityQueue& operator=(const PriorityQueue& obj)
	{
		if (heaparray) { delete[] heaparray; }
		size = obj.size;
		curindex = obj.curindex;
		heaparray = new queuenode<T>*[size];
		for (int i = 0; i < obj.curindex; i++)
		{
			if (!obj.heaparray[i]) { heaparray[i] = nullptr; }
			else
			{
				heaparray[i] = new queuenode<T>();
				*(heaparray[i]) = *(obj.heaparray[i]);
			}
		}
		return *this;
	}
	~PriorityQueue()
	{
		queuenode<T>* temp;

		for (int i = 1; i < curindex; i++)
		{
			temp = heaparray[i];
			delete temp;
		}

		delete[] heaparray;
	}
	bool isEmpty() { return curindex == 1; }
	void insert(const T& pdata, int prio)
	{

		//insertion starts from 1 index of array
		//each index possess pointer of node in which priority and data is present 

		queuenode<T>* Qnode = new queuenode<T>;
		Qnode->data = pdata;
		Qnode->priority = prio;

		if (curindex == 1)// 1st node case
		{
			heaparray[1] = Qnode;
		}
		else // further nodes
		{
			heaparray[curindex] = Qnode;
			insertsort();
		}

		curindex++;

	}
	T getMax()
	{
		if (isEmpty())
		{
			cout << "Can't return max value from priority queue as it is empty. ~getMatch().\n";
			return T();
		}
		queuenode<T>* temp = heaparray[1];
		heaparray[1] = heaparray[curindex - 1];
		deletesort();
		curindex--;
		T tmp = temp->data;
		delete temp;
		return tmp;

	}
	void levelorder()
	{
		queuenode<T>* temp;

		for (int i = 1; i < curindex; i++)
		{
			temp = heaparray[i];
			cout << temp->priority << " ";
		}
	}
};

template<class T>
class Graph
{
	struct adjListNode
	{
		int nodeIndex;
		int weight;
		adjListNode() :nodeIndex(-1), weight(0) {}
		adjListNode(int i, int w) :nodeIndex(i), weight(w){}
	};
	List<adjListNode>* adjList;
	T* nodeNames;
	int currNodes;
	int maxNodes;
public:
	Graph(int maxSize) :maxNodes(maxSize),currNodes(0)
	{
		nodeNames = new T[maxNodes];
		adjList = new List<adjListNode>[maxNodes];
	}
	~Graph()
	{
		delete[] nodeNames;
	}
	Graph(const Graph&) = delete;
	Graph& operator=(const Graph&) = delete;
	bool operator==(const Graph&) = delete;
	void insertNode(const T& nodeName)
	{
		if (currNodes == maxNodes) 
		{
			cout << "Can't add new node to graph as graph is full. ~insertNode().\n";
			return;
		}
		else
		{
			nodeNames[currNodes] = nodeName;
			adjList[currNodes].clear();
			currNodes++;
		}
	}
	void insertEdge(const T& node1, const T& node2, int weight)
	{
		int index1 = -1;
		int index2 = -1;
		for (int i = 0; i < currNodes; i++)
		{
			if (nodeNames[i] == node1) 
			{
				index1 = i;
			}
			if (nodeNames[i] == node2)
			{
				index2 = i;
			}
		}
		if (index1 == -1 || index2 == -1)
		{
			cout << "Edge can not be added as one or both of the nodes don't exist! ~insertEdge().\n";
			return;
		}
		adjListNode temp(index2, weight);
		adjList[index1].insert(temp);
		//temp.nodeIndex = index1;
		//adjList[index2].insert(temp);
	}
	void changeEdgeWeight(const T& node1, const T& node2, int newWeight)
	{
		int index1 = -1;
		int index2 = -1;
		for (int i = 0; i < currNodes; i++)
		{
			if (nodeNames[i] == node1)
			{
				index1 = i;
			}
			if (nodeNames[i] == node2)
			{
				index2 = i;
			}
		}
		if (index1 == -1 || index2 == -1)
		{
			cout << "Edge can not be added as one or both of the nodes don't exist! ~insertEdge().\n";
			return;
		}
		for (ListNode<adjListNode>* iter = adjList[index1].getStart(); iter;)
		{
			if (iter->value.nodeIndex == index2)
			{
				iter->value.weight = newWeight;
				break;
			}
			iter = iter->next;
		}
	}
	List<List<T>> shortestPaths(const T& startNode)
	{
		int stIndex = -1;
		for (int i = 0; i < currNodes; i++)
		{
			if (nodeNames[i] == startNode)
			{
				stIndex = i;
				break;
			}
		}
		if (stIndex == -1)
		{
			cout << "Could not find shortest paths as startNode was not found in graph! ~shortestPaths().\n";
			return List<List<T>>();
		}
		else
		{
			int* dists = new int[currNodes];
			List<int>* paths = new List<int>[currNodes];
			List<int> toBeAdded;
			List<int> inTree;
			dists[stIndex] = 0; //distance of starting Node from itself is set to be 0
			for (int i = 0; i < currNodes; i++)		
			{
				toBeAdded.insert(i); //all nodes added to toBeAdded List
				if (i != stIndex) 
				{ 
					dists[i] = 999999; //their distance is set to be a very large number
				}	
			}
			for (int minIndex; !toBeAdded.isEmpty();) //loop until all the nodes are not added to shortest path tree
			{	
				minIndex = -1;
				for (int i = 0, minVal = 9999999; i < currNodes; i++) // loop to find minimum distance in graph
				{
					if (toBeAdded.search(i) && dists[i] < minVal)  
					{
						minVal = dists[i];
						minIndex = i;
					}
				}
				toBeAdded.removeEle(minIndex);	//remove the min val index from to be added and add to shortest path tree
				inTree.insert(minIndex);		//^^
				paths[minIndex].insert(minIndex);//add the min val index to its path
				for (ListNode<int>* outIter = inTree.getStart(); outIter && !toBeAdded.isEmpty();)
				{
					for (ListNode<adjListNode>* inIter = adjList[outIter->value].getStart(); inIter;)
					{
						if (dists[inIter->value.nodeIndex] > dists[outIter->value] + inIter->value.weight)
						{
							dists[inIter->value.nodeIndex] = dists[outIter->value] + inIter->value.weight;
							paths[inIter->value.nodeIndex] = paths[outIter->value];
						}
						inIter = inIter->next;
					}
					outIter = outIter->next;
				}
			}
			List<List<T>> outPaths;
			List<T> temp;
			for (int i = 0; i < currNodes; i++)
			{
				//if (paths[i].getLen() == 1) { continue; } //Skip the node which has trivial path
				temp.clear();
				for (ListNode<int>* iter = paths[i].getStart(); iter; iter = iter->next)
				{
					temp.insert(nodeNames[iter->value]);
				}
				outPaths.insert(temp);
			}
			return outPaths;
		}
	}
};

class Message
{
public:
	int id;
	int prio;
	string source;
	string dest;
	string payload;
	string trace;
	Message(int id=int(), int prio=int(), string source=string(), string dest=string(), string payload=string(), string trace=string()) :id(id), prio(prio), source(source), dest(dest), payload(payload), trace(trace) {}
};

// A generic Key/Value pair. Both Key/Val are assumed to be of the same type, and all comparison operators use the key.
template <typename T>
struct KeyVal {
	T key;
	T val;

public:
	KeyVal(T k=T(), T v=T()) :key(k),val(v){}
	bool operator==(const KeyVal<T>& other) {
		return this->key == other.key;
	}
	bool operator>(const KeyVal<T>& other) {
		return this->key > other.key;
	}
	bool operator<(const KeyVal<T>& other) {
		return this->key < other.key;
	}
	bool operator<=(const KeyVal<T>& other) {
		return this->key <= other.key;
	}
	bool operator>=(const KeyVal<T>& other) {
		return this->key >= other.key;
	}
};

// A generic container interface.
template <typename T>
class Container {
public:
	// insert(KeyVal<T>): Insert a Key/Value pair into the container
	virtual void insert(KeyVal<T>) = 0;

	// Searches for a Key and returns pointer to location of Key/Val (if it exists).
	virtual KeyVal<T>* search(T key) = 0;

	virtual bool removeKey(T key) = 0;

	virtual void clear() = 0;

	virtual bool remove(KeyVal<T> pair) = 0;

	virtual ~Container(){}

};

template<class T>
class KeyValList:private List<KeyVal<T>>,public Container<T> 
{
public:
	virtual ~KeyValList() { List<KeyVal<T>>::~List(); }
	void insert(KeyVal<T> pair)
	{
		List<KeyVal<T>>::insert(pair);
	}
	void clear()
	{
		List<KeyVal<T>>::clear();
	}
	KeyVal<T>* search(T key)
	{
		ListNode<KeyVal<T>>* iter = List<KeyVal<T>>::start;
		while (iter)
		{
			if (iter->value.key == key)
			{
				return &(iter->value);
			}
			iter = iter->next;
		}
		return nullptr;
	}
	bool removeKey(T key)
	{
		ListNode<KeyVal<T>>* iter = List<KeyVal<T>>::start;
		for (int i=0;iter;i++)
		{
			if (iter->value.key == key)
			{
				List<KeyVal<T>>::removeAt(i);
				return true;
			}
			iter = iter->next;
		}
		return false;
	}
	bool remove(KeyVal<T> pair)
	{
		return List<KeyVal<T>>::removeEle(pair);
	}
};

template<typename T>
struct SplayNode {
	KeyVal<T> data;
	SplayNode<T>* left;
	SplayNode<T>* right;
};

template<typename T>
class SplayTree : public Container<T> {
	SplayNode<T>* root;

	SplayNode<T>* private_insert(SplayNode<T>* cur, KeyVal<T> data) {
		if (cur == NULL) {
			cur = new SplayNode<T>;
			cur->data = data;
			cur->left = NULL;
			cur->right = NULL;
		}
		else {
			if (data < cur->data) {
				cur->left = private_insert(cur->left, data);
			}
			else if (data > cur->data) {
				cur->right = private_insert(cur->right, data);
			}
		}
		return cur;
	}
	SplayNode<T>* rr_rotation(SplayNode<T>* node) {
		SplayNode<T>* tmp = node; // tmp is original root
		node = tmp->left;
		tmp->left = node->right;
		node->right = tmp;
		return node;
	}
	SplayNode<T>* ll_rotation(SplayNode<T>* node) {
		SplayNode<T>* tmp = node; // tmp is original root
		node = tmp->right;
		tmp->right = node->left;
		node->left = tmp;
		return node;
	}

	// splays a tree using key, and also returns it if key matches
	SplayNode<T>* splay(SplayNode<T>* node, T key) {
		if (node == NULL || node->data.key == key) {
			return node;
		}

		if (key < node->data.key) {
			if (node->left && key < node->left->data.key) { // key is likely in left child's left subtree (rr case)
				node->left->left = splay(node->left->left, key); // bubble up key to become root of left left
				node = rr_rotation(node);
			}
			else if (node->left && key > node->left->data.key) {
				node->left->right = splay(node->left->right, key);
				if (node->left->right) { // perform left rotation only if there is a right child of left child
					node->left = ll_rotation(node->left);
				}
			}
			if (node->left) {
				node = rr_rotation(node); // after previous rr/ll_rotations, this final rotation will make the searched key thew new root
			}
			return node;
		}
		else if (key > node->data.key) { // key is likely in right child
			if (node->right && key > node->right->data.key) { // key is likely in right child right subtree
				node->right->right = splay(node->right->right, key);
				node = ll_rotation(node);
			}
			else if (node->right && key < node->right->data.key) { // key is likely in right child left subtree
				node->right->left = splay(node->right->left, key);
				if (node->right->left) {
					node->right = rr_rotation(node->right);
				}
			}
			if (node->right) {
				node = ll_rotation(node);
			}
			return node;
		}
	}
	void destroy(SplayNode<T>* cur) {
		if (cur == NULL) {
			return;
		}

		destroy(cur->left);
		destroy(cur->right);
		delete cur;
	}
	SplayNode<T>* copy_tree(SplayNode<T>* other) {
		if (other == NULL) { // no copying performed
			return NULL;
		}
		SplayNode<T>* cur = new SplayNode<T>;
		cur->data = other->data;
		cur->left = copy_tree(other->left);
		cur->right = copy_tree(other->right);
		return cur;

	}
public:
	SplayTree() {
		this->root = NULL;
	}
	SplayTree(const SplayTree<T>& other) {
		this->root = NULL;
		this->root = copy_tree(other.root);
	}
	SplayTree& operator=(const SplayTree<T>& other) {
		this->root = NULL;
		this->root = copy_tree(other.root);
		return *this;
	}
	virtual ~SplayTree() {
		destroy(this->root);
	}
	SplayNode<T>* get_root() {
		return this->root;
	}

	void insert(KeyVal<T> kv) override {
		this->root = this->private_insert(this->root, kv);
	}
	KeyVal<T>* search(T key) override {
		SplayNode<T>* node = this->splay(this->root, key); // whenever searching is performed, the key becomes new root. If it doesn't exist, then the parent of where key is inserted will become root
		this->root = node;
		return node && node->data.key == key ? &node->data : NULL;
	}

	bool removeKey(T key) override {
		this->root = this->splay(this->root, key);
		if (!this->root || this->root->data.key != key) { // no root found
			return false;
		}
		if (this->root && this->root->data.key == key) {
			SplayNode<T>* to_delete = this->root;
			if (this->root->left && this->root->right) {
				SplayNode<T>* max_left = splay(this->root->left, key); // key is root, and so all the children on left will be smaller. splaying the left tree with key will give right-most value
				this->root = max_left;
				max_left->right = to_delete->right;
			}
			else if (this->root->left) {
				this->root = this->root->left;
			}
			else {
				this->root = this->root->right;
			}
			delete to_delete;
			return true;
		}
	}

	bool remove(KeyVal<T> key) override { return this->removeKey(key.key); }

	void clear() override {
		destroy(this->root);
		this->root = NULL;
	}
};

class Machine
{
public:
	string name;
	Queue<Message> inQ;
	Queue<Message> outQ;
	string cRouterName = string();
	Machine(string n=string(), string conRouName=string()) :name(n), cRouterName(conRouName) {}
};

class Router
{
public:
	string name;
	PriorityQueue<Message> inQ;
	Queue<Message> outQ;
	Container<string>* routingTable;
	Router(string n = string(), string routType="splay") :name(n) 
	{
		if (routType == "splay")
		{
			routingTable = new SplayTree<string>();
		}
		else
		{
			routingTable = new KeyValList<string>();
		}
	}
};

static mutex queue_lock;
static Queue<string> cmds;

class Network
{
	string routingContainer;
	List<Machine> machines;
	List<Router> routers;
	Graph<string> connections;
	List<string> parseLineCSV(string s, char delim = ',')
	{
		List<string> out;
		string temp = string();
		for (int index = 0; s[index]; index++)
		{
			if (s[index] == delim) 
			{
				out.insert(temp);
				temp = string();
				continue; 
			}
			temp.push_back(s[index]);
			if (s[index + 1] == '\0')
			{
				out.insert(temp);
				temp = string();
			}
		}
		return out;
	}
	bool writeToFile(string filename, string content)
	{
		ofstream fout(filename);
		if (!fout.is_open())
		{
			return false;
		}
		else
		{
			fout << content;
			fout.close();
			return true;
		}
	}
	bool appendToFile(string filename, string content)
	{
		ifstream check(filename);
		if (check.fail())
		{
			return false;
		}
		else
		{
			check.close();
			ofstream fout(filename, ios::app);
			fout << content;
			fout.close();
			return true;
		}
	}
public:
	Network(string routingContainer="splay") :connections(50),routingContainer(routingContainer) {}
	void populateLists(string filename)
	{
		ifstream fin(filename);
		string line = string();
		if (fin.is_open())
		{
			getline(fin, line);
			List<string> li = parseLineCSV(line);
			ListNode<string>* iter = li.getStart();
			iter = iter->next; //skip first column as it will be empty
			while (iter)
			{
				if (iter->value[0] == 'M')
				{
					machines.insert(Machine(iter->value));
				}
				else if (iter->value[0] == 'R')
				{
					routers.insert(Router(iter->value, routingContainer));
					connections.insertNode(iter->value);
				}
				iter = iter->next;
			}
			fin.close();
		}
		else
		{
			cout << "File could not be opened! ~populateLists().\n";
		}
	}
	void makeGraph(string filename)
	{
		ifstream fin(filename);
		string line = string();
		if (fin.is_open()) //File Opened Successfully
		{
			getline(fin, line);	//Read first line from file
			List<string> head = parseLineCSV(line); //save the parsed contents of first line(headers of data)
			List<string> row;
			string rowHead;
			head.removeAt(0);	//remove the empty cell in the parsed header
			while (!fin.eof())	//loop until file not completely read
			{
				line = string();	
				rowHead = string();
				getline(fin, line);	//read line from file
				row = parseLineCSV(line);	//parse line and save in variable row
				if (row.getLen() < head.getLen())	//skip line if number of elements in row are less than headers
				{
					continue;
				}
				rowHead = row.Start();	//save the first value in row in rowHead
				row.removeAt(0);		//remove the first value from row
				ListNode<string>* rowIter;
				ListNode<string>* headIter;
				for (rowIter = row.getStart(), headIter = head.getStart(); rowIter && headIter; )	//loop through each element of row and headers of data simultaneously
				{
					if (rowIter->value != "?") //If cell is not empty("?" means empty cell)
					{
						if (rowHead[0] == 'M' && headIter->value[0] == 'R') //if row is of a machine and header of a router then add the router name to the specific machine
						{
							for (ListNode<Machine>* oIter = machines.getStart(); oIter;)
							{
								if (oIter->value.name == rowHead)
								{
									oIter->value.cRouterName = headIter->value;
									break;
								}
								oIter = oIter->next;
							}
						}
						else if (headIter->value[0] != 'M') //if both row and header is router then add the edge in the graph of the specified weight
						{
							connections.insertEdge(rowHead, headIter->value, stoi(rowIter->value));
						}
					}
					rowIter = rowIter->next;
					headIter = headIter->next;
				}
			}
		}
		else
		{
			cout << "File could not be opened! ~makeGraph().\n";
		}
	}
	void updateRoutingTable()
	{
		List<List<string>> sPaths;
		for(ListNode<Router>* rIter = routers.getStart();rIter;)
		{
			rIter->value.routingTable->clear();
			sPaths = connections.shortestPaths(rIter->value.name);
			for (ListNode<Machine>* mIter = machines.getStart();mIter;)
			{
				for (ListNode<List<string>>* pIter = sPaths.getStart(); pIter;)
				{
					if (pIter->value.Last() == mIter->value.cRouterName)
					{
						if (pIter->value.getLen() == 1)
						{
							rIter->value.routingTable->insert(KeyVal<string>(mIter->value.name, mIter->value.name));
						}
						else
						{
							rIter->value.routingTable->insert(KeyVal<string>(mIter->value.name, pIter->value.getStart()->next->value));
						}
						break;
					}
					pIter = pIter->next;
				}
				mIter = mIter->next;
			}
			rIter = rIter->next;
		}
	}
	bool sendMessage(Message m)
	{
		for (ListNode<Machine>* iter = machines.getStart(); iter;)
		{
			if (iter->value.name == m.source)
			{
				iter->value.outQ.enqueue(m);
				return true;
			}
			iter = iter->next;
		}
		return false;
	}
	bool addToRTable(string routerName, string dest, string router)
	{
		KeyVal<string> pair(dest, router);
		for (ListNode<Router>* iter = routers.getStart(); iter;)
		{
			if (iter->value.name == routerName)
			{
				iter->value.routingTable->removeKey(dest);
				iter->value.routingTable->insert(pair);
				return true;
			}
			iter = iter->next;
		}
		return false;
	}
	bool remFromRTable(string routerName, string dest, string router)
	{
		KeyVal<string> pair(dest, router);
		for (ListNode<Router>* iter = routers.getStart(); iter;)
		{
			if (iter->value.name == routerName)
			{
				return iter->value.routingTable->remove(pair);
			}
			iter = iter->next;
		}
		return false;
	}
	string printPath(string source, string dest)
	{
		string path = source;
		bool possible = false;
		string nextRouter = string();
		for (ListNode<Machine>* iter = machines.getStart(); iter;)
		{
			if (iter->value.name == source)
			{
				nextRouter = iter->value.cRouterName;
				path += " -> " + nextRouter;
				possible = true;
				break;
			}
			iter = iter->next;
		}
		if (!possible) { return string(); }
		while (1)
		{
			possible = false;
			for (ListNode<Router>* iter = routers.getStart(); iter;)
			{
				if (iter->value.name == nextRouter)
				{
					KeyVal<string>* temp = iter->value.routingTable->search(dest);
					if (!temp) { return string(); }
					nextRouter = iter->value.routingTable->search(dest)->val;
					path += " -> " + nextRouter;
					if (nextRouter[0] == 'M')
					{
						return path;
					}
					possible = true;
					break;
				}
				iter = iter->next;
			}
			if (!possible) { return string(); }
		}
	}
	void forwardMessages(bool print = false)
	{
		if (print) { cout << "----------\n"; }
		for (ListNode<Router>* iter = routers.getStart();iter;) //Moving the messages in InQ of all the routers to outQ
		{
			while (!iter->value.inQ.isEmpty())
			{
				iter->value.outQ.enqueue(iter->value.inQ.getMax());
			}
			iter = iter->next;
		}
		for (ListNode<Machine>* oIter = machines.getStart(); oIter;) //Forwarding Messages from outQ of all machine
		{
			if (!oIter->value.outQ.isEmpty())
			{
				Message tmpMsg = oIter->value.outQ.dequeue();
				string receiver = oIter->value.cRouterName;
				bool received = false;
				for (ListNode<Router>* iIter = routers.getStart(); iIter;)
				{
					if (iIter->value.name == receiver)
					{
						tmpMsg.trace = to_string(tmpMsg.id) + ":" + oIter->value.name + ":" + iIter->value.name;
						iIter->value.inQ.insert(tmpMsg, tmpMsg.prio);
						if(print)
						{
							cout << "Message(" << tmpMsg.id << "," << tmpMsg.payload << ") moved from " << oIter->value.name << " to " << iIter->value.name << endl;
						}
						received = true;
						break;
					}
					iIter = iIter->next;
				}
				if (!received)
				{
					cout << "Message with id: " << tmpMsg.id << " from source: " << tmpMsg.source << " has been lost!\n";
				}
			}
			oIter = oIter->next;
		}
		for (ListNode<Router>* oIter = routers.getStart(); oIter;)
		{
			if (!oIter->value.outQ.isEmpty())
			{
				Message tmpMsg = oIter->value.outQ.dequeue();
				KeyVal<string>* sourceDest = oIter->value.routingTable->search(tmpMsg.dest);
				if (!sourceDest)
				{
					cout << "Message with id: " << tmpMsg.id << " from source: " << tmpMsg.source << " has been lost!\n";
				}
				string receiver = sourceDest->val;
				if(receiver[0]=='R')
				{
					for (ListNode<Router>* iIter = routers.getStart(); iIter;)
					{
						if (iIter->value.name == receiver)
						{
							tmpMsg.trace = tmpMsg.trace + ":" + iIter->value.name;
							iIter->value.inQ.insert(tmpMsg, tmpMsg.prio);
							if (print)
							{
								cout << "Message(" << tmpMsg.id << "," << tmpMsg.payload << ") moved from " << oIter->value.name << " to " << iIter->value.name << endl;
							}
							break;
						}
						iIter = iIter->next;
					}
				}
				else
				{
					for (ListNode<Machine>* iIter = machines.getStart(); iIter;)
					{
						if (iIter->value.name == receiver)
						{
							tmpMsg.trace = tmpMsg.trace + ":" + iIter->value.name;
							iIter->value.inQ.enqueue(tmpMsg);
							if (print)
							{
								cout << "Message(" << tmpMsg.id << "," << tmpMsg.payload << ") moved from " << oIter->value.name << " to " << iIter->value.name << endl;
							}
							if(!appendToFile("path.txt", "\n"+tmpMsg.trace))
							{
								if (!writeToFile("path.txt", tmpMsg.trace))
								{
									cout << "Trace writing to file failed!\n";
								}
							}
							break;
						}
						iIter = iIter->next;
					}
				}
			}
			oIter = oIter->next;
		}
		if (print) { cout << "----------\n"; }
	}
	void routerSimThread()
	{
		while (true) {
			queue_lock.lock(); // obtains the lock, if it's not being used right now
			while (!cmds.isEmpty()) {
				string command = cmds.dequeue();
				execCommand(command);
			}
			queue_lock.unlock();
			//cout << "Simulating routers" << endl;
			forwardMessages();
			chrono::seconds duration(1);
			this_thread::sleep_for(duration);
		}
	}
	void execCommand(string command)
	{
		command = strip(command);
		if (command == "") 
		{
			cout << "Command was invalid: \"" << command << "\"\n";
			return;
		}
		int weight = 0, count = 1;

		string comm, subcom, filename, params;
		string routetab, route;
		string parameter1, parameter2, value;

		char array[50] = {};

		for (int i = 0; command[i] != '\0'; i++)
		{
			array[i] = command[i];
		}

		char delim[] = { ' ', ',' , 0 };
		char zdelim[] = { 0 };
		char* token, * next_token = nullptr;

		token = strtok_s(array, delim, &next_token);
		comm = token;

		if (lowerStr(comm) == "send")
		{
			while (token != NULL)
			{
				if (token != NULL)
				{
					if (count == 1)
					{
						token = strtok_s(NULL, delim, &next_token);
						if (!token)
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
						subcom = token;
						if (lowerStr(token) != "msg")
						{
							cout << "Command was invalid: \""<<command<<"\"\n";
							return;
						}
						count++;
					}
					else if (count == 2)
					{
						token = strtok_s(NULL, zdelim, &next_token);
						if (!token)
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
						params = token;
						count++;
					}
					else
					{
						token = strtok_s(NULL, delim, &next_token);
						if (token != nullptr)
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
					}
				}
			}
			count = 1;
			if (countChar(params, ':') != 4 && countChar(params, '.') != 1)
			{
				cout << "Command was invalid: \"" << command << "\"\n";
				return;
			}
			else if (countChar(params, '.') == 1 and countChar(params, ' ') == 0)
			{
				filename = params;
				ifstream fin(filename);
				if (!fin.is_open())
				{
					cout << "File could not be opened: \""<<filename<<"\"\n";
					return;
				}
				else
				{
					while (!fin.eof())
					{
						getline(fin, params);
						if (params != "")
						{
							execCommand(comm + " " + subcom + " " + params);
						}
					}
					fin.close();
				}
			}
			else
			{
				List<string> funcParams;
				string temp;
				for (int i = 0; i < 4; i++)
				{
					temp = params.substr(0, params.find(':'));
					params = params.substr(params.find(':') + 1, -1);
					if (i < 2)
					{
						if (!isNumber(temp))
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
					}
					else
					{
						if (!isAlNum(temp))
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
					}
					funcParams.insertAt(-1, temp);
				}
				funcParams.insertAt(-1, params);
				Message m(stoi(funcParams.getStart()->value), stoi(funcParams.getStart()->next->value), funcParams.getStart()->next->next->value, funcParams.getStart()->next->next->next->value, funcParams.getStart()->next->next->next->next->value);
				if (sendMessage(m))
				{
					cout << "Command Executed: \"" << command << "\"\n";
				}
				else
				{
					cout << "Command Error: Failed to find source router!\n";
				}
			}
		}
		else if (lowerStr(comm) == "change")
		{
			while (token != NULL)
			{
				if (token != NULL)
				{
					if (count == 1)
					{

						token = strtok_s(NULL, delim, &next_token);
						if (!token)
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
						subcom = token;
						count++;

						//edge case
						if (lowerStr(subcom) == "edge")
						{
							bool txt = false;

							filename = next_token;
							token = strtok_s(NULL, delim, &next_token);
							if (!token)
							{
								cout << "Command was invalid: \"" << command << "\"\n";
								return;
							}

							if (countChar(filename, '.') == 1 && countChar(filename, ' ') == 0)
							{
								ifstream fin(filename);
								if (!fin.is_open())
								{
									cout << "File could not be opened: \"" << filename << "\"\n";
								}
								else
								{
									makeGraph(filename);
									updateRoutingTable();
									cout << "Command Executed: \"" << command << "\"\n";
								}
								count = 0;
							}
							else
							{
								parameter1 = token;
								count++;

								if (count == 3)
								{
									token = strtok_s(NULL, delim, &next_token);
									parameter2 = token;
									count++;

									if (count == 4)
									{
										token = strtok_s(NULL, delim, &next_token);
										if (!token)
										{
											cout << "Command was invalid: \"" << command << "\"\n";
											return;
										}
										value = token;
										count++;

										if (!isAlNum(parameter1) || !isAlNum(parameter2) || !isNumber(value))
										{
											cout << "Command was invalid: \"" << command << "\"\n";
											return;
										}
										weight = stoi(value);

										connections.changeEdgeWeight(parameter1, parameter2, weight);
										connections.changeEdgeWeight(parameter2, parameter1, weight);
										updateRoutingTable();
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else
									{
										token = strtok_s(NULL, delim, &next_token);
									}
								}
							}
						}

						//routing table change case
						else if (lowerStr(subcom) == "rt")
						{

							token = strtok_s(NULL, delim, &next_token);
							if (!token)
							{
								cout << "Command was invalid: \"" << command << "\"\n";
								return;
							}
							route = token;
							if (lowerStr(route)[0] != 'r')
							{
								cout << "Command was invalid: \"" << command << "\"\n";
								return;
							}
							count++;

							if (count == 3)
							{
								token = strtok_s(NULL, delim, &next_token);
								routetab = token;
								count++;

								//add routing table
								if (lowerStr(routetab) == "add")
								{
									token = strtok_s(NULL, zdelim, &next_token);
									filename = token;
									if (countChar(filename, ':') == 1)
									{
										params = filename;
										parameter1 = params.substr(0, params.find(':'));
										parameter2 = params.substr(params.find(':') + 1);
										if (!isAlNum(parameter1) || !isAlNum(parameter2))
										{
											cout << "Command was invalid: \"" << command << "\"\n";
											return;
										}
										addToRTable(route, parameter1, parameter2);
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else if (countChar(filename, '.') == 1 && countChar(filename, ' ') == 0)
									{
										ifstream fin(filename);
										if (!fin.is_open())
										{
											cout << "File could not be opened: \"" << filename << "\"\n";
											return;
										}
										else
										{
											while (!fin.eof())
											{
												getline(fin, params);
												if (params != "")
												{
													execCommand(comm + " RT " + route + " add " + params);
												}
											}
											fin.close();
										}
									}
									else
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
								}
								//remove routing table
								else if (lowerStr(routetab) == "remove")
								{
									token = strtok_s(NULL, zdelim, &next_token);
									filename = token;
									if (countChar(filename, ':') == 1)
									{
										params = filename;
										parameter1 = params.substr(0, params.find(':'));
										parameter2 = params.substr(params.find(':') + 1);
										if (parameter1[0] != 'M' || !isNumber(parameter1.substr(1)) || parameter2[0] != 'R' || !isNumber(parameter2.substr(1)))
										{
											cout << "Command was invalid: \"" << command << "\"\n";
											return;
										}
										remFromRTable(route, parameter1, parameter2);
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else if (countChar(filename, '.') == 1 && countChar(filename, ' ') == 0)
									{
										ifstream fin(filename);
										if (!fin.is_open())
										{
											cout << "File could not be opened!\n";
											return;
										}
										else
										{
											while (!fin.eof())
											{
												getline(fin, params);
												if (params != "")
												{
													execCommand(comm + " RT " + route + " remove " + params);
												}
											}
											fin.close();
										}
									}
									else
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
								}
								else
								{
									cout << "Command was invalid: \"" << command << "\"\n";
									return;
								}
							}
						}
						else
						{
						cout << "Command was invalid: \"" << command << "\"\n";
						return;
						}
					}
					else
					{
						token = strtok_s(NULL, delim, &next_token);
					}
				}
			}
			count = 0;

		}
		else if (lowerStr(comm) == "print")
		{
			while (token != NULL)
			{
				if (token != NULL)
				{
					if (count == 1)
					{
						token = strtok_s(NULL, delim, &next_token);
						if (!token)
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
						subcom = token;
						count++;

						if (lowerStr(subcom) == "path")
						{
							token = strtok_s(NULL, delim, &next_token);
							if (!token)
							{
								cout << "Command was invalid: \"" << command << "\"\n";
								return;
							}
							parameter1 = token;
							count++;

							if (parameter1 == "*")//from all to parameter2
							{
								token = strtok_s(NULL, delim, &next_token);
								count++;

								if (count == 4)
								{
									token = strtok_s(NULL, delim, &next_token);
									if (!token)
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
									parameter2 = token;

									if (isAlNum(token))
									{
										token = NULL;
										// * to parameter2
										for (ListNode<Machine>* iter = machines.getStart(); iter; )
										{
											if (iter->value.name != parameter2)
											{
												cout << printPath(iter->value.name, parameter2) << endl;
											}
											iter = iter->next;
										}
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
								}
							}
							else if (isAlNum(token))
							{
								token = strtok_s(NULL, delim, &next_token);
								count++;

								if (count == 4)
								{

									token = strtok_s(NULL, delim, &next_token);
									if (!token)
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
									parameter2 = token;
									count++;

									if (parameter2 == "*")
									{
										token = NULL;
										// parameter1 to *
										for (ListNode<Machine>* iter = machines.getStart(); iter; )
										{
											if (iter->value.name != parameter1)
											{
												cout<<printPath(parameter1, iter->value.name)<<endl;
											}
											iter = iter->next;
										}
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else if (isAlNum(token))
									{
										token = NULL;
										cout << printPath(parameter1, parameter2) << endl;
										cout << "Command Executed: \"" << command << "\"\n";
									}
									else
									{
										cout << "Command was invalid: \"" << command << "\"\n";
										return;
									}
								}
							}
							else
							{
								cout << "Command was invalid: \"" << command << "\"\n";
								return;
							}

						}
						else
						{
							cout << "Command was invalid: \"" << command << "\"\n";
							return;
						}
					}
				}
			}
		}
		else
		{
			cout << "Command was invalid: \"" << command << "\"\n";
			return;
		}
	}
};