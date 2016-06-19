/*
 * LoanInfo.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LOANINFO_H_
#define LOANINFO_H_
#include <string>
#include "Properties.h"
#include "Date.h"
using std::string;

class LoanInfo {
public:
	LoanInfo(None_type=Empty):_bookId(BookId(0)),_date(),_isLoaned(false){}
	explicit LoanInfo(const BookId &bookId):_bookId(bookId),_date(),_isLoaned(false){}

	LoanInfo(const BookId &bookId,const  unsigned int day,
			const unsigned int month, const unsigned int  year):
				_bookId(bookId),_date(day,month,year),_isLoaned(true){}
	LoanInfo(const LoanInfo &orig) : _bookId(orig._bookId),_date(orig._date),
			_isLoaned(orig._isLoaned){}

	virtual ~LoanInfo(){}

	inline BookId getBookId() const {return _bookId; }

	inline bool isLoaned() const { return _isLoaned; }

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

	friend ostream& operator<< (ostream& os,const LoanInfo &loanInfo)
	{
		if(!loanInfo.isLoaned())
		{
			throw logic_error("Book is Not loaned");
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
