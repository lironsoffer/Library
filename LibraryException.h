/*
 * LibraryExeption.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARYEXCEPTION_H_
#define LIBRARYEXCEPTION_H_
/*
 * This module is an extension of the runtime_error exception.
 */
#include<stdexcept>

class LibraryException : public std::runtime_error {
public:
/*
 * LibraryException(const std::string &str) - Constructor
 * @param str - the string which represents the error
 */
	LibraryException(const std::string &str) : std::runtime_error(str){}
};

#endif /* LIBRARYEXCEPTION_H_ */
