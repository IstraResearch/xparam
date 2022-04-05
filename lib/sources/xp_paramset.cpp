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

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include "../xparam/xp_error.h"
#include "../xparam/xp_value_management.h"
#include "../xparam/xp_paramset.h"
#include "../xparam/xp_value_source_imp.h"
#include "../xparam/xp_saver.h"
#include "../xparam/xp_parser.h"
#include "../src_include/xp_sstream.h"

using namespace std;

namespace xParam_internal {

	void print_table(ostream& os, const vector<vector<string> >& table)
	{
		typedef vector<vector<string> > tabletype;
		vector<int> column_width;
		tabletype::const_iterator i;
		vector<int>::iterator col;
		vector<string>::const_iterator row;
		int counter;
		
		assert(table.size()!=0);
		for(i=table.begin();i!=table.end();++i) { assert(i->size()==table[0].size()); }
		
		for(counter=0;counter<table[0].size();++counter) column_width.push_back(0);
		
		for(i=table.begin();i!=table.end();++i) {
			for(row=i->begin(),col=column_width.begin();row!=i->end();++row,++col) {
				if (*col<row->length()) *col=row->length();
			}
		}
		for(col=column_width.begin();col!=column_width.end();++col) {++(*col);}
		
		for(i=table.begin();i!=table.end();++i) {
			for(row=i->begin(),col=column_width.begin();row!=i->end();++row,++col) {
				os << (*row);
				for(counter=row->length();counter<(*col);++counter) { os << ' '; }
			}
			os << endl;
		}
	}
	
	class ParamSetListener : public AssignmentListener {
	public:
		ParamSetListener(ParamSet& param_set) : m_param_set(param_set) {}
		virtual void notify(const string& key, Handle<ParsedValue> value) {
			m_param_set.notify(key,value);
		}
	private:
		ParamSet& m_param_set;
	};
	
	
    
	ParamSet::ParamSet(ostream& os) 
		: 
		m_warning_is_error(true),
		m_multi_assign(LAST_HOLDS), 
		m_match(PREFIX), 
		m_ignore_unexpected_param(false),
		m_flexible_conversions(true), 
		m_feedback_enabled(false),
		m_max_feedback_length(100),
		m_p_feedback_stream(&cerr),
		m_phstream(&os) 
	{}
	
	ParamSet::ParamSet(const string& desc, std::ostream& os) 
		: 
		m_warning_is_error(true),
		m_multi_assign(LAST_HOLDS), 
		m_match(PREFIX), 
		m_ignore_unexpected_param(false),
		m_flexible_conversions(true), 
		m_feedback_enabled(false),
		m_max_feedback_length(100),
		m_p_feedback_stream(&cerr),
		m_phstream(&os)
	{
		*this << desc;
	}
	
	ParamSet& ParamSet::operator<<(const string& s) {
		general_description += s+'\n';
		return *this;
	}
    
	ParamSet& ParamSet::operator<<(const Handle<Param>& param) {
		bool duplicate=true;
		try {
			find_param(param->name(), EXACT);
			// A match has been found, and therefore duplicate definition.
		} catch (Error&) {
			duplicate=false;
		}
		if (duplicate)
			throw Error("Duplicate definition of parameter \'"+param->name()+"\'.");
		
		m_params.push_back(param);
		add_prefix(param->name());
		return *this;
	}
	
	void ParamSet::set_hstream(ostream& os) {
		m_phstream=&os;
	}
	
	void ParamSet::set_feedback_stream(std::ostream& os) {
		m_p_feedback_stream = &os;
	}
	
