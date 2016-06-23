/*
 * StrongID.h
 *
 *  Created on: Jun 14, 2016
 *      Author: liron_s
 */

#ifndef STRONGID_H_
#define STRONGID_H_
/*
 *  StrongId.h
 *  This module contains the StrongId class template.
 *  We will use StrongId class template later to create UserId and BookId,
 *  to store different kinds of information in our library.
 */
#include <iostream>
#include <string>
#include <stdexcept>
#include "Optional.h"

template<typename Properties>
class StrongId : public Optional<typename Properties::ValueType> {
private:
	typedef typename Properties::ValueType ValueType;

public:
	// Constructors
/*
 * StrongId() - empty constructo
 */
	StrongId():Optional<ValueType>(None){}
/*
 * explicit StrongId(const ValueType &value) -
 * constructor using a value, explicit to disallow conversions.
 */
	explicit StrongId(const ValueType &value):Optional<ValueType>(value){}
	StrongId(const StrongId &orig):Optional<ValueType>(orig){}
	virtual ~StrongId(){}

	// Operators
	inline StrongId& operator=(const StrongId &orig)
	{
		if (this==&orig)
		{
			return *this;
		}

		Optional<ValueType>::operator=(orig);
		return *this;
	}
/*
 * operator<=: checks 2 objects and returns true if the first is
 * smaller than the other
 */
	bool operator<=(const StrongId &orig) const
	{
		return ((this==orig)||(this<orig))?true:false;
	}
/* operator<<: used for printing
*
*  @param os - object of ostream&
*  @param object - a class member of StrongId
*
*  @return: an ostream& type for the function that used the operator for
*  printing
*/
	friend std::ostream& operator<< (std::ostream& os,const StrongId& variable)
	{
		os<<name()<<": ";
		if(variable.isEmpty())
		{
			os<<"Empty";
		}
		else
		{
			os<<variable.value();
		}

		return os;
	}
/*
 * value() - getter function, returns the value.
 */
	ValueType value() const
	{
		try
		{
			return Optional<ValueType>::value();
		}
		catch(std::logic_error& logicError)
		{
			throw std::logic_error("ID has no value");
		}

	}

	// Functions
/*
 *  name: static function that returns the name of the object stored,
 * will be used to identify if we are using the UserId or BookId
 */
	static const char* name() { return Properties::name(); }
};


#endif /* STRONGID_H_ */
