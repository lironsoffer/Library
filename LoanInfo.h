/*
 * LoanInfo.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LOANINFO_H_
#define LOANINFO_H_
/*	LoanInfo.h
 *  This module contains the class used for tracking the loan information of
 *  each user in the library. It also uses 2 identifiers, called UserId
 *  for the user's id, and a LoanInfo class object, for the loan information
 *  of a specific book and user
 */
#include <string>
#include "Properties.h"
#include "Date.h"

class LoanInfo;
/*
 * isLoanedEarlier() - a friend function we use to know which book had been
 * loaned earlier. Returns true if the left
 * @param left - the left LoanInfo to compare
 * @param right - the right LoanInfo to compare
 * Return true if left was loaned before right, false otherwise.
*/
bool isLoanedEarlier(const LoanInfo &left,const LoanInfo &right);

/*
 * LoanInfo: a class which holds the loan information of a book.
 */
class LoanInfo {
public:
/*
 * LoanInfo() or LoanInfo(Empty) -
 * empty constructor for creating an unidentified book which isn't loaned
 */
	LoanInfo(None_type=Empty):_bookId(BookId(0)),_date(),_isLoaned(false){}
/*
 * explicit LoanInfo(const BookId &bookId) -
 * constructor using a book's id, isn't loaned
 */
	explicit LoanInfo(const BookId &bookId):
			_bookId(bookId),_date(),_isLoaned(false){}
/*
 * LoanInfo: constructor to define a new loan of a book, using the book's
 * information and the date of the loan
 *
 * @param bookId - the id of the book
 * @param day
 * @param month
 * @param year
 * All 3 of the above are defining the date of the loan
 */
	LoanInfo(const BookId &bookId,const  unsigned int day,
			const unsigned int month, const unsigned int  year):
				_bookId(bookId),_date(day,month,year),_isLoaned(true){}
	LoanInfo(const LoanInfo &orig) : _bookId(orig._bookId),_date(orig._date),
			_isLoaned(orig._isLoaned){}

	virtual ~LoanInfo(){}

	inline BookId getBookId() const {return _bookId; }
/*
 * isLoaned() - checks if the book is already loaned.
 * Returns true if loaned, false otherwise.
 */
	inline bool isLoaned() const { return _isLoaned; }

	inline void setNotLoaned() {_isLoaned=false;}

	LoanInfo& operator=(const LoanInfo &otherLoanInfo)
	{
		if(this==&otherLoanInfo)
		{
			return *this;
		}
		_bookId=otherLoanInfo._bookId;
		_date=otherLoanInfo._date;
		_isLoaned=otherLoanInfo._isLoaned;
		return *this;
	}
/*
 * operator<<: a printing operator, throws an exception if the book is not
 * loaned, otherwise prints
 */
	friend std::ostream& operator<< (std::ostream& os,const LoanInfo &loanInfo)
	{
		if(!loanInfo.isLoaned())
		{
			throw std::logic_error("Book is Not loaned");
		}
		return os<<"LoanInfo: { id: {"<<
				loanInfo._bookId<<"}, "<<loanInfo._date<<"}";
	}

	friend bool isLoanedEarlier(const LoanInfo &left,const LoanInfo &right);
private:
	BookId _bookId;
	Date _date;
	bool _isLoaned;
};

inline bool isLoanedEarlier(const LoanInfo &left,const LoanInfo &right)
{
	return left._date<right._date;
}

#endif /* LOANINFO_H_ */
