#include <iostream>
#include <iterator>
#include "LibraryTests.h"
#include "LoanInfo.h"
#include "Library.h"
//
static void testLoanInfo();
static void testAddUser();
static void testAddBook();
static void testGetNonExistantUser();
static void testGetNonExistantBook();
static void testRemoveUser();
static void testRemoveBook();
static void testLoanBooks();
static void testBadLoans();
static void testRemovingUserAlsoRemovesLoans();
static void testRemovingLoanedBookCausesException();
static void testReturnLoanedBook();
void testBadReturnLoanedBook();
//
void runLibraryTests()
{
    std::cout << "== Library tests ==" << std::endl;
    testLoanInfo();
    testAddUser();
    testAddBook();
    testGetNonExistantUser();
    testGetNonExistantBook();
    testRemoveUser();
    testRemoveBook();
    testLoanBooks();
    testBadLoans();
    testRemovingUserAlsoRemovesLoans();
    testRemovingLoanedBookCausesException();
    testReturnLoanedBook();
    testBadReturnLoanedBook();
}

void testLoanInfo()
{
    std::cout << "-- testLoanInfo" << std::endl;

    LoanInfo loanInfo(BookId(50), 25, 9, 2016);
    std::cout << loanInfo << std::endl;
}

void testAddUser()
{
    std::cout << "-- testAddUser" << std::endl;

    Library library;
    library.addUser(UserId(10), "Details of user");

    Optional<std::string> userInfo = library.getUserInfo(UserId(10));
    std::cout << "User details: " << userInfo << std::endl;
}

void testAddBook()
{
    std::cout << "-- testAddBook" << std::endl;

    Library library;
    library.addBook(BookId(10), "A very good book!!!");

    Optional<std::string> bookInfo = library.getBookInfo(BookId(10));
    std::cout << "Book details: " << bookInfo << std::endl;

}

void testGetNonExistantUser()
{
    std::cout << "-- testGetNonExistantUser" << std::endl;

    Library library;
    library.addUser(UserId(10), "Bla bla");

    std::cout << "User details: " << library.getUserInfo(UserId(20)) << std::endl;
}

void testGetNonExistantBook()
{
    std::cout << "-- testGetNonExistantBook" << std::endl;

    Library library;
    library.addBook(BookId(10), "Bla bla");

    std::cout << "User details: " << library.getBookInfo(BookId(20)) << std::endl;
}

void testRemoveUser()
{
    std::cout << "-- testRemoveUser" << std::endl;

    Library library;
    library.addUser(UserId(10), "bla bla");

    std::cout << "Remove nonexistant user: " << library.removeUser(UserId(30)) << std::endl;
    std::cout << "Remove existing user: " << library.removeUser(UserId(10)) << std::endl;
    std::cout << "Removed user info: " << library.getUserInfo(UserId(10)) << std::endl;
    std::cout << "Remove same user again: " << library.removeUser(UserId(10)) << std::endl;
}

void testRemoveBook()
{
    std::cout << "-- testRemoveBook" << std::endl;

    Library library;
    library.addBook(BookId(10), "bla bla");

    std::cout << "Remove nonexistant user: " << library.removeBook(BookId(30)) << std::endl;
    std::cout << "Remove existing user: " << library.removeBook(BookId(10)) << std::endl;
    std::cout << "Removed user info: " << library.getBookInfo(BookId(10)) << std::endl;
    std::cout << "Remove same user again: " << library.removeBook(BookId(10)) << std::endl;
}

