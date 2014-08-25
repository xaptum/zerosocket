/********************************************************************************
 * Copyright (C) 2014-2014 Zero Socket
 * based on code by Pradeep Barthur copyright (C) 2014-2014 Zero Socket
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *
 * Created on:Aug 25, 2014
 *     Author: Pradeep Barthur
 ********************************************************************************/

#ifndef AUTOPTR_H_
#define AUTOPTR_H_

namespace zerosocket {

/*
 *
 */

template < typename T >
class auto_ptr
{
    private:
    T*    ptr;
    public:
    auto_ptr(T* pValue) : ptr(pValue){}

    virtual ~auto_ptr()
    {
        delete ptr;
    }

    T& operator* ()
    {
        return *ptr;
    }

    T* operator-> ()
    {
        return ptr;
    }
};

} /* namespace zerosocket */

#endif /* AUTOPTR_H_ */
