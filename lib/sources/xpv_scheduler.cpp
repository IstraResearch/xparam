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

#include "../xparam/xpv_scheduler.h"
#include "../xparam/xpv_regcom.h"
#include "../src_include/xp_sstream.h"

using namespace std;

#include <stdio.h>
#include <iostream>

#include "../xparam/xp_error.h"

namespace xParam_internal {

	void RegistrationScheduler::mark_initialized()
	{
		m_initialized = true;
	}

	// NOTE: 
	// A naive implementation would simply enqueue the command and then 
	// call execute_registration() if m_execute_called is true.
	// 
	// THIS IS WRONG!
	// 
	// The reason is that execute_registration() returns without doing anything
	// when it's called recursively. This means that the command will not be
	// executed immediately (it will execute before the top call to 
	// execute_registration returns). The problem is that registration code
	// that assumes that its registration commands execute immediately will fail.
	// An example of this is the vector registration, which registers the
	// vector class, and then tries to access the Type object.
	// It is perhaps possible to avoid such assumptions, but since they are
	// reasonable, it is better to ensure that commands that can execute 
	// immediately, are executed, and not enqueued.
	void RegistrationScheduler::add_command(Handle<RegistrationCommand> command)
	{
		if (m_execute_called && command->can_register()) {
			command->do_registration();

			// check if other commands can now register
			execute_registration();
		}
		else {
			// can't execute it now, so enqueue it
			m_commands.push_back(command);
		}
	}

	bool RegistrationScheduler::commands_pending() const
	{
		return !m_commands.empty();
	}

	string RegistrationScheduler::pending_commands_description() const
	{
		if (!commands_pending())
			return "No registration commands are pending.\n";

		Oss oss;
		oss << m_commands.size() << " registration commands are pending." << endl;

		if (!m_execute_called) {
			oss << "Registration not initiated yet. " << endl;
			return oss.str();
		}

		CommandList::const_iterator i;
		for (i=m_commands.begin(); i!=m_commands.end(); ++i) {
			if ((*i)->can_register()) {
				oss << endl << (*i)->description() << " can register." << endl;
			}
			else {
				oss << endl << (*i)->description() << " still waits for " 
					<< (*i)->unfulfilled_dependencies() << "." << endl;
			}
		}

		return oss.str();
	}

	/////////////////////////////////////////////////////////////////////////////
	// This method goes over the stored commands and executes those that have
	// their dependencies fulfilled.
	//
	// We must remember that commands may (directly or indirectly) call the 
	// add_command() and the execute_registration() methods while executing their
	// registration code.
	/////////////////////////////////////////////////////////////////////////////
	void RegistrationScheduler::execute_registration()
	{
		// mark that execute has been called
		m_execute_called = true;

#ifdef XPARAM_EXPLICIT_INIT
		if (!m_initialized) {
			fprintf(stderr,"Registry was used before xparam_init()\n");
			throw Error("Registry was used before xparam_init()");
			exit(-1);
		}
#endif

		if (m_already_checking)
			return;
		m_already_checking = true;

		while(true) {
			// collect all commands that can register themselves
			CommandList non_blocked;
			CommandList::iterator i = m_commands.begin();
			while (i != m_commands.end()) {
				CommandList::iterator j = i++;
				if ((*j)->can_register()) {
					non_blocked.splice(non_blocked.begin(),m_commands,j,i);
				}
			}

			if (non_blocked.empty())
				break; // we've reached equilibrium

			// register all commands in non_blocked_commands
			for (i=non_blocked.begin(); i!=non_blocked.end(); ++i)
				(*i)->do_registration();
		}

		m_already_checking = false;
	}

} // namespace xParam_internal