void testLoanBooks()
{
    std::cout << "-- testLoanBooks" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addUser(UserId(20), "User 20");
    library.addBook(BookId(100), "Book 100");
    library.addBook(BookId(200), "Book 200");
    library.addBook(BookId(300), "Book 300");
    library.addBook(BookId(400), "Book 400");

    library.loanBook(UserId(10), LoanInfo(BookId(100), 1, 2, 2017));
    library.loanBook(UserId(10), LoanInfo(BookId(200), 1, 2, 2016));
    library.loanBook(UserId(10), LoanInfo(BookId(300), 1, 1, 2017));
    library.loanBook(UserId(20), LoanInfo(BookId(400), 1, 1, 2015));

    std::vector<LoanInfo> user10Loans;
    user10Loans.push_back(LoanInfo(BookId(12345), 1, 2, 3));
    library.getLoansSortedByDate(UserId(10), user10Loans);

    std::vector<LoanInfo> user20Loans;
    library.getLoansSortedByDate(UserId(20), user20Loans);

    std::cout << "User 10 loans: ";
    std::copy(user10Loans.begin(), user10Loans.end(), std::ostream_iterator<LoanInfo>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "User 20 loans: ";
    std::copy(user20Loans.begin(), user20Loans.end(), std::ostream_iterator<LoanInfo>(std::cout, ", "));
    std::cout << std::endl;
}

void testBadLoans()
{
    std::cout << "-- testBadLoans" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addUser(UserId(20), "User 20");
    library.addBook(BookId(100), "Book 100");

    try
    {
        library.loanBook(UserId(30), LoanInfo(BookId(100), 1, 2, 3));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        library.loanBook(UserId(10), LoanInfo(BookId(200), 1, 2, 3));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    library.loanBook(UserId(10), LoanInfo(BookId(100), 1, 2, 3));
    try
    {
        library.loanBook(UserId(20), LoanInfo(BookId(100), 11, 12, 13));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void testRemovingUserAlsoRemovesLoans()
{
    std::cout << "-- testRemovingUserAlsoRemovesLoans" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addUser(UserId(20), "User 20");

    library.addBook(BookId(100), "Book 100");
    library.addBook(BookId(200), "Book 200");
    library.addBook(BookId(300), "Book 300");

    library.loanBook(UserId(10), LoanInfo(BookId(100), 1, 2, 3));
    library.loanBook(UserId(10), LoanInfo(BookId(200), 1, 2, 3));

    library.removeUser(UserId(10));

    // Books 100 and 200 are now free. So user 20 can loan them without getting
//    // an exception.
    library.loanBook(UserId(20), LoanInfo(BookId(100), 1, 2, 4));
    library.loanBook(UserId(20), LoanInfo(BookId(200), 1, 2, 5));

    std::cout << "Success!" << std::endl;
}

void testRemovingLoanedBookCausesException()
{
    std::cout << "-- testRemovingLoanedBookCausesException" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addBook(BookId(100), "Book 100");

    library.loanBook(UserId(10), LoanInfo(BookId(100), 10, 20, 30));

    try
    {
        library.removeBook(BookId(100));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    std::cout << "Book info: " << library.getBookInfo(BookId(100)) << std::endl;
}

void testReturnLoanedBook()
{
    std::cout << "-- testReturnLoanedBook" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addUser(UserId(20), "User 20");
    library.addBook(BookId(100), "Book 100");
    library.addBook(BookId(200), "Book 200");

    library.loanBook(UserId(10), LoanInfo(BookId(100), 10, 20, 30));

    std::cout << "Return non-loaned book [1]: " << library.returnBook(UserId(10), BookId(200)) << std::endl;
    std::cout << "Return non-loaned book [2]: " << library.returnBook(UserId(20), BookId(100)) << std::endl;
    std::cout << "Return loaned book: " << library.returnBook(UserId(10), BookId(100)) << std::endl;
    std::cout << "Return same book again: " << library.returnBook(UserId(10), BookId(100)) << std::endl;

    std::vector<LoanInfo> loans;
    library.getLoansSortedByDate(UserId(10), loans);
    std::cout << "Books loaned by user 10: " << loans.size() << std::endl;

    // Book 100 can be loaned again, since it was returned by user 10
    library.loanBook(UserId(20), LoanInfo(BookId(100), 11, 12, 13));
    library.getLoansSortedByDate(UserId(20), loans);
    std::cout << "Books loaned by user 20: " << loans.size() << std::endl;
    std::cout << "Loan info: " << loans.back() << std::endl;
}

void testBadReturnLoanedBook()
{
    std::cout << "-- testBadReturnLoanedBook" << std::endl;

    Library library;
    library.addUser(UserId(10), "User 10");
    library.addBook(BookId(100), "Book 100");

    try
    {
        library.returnBook(UserId(10), BookId(20));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    try
    {
        library.returnBook(UserId(20), BookId(100));
    }
    catch(const LibraryException& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}


