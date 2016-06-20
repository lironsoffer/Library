/*
 * Library.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#include "Library.h"

void printLibraryError(const LibraryException &error)
{
	std::cerr<<error.what()<<std::endl;
}

void Library::addUser(const UserId &userId, const std::string &userName)
{
	if (_users.insert(std::make_pair(userId,userName)).second==0)
	{
		throw LibraryException("User is already registered with the library");
	}
}

void Library::addBook(const BookId &bookId, const std::string &bookName)
{
	using std::pair;
	std::pair<BookId,Book> p = std::make_pair(bookId,Book(bookId,bookName));

	pair<std::map<BookId,Book>::iterator,bool> tmp (_bookShelf.insert(p));
	if (!tmp.second)
	{
		throw LibraryException("Book Id already exists");
	}
}

Optional<std::string> Library::getBookInfo(const BookId &bookId) const
{
	std::map<BookId,Book>::const_iterator iter = _bookShelf.find(bookId);
	if (iter!=_bookShelf.end())
	{
		return iter->second.getBookName();
	}
	return None;
}

Optional<std::string> Library::getUserInfo(const UserId &userId) const
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

	std::map<BookId,Book>::iterator bookShelfIter = _bookShelf.find(bookId);
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
	findUser(userId);
	std::map<BookId,Book>::iterator bookShelfIter =
			findBookInBookShelf(loanBookInfo.getBookId());

	if (bookShelfIter->second.isLoaned())
	{
		throw LibraryException("The book is already loaned by a different user");
	}

	bookShelfIter->second.setLoanInfo(loanBookInfo);
	_loansInfoByUser.insert(std::make_pair(userId,loanBookInfo.getBookId()));
}

bool Library::returnBook(const UserId &userId, const BookId &bookId)
{
	findUser(userId);
	std::map<BookId,Book>::iterator bookShelfIter = findBookInBookShelf(bookId);

	std::multimap<UserId,BookId>::iterator loansInfoByUserIter =
			findLoanByUser(userId,bookId);
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
		std::vector<LoanInfo> loans;
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

void Library::getLoansSortedByDate(const UserId &userId,
		std::vector<LoanInfo> &loans)
{
	loans.clear();
	std::multimap<UserId,BookId>::const_iterator begin =
			_loansInfoByUser.lower_bound(userId);
	std::multimap<UserId,BookId>::const_iterator end =
			_loansInfoByUser.upper_bound(userId);

	while(begin!=end)
	{
		BookId bookId = begin->second;
		loans.push_back(_bookShelf.find(bookId)->second.getLoanInfo());
		++begin;
	}
	sort(loans.begin(),loans.end(),isLoanedEarlier);
}

std::map<UserId,std::string>::const_iterator Library::findUser(const UserId& userId) const
{
	std::map<UserId,std::string>::const_iterator usersIter = _users.find(userId);
	if (usersIter==_users.end())
	{
		throw LibraryException("User is not registered with the library");
	}
	return usersIter;
}

std::map<UserId,std::string>::iterator Library::findUser(const UserId& userId)
{
	std::map<UserId,std::string>::iterator usersIter = _users.find(userId);
	if (usersIter==_users.end())
	{
		throw LibraryException("User is not registered with the library");
	}
	return usersIter;
}


std::map<BookId,Book>::iterator Library::findBookInBookShelf(const BookId &bookId)
{
	std::map<BookId,Book>::iterator iter = _bookShelf.find(bookId);
	if (iter==_bookShelf.end())
	{
		throw LibraryException("Book is not registered with the library");
	}
	return iter;
}

std::multimap<UserId,BookId>::iterator Library::findLoanByUser(const UserId &userId,
		const BookId &bookId)
{
	findUser(userId);

	std::multimap<UserId,BookId>::iterator begin =
			_loansInfoByUser.lower_bound(userId);
	std::multimap<UserId,BookId>::iterator end =
			_loansInfoByUser.upper_bound(userId);

	while(begin!=end)
	{
		if (begin->second==bookId)
		{
			return begin;
		}
		++begin;
	}

	return _loansInfoByUser.end();
}


