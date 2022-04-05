#ifndef __XP_CONVWEIGHT_H__
#define __XP_CONVWEIGHT_H__

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

#include <typeinfo>
#include<vector>
#include<utility>
#include<typeinfo>
#include <iosfwd>
#include "xp_config.h"
#include "xp_handle.h"
#include "xpv_ctor.h"

namespace xParam_internal {
	
	enum AtomicWeightConstant { 
		CONV_IMPOSSIBLE=0,
		CONV_USER,
		CONV_TENTATIVE,
		CONV_TO_PARENT, 
		CONV_STANDARD, 
		CONV_PROMOTION, 
		CONV_EXACT
	};

	enum ScalarConvWeightType {
		CONV_TYPE_NORMAL = 0,
		CONV_TYPE_LIST,
		CONV_TYPE_TUPLE
	};

	const int nWeightTypes = (int)CONV_EXACT; // number of types - 1

	class ScalarConvWeight { // atomic_conversion_weight
	private:
		ScalarConvWeightType m_conv_type;
		int w[nWeightTypes];
		std::vector<const std::type_info*> m_tuple_types;
		
	public:
		ScalarConvWeight(AtomicWeightConstant atomic_constant = CONV_EXACT);
		ScalarConvWeight(const std::type_info& list_type);
		ScalarConvWeight(const std::vector<const std::type_info*>& tuple_types);

		const int& operator[](const int i) const {return w[i];}
		ScalarConvWeightType conv_type() const { return m_conv_type; }
		const std::vector<const std::type_info*>& tuple_types() const;
		const std::type_info* list_type() const;

		friend ScalarConvWeight operator+(const ScalarConvWeight& aw1,
										const ScalarConvWeight& aw2);
		friend ScalarConvWeight operator*(const ScalarConvWeight& aw, int k);
	};

	ScalarConvWeight operator+(const ScalarConvWeight& aw1,
								const ScalarConvWeight& aw2);
	ScalarConvWeight operator*(const ScalarConvWeight& aw, int k);


	std::ostream& operator<<(std::ostream& os, const ScalarConvWeight& w);

	int scalar_compare(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator<(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator>(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator<=(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator>=(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator==(const ScalarConvWeight& a, const ScalarConvWeight& b);
	bool operator!=(const ScalarConvWeight& a, const ScalarConvWeight& b);
	
	class ConvWeight { // conversion weight
	private:
		ScalarConvWeight m_scalar_weight;
		std::vector< Handle<ConvWeight> > m_list_weight;

	public:
		ConvWeight(const ScalarConvWeight& a=CONV_EXACT);
		ConvWeight(const std::vector<ConvWeight>& v, 
					const ScalarConvWeight& a=CONV_EXACT);

		const ScalarConvWeight& scalar_weight() const { return m_scalar_weight; }
		std::vector<ConvWeight> list_weight() const;
	};

	std::ostream& operator<<(std::ostream& os, const ConvWeight& w);
	
	ConvWeight operator+(const ConvWeight& a, const ConvWeight& b);
	int compare(const ConvWeight& a, const ConvWeight& b);
	int inner_compare(const ConvWeight& a, const ConvWeight& b);
	
	typedef std::vector<const std::type_info*> ConvPath;
	std::ostream& operator<<(std::ostream& os, const ConvPath& path);

	typedef std::pair<ConvPath, ConvWeight> ConvPathData;
	
	std::vector<std::vector<ConvPathData> >
		cartesian_mult(const std::vector<std::vector<ConvPathData> >& path_list);
	
	std::vector<std::pair<Handle<Ctor>,std::vector<ConvPath> > >
		extract_path(const std::vector<std::pair<Handle<Ctor>, std::vector<ConvPathData> > >& path_list);
	
	std::vector<std::vector<ConvWeight> >
		extract_weight(const std::vector<std::vector<ConvPathData> >& path_list);

	std::vector<ConvPathData> attach_weight(const std::vector<ConvPath>& paths,
											const ConvWeight& weight);

	
	ConvWeight make_weight(const std::vector<ConvPathData>& path_list);


	typedef std::pair<const std::type_info*,ScalarConvWeight> WeightedConvSource;
	std::ostream& operator<<(std::ostream& os, const WeightedConvSource& wcs);

	///////////////////////////////////////////////////////////////////////////////
	// This function should return a vector of all types the target type can
	// be converted from, and their respective weights.
	// Note: if that target is a std::vector type, one of the elements in the vector
	// should be its scalar type, with the weight LIST_TO_VECTOR
	///////////////////////////////////////////////////////////////////////////////
	std::vector<WeightedConvSource>	atomic_conversions(const std::type_info& target);
	
	///////////////////////////////////////////////////////////////////
	// Is there an atomic conversion from 'source' to the target type, and if so, 
	// what's its weight?
	// This is a different function from the previous one, because it is only
	// used in the first conversion, where the value information is available.
	///////////////////////////////////////////////////////////////////
	ScalarConvWeight atomic_conversion(Handle<Value> source,
		const std::type_info& target);
	
}

#endif

