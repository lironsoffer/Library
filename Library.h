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

using std::map;
using std::make_pair;
using std::vector;
using std::string;

void printLibraryError(const LibraryException &error);

class Library {
public:
	Library(){}
	virtual ~Library(){}
	void addBook(const BookId &bookId, const string &bookName);
	Optional<string> getBookInfo(const BookId &bookId) const;
	bool removeBook(const BookId &bookId);
	void loanBook(const UserId &userId,const LoanInfo &loanBookInfo);
	bool returnBook(const UserId &userId, const BookId &bookId);
	void addUser(const UserId &userId, const string &userName);
	Optional<string> getUserInfo(const UserId &userId) const;

	bool removeUser(const UserId &userId);
	void getLoansSortedByDate(const UserId &userId, vector<LoanInfo> &loans);

private:
	map<BookId,Book> _bookShelf;
	map<UserId,string> _users;
	multimap<UserId,BookId> _loansInfoByUser;

	map<UserId,string>::const_iterator findUser(const UserId& userId) const;
	map<UserId,string>::iterator findUser(const UserId& userId);

	multimap<UserId,BookId>::iterator findLoanByUser(const UserId &userId,
			const BookId &bookId);
	map<BookId,Book>::iterator findBookInBookShelf(const BookId &bookId);

};



#endif /* LIBRARY_H_ */
