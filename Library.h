/*
 * Library.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include "Properties.h"
#include "LoanInfo.h"
#include "Book.h"
#include "LibraryException.h"

void printLibraryError(const LibraryException &error);

class Library {
public:
	Library(){}
	virtual ~Library(){}
	void addBook(const BookId &bookId, const std::string &bookName);
	Optional<std::string> getBookInfo(const BookId &bookId) const;
	bool removeBook(const BookId &bookId);
	void loanBook(const UserId &userId,const LoanInfo &loanBookInfo);
	bool returnBook(const UserId &userId, const BookId &bookId);
	void addUser(const UserId &userId, const std::string &userName);
	Optional<std::string> getUserInfo(const UserId &userId) const;

	bool removeUser(const UserId &userId);
	void getLoansSortedByDate(const UserId &userId, std::vector<LoanInfo> &loans);

private:
	std::map<BookId,Book> _bookShelf;
	std::map<UserId,std::string> _users;
	std::multimap<UserId,BookId> _loansInfoByUser;

	std::map<UserId,std::string>::const_iterator findUser(const UserId& userId) const;
	std::map<UserId,std::string>::iterator findUser(const UserId& userId);

	std::multimap<UserId,BookId>::iterator findLoanByUser(const UserId &userId,
			const BookId &bookId);
	std::map<BookId,Book>::iterator findBookInBookShelf(const BookId &bookId);

};



#endif /* LIBRARY_H_ */
