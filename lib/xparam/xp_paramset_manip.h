#ifndef XP_PARAMSET_MANIP_H
#define XP_PARAMSET_MANIP_H

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
 * ParamSet manipulators
 */

#include "xp_paramset.h"

namespace xParam_internal {

	class ParamSetManip {
		public:
			virtual void manipulate(ParamSet& ps) const = 0;
	};

	inline ParamSet& operator<<(ParamSet& ps, const ParamSetManip& m) {
		m.manipulate(ps);
		return ps;
	}

	class MultipleAssign : public ParamSetManip {
		public:
			MultipleAssign(MultipleAssignMode m) : m_multi_assign(m) {}

			virtual void manipulate(ParamSet& ps) const {
				ps.multiple_assign(m_multi_assign);
			}
		private:
			MultipleAssignMode m_multi_assign;
	};

	class Match : public ParamSetManip {
		public:
			Match(MatchMode m) : m_match(m) {}
		
			virtual void manipulate(ParamSet& ps) const {
				ps.match(m_match);
			}
		private:
			MatchMode m_match;
	};

}

#endif // XP_PARAMSET_MANIP_H
