#ifndef __XP_PARAM_SET_H__
#define __XP_PARAM_SET_H__

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

#include <string>
#include <vector>
#include <map>
#include "xp_config.h"
#include "xp_param.h"
#include "xp_parsed_types.h"

namespace xParam_internal {
  
	enum MultipleAssignMode {
		FIRST_HOLDS,
		LAST_HOLDS,
		IS_ERROR
	};

	enum MatchMode {
		EXACT,
		PREFIX
	};

        class MatchError : public Error {
        public:
                MatchError(bool ambiguous, const std::string& msg)
                        :
                Error(msg),
                        m_ambiguous(ambiguous)
                {}

                virtual ~MatchError() throw() {}

                bool ambiguous() const throw() {
                        return m_ambiguous;
                }

        private:
                bool m_ambiguous;
        };

	class ParamSetListener;

	class ParamSet {		
	public:
		explicit ParamSet(std::ostream& os=std::cout);
		explicit ParamSet(const std::string& desc, std::ostream& os = std::cout);

		ParamSet& operator<<(const std::string& s);
		ParamSet& operator<<(const Handle<Param>& param);
		
		void set_hstream(std::ostream& os);
		void set_feedback_stream(std::ostream& os);
		void info(void) const;
		void input(std::istream& is, bool check=true);
		void input(const int argc, const char* const argv[], bool check=true);
		void input(const char* const lpstr, bool check=true);
		void check(void) const;
		void output(std::ostream& os=std::cout) const;
		void write_feedback(void) const;
		
		const Param& operator[](const std::string& name) const {
			return *find_param(name);
		}
		std::vector<std::string> names(void);

		bool warning_is_error(bool val) {
			return m_warning_is_error = val;
		}
		bool warning_is_error(void) const {
			return m_warning_is_error;
		}

		MultipleAssignMode multiple_assign(MultipleAssignMode m) {
			return m_multi_assign=m;
		}
		MultipleAssignMode multiple_assign(void) const {
			return m_multi_assign;
		}

		MatchMode match(MatchMode m) {
			return m_match=m;
		}
		MatchMode match(void) const {
			return m_match;
		}

		bool ignore_unexpected(bool ignore) {
			return m_ignore_unexpected_param = ignore;
		}
		bool ignore_unexpected(void) const {
			return m_ignore_unexpected_param;
		}

/* XXX - not finished
		void enable_flexible_conversions(bool flexible) {
			m_flexible_conversions = flexible;
		}

		bool flexible_conversions_enabled() const {
			return m_flexible_conversions;
		}
*/

		bool feedback_enabled(bool enabled) {
			return m_feedback_enabled = enabled;
		}
		bool feedback_enabled(void) const {
			return m_feedback_enabled;
		}

		int max_feedback_length(int n) {
			return m_max_feedback_length = n;
		}
		int max_feedback_length(void) const {
			return m_max_feedback_length;
		}

		void import(ParamSet& ps);
	private:
		friend class ParamSetListener;

		struct prefix_info {
			bool is_exact;
			std::vector<std::string> matches;
		};

		typedef std::map<std::string, prefix_info> prefix_map_type;

		void notify(const std::string& key, const Handle<ParsedValue>& parsed_value);
		Handle<Param> find_param(const std::string& name) const {
			return find_param(name, m_match);
		}
		Handle<Param> find_param(const std::string& name, MatchMode m) const;
		void add_prefix(const std::string& name);

		std::vector< Handle<Param> > m_params;
		std::string general_description;

		bool m_warning_is_error;
		MultipleAssignMode m_multi_assign;
		MatchMode m_match;
		bool m_ignore_unexpected_param;
		bool m_flexible_conversions;

		bool m_feedback_enabled;
		int m_max_feedback_length;
		std::ostream* m_p_feedback_stream;

		prefix_map_type m_prefix_map;
		std::ostream* m_phstream;
	};
    
inline std::ostream& operator<<(std::ostream& os, const ParamSet& ps) {
  ps.output(os);
  return os;
}

inline std::istream& operator>>(std::istream& is, ParamSet& ps) {
  ps.input(is);
  return is;
}

} // namespace xParam_internal
  
#endif // __XP_PARAM_SET_H__
