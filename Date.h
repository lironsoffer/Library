/*
 * Date.h
 *
 *  Created on: Jun 17, 2016
 *      Author: liron_s
 */

#ifndef DATE_H_
#define DATE_H_
#include <iostream>

class Date {
public:
	Date():_day(0),_month(0),_year(0){}
	explicit Date(const  unsigned int day, const unsigned int month,
			const unsigned int  year): _day(day), _month(month), _year(year){}
	Date(const Date& orig): _day(orig._day),_month(orig._month),
			_year(orig._year){}
	virtual ~Date(){}

	friend std::ostream& operator<< (std::ostream& os,const Date &date)
	{
		return os<<"date: "<<date._day<<"."<<date._month<<"."<<date._year;
	}

	friend bool operator< (const Date &left,const Date &right)
	{
		if(left._year<right._year)
		{
			return true;
		}
		else if((left._year==right._year)&&(left._month<right._month))
		{
			return true;
		}
		else if((left._year==right._year)&&(left._month==right._month)&&(left._day<right._day))
		{
			return true;
		}
		return false;
	}

	friend bool operator==(const Date &dateLeft,const Date &dateRight)
	{
		return ((dateLeft._day==dateRight._day)&&
				(dateLeft._month==dateRight._month)&&
				(dateLeft._year==dateRight._year));
	}

private:
	unsigned int _day;
	unsigned int _month;
	unsigned int _year;
};


#endif /* DATE_H_ */
