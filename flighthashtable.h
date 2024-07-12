#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include<fstream>
#include<chrono>
#include<sstream>
#include<regex>
#include<cctype>
#include<cstdlib>
using namespace std;

#include "mylist.h"
#include "flightticket.h"

template <typename T>
class ListNode; 
template <typename T>
class MyList;

class HashNode
{
	private:
		string key; //key = companyName+','+flightNumber
		Flight_Ticket value;
	public:
		HashNode(){} //default constructor
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		bool operator==(const HashNode& other) const //overloaded operators to compare all attributes of flight ticket
		{
    		return key == other.key && value == other.value;
		}
		bool operator!=(const HashNode& other) const 
		{
    		return value != other.value;
		}
		friend class FlightHASHTABLE;
		template <typename> friend class MyList;
};
//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;		//List of Buckets, Please create your own Linked List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
	public:
		FlightHASHTABLE();						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string str_key); //implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file
		int count_collisions();					//return the number of collisions in the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		void hashChoice(); 				//method to allow change of hash function at start of program
		void increaseCap();			//increase capacity of hash table when it gets filled up
};
//=============================================================================
#endif
