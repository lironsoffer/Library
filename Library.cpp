/*
 * Library.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#include "Library.h"

void printLibraryError(const LibraryException &error)
{
	cerr<<error.what()<<endl;
}

void Library::addBook(const BookId &bookId, const std::string &bookName)
{

	pair<BookId,Book> p = make_pair(bookId,Book(bookId,bookName));

	pair<map<BookId,Book>::iterator,bool> tmp (_bookShelf.insert(p));
	if (!tmp.second)
	{
		throw LibraryException("Book Id already exists");
	}
}

Optional<std::string> Library::getBookInfo(const BookId &bookId) const
{
	map<BookId,Book>::const_iterator iter = _bookShelf.find(bookId);
	map<BookId,Book>::const_iterator endIter = _bookShelf.end();
	if (iter!=endIter)
	{
		return Optional<std::string>(iter->second.getBookName());
	}
	return Optional<std::string>(None);
}

bool Library::removeBook(const BookId &bookId)
{

	map<BookId,Book>::iterator bookShelfIter = _bookShelf.find(bookId);
	if (bookShelfIter==_bookShelf.end())
	{
		return false;
	}
	else if (bookShelfIter->second.isLoaned())
	{
		throw LibraryException("The book is loaned, and cannot be removed");
	}

	_bookShelf.erase(bookShelfIter);
	return true;

//	catch(const LibraryException &error)
//	{
//		printLibraryError(error);
//	}
}

void Library::loanBook(const UserId &userId,const LoanInfo &loanBookInfo)
{

	map<BookId,Book>::iterator bookShelfIter = _bookShelf.find(loanBookInfo.getBookId());
	if (bookShelfIter==_bookShelf.end())
	{
		throw LibraryException("Book is not registered with the library");
	}
	else if (bookShelfIter->second.isLoaned())
	{
		throw LibraryException("The book is already loaned by a different user");
	}
	// TODO: Add a test for UserId in DB

	bookShelfIter->second.setLoanInfo(loanBookInfo);

}
