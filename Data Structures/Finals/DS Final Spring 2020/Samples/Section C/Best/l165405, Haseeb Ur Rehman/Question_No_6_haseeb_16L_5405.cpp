//Haseeb
//16L-5405
//QUESTION NO 6 


#include<iostream>
using namespace std;

//template for generic type 
template<typename K, typename V>

//Hashnode class 
class HashNode
{
public:
	V value;
	K key;
	int next;

	//Constructor of hashnode 
	HashNode(K key, V value, int next)
	{
		this->value = value;
		this->key = key;
		this->next = next;
	}
	HashNode(K key, V value)
	{
		this->value = value;
		this->key = key;
		this->next = NULL;
	}
};

//template for generic type 
template<typename K, typename V>

//Our own Hashmap class 
class HashMap
{
	//hash element array 
	HashNode<K, V>** arr;
	int capacity;
	//current size 
	int size;
	//dummy node 
	HashNode<K, V>* dummy;

public:
	HashMap()
	{
		//Initial capacity of hash array 
		capacity = 20;
		size = 0;

		arr = new HashNode<K, V> *[capacity];

		//Initialise all elements of array as NULL 
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;

		//dummy node with value and key -1 
		dummy = new HashNode<K, V>(-1, -1);
	}
	// This implements hash function to find index 
	// for a key 
	int hashCode(K key)
	{
		return key % capacity;
	}
	
	////////////////////////////// PART A : INSERT KEY //////////////////////////////////////////////////

	//Function to add key value pair 
	void insertNode(K key, V value)
	{
		HashNode<K, V>* temp = new HashNode<K, V>(key, value);

		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		//Saving the value of hashIndex to store value in next
		int pre = hashIndex;

		cout << "HashIndex=" << hashIndex << endl;
		//cout << arr[hashIndex];

		//find next free space 
		while (arr[hashIndex] != NULL && (arr[hashIndex]->key != key
			|| arr[hashIndex]->key != -1))
		{
			//cout<<"WHILE true";
			pre = hashIndex;
			hashIndex++;
			//cout << "hashIndex =" << hashIndex; 

			hashIndex %= capacity;
			//cout <<"hashIndex %= capacity ="<< hashIndex;

		}

		//if new node to be inserted increase the current size 
		if (arr[hashIndex] == NULL || arr[hashIndex]->key == -1) {
			//hashIndex++; 
			//hashIndex %= capacity;
			//cout <<"if new node to be inserted increase the current size";	
			size++;

		}

		arr[hashIndex] = temp;
		
		//Setting up the next Attribute Value if hashIndex value 
		//Node is not NULL
		if (pre != hashIndex)
		{
			arr[pre]->next = hashIndex;
		}
	}

	////////////////////////////// PART B : DELETE KEY //////////////////////////////////////////////////


	//Function to delete a key value pair 
	V deleteNode(int key)
	{
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);

		//finding the node with given key 
		while (arr[hashIndex] != NULL)
		{
			//if node found 
			if (arr[hashIndex]->key == key)
			{
				HashNode<K, V>* temp = arr[hashIndex];

				//Insert dummy node here for further use 
				arr[hashIndex] = dummy;

				// Reduce size 
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;

		}

		//If not found return null 
		cout << "Key not found";
		return 0;
	}

	bool SEARCH(int key)
	{
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		cout << "Mmmmmm hashIndex " << hashIndex << endl;
		//finding the node with given key 
		while (arr[hashIndex] != NULL)
		{
			cout << "key = " << arr[hashIndex]->key
				<< " value = " << arr[hashIndex]->value
				<< " Next = " << arr[hashIndex]->next << endl;

			//if node found return true 
			if (arr[hashIndex]->key == key)
				return true;
			
			hashIndex = arr[hashIndex]->next;

			if (hashIndex == NULL)
			{
				return false;
			}
		}

		//if not found
		return false;
	}

	//Function to search the value for a given key 
	V get(int key)
	{
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);
		int counter = 0;
		//finding the node with given key 
		while (arr[hashIndex] != NULL)
		{
			int counter = 0;
			if (counter++ > capacity) //to avoid infinite loop 
				return -20;
			//if node found return its value 
			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;
			hashIndex++;
			hashIndex %= capacity;
		}

		//If not found return -10 
		return -10;
	}

	//Return current size 
	int sizeofMap()
	{
		return size;
	}

	//Return true if size is 0 
	bool isEmpty()
	{
		return size == 0;
	}

	//Function to display the stored key value pairs 
	void display()
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] != NULL && arr[i]->key != -1)
				cout << "key = " << arr[i]->key
				<< " value = " << arr[i]->value
				<< " Next = " << arr[i]->next << endl;
			//cout << i << endl;
		}
	}
};


////////////////////////////// PART C : worst complexity : O(N) for both insert and delete key  //////////////////////////////////////////////////


/////////////////////////////// MAIN FUNCTION /////////////////////////////////

//Driver method to test map class 
int main()
{
	HashMap<int, int>* h = new HashMap<int, int>;
	h->insertNode(1, 1);
	//h->display(); 
	h->insertNode(3, 13);
	h->insertNode(2, 2);
	//h->display(); 
	h->insertNode(2, 3);
	h->display();

	//h->display(); 
	h->insertNode(3, 33);

	cout << "h->sizeofMap()" << endl;
	cout << h->sizeofMap() << endl;
	cout << "h->display()";
	h->display();

	cout << h->deleteNode(2) << endl;
	cout << "h->sizeofMap()" << endl;
	cout << h->sizeofMap() << endl;
	h->display();
	cout << h->isEmpty() << endl;

	cout << h->get(2) << endl;

	system("pause");

	cout << "Search Index" << h->SEARCH(3);

	system("pause");

	return 0;
}
