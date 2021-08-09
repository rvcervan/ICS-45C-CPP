#include "HashMap.hpp"
#include "HashFunction.hpp"
#include <string>
#include <iostream>


HashMap::HashMap()
	: HashTablesize{0}, HashTable{new Node*[initialBucketCount]}, thehash{Hash}, buckets{initialBucketCount}
{
}

HashMap::HashMap(HashFunction hasher)
	: HashTablesize{0}, HashTable{new Node*[initialBucketCount]}, thehash{Hash}, buckets{initialBucketCount}
{
	thehash = hasher;
}

HashMap::HashMap(const HashMap& hm)
	: HashTablesize{0}, HashTable{new Node*[hm.buckets]}, thehash{hm.thehash}, buckets{hm.buckets}
{
	for(int i = 0; i < buckets; ++i)
	{
		Node* current = HashTable[i];
		while(current != nullptr)
		{
			HashMap::add(current->key, current->value);
			current = current->next;
		}
	}
}

HashMap::~HashMap()
{
	delete[] HashTable;
}

HashMap& HashMap::operator=(const HashMap& hm)
{
	if(this != &hm)
	{
		Node** newHashTable = new Node*[hm.buckets];
		for(int i = 0; i < buckets; ++i)
		{
			Node* current = HashTable[i];
			while(current != nullptr)
			{//fix in this while loop
				HashMap::add(current->key, current->value);
				current = current->next;
			}
		}

		thehash = hm.thehash;
		buckets = hm.buckets;
		HashMap::removeAllNodes();

		delete[] HashTable;
		HashTable = newHashTable;

	}

	return *this;
}

void HashMap::add(const std::string& key, const std::string& value)
{
	//DONT TOUCH ITS FIXED?
	int index = thehash(key) % buckets;
	Node*& current = HashTable[index];


	Node* tail;
	tail = HashTable[index];


	Node* newNode = new Node;

	newNode->key = key;
	newNode->value = value;
	newNode->next = nullptr;

	if(tail == nullptr)
	{
		current = newNode;
	}
	else
	{
		while(tail->next != nullptr)
		{
			tail = tail->next;
		}

		tail->next = newNode;
		
	}
	HashTablesize++;


	if(HashMap::loadFactor() > 0.8)
	{
		HashMap::rehash();
	}
	// delete newNode;
	
}

void HashMap::loggingon(const std::string& key, const std::string& value)
{
	int index = thehash(key) % buckets;

	Node* current = HashTable[index];

	while(current != nullptr)
	{	
		if(key == current->key && value == current->value)
		{	
			std::cout << "SUCCEEDED" << std::endl;
			return;
		}
		current = current->next;
	}


	std::cout << "FAILED" << std::endl;
}

bool HashMap::contains(const std::string& key) const
{	
	//DONT TOUCH IT 
	int index = thehash(key) % buckets;

	Node* current = HashTable[index];

	while(current != nullptr)
	{	
		if(key == current->key)
		{	
			

			return 1;
		}
		current = current->next;
	}

	return 0;
}

void HashMap::rehash()
{
	//DONT TOUCH ITS GOOD
	int newBucketCount = buckets * 2 + 1;

	Node** newHashTable = new Node*[newBucketCount];
	Node** oldtable = HashTable;

	HashTable = newHashTable;
	HashTablesize = 0;

	int oldbucket = buckets;
	buckets = newBucketCount;

	for(int i = 0; i < oldbucket; ++i)
	{
		Node* head = oldtable[i];
		Node* headnext;
		if(head == nullptr)
		{
		}
		else
		{
			headnext = head->next;
			while(head != nullptr)
			{
				HashMap::add(head->key, head->value);
				delete head;
				head = headnext;
				if(headnext == nullptr)
				{
				}
				else
				{
					headnext = headnext->next;
				}
			}
		}
	}
	delete[] oldtable;

}

void HashMap::remove(const std::string& key)
{

	//DON'T TOUCH ITS GOOD
	int index = thehash(key) % buckets;

	Node* current = HashTable[index];
	Node* trail = nullptr;

	if(current == nullptr)
	{
		std::cout << "NONEXISTENT" << std::endl;
	}
	else
	{
		while(current != nullptr)
		{
			if(current->key == key)
			{
				break;
			}
			else
			{
				trail = current;
				current = current->next;
			}
		}
		if(current == nullptr)
		{
			std::cout << "NONEXISTENT" << std::endl;
		}
		else
		{
			if(HashTable[index] == current)
			{
				HashTable[index] = HashTable[index]->next;
				
			}
			else
			{
				trail->next = current->next;

			}
			delete current;
			std::cout << "REMOVED" << std::endl;
			HashTablesize--;
		}
	}

}

void HashMap::removeAllNodes()
{
	//DON'T TOUCH ITS GOOD

	for(int i = 0; i < buckets; i++)
	{	
		Node* head = HashTable[i];
		Node* headnext;
		if(head == nullptr)
		{
		}
		else
		{
			headnext = head->next;
			while(head != nullptr)
			{
				delete head;
				head = headnext;
				if(headnext == nullptr)
				{
				}
				else
				{
					headnext = headnext->next;
				}
			}
		}
	}
	HashTablesize = 0;
}



std::string HashMap::value(const std::string& key) const //returns value or empty string
{
	//DON'T TOUCH ITS GOOD

	int index = thehash(key) % buckets;

	Node* current = HashTable[index];

	while(current != nullptr)
	{
		if(key == current->key)
		{
			return current->value;
		}
		current = current->next;
	}
	return "";
}

unsigned int HashMap::size() const
{
	//DON'T TOUCH ITS GOOD

	return HashTablesize;
}

unsigned int HashMap::bucketCount() const
{
	//DON'T TOUCH ITS GOOD

	return buckets;
}

double HashMap::loadFactor() const
{
	//DON'T TOUCH ITS GOOD

	double load = HashMap::size() * 1.0/buckets;
	return load;
}

unsigned int HashMap::maxBucketSize() const
{
	//DON'T TOUCH ITS GOOD

	unsigned int max = 0;

	for(unsigned int i = 0; i < buckets; i++)
	{
		Node* current = HashTable[i];

		unsigned int amount = 0;

		while(current != nullptr)
		{
			amount++;
			current = current->next;
		}

		if(amount > max)
		{
			max = amount;
		}

	}

	return max;
}

void HashMap::gimmeHashTablesize()
{
	//DON'T TOUCH ITS GOOD

	std::cout << HashTablesize << std::endl;
}

void HashMap::gimmebuckets()//???? buckets made from add() or total number of array cells?
{
	//DON'T TOUCH ITS GOOD

	std::cout << buckets << std::endl;
}

void HashMap::displayAllNodesInfo_Index_HashValue()
{
	//DON'T TOUCH ITS GOOD

	for(unsigned int i = 0; i < buckets; i++)
	{
		Node* current = HashTable[i];

		while(current != nullptr)
		{
			int index = thehash(current->key) % buckets;

			std::cout << current->key << " is at array index " << i 
			<<" and its hash value is " << index << std::endl;

			
			
			current = current->next;
		}
	}
}