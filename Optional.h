/*
 * Optional.h
 *
 *  Created on: Jun 11, 2016
 *      Author: Ben
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_
#include <iostream>
#include <stdexcept>
#include <typeinfo>
using namespace std;

enum optionalparam {paramNone,paramint,paramdouble};

class None_type {};
static const None_type None;

template <typename T>
class Optional {
private:
T _paramValue;
optionalparam _paramType;
bool _isEmpty;

public:
	// Constructors
	Optional(): _paramValue(),_paramType(paramNone),_isEmpty(true){}
	Optional(None_type): _paramValue(),_paramType(paramNone),_isEmpty(true){}
	Optional(T param): _paramValue(param),_paramType(typeid(param)==typeid(double)?
			paramdouble:paramint),_isEmpty(false) {} //TODO: Why only int and double?
	Optional(const Optional & orig): _paramValue(orig._paramValue),
			_paramType(orig._paramType),_isEmpty(orig._isEmpty){}
	virtual ~Optional(){}

	// Functions
//	bool isEmpty() const {return(_paramType==paramNone?true:false);}
	bool isEmpty() const {return _isEmpty;}
	inline T value() const {
		if (this->_isEmpty)
		{
			throw (std::logic_error ("Optional is empty"));
		}

		return(_paramValue);
	}
	optionalparam getType() const {return _paramType;};

	// Operators
	T operator*() {
//		return (_paramType==paramNone?false:_paramValue);
	return (this->value());
	}
	bool operator==(const Optional &orig)
	{
		if(((orig._paramType)==(this->_paramType))&&((orig._paramType)==(paramNone)))
			{
			return true;
			}
		else if((orig._paramType)!=(this->_paramType))
			{
			return false;
			}
		else
		{
			if(orig._paramValue==this->_paramValue)
			{
				return true;
			}
		return false;
		}
	}

	bool operator<(const Optional &orig)
	{
		return ((!this->_isEmpty)&&(!orig._isEmpty)&&
				(this->value()<orig.value()))?true:false;
	}

	friend ostream& operator<< (ostream& os,const Optional& orig)
	{ //TODO: doesn't work for empty
//		if(orig._paramType!=paramNone)
//		{
//			T value=orig._paramValue;
//			os<<value;
//		}
		if(orig._isEmpty)
		{
			os<<"Empty";
		}
		else
		{
			os<<orig._paramValue;
		}

		return os;
	}

	inline operator bool() const {
		return !(this->isEmpty());
	}

};

template<typename T>
bool operator<(const Optional<T> &first,const Optional<T> &second)
{
	return first.operator<(second);
}

#endif /* OPTIONAL_H_ */



