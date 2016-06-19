/*
 * StrongID.h
 *
 *  Created on: Jun 14, 2016
 *      Author: liron_s
 */

#ifndef STRONGID_H_
#define STRONGID_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include "Optional.h"
using std::string;

template<typename Properties>
class StrongId : public Optional<typename Properties::ValueType> {
private:
	typedef typename Properties::ValueType ValueType;

public:
	// Constructors
	StrongId():Optional<ValueType>(None){}
	explicit StrongId(const ValueType &value):Optional<ValueType>(value){}

	StrongId(const StrongId &orig):Optional<ValueType>(orig){}
	virtual ~StrongId(){}

	// Operators
	StrongId& operator=(const StrongId &orig){
		if (this==&orig)
		{
			return *this;
		}

		Optional<ValueType>::operator=(orig);
		return *this;
	}

	bool operator<=(const StrongId &orig) const {
		return ((this==orig)||(this<orig))?true:false;
	}

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
	static const char* name() { return Properties::name(); }
};


#endif /* STRONGID_H_ */
