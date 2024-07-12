
//=================================================================================
// Name         : DS Assignment#3
// Author       : 
// Version      : 1.0
// Date Created : 22-Nov-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>

#include "flightticket.h"
#include "flighthashtable.h"
#include "mylist.h"
//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================
// to be completed with any necessary method definitions
//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	string choice;
	cout<<"By default the hash function being used is polynomial."<<endl; //asks user of they want to change hash function being used at start of program
	cout<<"Do you want to chose a different type (y/n)?: ";
	getline(cin,choice);
    bool isChange=false;
    while (isChange==false)
    {
        if (choice.length() == 1)
        {
            char c = toupper(choice[0]);
            if (c == 'Y')
            {
                isChange = true;
                break;
            }
            else if (c == 'N')
            {
                isChange = false;
                break;
            }
        }
        cout << "Invalid input. Please enter 'y' or 'n': ";
        getline(cin,choice);
    }
    if (isChange==true)
    {
    	myFlightHASHTABLE.hashChoice();
    }
    choice=" ";
        fflush(stdin);
        fflush(stdout);
	string user_input;
	string command;
	string parameter;
	Flight_Ticket* data=NULL;
	while(true)
	{
		listCommands();
		cout<<">";
		getline(cin,user_input);
		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		if(command =="import")
        {
            cout<<myFlightHASHTABLE.importCSV(parameter)<<" record(s) have been imported"<<endl;
        }
		else if(command == "export")
        {
        	cout<<myFlightHASHTABLE.exportCSV(parameter)<<" record(s) have been exported"<<endl;
        }
        else if(command == "add")						myFlightHASHTABLE.add(data);
        else if(command == "count_collisions")			cout<<myFlightHASHTABLE.count_collisions()<<endl;
        else if(command == "delete")
        {
        	const regex keyPattern("^[a-zA-Z\\s]+,\\d+$"); //validation of key
    		while (regex_match(parameter,keyPattern)==false)
    		{
    		    cout<<"Incorrect Key format, enter again: ";
    		    getline(cin,parameter);
    		}	
        	string companyName;
    		int flightNumber;
    		stringstream param_sstr(parameter);
    		getline(param_sstr, companyName, ',');
    		param_sstr >> flightNumber;
    		myFlightHASHTABLE.removeRecord(companyName, flightNumber);
        }
        else if(command == "find")
        {
        	const regex keyPattern("^[a-zA-Z\\s]+,\\d+$"); //validation of key
    		while (regex_match(parameter,keyPattern)==false)
    		{
    		    cout<<"Incorrect Key format, enter again: ";
    		    getline(cin,parameter);
    		}	
        	string companyName;
    		int flightNumber;
    		stringstream param_sstr(parameter);
    		getline(param_sstr, companyName, ',');
    		param_sstr >> flightNumber;
    		myFlightHASHTABLE.find(companyName, flightNumber);
        }				
        else if(command == "allinday")
        {
      		//myFlightHASHTABLE.allinday(parameter);
      		const regex datePattern("^\\d{1,2}-(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)$"); //validation of date
    		while (regex_match(parameter,datePattern)==false)
    		{
    		    cout<<"Incorrect Date format, enter again: ";
    		    getline(cin,parameter);
    		}
    		myFlightHASHTABLE.allinday(parameter);
        }
        else if(command == "printASC")
        {
        	const regex keyPattern("^[a-zA-Z\\s]+,\\d+$"); //validation of key
    		while (regex_match(parameter,keyPattern)==false)
    		{
    		    cout<<"Incorrect Key format, enter again: ";
    		    getline(cin,parameter);
    		}	
        	string companyName;
    		int flightNumber;
    		stringstream param_sstr(parameter);
    		getline(param_sstr, companyName, ',');
    		param_sstr >> flightNumber;
    		myFlightHASHTABLE.printASC(companyName, flightNumber);
        }
        else if(command == "exit" or command=="quit")	break;
		else cout<<"Invalid Command!!"<<endl;
        parameter=" ";
        fflush(stdin);
        fflush(stdout);
	}
	return 0;
}