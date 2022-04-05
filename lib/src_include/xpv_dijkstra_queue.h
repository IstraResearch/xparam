#ifndef __XP_DIJKSTRA_QUEUE__
#define __XP_DIJKSTRA_QUEUE__

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
#include <vector>
#include <set>
#include <map>
#include "../xparam/xp_type_compare.h"
#include "../xparam/xpv_convweight.h"

namespace xParam_internal {
	
	struct TypeWeight {
		const std::type_info* type;
		ScalarConvWeight weight;

		TypeWeight() {}

		TypeWeight(const std::type_info* t, const ScalarConvWeight& w) 
			: type(t), weight(w) 
		{}
		
	};
	
	inline bool operator<(const TypeWeight& tw1, const TypeWeight& tw2) 
	{
		if (tw1.weight == tw2.weight)
			return TypeInfoCmp()(tw1.type,tw2.type);	
		return tw1.weight < tw2.weight;
	}
	
	
	struct TypeWeightSources {
		TypeWeight type_weight;
		std::vector<const std::type_info*> sources;
		
		TypeWeightSources() {}

		TypeWeightSources(const TypeWeight& tw, 
							const std::vector<const std::type_info*>& srcs)
			: type_weight(tw), sources(srcs)
		{}
		
		TypeWeightSources(const TypeWeight& tw, const std::type_info* source)
			: type_weight(tw)
		{
			sources.push_back(source);
		}
	};
	
	class DijkstraQueue {
	public:
		
		DijkstraQueue(const std::type_info* origin);

		bool empty() const;

		const std::type_info* extract_min();

		void update(const std::type_info* type, 
					const ScalarConvWeight& delta_weight, 
					const std::type_info* source);
		
		ScalarConvWeight get_weight(const std::type_info* t);

		std::vector<ConvPath> get_paths_from(const std::type_info* t);

	private:
		typedef std::set<TypeWeight> WeightSet;
		WeightSet type_weights;
		
		typedef std::map<const std::type_info*, TypeWeightSources, TypeInfoCmp> SourceMap;
		SourceMap type_weight_sources;
		
	};
	
	
}

#endif // __XP_DIJKSTRA_QUEUE__


