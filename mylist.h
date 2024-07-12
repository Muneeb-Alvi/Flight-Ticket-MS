#ifndef MY_LIST_H
#define MY_LIST_H

#include<iostream>
using namespace std;

#include "flighthashtable.h"
//=============================================================================
template <typename T>
class ListNode 
{
	private:
		T elem;
		ListNode<T> *next;

	public:
		ListNode(): next(NULL) {}
    	ListNode(const T &elem) : elem(elem), next(NULL) {}
    	friend class FlightHASHTABLE;
    	friend class HashNode;
    	template <typename> friend class MyList;
    	
};
//=============================================================================
template <typename T>
class MyList 
{
	private:
    	ListNode<T> *head;
    	int size;
    public:
    	MyList();
    	~MyList();
    	bool isEmpty() const;
    	int getSize() const;
    	void insertAtHead(const T &elem);	
    	void removeAtHead();
    	void remove(const T &elem);
    	int countCollisions() const; //count collisions in the bucket
    	ListNode<T>* search(const T& elem) const; //search for node in the bucket
    	friend class FlightHASHTABLE;
    	friend class HashNode;
};
//=============================================================================
#endif
