#include "flighthashtable.h"

int collisions = 0;
int choice = 2;
//=============================================================================
FlightHASHTABLE::FlightHASHTABLE() //constructor
{
    capacity = 100000; //default capacity
    size = 0;
    buckets = new MyList<HashNode>[capacity]; //create an array of MyList objects with capacity specified
}
//=============================================================================
FlightHASHTABLE::~FlightHASHTABLE() //destructor
{
    for (int i = 0; i < capacity; i++) 
    {
        MyList<HashNode>* bucket = &buckets[i];
        bucket->~MyList(); //call the destructor of each bucket
    }
    delete[] buckets; //delete the array of buckets
}
//=============================================================================
long FlightHASHTABLE::hashCode(string str_key) //implement and test different hash functions 
{
	if (choice==1) //summation with division function
    {
        long hash = 0;
        for(int i = 0; i < str_key.length(); i++)
        {
            hash += str_key[i];
        }
        return hash % capacity;
    }
    else if (choice==2) //polynomial with division function
    {
        const int a = 33;
        long hash = 0;
        for (int i = 0; i < str_key.length(); i++) 
        {
            hash = (hash * a + str_key[i]);
        }
        return labs(hash)%capacity;
    }
    else if (choice==3) //cycle shift with divison function
    {
        long hash = 0; 
        for (int i = 0; i < str_key.length(); i++) 
        {
            hash = (hash << 5) | (hash >> (27)); //cyclic shift by 5 bits
            hash += str_key[i];
        }
        return labs(hash)%capacity;
    }
    else
    {
        return 0;
    }
}
//=============================================================================
int FlightHASHTABLE::importCSV(string path) //Load all the flight-tickets from the CSV file to the HashTable
{
    if (size>=capacity) //if hashtable is full, increase capacity
    {
        increaseCap();
    }
    string key;
    ifstream file(path);
        if (!file.is_open()) //check if file is open
        {
            cout << "Error: could not open file." << endl;
            return -1;
        }
        string line;
        int count = 0;
        getline(file,line);
        while (getline(file, line)) //while lines in file are present, run the loop
        {
            stringstream ss(line);

            string companyName, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date,number; //get the values separated by commas into the variables
            int flightNumber;
            getline(ss, companyName, ',');
            getline(ss, number, ',');
            const regex flightNumberPattern("^[1-9][0-9]*$"); //validation of flight number
            if (regex_match(number,flightNumberPattern)==false)
            {
                continue;
            }
            getline(ss, country_of_origin, ',');
            const regex country_of_originPattern("^[a-zA-Z]+( [a-zA-Z]+){0,7}$"); //validation of country name
            if (regex_match(country_of_origin,country_of_originPattern)==false)
            {
                continue;
            }
            getline(ss, country_of_destination, ',');
            const regex country_of_destinationPattern("^[a-zA-Z]+( [a-zA-Z]+){0,7}$"); //validation of country name
            if (regex_match(country_of_destination,country_of_destinationPattern)==false)
            {
                continue;
            }
            getline(ss, stopOver, ',');
            const regex stopOverPattern("^[0-9][0-9]*$"); //validation of stop overs
            if (regex_match(stopOver,stopOverPattern)==false)
            {
                continue;
            }
            getline(ss, price, ',');
            const regex pricePattern("^[1-9][0-9]*$"); //validation of price
            if (regex_match(price,pricePattern)==false)
            {
                continue;
            }
            getline(ss, time_of_departure, ',');
            const regex time_of_departurePattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"); //validation of time
            if (regex_match(time_of_departure,time_of_departurePattern)==false)
            {
                continue;
            }
            getline(ss, time_of_arrival, ',');
            const regex time_of_arrivalPattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"); //validation of time
            if (regex_match(time_of_arrival,time_of_arrivalPattern)==false)
            {
                continue;
            }
            getline(ss, date, ',');
            const regex datePattern("^\\d{1,2}-(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)$"); //validation of date
            if (regex_match(date.substr(0,date.find('\r')),datePattern)==false)
            {
                continue;
            }
            flightNumber=stoi(number);
            string companyNameL=companyName;
            for (int i = 0; i < companyNameL.length(); i++) //convert company name to lowercase
            {
                companyNameL[i] = tolower(companyNameL[i]);
            }
            string key = companyNameL+","+to_string(flightNumber); //key is company name in lowercase with flight number
            //cout<<key<<endl;
            Flight_Ticket newFlight(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date.substr(0,date.find('\r'))); //create new flight ticket
            HashNode newNode(key, newFlight);; //create the new hashnode for flight ticket
            long code = hashCode(key); //get the hashcode for new flight ticket
            ListNode<HashNode>* searched=buckets[code].search(newNode);
            if (searched != nullptr)  //if node already exists, continue so skip the line
            {
                continue;  //node already exists
            }
            MyList<HashNode>* bucket = &buckets[code];
            ListNode<HashNode>* current = bucket->head;
            int cnt=0;
            while (current != nullptr) //if keys are the same, increase cnt by 1
            {
                if (newNode.value.getKey()==current->elem.value.getKey())
                {
                    cnt++;
                }
                current=current->next; //go through the whole bucket
            }
            if (cnt==0 && bucket->getSize()>=1) //if key of new node is different that keys of whole bucket then collision so increase collisions by 1
            {
                collisions++;
            }
            buckets[code].insertAtHead(newNode); //insert node into bucket
            size++; //increase size
            count++; //increase count of records imported
        }
        file.close(); //close the file
    return count; //return number of records imported
}
//=============================================================================
int FlightHASHTABLE::exportCSV(string path) //Export all the flight-tickets from the HashTable to a CSV file
{
	ofstream outfile;
    outfile.open(path, ios::out); //if no file with name exists, create it

    if (!outfile.is_open()) //if file cannot be created, error message
    { 
        cout << "Error: Unable to create file " << path << endl;
        return -1;
    }
    int count = 0;
    for (int i = 0; i < capacity; i++)
    {
        MyList<HashNode>* bucket = &buckets[i];
        ListNode<HashNode>* current = bucket->head;
        while (current != nullptr) 
        {
            Flight_Ticket ticket = current->elem.value;
            outfile << ticket.companyName << "," << ticket.flightNumber << "," << ticket.country_of_origin << "," << ticket.country_of_destination << "," << ticket.stopOver << "," << ticket.price << "," << ticket.time_of_departure << "," << ticket.time_of_arrival << "," << ticket.date << endl;
            count++;
            current = current->next;
        }
    }
    outfile.close();
    return count;
}
//=============================================================================
int FlightHASHTABLE::count_collisions() //return the number of collisions in the HashTable
{
    return collisions; //returns collisions which get incremented in the add and import methods
}
//=============================================================================
int FlightHASHTABLE::add(Flight_Ticket* data) //add new flight to the HashTable
{
    if (size==capacity) //if hashtable is full, increase capacity
    {
        increaseCap();
    }
	string companyName, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date, number;
    int flightNumber;
    //ask user for input and validate it
    cout << "Enter the airline company name: ";
    getline(cin,companyName);
    const regex companyNamePattern("^[a-zA-Z]+(?: [A-Z][a-z]*)*$"); //validation of company name
    while (regex_match(companyName,companyNamePattern)==false)
    {
        cout<<"Incorrect Company Name format, enter again: ";
        getline(cin,companyName);
    }
    cout << "Enter the flight number: ";
    getline(cin,number);
    const regex flightNumberPattern("^[1-9][0-9]*$"); //validation of flight number
    while (regex_match(number,flightNumberPattern)==false)
    {
        cout<<"Incorrect Flight Number format, enter again: ";
        getline(cin,number);
    }
    flightNumber=stoi(number);
    cout << "Enter the country of origin: ";
    getline(cin,country_of_origin);
    const regex country_of_originPattern("^[a-zA-Z]+( [a-zA-Z]+){0,7}$"); //validation of country name
    while (regex_match(country_of_origin,country_of_originPattern)==false)
    {
        cout<<"Incorrect Country format, enter again: ";
        getline(cin,country_of_origin);
    }
    cout << "Enter the country of destination: ";
    getline(cin,country_of_destination);
    const regex country_of_destinationPattern("^[a-zA-Z]+( [a-zA-Z]+){0,7}$"); //validation of country name
    while (regex_match(country_of_destination,country_of_destinationPattern)==false)
    {
        cout<<"Incorrect Country Name format, enter again: ";
        getline(cin,country_of_destination);
    }
    cout << "Enter the number of stopover locations: ";
    getline(cin,stopOver);
    const regex stopOverPattern("^[0-9][0-9]*$"); //validation of stop overs
    while (regex_match(stopOver,stopOverPattern)==false)
    {
        cout<<"Incorrect number of stop overs format, enter again: ";
        getline(cin,stopOver);
    }
    cout << "Enter the ticket price: ";
    getline(cin,price);
    const regex pricePattern("^[1-9][0-9]*$"); //validation of price
    while (regex_match(price,pricePattern)==false)
    {
        cout<<"Incorrect price format, enter again: ";
        getline(cin,price);
    }
    cout << "Enter the departure time: ";
    getline(cin,time_of_departure);
    const regex time_of_departurePattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"); //validation of time
    while (regex_match(time_of_departure,time_of_departurePattern)==false)
    {
        cout<<"Incorrect Time format, enter again: ";
        getline(cin,time_of_departure);
    }
    cout << "Enter the arrival time: ";
    getline(cin,time_of_arrival);
    const regex time_of_arrivalPattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$"); //validation of time
    while (regex_match(time_of_arrival,time_of_arrivalPattern)==false)
    {
        cout<<"Incorrect Time format, enter again: ";
        getline(cin,time_of_arrival);
    }
    cout << "Enter the date of the flight: ";
    getline(cin,date);
    const regex datePattern("^\\d{1,2}-(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)$"); //validation of date
    while (regex_match(date,datePattern)==false)
    {
        cout<<"Incorrect Date format, enter again: ";
        getline(cin,date);
    }
    string companyNameL=companyName;
	for (int i = 0; i < companyNameL.length(); i++) {
        companyNameL[i] = tolower(companyNameL[i]);
    }
    string key = companyNameL+","+to_string(flightNumber); 
    Flight_Ticket newFlight(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date); //create new flight ticket
    long code = hashCode(key);
    HashNode newNode(key, newFlight); 
    if (buckets[code].search(newNode) != NULL) 
    {
        cout<<"FLight Ticket already exists, not added."<<endl;
        return 0; //node already exists, return 0 to indicate failure
    }
    MyList<HashNode>* bucket = &buckets[code];
    ListNode<HashNode>* current = bucket->head;
    int cnt=0;
    while (current != nullptr)
    {
        if (newNode.value.getKey()==current->elem.value.getKey())
        {
            cnt++;
        }
        current=current->next;
    }
    if (cnt==0 && bucket->getSize()>=1)
    {
        collisions++;
    }
    buckets[code].insertAtHead(newNode);
    cout<<"Flight Ticket has been successfully added"<<endl;
    size++;
    return 1;
}
//=============================================================================
void FlightHASHTABLE::removeRecord (string companyName, int flightNumber) //Delete a record with key from the hashtable
{
    string companyNameL=companyName;
    for (int i = 0; i < companyNameL.length(); i++) {
        companyNameL[i] = tolower(companyNameL[i]);
    }
    string key = companyNameL+","+to_string(flightNumber);
    int bucketIndex = hashCode(key); //get the index of the bucket with the key
    MyList<HashNode>* bucket = &buckets[bucketIndex];
    HashNode* nodeArray[bucket->getSize()]; //make an array of size of bucket
    int i = 0;
    int arrSize=0;
    ListNode<HashNode>* current = bucket->head;
    while (current != nullptr) //store flight tickets with the same key in the bucket
    {
        if (current->elem.value.getKey() == key) 
        {
            nodeArray[i] = &current->elem;
            arrSize++;
        }
        current = current->next;
        i++;
    }
    if (arrSize==0) //if array is empty means record does not exist
    {
        cout << "Error: Record not found." << endl;
    }
    else if (arrSize==1) //if only one element in array, remove it
    {
        bucket->remove(*nodeArray[0]);
        cout << "Record has been removed." << endl;
    }
    else //if more than one element ina rray, display all elements and ask which one to delete and delete it
    {
        cout << "There are " << arrSize << " records with key (" << key << "):" << endl;
        for (int i=0; i<arrSize;i++)
        {
            cout<<"     "<<i+1<<". "<<nodeArray[i]->value.companyName<<","<<nodeArray[i]->value.flightNumber<<","<<nodeArray[i]->value.country_of_origin<<","<<nodeArray[i]->value.country_of_destination<<","<< nodeArray[i]->value.stopOver<<","<<nodeArray[i]->value.price<<","<<nodeArray[i]->value.time_of_departure<<","<<nodeArray[i]->value.time_of_arrival<<","<<nodeArray[i]->value.date<<endl;
        }
        cout << "Please enter the index of the record to remove (1-" << arrSize << "): ";
        int selection;
        cin >> selection;
        while (selection < 1 || selection > arrSize)
        {
            cout << "Error: Invalid selection." << endl;
            cin>>selection;
        }
        bucket->remove(*nodeArray[selection-1]);
        cout << "Record has been removed." << endl;
    }
}
//=============================================================================
void FlightHASHTABLE::find(string companyName, int flightNumber) //Find and Display records with same key entered 
{
    string companyNameL=companyName;
    for (int i = 0; i < companyNameL.length(); i++) 
    {
        companyNameL[i] = tolower(companyNameL[i]);
    }
    string key = companyNameL+","+to_string(flightNumber);
    int bucketIndex = hashCode(key);
    MyList<HashNode>* bucket = &buckets[bucketIndex];
    auto start_time = chrono::high_resolution_clock::now(); //start measuring time
    ListNode<HashNode>* current = bucket->head;
    bool found = false;
    int cnt=0;
    while (current != nullptr)  
    {
        if (current->elem.value.getKey() == key) //if key matches change flag to true and increase count
        {
            found = true;
            cnt++;
        }
        current = current->next;
    }
    if (found) //use count to print how many records found
    {
        cout<<cnt<<" record(s) found:"<<endl;
    }
    cnt=0;
    current=bucket->head;
    while (current != nullptr) 
    {
        if (current->elem.value.getKey() == key) //print out all records with details
        {
            found = true;
            cout<<"  "<<cnt+1<<". "<<"Company Name: "<<current->elem.value.companyName<<endl;
            cout<<"     "<<"Flight Number: "<<current->elem.value.flightNumber<<endl;
            cout<<"     "<<"Country of Origin: "<<current->elem.value.country_of_origin<<endl;
            cout<<"     "<<"Country of Destination: "<<current->elem.value.country_of_destination<<endl;
            cout<<"     "<<"Stop Over: "<<current->elem.value.stopOver<<endl;
            cout<<"     "<<"Price: "<<current->elem.value.price<<endl;
            cout<<"     "<<"Time of Departure: "<<current->elem.value.time_of_departure<<endl;
            cout<<"     "<<"Time of Arrival: "<<current->elem.value.time_of_arrival<<endl;
            cout<<"     "<<"Date: "<<current->elem.value.date<<endl;
            cnt++;
        }
        current = current->next;
    }
    auto end_time = chrono::high_resolution_clock::now(); //stop measuring time
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time); //calculate time taken
    double search_time = duration.count() / 1000000.0; //convert to seconds
    if (!found) //if flight not found print error
    {
        cout << "Flight not found." << endl;
    }
    cout << "Search took " << search_time << " seconds." << endl; //print elapsed time in seconds
}
//=============================================================================
void FlightHASHTABLE::allinday(string date) //Find and Display records with same day entered
{
    int day;
    istringstream ss(date);
    ss >> day; //get the day of flight
    string monthStr;
    ss.ignore(); // ignore the '-'
    ss >> monthStr; //get the month of the flight
    int cnt=0;
    for (int i = 0; i < capacity; i++) // go through all buckets in the array
    {
        MyList<HashNode>* bucket = &buckets[i];
        ListNode<HashNode>* current = bucket->head;
        while (current != nullptr) 
        {
            //parse through the flight date and compare the day and month
            istringstream ss2(current->elem.value.date);
            int flightDay;
            string flightMonthStr;
            ss2 >> flightDay;
            ss2.ignore(); // ignore the '-'
            ss2 >> flightMonthStr;
            if (flightDay == day && flightMonthStr == monthStr) 
            {
                cnt++;
            }
            current = current->next;
        }
    }
    if (cnt>0) //if matches found then print
    {
        cout<<cnt<<" records found:"<<endl;
        cnt=0;
        for (int i = 0; i < capacity; i++) //iterate through bucketa again to print
        {
            MyList<HashNode>* bucket = &buckets[i];
            ListNode<HashNode>* current = bucket->head;
            while (current != nullptr) 
            {
                // Parse the flight date and compare the day, month, and year
                istringstream ss2(current->elem.value.date);
                int flightDay;
                string flightMonthStr;
                ss2 >> flightDay;
                ss2.ignore(); // ignore the '-'
                ss2 >> flightMonthStr;
                if (flightDay == day && flightMonthStr == monthStr) 
                {
                    cout<<"  "<<cnt+1<<". "<<current->elem.value.companyName<<","<<current->elem.value.flightNumber<<","<<current->elem.value.country_of_origin<<","<<current->elem.value.country_of_destination<<","<< current->elem.value.stopOver<<","<<current->elem.value.price<<","<<current->elem.value.time_of_departure<<","<<current->elem.value.time_of_arrival<<","<<current->elem.value.date<<endl;
                    cnt++;
                }
                current = current->next;
            }
        }
    } 
    else
    {
        cout<<"Not Found!"<<endl;
    }      
}
//=============================================================================
void FlightHASHTABLE::printASC(string companyName, int flightNumber) //display the collisions for the entered key in an ascending order 
{
	string companyNameL=companyName;
    for (int i = 0; i < companyNameL.length(); i++) 
    {
        companyNameL[i] = tolower(companyNameL[i]);
    }
    string key = companyNameL+","+to_string(flightNumber);
    int bucketIndex = hashCode(key);
    MyList<HashNode>* bucket = &buckets[bucketIndex];
    HashNode* nodeArray[bucket->getSize()];
    int i = 0;
    int cnt=0;
    ListNode<HashNode>* current = bucket->head;
    while (current != nullptr) //store all tickets with same key in array
    {
        if (current->elem.value.getKey() == key) 
        {
            nodeArray[i] = &current->elem;
            cnt++;
            i++;
        }
        current = current->next;
    }
    for (int i = 0; i < cnt-1; i++) //sort based of destination country using bubble sort
    {
        for (int j = 0; j < cnt-i-1; j++) 
        {
            if (nodeArray[j]->value.country_of_destination > nodeArray[j+1]->value.country_of_destination) 
            {
                HashNode* temp = nodeArray[j];
                nodeArray[j] = nodeArray[j+1];
                nodeArray[j+1] = temp;
            }
        }
    }
    for (int i = 0; i < cnt; i++) //print the tickets
    {
        cout<<i+1<<". "<<nodeArray[i]->value.companyName<<","<<nodeArray[i]->value.flightNumber<<","<<nodeArray[i]->value.country_of_origin<<","<<nodeArray[i]->value.country_of_destination<<","<< nodeArray[i]->value.stopOver<<","<<nodeArray[i]->value.price<<","<<nodeArray[i]->value.time_of_departure<<","<<nodeArray[i]->value.time_of_arrival<<","<<nodeArray[i]->value.date<<endl;
    }
}
//=============================================================================
void FlightHASHTABLE::hashChoice() //Allow user to change which hash function is being used only at the start of the program
{
    string choiceS;
    cout<<"Enter choice of hash function: "<<endl;
    cout<<"1. Summation"<<endl;
    cout<<"2. Polynomial"<<endl;
    cout<<"3. Cycle Shift"<<endl;
    cout<<">";
    getline(cin,choiceS);
    const regex choicePattern("^[123]$"); //validation of chocie name
    while (regex_match(choiceS,choicePattern)==false)
    {
        cout<<"Incorrect Choice format, enter again: ";
        getline(cin,choiceS);
    }
    choice=stoi(choiceS);
}
//=============================================================================
void FlightHASHTABLE::increaseCap() //Increase capacity of the hashtable once size=capacity
{
    int newCapacity = capacity * 1.2; //increase capacity by 20%
    MyList<HashNode>* newBuckets = new MyList<HashNode>[newCapacity]; //create new array of buckets
    int oldCap=capacity;
    for (int i = 0; i < oldCap; i++) //copy all elements from old array to new one
    {
        MyList<HashNode>* bucket = &buckets[i];
        ListNode<HashNode>* current = bucket->head;
        while (current != nullptr) 
        {
            HashNode node = current->elem;
            capacity = newCapacity; //update capacity
            long code = hashCode(node.value.getKey()); 
            newBuckets[code].insertAtHead(node);
            current = current->next;
        }
    }
    delete[] buckets; //free memory used by old array of buckets
    buckets = newBuckets; //assign new array of buckets
    capacity = newCapacity; //update capacity
}
//=============================================================================
