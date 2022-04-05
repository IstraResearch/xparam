#ifndef INC_BaseAST_hpp__
#define INC_BaseAST_hpp__

/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Insitute, 1999
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.6.0 MageLang Insitute, 1999
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 */

#include "antlr/config.hpp"
#include "antlr/AST.hpp"

ANTLR_BEGIN_NAMESPACE(xparam_antlr)

class BaseAST;
typedef ASTRefCount<BaseAST> RefBaseAST;

class BaseAST : public AST {
public:
	BaseAST() : AST() {}
	virtual ~BaseAST() {}
protected:
	RefBaseAST down;
	RefBaseAST right;

//private:
//	static bool verboseStringConversion;
//	static ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string> tokenNames;

public:
	virtual void addChild(RefAST c);

private:
	void doWorkForFindAll(ANTLR_USE_NAMESPACE(std)vector<RefAST>& v,
			RefAST target,bool partialMatch);

public:
	virtual bool equals(RefAST t) const;
	virtual bool equalsList(RefAST t) const;
	virtual bool equalsListPartial(RefAST t) const;
	virtual bool equalsTree(RefAST t) const;
	virtual bool equalsTreePartial(RefAST t) const;

	virtual ANTLR_USE_NAMESPACE(std)vector<RefAST> findAll(RefAST t);
	virtual ANTLR_USE_NAMESPACE(std)vector<RefAST> findAllPartial(RefAST t);

	/** Get the first child of this node; null if no children */
	virtual RefAST getFirstChild() const;
	/** Get  the next sibling in line after this one */
	virtual RefAST getNextSibling() const;

	/** Get the token text for this node */
	virtual ANTLR_USE_NAMESPACE(std)string getText() const;
	/** Get the token type for this node */
	virtual int getType() const;

	/** Remove all children */
	virtual void removeChildren();

	/** Set the first child of a node. */
	virtual void setFirstChild(RefAST c);
	/** Set the next sibling after this one. */
	void setNextSibling(RefAST n);

	/** Set the token text for this node */
	virtual void setText(const ANTLR_USE_NAMESPACE(std)string& txt);
	/** Set the token type for this node */
	virtual void setType(int type);

//	static void setVerboseStringConversion(bool verbose,
//			const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& names);

	virtual ANTLR_USE_NAMESPACE(std)string toString() const;
	virtual ANTLR_USE_NAMESPACE(std)string toStringList() const;
	virtual ANTLR_USE_NAMESPACE(std)string toStringTree() const;
};

ANTLR_END_NAMESPACE

#endif //INC_BaseAST_hpp__