	void ParamSet::info(void) const {
		(*m_phstream) << general_description << endl;
		if (m_params.empty())
			return; // don't print table when no parameters are defined
		
		(*m_phstream) << "Usage: progname <param1>=<val1> <param2>=<val2> -<flag1> -no_<flag2>..." << endl;
		switch (match()) {
		case EXACT:
			(*m_phstream) << "Use exact parameter names. " << endl;
			break;
		case PREFIX:
			(*m_phstream) << "Use any unambiguous prefix of the parameter names" << endl;
			break;
		default:
			assert(false);
		}
		switch (multiple_assign()) {
		case FIRST_HOLDS:
			(*m_phstream) << "In case of multiple assignment to the same parameter, the first holds." << endl;
			break;
		case LAST_HOLDS:
			(*m_phstream) << "In case of multiple assignment to the same parameter, the last holds." << endl;
			break;
		case IS_ERROR:
			(*m_phstream) << "Multiple assignment to the same parameter is not allowed." << endl;
			break;
		};
		(*m_phstream) << endl;
		
		vector<vector<string> > table;
		vector<string> row;
		row.push_back("Name");
		row.push_back("Type");
		row.push_back("I/O");
		row.push_back("Default Value");
		row.push_back("Description");
		table.push_back(row);
		row=vector<string>();
		row.push_back("====");
		row.push_back("====");
		row.push_back("===");
		row.push_back("=============");
		row.push_back("===========");
		table.push_back(row);
		
		for(vector<Handle<Param> >::const_iterator i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			row=vector<string>();
			row.push_back(param->name());
			row.push_back(xparam_name(param->static_type_info()));
			
			if (param->is_input() && !param->is_output())
				row.push_back(" I ");
			if (!param->is_input() && param->is_output())
				row.push_back(" O ");
			if (param->is_input() && param->is_output())
				row.push_back("I/O");
			
			if (param->is_input()) {
				if (param->has_default()) {
					Oss oss;
					oss << make_source(param->get_default());
					row.push_back(oss.str());
				} else {
					row.push_back("[ required ]");
				}
			}
			else {
				row.push_back("");
			}
			row.push_back(param->description());
			table.push_back(row);
		}
		print_table((*m_phstream),table);
    }
	
	void ParamSet::input(std::istream& is, bool check) 
	{
		// read from 'is'
        ParamSetListener my_listener(*this);
		parse_value_set(is,my_listener);
		
		if (m_feedback_enabled)
			write_feedback();
		
		// check all required parameters have values (if requested)
		if (check) ParamSet::check();
    }
    
	void ParamSet::input(const int argc, const char* const argv[], bool check) 
	{	
		string str;
		if (argc>1) str=argv[1];
		if (argc==2 || argc==3) { // might be help request
			if ((str=="!")||(str=="/?")||(str=="-?")||(str=="--help")
				|| (str=="/h") || (str=="/H") || (str=="/help")) {
				if (argc==2) // program help
					info(); 
				else // help for a type
					(*m_phstream) << xparam_help(argv[2]);
				exit(0);
			}
		}
		for(int i=2;i<argc;++i) {
			str+=cmdline_glue_char();
			str+=argv[i];
		}
		Iss iss(str);
		input(iss,check);
    }
    
	void ParamSet::input(const char* const lpstr, bool check) {
		const char* const argv[] = { "progname", lpstr };
		input(2,argv,check);
	}
	
	void ParamSet::output(ostream& os) const
	{
		vector< Handle<Param> >::const_iterator i;
		for(i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			if (param->is_output()) {
				Handle<Value> val = param->get_value();
				os << param->name() << " = ";
				os << make_source(val);
				os << endl;
			}
		}
		os << ";" << endl; // mark end of ParamSet
    }
	
	void ParamSet::write_feedback(void) const
	{
		ostream& os = *m_p_feedback_stream;
		
		os << "--------------------------------------------------" << endl;
		os << "Values of input parameters:" << endl;
		
		vector< Handle<Param> >::const_iterator i;
		for(i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			
			if (!param->is_input())
				continue;
			
			os << param->name() << " ";
			if (param->has_given_value()) {
				if (!param->was_assigned_to()) {
					os << "[default] ";
				}
				os << "= ";
				Handle<Value> val = param->get_value();
				
				if (m_max_feedback_length > 0) {
					Oss oss;
					oss << make_source(val);
					string str = oss.str();
					
					bool truncated = false;
					if (str.size() > m_max_feedback_length) {
						str.resize(m_max_feedback_length);
						truncated = true;
					}
					os << str;
					if (truncated)
						os << " ...";
				}
				else {
					os << make_source(val);
				}
			}
			else {
				os << "[unassigned]";
			}
			os << endl;
		}
		os << "--------------------------------------------------" << endl << endl;
	}
	
