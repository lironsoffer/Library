/*
 * Library.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_
/*
 * Library.h
 * This module contains the library class, used to operate a real life library,
 * with books and users.
 * This module uses both StrongId and Optional classes, for the identification
 * of the users or books. Additionally, LoanInfo is used here to control the
 * books that are already loaned, sorted by the user's id.
 */
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

/*
 * printLibraryError: used to print the exception thrown by Library functions
 *
 * @param error - the exception thrown by each function is translated using
 * this paramter
 */
void printLibraryError(const LibraryException &error);

class Library {
public:
	Library(){} //constructor
	virtual ~Library(){}
	/*
	 * addBook: used to add a user to the library
	 * It won't add a book if it already exists in the database - it will throw
	 * an exception
	 *
	 * @param bookId - the book's id
	 * @param bookName - a string with a short description
	 */
	void addBook(const BookId &bookId, const std::string &bookName);
	/*
	 * getBookInfo: Used to get the book's information, aka its description.
	 *
	 * @param bookId - using the book's id, we get the information
	 *
	 * @return: a string containing the description, from Optional<string> type
	 */
	Optional<std::string> getBookInfo(const BookId &bookId) const;
	/*
	 * removeBook: used to remove a book from the library, only if the book does
	 * exist in the library. Will throw an exception otherwise.
	 *
	 * @param bookId - the book we intend to remove
	 *
	 * @return: true if the book was removed, false otherwise.
	 */
	bool removeBook(const BookId &bookId);
	/*
	 * loanBook: Checks if the book or user exists in the library, throws an
	 * exception if either one does not exist. It also checks if the book
	 * is already loaned to someone else. If not exception is thrown -
	 * the book will be loaned.
	 *
	 * @param userId - the user that wants to loan the book.
	 * @param loanBookInfo - Loan information of this book, by user id.
	 */
	void loanBook(const UserId &userId,const LoanInfo &loanBookInfo);
	/*
	 * returnBook: used to return a book if it's possible - possible means
	 * the user and the book exists.
	 * Throws an exception if the terms don't match.
	 *
	 * @param userId - the user that book belongs to.
	 * @param bookId - the book's id.
	 *
	 * @return: true if successful, false otherwise.
	 */
	bool returnBook(const UserId &userId, const BookId &bookId);
	/*
	 * addUser: used to add a user to the library
	 * It won't add a user if he/she already exists in the database
	 *
	 * @param userId - the user's id
	 * @param userName - a string with a short description about the user
	 */
	void addUser(const UserId &userId, const std::string &userName);
	/*
	 * getUserInfo: Used to get the user's information.
	 *
	 * @param userId - using the user's id, we get the information
	 *
	 * @return: a string containing the description, from Optional<string> type
	 */
	Optional<std::string> getUserInfo(const UserId &userId) const;
	/*
	 * removeUser: used to remove a user from the library, once he returned all
	 * of his loaned books.
	 *
	 * @param userId - the user we intend to remove
	 *
	 * @return: true if the user was removed, false otherwise.
	 */
	bool removeUser(const UserId &userId);
	/*
	 * getLoansSortedByDate: sorts the loans for a user that exists in the library
	 *
	 * @param userId - the user we want to sort his loans
	 * @param loans - the vector we need to sort by dates
	 */
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
