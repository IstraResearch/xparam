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
#pragma warning (disable: 4800)

#include <typeinfo>
#include <vector>
#include <iostream>
#include "../xparam/xpv_convweight.h"
#include "../xparam/xpv_type.h"
#include "../xparam/xpv_registry.h"
#include "../src_include/xpv_tentative.h"
#include "../xparam/xp_value_management.h"
#include "../xparam/xp_value_list.h"

using namespace std;

namespace xParam_internal {

	
	////////////////////////////////////////////////////////////
	// ScalarConvWeight
	////////////////////////////////////////////////////////////

	ScalarConvWeight::ScalarConvWeight(AtomicWeightConstant atomic_constant)
		: m_conv_type(CONV_TYPE_NORMAL)
	{
		for (int i=0; i<nWeightTypes; ++i)
			w[i] = 0;

		switch (atomic_constant) {
		case(CONV_IMPOSSIBLE):
		case(CONV_USER):
		case(CONV_TENTATIVE):
		case(CONV_TO_PARENT):
		case(CONV_STANDARD):
		case(CONV_PROMOTION):
			w[atomic_constant] = 1;
		case(CONV_EXACT):
			break;
		default:
			assert(false);
		}
	}

	ScalarConvWeight::ScalarConvWeight(const type_info& list_type)
		: m_conv_type(CONV_TYPE_LIST), m_tuple_types(1,&list_type)
	{
	}

	ScalarConvWeight::ScalarConvWeight(const vector<const type_info*>& tuple_types)
		: m_conv_type(CONV_TYPE_TUPLE), m_tuple_types(tuple_types)
	{
	}

	const vector<const type_info*>& ScalarConvWeight::tuple_types() const 
	{
		assert(m_conv_type == CONV_TYPE_TUPLE);
		return m_tuple_types;
	}

	const type_info* ScalarConvWeight::list_type() const
	{
		assert(m_conv_type == CONV_TYPE_LIST);
		assert(m_tuple_types.size() == 1);
		return m_tuple_types[0];
	}


	ScalarConvWeight operator+(const ScalarConvWeight& aw1, 
								const ScalarConvWeight& aw2)
	{
		// only NORMAL weight types should ever be added
		assert(aw1.m_conv_type == CONV_TYPE_NORMAL);
		assert(aw2.m_conv_type == CONV_TYPE_NORMAL);

		if (aw1.w[CONV_IMPOSSIBLE] || aw2.w[CONV_IMPOSSIBLE])
			return CONV_IMPOSSIBLE;

		ScalarConvWeight rc = aw1;
		for (int i=0; i<nWeightTypes; ++i)
			rc.w[i] += aw2.w[i];

		if (rc.w[CONV_USER] > 1)
			return CONV_IMPOSSIBLE;
		return rc;
	}

	ScalarConvWeight operator*(const ScalarConvWeight& aw, int k)
	{
		assert(aw.m_conv_type == CONV_TYPE_NORMAL);

		if (aw.w[CONV_IMPOSSIBLE])
			return CONV_IMPOSSIBLE;

		ScalarConvWeight rc = aw;
		for (int i=1; i<nWeightTypes; ++i)
			rc.w[i] *= k;
		return rc;
	}

	ostream& operator<<(ostream& os, const ScalarConvWeight& w) 
	{
		switch(w.conv_type()) {
		case CONV_TYPE_NORMAL:
			{
				string part_names[nWeightTypes];
				assert(nWeightTypes == 6);
				part_names[CONV_IMPOSSIBLE] = "IMPOSSIBLE";
				part_names[CONV_USER] = "USER";
				part_names[CONV_TENTATIVE] = "TENTATIVE";
				part_names[CONV_TO_PARENT] = "TO_PARENT";
				part_names[CONV_STANDARD] = "STANDARD";
				part_names[CONV_PROMOTION] = "PROMOTION";
				
				if (w[CONV_IMPOSSIBLE])
					return os << part_names[CONV_IMPOSSIBLE];
				
				bool exact = true;
				
				for (int i=0; i<nWeightTypes; ++i) {
					if (w[i] != 0) {
						if (!exact)
							os << " + ";
						if (w[i] != 1)
							os << w[i] << "*";
						os << part_names[i];
						exact = false;
					}
				}
				
				if (exact)
					os << "EXACT";
			}
			break;

		case CONV_TYPE_LIST:
			os << "LIST(" << xparam_name(*w.list_type()) << ")";
			break;

		case CONV_TYPE_TUPLE:
			{
				os << "TUPLE(";
				vector<const type_info*>::const_iterator iType;
				for (iType=w.tuple_types().begin(); iType!=w.tuple_types().end(); ++iType) {
					if (iType != w.tuple_types().begin())
						os << ",";
					os << xparam_name(**iType);
				}
				os << ")";
			}
			break;

		default:
			assert(false);
		}

		return os;
	}


