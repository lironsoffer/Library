/*
 * Optional.h
 *
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_
/*
 * Optional.h
 * This module contains the class template Optional,
 * which contains an object which may or may not be empty.
 */
#include <iostream>
#include <typeinfo>
#include <stdexcept>

/*
 * This module contains class None_type - a class which represents an empty object
 * by creating the static const variable "None"
 */
class None_type {};
static const None_type None;

template <typename T>
class Optional {
public:
/*
 * Optional() - default constructor with empty values
 */
	Optional(): _value(),_isEmpty(true){}
/*
 * constructor for creating an object with value
 * @param param - defines the type of the class by type T,
 * and the value which the class stores.
 */
	Optional(T param): _value(param),_isEmpty(false) {}
/*
 * Optional(None_type) - constructor for creating an object with no value
 * using the word "None"
 */
	Optional(None_type): _value(),_isEmpty(true){}
	Optional(const Optional & orig): _value(orig._value),
			_isEmpty(orig._isEmpty){}
	virtual ~Optional(){}
/*
 * isEmpty(): checks if the object is empty,
 * returns a boolean value (true for empty)
*/
	inline bool isEmpty() const {return _isEmpty;}
/*
 * value(): a function to return the value of a T object,
 * throw an exception if empty.
 */
	inline virtual T value() const
	 {
		  if(this->isEmpty())
		  {
			  throw (std::logic_error ("Optional is empty"));
		  }
		  return(_value);
	 }

	inline T operator*() const {return this->value();}
/*
 * bool operator: checks if the object is empty using boolean operator
 */
	inline operator bool() const {	return !(this->isEmpty()); }
/*
 * operator<: checks if the first object is smaller than the second,
 * return true if so, false otherwise.
 */
	inline bool operator < (const Optional &orig) const
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
/*
 * operator<<: printing operator using &ostream,
 * also checks if the object is empty.
 */
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