	void ParamSet::import(ParamSet& ps) {
		vector< Handle<Param> >::const_iterator i;
		for(i=ps.m_params.begin();i!=ps.m_params.end();++i) {
			Handle<Param> p(*i);
			operator<<(p);
		}
	}
	void ParamSet::check(void) const
	{	
		vector< Handle<Param> >::const_iterator i;
		for(i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			
			if ((param->is_input()) && (!param->has_default())
				&& (!param->was_assigned_to())) {
				throw Error("No value given for required parameter " 
					+ param->name() + ".");
			}
		}
    }
	
	void ParamSet::notify(const string& key, const Handle<ParsedValue>& parsed_value) 
	{
		Handle<Value> value = parsed_value->get_value(m_flexible_conversions); // may throw exception
		Handle<Param> p;
		try {
			p = find_param(key);
		} catch (MatchError& e) {
			if (!e.ambiguous() && m_ignore_unexpected_param)
				return;

			if (m_warning_is_error)
				throw;
			else {
				(*m_p_feedback_stream)
					<< "WARNING: Assignment to parameter " << key 
					<< " was ignored. "	<< e.what() << endl;
				return;
			}
		}
		assert(!p.empty());
		
		if (!p->is_input())
			throw Error("Parameter " + key + " isn't an input parameter.");
		
		switch (multiple_assign()) {
		case IS_ERROR:
			if (p->was_assigned_to())
				throw Error("Multiple assignment to parameter " + key + ".");
		case FIRST_HOLDS:
			if (p->was_assigned_to()) break;
		case LAST_HOLDS:
			p->set_value(value,m_flexible_conversions);
			break;
		default:
			assert(false);
		}
	}
	
	Handle<Param> ParamSet::find_param(const std::string& name, MatchMode m) const
	{
		std::string real_name;
		prefix_map_type::const_iterator p;
		switch (m) {
		case(EXACT):
			real_name=name;
			break;
		case(PREFIX):
			p=m_prefix_map.find(name);
			if (p==m_prefix_map.end())
				throw MatchError(false,"No match for parameter \'" + name + "\'.");
			if (p->second.matches.size()>1) {
				Oss oss;
				oss << "Reference to parameter " << name << " is ambiguous. Candidates are: ";
				for(int i=0;i<p->second.matches.size()-1;++i) {
					oss << p->second.matches[i] << ", ";
				}
				oss << p->second.matches[p->second.matches.size()-1] << ".";
				throw MatchError(true,oss.str());
			}
			assert(p->second.matches.size()>0);
			real_name=p->second.matches[0];
			break;
		default:
			assert(false);
		}
		vector< Handle<Param> >::const_iterator i;
		for(i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			if (param->name() == real_name)
				return param;
		}
		throw MatchError(false,"No match for parameter \'" + name + "\'.");
		assert(false);
		return Handle<Param>(); // suppress warnings.
	}
	
	void ParamSet::add_prefix(const string& name) {
		assert((m_prefix_map.find(name)==m_prefix_map.end())||(!m_prefix_map[name].is_exact));
		vector<string> to_erase=m_prefix_map[name].matches;
		m_prefix_map[name].matches=vector<string>(1,name);
		m_prefix_map[name].is_exact=true;
		for(int i=name.size()-1;(i>0)&&((m_prefix_map.find(name.substr(0,i))==m_prefix_map.end())||(!m_prefix_map[name.substr(0,i)].is_exact));--i) {
			string n=name.substr(0,i);
			m_prefix_map[n].is_exact=false;
			vector<string>& v=m_prefix_map[n].matches;
			vector<string>::const_iterator j;
			for(j=to_erase.begin();j!=to_erase.end();++j) {
				v.erase(find(v.begin(),v.end(),*j));
			}
			v.insert(v.end(),name);
		}
	}
	
	vector<string> ParamSet::names(void) {
		vector<string> rc;
		vector< Handle<Param> >::const_iterator i;
		for(i=m_params.begin(); i!=m_params.end(); ++i) {
			const Handle<Param>& param = *i;
			rc.push_back(param->name());
		}
		return rc;
	}
	
} // namespace xParam_internal