	// Note: this function returns negative if a>b, positive if a<b
	// and zero if a==b.
	int scalar_compare(const ScalarConvWeight& a, const ScalarConvWeight& b)
	{
		assert(a.conv_type() == CONV_TYPE_NORMAL);
		assert(b.conv_type() == CONV_TYPE_NORMAL);

		for(int i=0; i<nWeightTypes; ++i) 
			if (a[i] != b[i]) 
				return b[i] - a[i];
		return 0;
	}


	bool operator<(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		return scalar_compare(a,b)>0;
	}
	
	bool operator<=(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		return scalar_compare(a,b)>=0;
	}
	
	bool operator>(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		return scalar_compare(a,b)<0;
	}
	
	bool operator>=(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		return scalar_compare(a,b)<=0;
	}
	
	bool operator==(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		if (a.conv_type() != b.conv_type())
			return false;

		switch(a.conv_type()) {
		case CONV_TYPE_NORMAL:
			return scalar_compare(a,b)==0;

		case CONV_TYPE_LIST:
			return (*a.list_type()) == (*b.list_type());

		case CONV_TYPE_TUPLE:
			const vector<const type_info*>& a_types = a.tuple_types();
			const vector<const type_info*>& b_types = b.tuple_types();
			if (a_types.size() != b_types.size())
				return false;

			vector<const type_info*>::const_iterator i,j;
			for (i=a_types.begin(), j=b_types.begin(); i!=a_types.end(); ++i,++j) {
				if (**i != **j)
					return false;
			}
			return true;
		}

		assert(false);
		return false;
	}
	
	bool operator!=(const ScalarConvWeight& a, const ScalarConvWeight& b) {
		return !(a==b);
	}
	
	////////////////////////////////////////////////////////////
	// ConvWeight
	////////////////////////////////////////////////////////////

	ConvWeight::ConvWeight(const ScalarConvWeight& a) 
		: m_scalar_weight(a)
	{
		assert(a.conv_type() == CONV_TYPE_NORMAL);
	}

	ConvWeight::ConvWeight(const vector<ConvWeight>& v, const ScalarConvWeight& a) 
		: m_scalar_weight(a)
	{
		assert(a.conv_type() == CONV_TYPE_NORMAL);

		for(vector<ConvWeight>::const_iterator i=v.begin(); i!=v.end(); ++i) 
		{
			Handle<ConvWeight> hw(new ConvWeight(*i));
			m_list_weight.push_back(hw);
		}
	}
	
	vector<ConvWeight> ConvWeight::list_weight() const
	{
		vector<ConvWeight> rc;

		vector< Handle<ConvWeight> >::const_iterator i;
		for ( i=m_list_weight.begin(); i!=m_list_weight.end(); ++i)
			rc.push_back(**i);

		return rc;
	}
	
	ostream& operator<<(ostream& os, const ConvWeight& w)
	{
		return os << w.scalar_weight() 
				<< " (and " << w.list_weight().size() << " list weights)";
	}

	ConvWeight operator+(const ConvWeight& a, const ConvWeight& b) 
	{
		assert(b.list_weight().empty()); // list->vector only allowed as first step
		return ConvWeight(a.list_weight(), a.scalar_weight() + b.scalar_weight());
	}
	
	// This function returns negative if a>b, positive if a<b
	// and zero if a==b or if a is uncomparable to b
	int compare(const ConvWeight& a, const ConvWeight& b) 
	{
		int cmp = inner_compare(a,b);
		assert(cmp>=-1 && cmp<=2);
		return (cmp==2) ? 0 : cmp;
	}

	// Note: this function returns -1 if a>b, 1 if a<b,
	// zero if a==b, and 2 if a is uncomparable to b.
	int inner_compare(const ConvWeight& a, const ConvWeight& b) 
	{
		vector<ConvWeight> a_list_weight = a.list_weight();
		vector<ConvWeight> b_list_weight = b.list_weight();

		assert(a_list_weight.size() == b_list_weight.size());
		const int list_size = a_list_weight.size();
		
		bool found_gr = false;
		bool found_ls = false;
		bool uncomparable = false;
		
		int i;
		for(i=0; i<list_size && !uncomparable; ++i) {
			int cmp = inner_compare(a_list_weight[i], b_list_weight[i]);
			switch (cmp) {
				case 1: found_ls = true; break;
				case -1: found_gr = true; break;
				case 0: break;
				case 2: uncomparable = true; break;
				default: assert(false);
			}
		}
		
		if (uncomparable || (found_ls && found_gr)) return 2; // uncomparable
		if (found_ls) return 1;
		if (found_gr) return -1;

		int scalar_cmp = scalar_compare(a.scalar_weight(),b.scalar_weight());
		if (scalar_cmp > 0)
			return 1;
		if (scalar_cmp < 0)
			return -1;
		return 0;
	}
	
