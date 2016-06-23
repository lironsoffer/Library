/*
 * Date.h
 *
 *  Created on: Jun 17, 2016
 *      Author: liron_s
 */

#ifndef DATE_H_
#define DATE_H_
/*
 * This Module provides basic solution to store, present and compare dates.
 */

#include <iostream>

class Date {
public:
/*
 * Date() - Constructor.
 * Builds the undefined date 0/0/0.
 */
	Date():_day(0),_month(0),_year(0){}
/* explicit Date(const unsigned int day, const unsigned int month,
 * 			const unsigned int  year) - Constructor for a date.  - Constructor
 * 	Builds the date according to the parameters - day,month,year.
 *
 */
	explicit Date(const unsigned int day, const unsigned int month,
			const unsigned int  year): _day(day), _month(month), _year(year){}
	Date(const Date& orig): _day(orig._day),_month(orig._month),
			_year(orig._year){}
	virtual ~Date(){}
	friend std::ostream& operator<< (std::ostream& os,const Date &date);
	friend bool operator< (const Date &left,const Date &right);
	friend bool operator==(const Date &dateLeft,const Date &dateRight);

private:
	unsigned int _day;
	unsigned int _month;
	unsigned int _year;
};

/*
 *  operator<<:   used for printing
 *  @param os - object of ostream&
 *  @param date - a class member of Date
 *  @return: an ostream& type for the function that used the operator,
 *  for printing.
 */
inline std::ostream& operator<< (std::ostream& os,const Date &date)
{
	return os<<"date: "<<date._day<<"."<<date._month<<"."<<date._year;
}



#endif /* DATE_H_ */
