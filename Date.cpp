/*
 * Date.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: liron_s
 */

#include "Date.h"

bool operator==(const Date &dateLeft,const Date &dateRight)
{
	return ((dateLeft._day==dateRight._day)&&
			(dateLeft._month==dateRight._month)&&
			(dateLeft._year==dateRight._year));
}

bool operator< (const Date &left,const Date &right)
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
