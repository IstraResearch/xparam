#ifndef XPARAM_SCHEDULER_H
#define XPARAM_SCHEDULER_H

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
 * Schedules registration commands according to their dependencies
 */

#include <string>
#include <list>
#include "xp_config.h"
#include "xp_singleton.h"
#include "xp_handle.h"
#include "xpv_regcom.h"

namespace xParam_internal {

	class RegistrationCommand;

	class RegistrationScheduler {
		public:
			RegistrationScheduler() 
				: m_initialized(false), 
				m_execute_called(false),
				m_already_checking(false) {}

			void mark_initialized();
			void add_command(Handle<RegistrationCommand> command);
			bool commands_pending() const;
			std::string pending_commands_description() const;
			void execute_registration();

		private:
			bool m_initialized;
			bool m_execute_called;
			typedef std::list< Handle<RegistrationCommand> > CommandList;
			CommandList m_commands;
			bool m_already_checking;
	};

	// nicer syntax for access to the singleton
	inline RegistrationScheduler& registration_scheduler() { 
		return Singleton<RegistrationScheduler>::get(); 
	}

} // namespace xParam_internal

#endif // XPARAM_SCHEDULER_H
