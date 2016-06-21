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
/*
 * Book() - default Constructor
 *
 */
	Book():_bookId(),_bookName(),_loanInfo(Empty){}
/*
 * Book(const BookId &bookId,const std::string &bookName) - Constructor
 * @param bookId - represents the unique ID of the book
 * @param bookName - represents the book's title
 */
	Book(const BookId &bookId,const Optional<std::string> &bookName = None) :
		_bookId(bookId),_bookName(bookName),_loanInfo(Empty) {}
	Book(const Book &orig):_bookId(orig._bookId),_bookName(orig._bookName),
				_loanInfo(orig._loanInfo){}

	bool operator==(Book &otherBook);
	inline void setLoanInfo(const LoanInfo &loanInfo) { _loanInfo = loanInfo; }
	inline std::string getBookName() const {return *_bookName; }
	inline BookId getBookId() const { return _bookId; }
	inline LoanInfo getLoanInfo() const { return _loanInfo; }
	inline void setNotLoaned() { _loanInfo.setNotLoaned(); }
	inline bool isLoaned() const { return _loanInfo.isLoaned(); }

	friend std::ostream& operator<< (std::ostream &os, const Book& book);

private:
	const BookId _bookId;
	const Optional<std::string> _bookName;
	LoanInfo _loanInfo;
};

inline bool Book::operator==(Book &otherBook)
{
	return ((_bookId==otherBook._bookId)&&
			(_bookName==otherBook._bookName))?true:false;
}

inline std::ostream& operator<< (std::ostream &os, const Book& book)
{
	return os << "Book id: " << book.getBookId() << " Book name: " <<
			book.getBookName();
}

#endif /* BOOK_H_ */
