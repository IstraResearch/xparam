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
#include <queue>
#include <iostream>
#include "../src_include/xpv_conversions.h"
#include "../xparam/xp_value_management.h"
#include "../xparam/xpv_registry.h"
#include "../src_include/xpv_tentative.h"
#include "../src_include/xpv_dijkstra_queue.h"

using namespace std;

namespace xParam_internal {

	//////////////////////////////////////////////////////////////////////////
	// Inner Declarations
	//////////////////////////////////////////////////////////////////////////

	template<class T, class Cmp>
		void add_to_best(vector<T>& best, const T& candidate, TypeTag<Cmp>);
	
	vector<ConvPathData> find_best_matches(const Handle<Value>& arg,
		const type_info* ctor_type);
	
	void mult_add_to_best(vector<ConvPathData>& best_paths,
		const vector<ConvPath>& paths, 
		const vector<ConvWeight>& path_weights);
	
	void insert_before_path(const type_info* first_type, vector<ConvPath>& paths);

	vector<ConvWeight> element_weights_to_path_weight(
			const vector< vector<ConvPathData> >& element_conversions,
			const ScalarConvWeight& scalar_weight);
	
	vector<ConvWeight> list_to_target_weights(const Handle<Value>& arg, 
		const type_info* element_type,
		const ScalarConvWeight& scalar_weight);

	vector<ConvWeight> tuple_to_target_weights(const Handle<Value>& arg, 
		const type_info* element_type,
		const ScalarConvWeight& scalar_weight);
	
	vector<ConvPathData> find_best_matches(const Handle<Value>& arg,
		const type_info* ctor_type);
		
	vector<vector<ConvPathData> > find_best_matches(const ValueList& args,
		const vector<const type_info*>& ctor_types);
	
	//////////////////////////////////////////////////////////////////////////
	// Implementation
	//////////////////////////////////////////////////////////////////////////

	template<class T, class Cmp>
	void add_to_best(vector<T>& best, const T& candidate, TypeTag<Cmp>)
	{
		bool should_go_in=true;

		typename vector<T>::iterator i = best.begin();
		while (i != best.end() )
		{ 
			int cmp = Cmp::compare(candidate,*i);
			if (cmp<0) 
				should_go_in=false;
			if (cmp>0)
				best.erase(i);
			else
				++i;
		}

		if (should_go_in)
			best.push_back(candidate);
	}

	struct PathDataCmp {
		static int compare(const ConvPathData& a, const ConvPathData& b) {
			return xParam_internal::compare(a.second,b.second);
		}
	};

	void mult_add_to_best(vector<ConvPathData>& best_paths,
						 const vector<ConvPath>& paths, 
						 const vector<ConvWeight>& path_weights)
	{	
		typedef vector<ConvWeight>::const_iterator ConvWeightIter;
		typedef vector<ConvPath>::const_iterator ConvPathIter;

		for(ConvWeightIter i=path_weights.begin(); i!=path_weights.end(); ++i) 
			for (ConvPathIter j=paths.begin(); j!=paths.end(); ++j) 
				add_to_best(best_paths, ConvPathData(*j,*i), TypeTag<PathDataCmp>());
	}

	void insert_before_path(const type_info* first_type, vector<ConvPath>& paths)
	{
		vector<ConvPath>::iterator i;
		for (i=paths.begin(); i!=paths.end(); ++i)
			i->insert(i->begin(),first_type);
	}

	vector<ConvWeight> element_weights_to_path_weight(
			const vector< vector<ConvPathData> >& element_conversions,
			const ScalarConvWeight& scalar_weight)
	{
		assert(scalar_weight.conv_type() == CONV_TYPE_NORMAL);

		// get weights of all combinations of element paths
		vector< vector<ConvWeight> > expanded_weights 
			= extract_weight(cartesian_mult(element_conversions));

		// compute list weight for each option (list->vec), and add the given 
		// scalar weight for the rest of the path (vec->target)
		vector<ConvWeight> whole_path_weights;
		vector< vector<ConvWeight> >::const_iterator j;
		for(j=expanded_weights.begin(); j!=expanded_weights.end(); ++j) 
			whole_path_weights.push_back(ConvWeight(*j,scalar_weight));

		return whole_path_weights;
	}


