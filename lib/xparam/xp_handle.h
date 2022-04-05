#ifndef XPARAM_HANDLE_H
#define XPARAM_HANDLE_H

/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * As a special exception, the copyright holders give permission
 * for additional uses of the text contained in its release of XPARAM.
 *
 * The exception is that, if you link the XPARAM library with other files
 * to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the XPARAM library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * If you write modifications of your own for XPARAM, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.  
 */

/*
 * simple reference counted pointer.
 *
 * This is a non-intrusive implementation that allocates an additional
 * int and pointer for every counted object.
 */

#include <assert.h>
#include "xp_type_tag.h"

/* For ANSI-challenged compilers, you may want to #define
* NO_TEMPLATE_FRIENDS or explicit */

namespace xParam_internal {

	template <class T> 
		class Handle {
		
#ifndef NO_TEMPLATE_FRIENDS
private:
//	template<class U> friend class Handle;
	template<class U,class V>
	  friend Handle<U> dynamic_handle_cast(Handle<V> source, TypeTag<U>);
	template<class U,class V>
	  friend Handle<U> handle_upcast(Handle<V> source, TypeTag<U>);
#else
public:
#endif
	
	explicit Handle(T* data, int* counter, bool owner) : m_data(0), m_counter(0) {
		acquire(data,counter);
		m_owner = owner;
	}
	int* counter() const {return m_counter;}
	
public:
	bool is_owner() const {return m_owner;}
	
	explicit Handle(T* data = 0, bool owner=true) : m_data(data), m_owner(owner) {
		if (data)
			m_counter = new int(1);
		else
			m_counter = 0;
	}
	
	~Handle() {release();}
	
	Handle(const Handle& other) throw() {
		acquire(other.m_data, other.m_counter);
		m_owner = other.m_owner;
	}
	
	Handle& operator=(const Handle& other) {
		if (this == &other) 
			return *this;
		release();
		acquire(other.m_data,other.m_counter);
		m_owner = other.m_owner;
		return *this;
	}
	
	T& operator*()  const throw()   {return *m_data;}
	T* operator->() const throw()   {return m_data;}
	T* get()        const throw()   {return m_data;}
	bool unique()   const throw()   {return (m_counter ? (*m_counter == 1) : true);}
	bool empty() const { return m_data == 0; }
	
private:
	T* m_data;
	int *m_counter;
	bool m_owner;
	
    void acquire(T* data, int* counter) throw() { // increment the count
		m_data = data;
		m_counter = counter;
		if (m_counter)
			++(*m_counter);
    }
	
    void release() { // decrement the count, delete if it is 0
		if (m_counter) {
			--(*m_counter);
			if (*m_counter == 0) {
				delete m_counter;
				if (m_owner)
					delete m_data;
			}
			m_data = 0;
			m_counter = 0;
		}
	}
};
	
	template<class T, class S>
		inline Handle<T> dynamic_handle_cast(Handle<S> source, TypeTag<T>) 
	{
		T* tptr = dynamic_cast<T*>(source.get());
		if (tptr)
			return Handle<T>(tptr,source.counter(),source.is_owner());
		else
			return Handle<T>();
	}
	
	template<class T,class S>
		inline Handle<T> handle_upcast(Handle<S> source, TypeTag<T>) 
	{
		T* tptr = source.get();
		return Handle<T>(tptr,source.counter(),source.is_owner());
	}
	
} // namespace xParam_internal

#endif // XPARAM_HANDLE_H
