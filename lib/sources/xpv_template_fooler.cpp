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

#pragma warning (disable: 4786)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../xparam/xpv_template_fooler.h"

namespace xParam_internal {

	namespace TemplateFooler {

		// just to make sure we don't get outsmarted by an optimizing compiler
		// which does project level optimizations (beyond a single compilation unit)
		// we use fermat's little theorem so the compiler won't be able to tell that
		// always_false() does indeed always return false.
		bool always_false()
		{
			const int p = 5;

			srand( (unsigned)time(0) );
			int n = (rand() % (p-1)) + 1; // get number in [1,p-1]

			// compute n^(p-1) (mod p)
			int j = n;
			for (int i=1; i<p-1; ++i)
				j *= n;

			return (j%p) != 1;
		}

		void assert_false()
		{
			printf("template fooler failed!\n");
			exit(-1);
		}

		void launder(void* vp)
		{
		}

	} // namespace TemplateFooler

} // namespace xParam_internal