	vector<ConvWeight> list_to_target_weights(const Handle<Value>& arg, 
											const ScalarConvWeight& list_weight,
											const ScalarConvWeight& scalar_weight)
	{
		assert(list_weight.conv_type() == CONV_TYPE_LIST);

		Handle<ValueList> val_list = extract(*arg,TypeTag<ValueList>());
		assert(!val_list.empty());

		const type_info* target_type = list_weight.list_type();

		// compute best paths for each element
		vector< vector<ConvPathData> > element_conversions;
		ValueList::const_iterator iVal;
		for(iVal=val_list->begin(); iVal!=val_list->end(); ++iVal) {
			element_conversions.push_back(find_best_matches(*iVal,target_type));
		}

		return element_weights_to_path_weight(element_conversions,scalar_weight);
	}

	vector<ConvWeight> tuple_to_target_weights(const Handle<Value>& arg, 
											const ScalarConvWeight& list_weight,
											const ScalarConvWeight& scalar_weight)
	{
		assert(list_weight.conv_type() == CONV_TYPE_TUPLE);

		Handle<ValueTuple> val_tuple = extract(*arg,TypeTag<ValueTuple>());
		assert(!val_tuple.empty());

		vector<const type_info*> target_types = list_weight.tuple_types();

		// if list size doesn't match, there are no conversions
		// (this test will only matter for tuples - not for lists)
		if (target_types.size() != val_tuple->size())
			return vector<ConvWeight>();

		// compute best paths for each element
		vector< vector<ConvPathData> > element_conversions;
		ValueTuple::const_iterator iVal;
		vector<const type_info*>::const_iterator iTargetType;
		for(iVal=val_tuple->begin(), iTargetType=target_types.begin(); 
		    iVal!=val_tuple->end(); 
			++iVal,++iTargetType) {
			element_conversions.push_back(find_best_matches(*iVal,*iTargetType));
		}

		return element_weights_to_path_weight(element_conversions,scalar_weight);
	}


	
	vector<ConvPathData> find_best_matches(const Handle<Value>& arg,
											const type_info* ctor_type)	
	{
		const type_info* arg_type = &(arg->static_type_info());

		if ((*arg_type == typeid(ValueList)) || (*arg_type == typeid(ValueTuple))) {
			ScalarConvWeightType multi_weight_type 
				= (*arg_type == typeid(ValueList)) ?	
                                           CONV_TYPE_LIST : CONV_TYPE_TUPLE; 
			vector<ConvPathData> best_paths_to_source;
			DijkstraQueue q(ctor_type);
			while (!q.empty()) {
				const type_info* frontier = q.extract_min();

				vector<WeightedConvSource> step = atomic_conversions(*frontier);
				vector<WeightedConvSource>::const_iterator i;
				for(i=step.begin(); i!=step.end(); ++i) {
					const type_info* conv_source = i->first;
					const ScalarConvWeight& conv_weight = i->second;
					
					if (conv_weight.conv_type() == CONV_TYPE_NORMAL) {
						q.update(conv_source, conv_weight, frontier);
					} 
					else { // list or tuple conversion

						// CONV_TYPE_LIST only applies to ValueLists and 
						// CONV_TYPE_TUPLE only applies to ValueTuples
						if (conv_weight.conv_type() != multi_weight_type)
							continue;

						// get best weights for list -> vector (frontier) -> ctor_type
						ScalarConvWeight scalar_weight = q.get_weight(frontier);
						vector<ConvWeight> path_weights 
							= (multi_weight_type == CONV_TYPE_LIST) ? 
							  list_to_target_weights(arg,conv_weight,scalar_weight)
						    : tuple_to_target_weights(arg,conv_weight,scalar_weight);
						
						// compute paths list->vector->ctor_type
						vector<ConvPath> paths = q.get_paths_from(frontier);
						insert_before_path(frontier,paths);
						
						// add all combinations (path + weight) to best paths known
						mult_add_to_best(best_paths_to_source, paths, path_weights);
					}
				}
			}
			return best_paths_to_source;
		}
		else { // scalar arg
			DijkstraQueue q(ctor_type);
			while (!q.empty()) {
				const type_info* frontier = q.extract_min();

				if (*frontier == *arg_type) // found paths to source - return them
					return attach_weight(q.get_paths_from(frontier),
											q.get_weight(frontier));
				
				ScalarConvWeight final_step=atomic_conversion(arg,*frontier);
				if (final_step != CONV_IMPOSSIBLE)
					q.update(arg_type, final_step, frontier);
				

				vector<WeightedConvSource> step = atomic_conversions(*frontier);
				vector<WeightedConvSource>::const_iterator i;
				for(i=step.begin(); i!=step.end(); ++i) {
					const type_info* conv_source = i->first;
					const ScalarConvWeight& conv_weight = i->second;
					if (conv_weight.conv_type() == CONV_TYPE_NORMAL)
						q.update(conv_source, conv_weight, frontier);
				}
			}
			return vector<ConvPathData>(); // no paths found
		}
	}


