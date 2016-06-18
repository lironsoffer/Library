/*
 * Library.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <iostream>
#include<vector>
#include<string>
#include<map>
#include <utility>
#include "Properties.h"
#include "LoanInfo.h"
#include "Book.h"
#include "LibraryException.h"

using std::map;
using std::make_pair;

void printLibraryError(const LibraryException &error);

class Library {
public:
	Library(){}
	virtual ~Library(){}
	void addBook(const BookId &bookId, const std::string &bookName);
	Optional<std::string> getBookInfo(const BookId &bookId) const;
	bool removeBook(const BookId &bookId);
	void loanBook(const UserId &userId,const LoanInfo &loanBookInfo);
	bool returnBook(const BookId &bookId); // TODO: built it based on User

	void addUser(UserId,std::string);
	Optional<std::string> getUserInfo(UserId userId) const;
	bool removeUser(UserId);
	std::vector<LoanInfo> getLoansSortedByDate() const;

private:
	map<BookId,Book> _bookShelf;
//	map<UserId,vector<LoanInfo>> _loansInfoByUser;
};



#endif /* LIBRARY_H_ */
