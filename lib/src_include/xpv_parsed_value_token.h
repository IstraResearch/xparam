#ifndef XPARAM_PARSED_VALUE_TOKEN_H
#define XPARAM_PARSED_VALUE_TOKEN_H

#include "antlr/CommonToken.hpp"
#include "../xparam/xp_parsed_types.h"

namespace xParam_internal {
	
	//====================================================================
	// CLASS: ParsedValueToken
	// DESCRIPTION: Derives from ANTLR's CommonToken, and passes an addiitonal
	//              ParsedValue.
	//====================================================================
	class ParsedValueToken : public xparam_antlr::CommonToken {
	public:
		ParsedValueToken() : xparam_antlr::CommonToken() {}
		ParsedValueToken(const Handle<ParsedValue>& val)
			: xparam_antlr::CommonToken(), 
			m_val(val) 
		{}
		
		Handle<ParsedValue> getValue() const { return m_val; }
		
	private:
		Handle<ParsedValue> m_val;
	};
	
} // namespace xParam 

#endif // XPARAM_PARSED_VALUE_TOKEN_H
