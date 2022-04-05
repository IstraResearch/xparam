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

#include <typeinfo>
#include "../src_include/xpv_dijkstra_queue.h"

#ifdef XPARAM_DEBUG
#include <iostream>
#include "../xparam/xp_value_management_facade.h"
#endif

using namespace std;

namespace xParam_internal {

	DijkstraQueue::DijkstraQueue(const type_info* origin) 
	{
		TypeWeight tw(origin,CONV_EXACT);
		vector<const type_info*> sources; // no sources
		type_weight_sources[origin] = TypeWeightSources(tw,sources);
		type_weights.insert(tw);
	}
		
	bool DijkstraQueue::empty() const 
	{
		return type_weights.empty();
	}
	
	const type_info* DijkstraQueue::extract_min() 
	{
		TypeWeight min = *type_weights.begin();
#ifdef XPARAM_DEBUG
		cout << "DijkstraQueue::extract_min():" << endl;
		cout << "\t type = " << xparam_name(*min.type) << endl;
		cout << "\t weight = " << min.weight << endl << endl;
#endif
		type_weights.erase(type_weights.begin());
		return min.type;
	}
		
	void DijkstraQueue::update(const type_info* type, const ScalarConvWeight& delta_weight, 
		const type_info* source)
	{
		assert(type_weight_sources.find(source) != type_weight_sources.end());
		ScalarConvWeight source_weight 
			= type_weight_sources[source].type_weight.weight;
		
		TypeWeight tw(type,delta_weight + source_weight);
		const ScalarConvWeight& new_weight = tw.weight;

		if (new_weight == CONV_IMPOSSIBLE)
			return;
		
		SourceMap::iterator i = type_weight_sources.find(tw.type);
		if (i == type_weight_sources.end()) {
			if (type_weight_sources.find(tw.type) == type_weight_sources.end()) {
				type_weight_sources[tw.type] = TypeWeightSources(tw,source);
				type_weights.insert(tw);
			}
			return;
		}
		assert(type_weight_sources.find(tw.type) != type_weight_sources.end());
		const TypeWeightSources& tws = i->second;
		const ScalarConvWeight& old_weight = tws.type_weight.weight;
		if (new_weight < old_weight) {
			// update weight
			type_weights.erase(type_weights.find(tws.type_weight));
			type_weights.insert(tw);
			
			// update sources
			type_weight_sources[tw.type] = TypeWeightSources(tw,source);
			return;
		}
		
		if (new_weight == old_weight) {
			type_weight_sources[tw.type].sources.push_back(source);
		}
	}
		
	ScalarConvWeight DijkstraQueue::get_weight(const type_info* t)
	{
		assert(type_weight_sources.find(t) != type_weight_sources.end());
		return type_weight_sources[t].type_weight.weight;
	}

	vector<ConvPath> DijkstraQueue::get_paths_from(const type_info* t)
	{
		assert(type_weight_sources.find(t) != type_weight_sources.end());

		const TypeWeightSources& tws = type_weight_sources[t];
		const vector<const type_info*>& sources = tws.sources;
		ScalarConvWeight path_weight = tws.type_weight.weight;

		if (sources.empty()) {
			ConvPath empty_path;
			assert(get_weight(t) == CONV_EXACT);
			return vector<ConvPath>(1,empty_path);
		}

		vector<ConvPath> paths;

		vector<const type_info*>::const_iterator i;
		for (i=sources.begin(); i!=sources.end(); ++i) 
		{
			const type_info* source = *i;
			assert(get_weight(source) < get_weight(t));

			vector<ConvPath> sub_paths = get_paths_from(source);
			vector<ConvPath>::iterator j;
			for (j=sub_paths.begin(); j!=sub_paths.end(); ++j) 
			{
				ConvPath& new_path = *j;
				new_path.insert(new_path.begin(),source);
				paths.push_back(new_path);
			}
		}

		return paths;
	}


} // namespace xParam_internal