	////////////////////////////////////////////////////////////
	// Other Functions
	////////////////////////////////////////////////////////////

	ostream& operator<<(ostream& os, const ConvPath& path)
	{
		ConvPath::const_iterator i;
		for (i=path.begin(); i!=path.end(); ++i) {
			os << "--> " << xparam_name(**i);
		}
		return os;
	}

	vector<vector<ConvPathData> >
		cartesian_mult(const vector<vector<ConvPathData> >& path_list) 
	{
		if (path_list.empty()) {
			vector<ConvPathData> empty_path;
			return vector< vector<ConvPathData> >(1, empty_path);
		}
		
		vector<vector<ConvPathData> > cpy=path_list;
		cpy.pop_back(); // erase last member
		vector<vector<ConvPathData> > mult=cartesian_mult(cpy);
		vector<vector<ConvPathData> > rc;
		
		vector<vector<ConvPathData> >::const_iterator i;
		for(i=mult.begin();	i!=mult.end(); ++i) {
			const vector<ConvPathData>& last_arg_paths = path_list.back();
			vector<ConvPathData>::const_iterator j;
			for(j=last_arg_paths.begin(); j!=last_arg_paths.end(); ++j) {
				vector<ConvPathData> mult_member = *i;
				mult_member.push_back(*j);
				rc.push_back(mult_member);
			}
		}
		return rc;
	}
	
	vector<pair<Handle<Ctor>,vector<ConvPath> > >
		extract_path(
		const vector<pair<Handle<Ctor>,vector<ConvPathData> > >& path_list) {
		
		vector<pair<Handle<Ctor>,vector<ConvPath> > > rc;
		for(vector<pair<Handle<Ctor>,vector<ConvPathData> > >::const_iterator
			i=path_list.begin();i!=path_list.end();++i) {
			vector<ConvPath> temp;
			for(vector<ConvPathData>::const_iterator
				j=i->second.begin();j!=i->second.end();++j) {
				temp.push_back(j->first);
			}
			rc.push_back(pair<Handle<Ctor>,vector<ConvPath> >(i->first,temp));
		}
		return rc;
	}
	
	vector<vector<ConvWeight> >
		extract_weight(const vector<vector<ConvPathData> >& path_list) {
		
		vector<vector<ConvWeight> > rc;
		for(vector<vector<ConvPathData> >::const_iterator i=path_list.begin();
		i!=path_list.end();++i) {
			vector<ConvWeight> temp;
			for(vector<ConvPathData>::const_iterator j=i->begin();j!=i->end();++j) {
				temp.push_back(j->second);
			}
			rc.push_back(temp);
		}
		return rc;
	}

	vector<ConvPathData> 
		attach_weight(const vector<ConvPath>& paths, const ConvWeight& weight)
	{
		vector<ConvPathData> weighted_paths;
		vector<ConvPath>::const_iterator i;
		for (i=paths.begin(); i!=paths.end(); ++i)
			weighted_paths.push_back(ConvPathData(*i,weight));
		return weighted_paths;
	}

	
	ConvWeight make_weight(const vector<ConvPathData>& path_list) 
	{
		vector<ConvWeight> rc;
		for(vector<ConvPathData>::const_iterator
			i=path_list.begin();i!=path_list.end();++i) {
			rc.push_back(i->second);
		}
		return rc;
	}

	ostream& operator<<(ostream& os, const WeightedConvSource& wcs)
	{
		return os << xparam_name(*wcs.first) << " (" << wcs.second << ")";
	}

		
	std::vector<WeightedConvSource>	atomic_conversions(const type_info& target)
	{
		Type& type = type_registry().type(target);
		return type.get_conversion_sources();
	}
	
	ScalarConvWeight atomic_conversion(Handle<Value> source, const type_info& target)
	{
		const std::type_info& source_type = source->static_type_info();

		if (source_type == target)
			return CONV_EXACT;

		if (source_type == typeid(TentativeValue)) {
			Handle<TentativeValue> tv = extract(*source,TypeTag<TentativeValue>());
			ScalarConvWeight w = tv->conversion_weight(target);
			return w;
		}

		return CONV_IMPOSSIBLE;
	}

}
