#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;
	public:
		Flight_Ticket() : companyName(""), flightNumber(0), country_of_origin(""), country_of_destination(""),stopOver(""), price(""), time_of_departure(""), time_of_arrival(""), date("") {} //default constructor
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		string getKey(); //method to get key
		bool operator==(const Flight_Ticket& other) const //overloaded == operator
		{
    		return (companyName == other.companyName && flightNumber==other.flightNumber && country_of_origin==other.country_of_origin && country_of_destination==other.country_of_destination && stopOver==other.stopOver && price == other.price && time_of_departure == other.time_of_departure && time_of_arrival==other.time_of_arrival && date == other.date);
		}
		bool operator!=(const Flight_Ticket& other) const //overloaded != operator
		{
    		return (companyName != other.companyName || flightNumber!=other.flightNumber || country_of_origin!=other.country_of_origin || country_of_destination!=other.country_of_destination || stopOver!=other.stopOver || price != other.price || time_of_departure != other.time_of_departure || time_of_arrival!=other.time_of_arrival || date != other.date);
		}
		friend class HashNode;
		friend class FlightHASHTABLE;
};
//=============================================================================
#endif