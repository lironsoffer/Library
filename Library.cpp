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

void Library::addUser(const UserId &userId, const string &userName)
{
	if (_users.insert(make_pair(userId,userName)).second==0)
	{
		throw LibraryException("User is already registered with the library");
	}
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
	if (iter!=_bookShelf.end())
	{
		return iter->second.getBookName();
	}
	return None;
}

Optional<string> Library::getUserInfo(const UserId &userId) const
{
	try
	{
		return findUser(userId)->second;
	}
	catch(LibraryException&)
	{
		return None;
	}
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

}

void Library::loanBook(const UserId &userId,const LoanInfo &loanBookInfo)
{

	map<BookId,Book>::iterator bookShelfIter = _bookShelf.find(loanBookInfo.getBookId());
	if (findUser(userId)==_users.end())
	{
		throw LibraryException("User is not registered with the library");
	}
	else if (bookShelfIter==_bookShelf.end())
	{
		throw LibraryException("Book is not registered with the library");
	}
	else if (bookShelfIter->second.isLoaned())
	{
		throw LibraryException("The book is already loaned by a different user");
	}

	bookShelfIter->second.setLoanInfo(loanBookInfo);
	_loansInfoByUser.insert(make_pair(userId,loanBookInfo.getBookId()));
}

bool Library::returnBook(const UserId &userId, const BookId &bookId) // TODO: complete it. waiting for user map
{
	findUser(userId);
	map<BookId,Book>::iterator bookShelfIter = _bookShelf.find(bookId);
	if (bookShelfIter==_bookShelf.end())
	{
		throw LibraryException("Book does not exist in the library");
	}


	multimap<UserId,BookId>::iterator loansInfoByUserIter = findLoanByUser(userId,bookId);
	if (loansInfoByUserIter==_loansInfoByUser.end())
	{
		return false;
	}

	_loansInfoByUser.erase(loansInfoByUserIter);
	bookShelfIter->second.setNotLoaned();
	return true;

}

bool Library::removeUser(const UserId &userId)
{
	try
	{
		_users.erase(findUser(userId));
		vector<LoanInfo> loans;
		getLoansSortedByDate(userId,loans);
		size_t numberOfLoans = _loansInfoByUser.erase(userId);
		for(size_t i=0;i<numberOfLoans;i++)
		{
			_bookShelf.find(loans[i].getBookId())->second.setNotLoaned();
		}
		return true;
	}
	catch(LibraryException&)
	{
		return false;
	}
}

map<UserId,string>::const_iterator Library::findUser(const UserId& userId) const
{
	map<UserId,string>::const_iterator usersIter = _users.find(userId);
	if (usersIter==_users.end())
	{
		throw LibraryException("User is not registered with the library");
	}
	return usersIter;
}

map<UserId,string>::iterator Library::findUser(const UserId& userId)
{
	map<UserId,string>::iterator usersIter = _users.find(userId);
	if (usersIter==_users.end())
	{
		throw LibraryException("User is not registered with the library");
	}
	return usersIter;
}

