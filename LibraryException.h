/*
 * LibraryExeption.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef LIBRARYEXCEPTION_H_
#define LIBRARYEXCEPTION_H_

#include<stdexcept>

class LibraryException : public std::runtime_error {
public:
	LibraryException(const std::string &str) : std::runtime_error(str){}
};

#endif /* LIBRARYEXCEPTION_H_ */
