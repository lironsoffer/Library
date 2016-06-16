/*
 * Library.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include<vector>
#include<string>
#include "Properties.h"
#include "LoanInfo.h"

class Library {
public:
	Library();
	virtual ~Library();
	void addBook(BookId,std::string);
	void addUser(UserId,std::string);
	Optional<std::string> getBookId() const;
	Optional<std::string> getUserInfo() const;
	void loanbook(LoanInfo);
	bool returnBook(BookId);
	bool removeBook(BookId);
	bool removeUser(UserId);
	std::vector<LoanInfo> getLoansSortedByDate() const;
};

#endif /* LIBRARY_H_ */