	vector<vector<ConvPathData> > find_best_matches(const ValueList& args,
		const vector<const type_info*>& ctor_types)
	{
		vector<vector<ConvPathData> > paths;
		if (args.size()!=ctor_types.size()) return paths;
		// This is meant to return an empty path list, if the number of parameters
		// doesn't match. True, we could have found it out sooner, but this is
		// methodically the correct place for this check.
		
		ValueList::const_iterator ai;
		vector<const type_info*>::const_iterator ci;
		for(ai=args.begin(),ci=ctor_types.begin();ai!=args.end();++ai,++ci) {
			paths.push_back(find_best_matches(*ai,*ci));
		}
		return cartesian_mult(paths);
	}
	

	typedef pair< Handle<Ctor>, vector<ConvPathData> > CtorConvData;

	struct CtorConvCmp {
		static int compare(const CtorConvData& a, const CtorConvData& b) {
			return xParam_internal::compare(make_weight(a.second), make_weight(b.second));
		}
	};

	// This routine utilizes a highly naive algorithm.
	vector<pair<Handle<Ctor>,vector<ConvPath> > > 
		find_best_matches(const ValueList& args, const CtorList& ctor_list)
	{
		vector<CtorConvData> rc;
		for(CtorList::const_iterator i=ctor_list.begin();i!=ctor_list.end();++i) 
		{
			vector< vector<ConvPathData> > paths 
					= find_best_matches(args,(*i)->arg_types());

			vector< vector<ConvPathData> >::const_iterator j;
			for(j=paths.begin(); j!=paths.end(); ++j)
				add_to_best(rc, CtorConvData(*i,*j), TypeTag<CtorConvCmp>());
		}
		return extract_path(rc);
	}
	
	vector<ConvPath> find_best_paths(Handle<Value> val, const type_info& target)
	{
		vector<ConvPathData> best_matches = find_best_matches(val,&target);
		vector<ConvPath> paths;
		for (vector<ConvPathData>::const_iterator i=best_matches.begin(); i!=best_matches.end(); ++i)
			paths.push_back(i->first);
		return paths;
	}


	Handle<Value> convert_along_path(Handle<Value> val, const ConvPath& path)
	{
//	DEBUG	cerr << path << endl;
		ConvPath::const_iterator i=path.begin();
		if (i == path.end())
			return val;

		// TentativeValues may occur as the conversion source, and they get
		// special treatment.
		if (val->static_type_info() == typeid(TentativeValue)) {
			Handle<TentativeValue> tv = extract(*val,TypeTag<TentativeValue>());
			assert(!tv.empty());
			val = tv->convert_to(**i);
			++i;
		}

		// other conversion steps should be normal registered conversions
		for (; i!=path.end(); ++i) {
			Type& type = type_registry().type(**i);
			val = type.create_atomically_from(val);
		}
		return val;		
	}
	
}

