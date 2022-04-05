#ifndef INC_ASTFactory_hpp__
#define INC_ASTFactory_hpp__

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
#include "antlr/ASTArray.hpp"
#include "antlr/ASTPair.hpp"

ANTLR_BEGIN_NAMESPACE(xparam_antlr)

/** AST Support code shared by TreeParser and Parser.
 *  We use delegation to share code (and have only one
 *  bit of code to maintain) rather than subclassing
 *  or superclassing (forces AST support code to be
 *  loaded even when you don't want to do AST stuff).
 *
 *  Typically, setASTNodeType is used to specify the
 *  type of node to create, but you can override
 *  create to make heterogeneous nodes etc...
 */
class ASTFactory {
public:
	typedef RefAST (*factory_type)();
protected:
	/** Name of AST class to create during tree construction.
	 *  Null implies that the create method should create
	 *  a default AST type such as CommonAST.
	 */
	factory_type nodeFactory;

public:
	ASTFactory();
	/** Add a child to the current AST */
	void addASTChild(ASTPair& currentAST, RefAST child);
	/** Create a new empty AST node; if the user did not specify
	 *  an AST node type, then create a default one: CommonAST.
	 */
	virtual RefAST create();
	RefAST create(int type);
	RefAST create(int type, const ANTLR_USE_NAMESPACE(std)string& txt);
	/** Create a new empty AST node; if the user did not specify
	 *  an AST node type, then create a default one: CommonAST.
	 */
	RefAST create(RefAST tr);
	RefAST create(RefToken tok);
	/** Copy a single node.  clone() is not used because
	 *  we want to return an AST not a plain object...a type
	 *  safety issue.  Further, we want to have all AST node
	 *  creation go through the factory so creation can be
	 *  tracked.  Returns null if t is null.
	 */
	RefAST dup(RefAST t);
	/** Duplicate tree including siblings of root. */
	RefAST dupList(RefAST t);
	/**Duplicate a tree, assuming this is a root node of a tree--
	 * duplicate that node and what's below; ignore siblings of root node.
	 */
	RefAST dupTree(RefAST t);
	/** Make a tree from a list of nodes.  The first element in the
	 *  array is the root.  If the root is null, then the tree is
	 *  a simple list not a tree.  Handles null children nodes correctly.
	 *  For example, build(a, b, null, c) yields tree (a b c).  build(null,a,b)
	 *  yields tree (nil a b).
	 */
	RefAST make(ANTLR_USE_NAMESPACE(std)vector<RefAST> nodes);
	/** Make a tree from a list of nodes, where the nodes are contained
	  * in an ASTArray object
	  */
	RefAST make(ASTArray* nodes);
	/** Make an AST the root of current AST */
	void makeASTRoot(ASTPair& currentAST, RefAST root);
	void setASTNodeFactory(factory_type factory);
	virtual ~ASTFactory() {}
private:
	ASTFactory( const ASTFactory& );
	ASTFactory& operator=( const ASTFactory& );
};

ANTLR_END_NAMESPACE

#endif //INC_ASTFactory_hpp__
