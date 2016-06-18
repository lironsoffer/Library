/*
 * Date.h
 *
 *  Created on: Jun 17, 2016
 *      Author: liron_s
 */

#ifndef DATE_H_
#define DATE_H_
#include <iostream>
using namespace std;

class Date {
public:
	Date():_day(0),_month(0),_year(0){}
	Date(const  unsigned int day, const unsigned int month,
			const unsigned int  year): _day(day), _month(month), _year(year){}
	Date(const Date& orig): _day(orig._day),_month(orig._month),
			_year(orig._year){}
	virtual ~Date(){}

	friend ostream& operator<< (ostream& os,const Date &date)
	{
		return os<<"date: "<<date._day<<"."<<date._month<<"."<<date._year;
	}

private:
	unsigned int _day;
	unsigned int _month;
	unsigned int _year;
};

#endif /* DATE_H_ */
