// #include<iostream>
#include "mylist.h"
//=============================================================================
// #include "flighthashtable.h"
template <typename T> MyList<T>::MyList()
{
	head=nullptr;
	size=0;
}
//=============================================================================
template <typename T> MyList<T>::~MyList()
{
	while (head != nullptr) 
	{
        removeAtHead();
    }
}
//=============================================================================
template <typename T> bool MyList<T>::isEmpty() const
{
	return size == 0;
}
//=============================================================================
template <typename T> int MyList<T>::getSize() const
{
	return size;
}
//=============================================================================
template <typename T> void MyList<T>::insertAtHead(const T &elem) 
{
        ListNode<T> *newNode = new ListNode<T>(elem);
        newNode->next = head;
        head = newNode;
        size++;
}
//=============================================================================
template <typename T> void MyList<T>::removeAtHead() 
{
    if (head == nullptr) 
    {
        return;
    }

    ListNode<T> *nodeToDelete = head;
    head = nodeToDelete->next;
    delete nodeToDelete;
    size--;
}
//=============================================================================
template <typename T> void MyList<T>::remove(const T &elem)
{
	if (head == nullptr) 
	{
        return;
    }

    if (head->elem == elem) 
    {
       	removeAtHead();
        return;
    }

    ListNode<T> *currentNode = head;
    while (currentNode->next != nullptr && currentNode->next->elem != elem) 
    {
        currentNode = currentNode->next;
    }

    if (currentNode->next != nullptr) 
    {
        ListNode<T> *nodeToDelete = currentNode->next;
        currentNode->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;
    }
}
//=============================================================================
template <typename T> int MyList<T>::countCollisions() const 
{
    int collisions = 0;
    if (head!=nullptr) {
        ListNode<T> *curr = head;
        while (curr!=nullptr) 
        {
            ListNode<T> *next = curr->next;
            while (next!=nullptr) 
            {
                if (curr->elem.value.getKey() != next->elem.value.getKey()) 
                {
                    collisions++;
                    break;
                }
                next = next->next;
            }
            curr = curr->next;
        }
    }
    if (collisions>2)
    {
        return collisions-1;
    }
    else
    {
        return collisions;
    }
}
//=============================================================================
template <typename T> ListNode<T>* MyList<T>::search(const T& elem) const
{
    ListNode<T> *current = head;
    while (current != nullptr) 
    {
        if (current->elem == elem) 
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
//=============================================================================
template class ListNode<HashNode>;
template class MyList<HashNode>;