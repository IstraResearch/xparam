#ifndef XPARAM_REG_MACROS_H
#define XPARAM_REG_MACROS_H

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
 * Macros that make it easier to run code when program/library loads
 */

#include <exception>
#include <iostream>
#include "xp_config.h"

/* 
This is what we want to get:

namespace {
namespace L##__LINE__ {
	class GlobalCode {
		public:
		GlobalCode() {
			try {
				// user code here;
			}
			catch(std::exception& ex) {
				std::cerr << "Error during global initialization - " 
					<< std::endl << ex.what() << std::endl;
				exit(-1);
			}
			catch(...) {
				std::cerr << "Error during global initialization" 
						  << std::endl;
				exit(-1);
			}
		}
	};

	GlobalCode global_code_instance;
} // end line namespace
} // end annonymous namespace
*/

#define APPEND2(x,y) x##y
#define APPEND(x,y) APPEND2(x,y)

#define PARAM_BEGIN_REG \
namespace { \
namespace APPEND(L,__LINE__) { \
class GlobalCode { \
  public: \
    GlobalCode() { \
		try {


#define PARAM_END_REG \
			} \
			catch(std::exception& ex) { \
				std::cerr << "Error during global initialization - " \
					<< std::endl << ex.what() << std::endl; \
				exit(-1); \
			} \
			catch(...) { \
				std::cerr << "Error during global initialization" \
					<< std::endl; \
				exit(-1); \
			} \
		} \
	}; \
	GlobalCode global_code_instance; \
} \
}


#endif // XPARAM_REG_MACROS_H


