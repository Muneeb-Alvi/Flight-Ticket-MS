#include "flightticket.h"
//=============================================================================
Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date)
{
	this->companyName=companyName;
	this->flightNumber=flightNumber;
	this->country_of_origin=country_of_origin;
	this->country_of_destination=country_of_destination;
	this->stopOver=stopOver;
	this->price=price;
	this->time_of_departure=time_of_departure;
	this->time_of_arrival=time_of_arrival;
	this->date=date;
}
//=============================================================================
string Flight_Ticket::getKey()
{
	string companyNameL=companyName;
	for (int i=0; i<companyNameL.length(); i++)
	{
		companyNameL[i]=tolower(companyNameL[i]);
	}
	return companyNameL+","+to_string(flightNumber);
}
//=============================================================================