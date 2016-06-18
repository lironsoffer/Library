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

using std::make_pair;

class Book {
public:
	Book():_bookId(),_bookName(),_loanInfo(Empty){}
//	{cout<<"Book()"<<endl;}
	Book(const Book &orig):_bookId(orig._bookId),_bookName(orig._bookName),
			_loanInfo(orig._loanInfo){}
//	{cout<<"Book(const Book &orig)"<<endl;}
	Book(const BookId &bookId,const std::string &bookName) :
		_bookId(bookId),_bookName(bookName),_loanInfo(bookId) {}
//	{ cout<<"Book(const BookId&,const string&)"<<endl; }
	bool operator==(Book &otherBook) {
		return ((_bookId==otherBook._bookId)&&(_bookName==otherBook._bookName))?
				true:false;
	}
	void setLoanInfo(const LoanInfo &loanInfo)
	{
		_loanInfo = loanInfo;
	}
	std::string getBookName() const {return _bookName; }
	BookId getBookId() const {return _bookId; }
	inline bool isLoaned() const { return _loanInfo.isLoaned(); }
	friend ostream& operator<< (ostream &os, const Book& book) {
	return os << "Book id: " << book.getBookId() << " Book name: " << book.getBookName();
	}

private:
	const BookId _bookId;
	const string _bookName;
	LoanInfo _loanInfo;
};


#endif /* BOOK_H_ */
