/*
 * Optional.h
 *
 *  Created on: Jun 11, 2016
 *      Author: Ben
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_
#include <iostream>
#include <typeinfo>
#include <stdexcept>
using namespace std;

enum optionalparam {paramNone,paramint,paramdouble};

class None_type {};
static const None_type None;

template <typename T>
class Optional {
public:
	Optional(): _paramValue(),_paramType(paramNone){}
	Optional(T param): _paramValue(param),_paramType(typeid(param)==typeid(double)?
			paramdouble:paramint) {}
	Optional(None_type): _paramValue(),_paramType(paramNone){}
	Optional(const Optional & orig): _paramValue(orig._paramValue),
			_paramType(orig._paramType){}
	virtual ~Optional(){}
	bool isEmpty() const {return(_paramType==paramNone?true:false);}
	virtual T value() const
	 {
		  if(this->isEmpty())
		  {
			  throw (std::logic_error ("Optional is empty"));
		  }
		  else
		  {
			  return(_paramValue);
		  }
	 }
	optionalparam getType() const {return _paramType;};
	T operator*() const
	{
		return this->value();
	}
	operator bool() const
		{
		return !(this->isEmpty());
		}
	bool operator < (const Optional &orig)
	{
		if((this->_paramType==paramNone)&&(orig._paramType!=paramNone))
		{
			return true;
		}
		else if((this->_paramType!=paramNone)&&(orig._paramType!=paramNone))
		{
			return this->_paramValue<orig._paramValue?true:false;
		}
		return false;
	}
	bool operator ==(const Optional &orig)
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
	friend ostream& operator<< (ostream& os,const Optional& orig)
	{
		if(orig._paramType!=paramNone)
		{
			T value=orig._paramValue;
			os<<value;

		}
		else
		{
			os<<"Empty";
		}
		return os;
	}

private:

T _paramValue;
optionalparam _paramType;
};


#endif /* OPTIONAL_H_ */



