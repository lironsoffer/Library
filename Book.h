/*
 * Book.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef BOOK_H_
#define BOOK_H_

#include <utility>
#include "Properties.h"
#include "LoanInfo.h"

class Book {


public:
	Book():_bookId(),_bookName(),_loanInfo(Empty){}
	Book(const Book &orig):_bookId(orig._bookId),_bookName(orig._bookName),
			_loanInfo(orig._loanInfo){}
	Book(const BookId &bookId,const std::string &bookName) :
		_bookId(bookId),_bookName(bookName),_loanInfo(bookId) {}
	bool operator==(Book &otherBook) {
		return ((_bookId==otherBook._bookId)&&(_bookName==otherBook._bookName))?
				true:false;
	}
	inline void setLoanInfo(const LoanInfo &loanInfo)
	{
		_loanInfo = loanInfo;
	}

	std::string getBookName() const {return _bookName; }
	BookId getBookId() const {return _bookId; }
	LoanInfo getLoanInfo() const { return _loanInfo; }
	void setNotLoaned() { _loanInfo.setNotLoaned(); }
	inline bool isLoaned() const { return _loanInfo.isLoaned(); }
	friend std::ostream& operator<< (std::ostream &os, const Book& book) {
	return os << "Book id: " << book.getBookId() << " Book name: " <<
			book.getBookName();
	}

private:
	const BookId _bookId;
	const std::string _bookName;
	LoanInfo _loanInfo;


};


#endif /* BOOK_H_ */
