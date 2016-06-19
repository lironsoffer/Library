/*
 * Optional.h
 *
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_
#include <iostream>
#include <typeinfo>
#include <stdexcept>
//using namespace std;
using std::string;

class None_type {};
static const None_type None;

template <typename T>
class Optional {
public:
	Optional(): _value(),_isEmpty(true){}
	Optional(T param): _value(param),_isEmpty(false) {}
	Optional(None_type): _value(),_isEmpty(true){}
	Optional(const Optional & orig): _value(orig._value),
			_isEmpty(orig._isEmpty){}
	virtual ~Optional(){}
	bool isEmpty() const {return _isEmpty;}
	virtual T value() const
	 {
		  if(this->isEmpty())
		  {
			  throw (std::logic_error ("Optional is empty"));
		  }
		  return(_value);

	 }
	T operator*() const
	{
		return this->value();
	}
	operator bool() const
	{
	return !(this->isEmpty());
	}
	bool operator < (const Optional &orig) const
	{
		if((this->isEmpty())&&(!orig.isEmpty()))
		{
			return true;
		}
		else if((!this->isEmpty())&&(!orig.isEmpty()))
		{
			return this->_value<orig._value?true:false;
		}
		return false;
	}
	bool operator ==(const Optional &orig) const
	{
		if((orig._isEmpty)&&(this->_isEmpty))
		{
		return true;
		}
		else if((orig._isEmpty) xor (this->_isEmpty))
		{
		return false;
		}
		else if(orig._value==this->_value)
		{
			return true;
		}
		return false;

	}
	friend std::ostream& operator<< (std::ostream& os,const Optional& orig)
	{
		if(!orig._isEmpty)
		{
			T value=orig._value;
			os<<value;
		}
		else
		{
			os<<"Empty";
		}
		return os;
	}

private:

T _value;
bool _isEmpty;
};


#endif /* OPTIONAL_H_ */



