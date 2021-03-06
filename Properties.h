/*
 * Properties.h
 *
 *  Created on: Jun 16, 2016
 *      Author: liron_s
 */

#ifndef PROPERTIES_H_
#define PROPERTIES_H_
/*
 * Properties.h
 * This module defines properties for UserId and BookId.
 */
#include "Properties.h"
#include "StrongId.h"

static const None_type Empty;

/*
 * BookIdProperties - This module defines UserId
 */
class BookIdProperties
{
public:
    typedef unsigned int ValueType;
    static const char* name() { return "BookId"; }
};

/*
 * UserIdProperties - This module defines BookId.
 */
class UserIdProperties
{
public:
    typedef int ValueType;
    static const char* name() { return "UserId"; }
};

typedef StrongId<UserIdProperties> UserId;
typedef StrongId<BookIdProperties> BookId;


#endif /* PROPERTIES_H_ */
