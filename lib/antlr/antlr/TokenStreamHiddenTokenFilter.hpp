#ifndef INC_TokenStreamHiddenTokenFilter_hpp__
#define INC_TokenStreamHiddenTokenFilter_hpp__

#include "antlr/config.hpp"
#include "antlr/TokenStreamBasicFilter.hpp"

ANTLR_BEGIN_NAMESPACE(xparam_antlr)

/**This object filters a token stream coming from a lexer
 * or another TokenStream so that only certain token channels
 * get transmitted to the parser.
 *
 * Any of the channels can be filtered off as "hidden" channels whose
 * tokens can be accessed from the parser.
 */
class TokenStreamHiddenTokenFilter : public TokenStreamBasicFilter {
	// protected BitSet discardMask;
protected:
	BitSet hideMask;

private:
	RefToken nextMonitoredToken;
	
protected:
	/** track tail of hidden list emanating from previous
	 *  monitored token
	 */
	RefToken lastHiddenToken;

	RefToken firstHidden; // = null;

public:
	TokenStreamHiddenTokenFilter(TokenStream& input);

protected:
	void consume();

private:
	void consumeFirst();

public:
	BitSet getDiscardMask() const;
	 
	/** Return a ptr to the hidden token appearing immediately after
	 *  token t in the input stream.
	 */
	RefToken getHiddenAfter(RefToken t);

	/** Return a ptr to the hidden token appearing immediately before
	 *  token t in the input stream.
	 */
	RefToken getHiddenBefore(RefToken t);

	BitSet getHideMask() const;

	/** Return the first hidden token if one appears
	 *  before any monitored token.
	 */
	RefToken getInitialHiddenToken();

	void hide(int m);

	void hide(const BitSet& mask);

protected:
	RefToken LA(int i);

public:
/** Return the next monitored token.
 *  Test the token following the monitored token.
 *  If following is another monitored token, save it
 *  for the next invocation of nextToken (like a single
 *  lookahead token) and return it then.
 *  If following is unmonitored, nondiscarded (hidden)
 *  channel token, add it to the monitored token.
 *
 *  Note: EOF must be a monitored Token.
 */
	RefToken nextToken();
};

ANTLR_END_NAMESPACE

#endif //INC_TokenStreamHiddenTokenFilter_hpp__
