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


#pragma warning (disable: 4101)

/* $ANTLR 2.7.1: "parser.g" -> "xParamParser.cpp"$ */
#include <../src_include/xParamParser.hpp>
#include "antlr/NoViableAltException.hpp"
#include "antlr/SemanticException.hpp"


#include "../xparam/xp_error.h"

using namespace xparam_antlr;
using namespace std;


ANTLR_BEGIN_NAMESPACE(xParam_internal)



xParamParser::xParamParser(xparam_antlr::TokenBuffer& tokenBuf, int k)
: xparam_antlr::LLkParser(tokenBuf,k)
{
	setTokenNames(_tokenNames);
}

xParamParser::xParamParser(xparam_antlr::TokenBuffer& tokenBuf)
: xparam_antlr::LLkParser(tokenBuf,1)
{
	setTokenNames(_tokenNames);
}

xParamParser::xParamParser(xparam_antlr::TokenStream& lexer, int k)
: xparam_antlr::LLkParser(lexer,k)
{
	setTokenNames(_tokenNames);
}

xParamParser::xParamParser(xparam_antlr::TokenStream& lexer)
: xparam_antlr::LLkParser(lexer,1)
{
	setTokenNames(_tokenNames);
}

xParamParser::xParamParser(const xparam_antlr::ParserSharedInputState& state)
: xparam_antlr::LLkParser(state,1)
{
	setTokenNames(_tokenNames);
}

void xParamParser::value_set(
	 AssignmentListener& listener 
) {
	
	try {      // for error handling
		{
		for (;;) {
			if ((LA(1)==URL||LA(1)==ID||LA(1)==FLAG)) {
				value_set_member(listener);
			}
			else {
				goto _loop3;
			}
			
		}
		_loop3:;
		}
		{
		switch ( LA(1)) {
		case 4:
		{
			match(4);
			break;
		}
		case xparam_antlr::Token::EOF_TYPE:
		{
			match(xparam_antlr::Token::EOF_TYPE);
			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
		}
	}
	catch (ANTLRException& ex) {
		if (inputState->guessing==0) {

			
					throw Error(ex.what());
				

		} else {
			throw ex;
		}
	}
}

void xParamParser::value_set_member(
	 AssignmentListener& listener 
) {
	xparam_antlr::RefToken  url = xparam_antlr::nullToken;
	
	switch ( LA(1)) {
	case ID:
	{
		member_assignment(listener);
		break;
	}
	case URL:
	{
		url = LT(1);
		match(URL);
		if ( inputState->guessing==0 ) {

			m_url_read_value_set(url->getText(),listener);

		}
		break;
	}
	case FLAG:
	{
		flag_setting(listener);
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltException(LT(1), getFilename());
	}
	}
}

Handle<ParsedValue>  xParamParser::value() {

	Handle<ParsedValue> val;

	xparam_antlr::RefToken  url = xparam_antlr::nullToken;
	
	try {      // for error handling
		switch ( LA(1)) {
		case TENTATIVE:
		case CHAR:
		case STRING:
		case SHELL_STRINGS:
		case PARSED_VALUE:
		{
			val=basic_type();
			break;
		}
		case ID:
		{
			val=id_tentative_string();
			break;
		}
		case TYPENAME:
		{
			val=compound_value();
			break;
		}
		case 12:
		{
			val=list_value();
			break;
		}
		case 14:
		{
			val=map_value();
			break;
		}
		case URL:
		{
			url = LT(1);
			match(URL);
			if ( inputState->guessing==0 ) {

				val=m_url_read_value(url->getText());

			}
			break;
		}
		default:
		{
			throw xparam_antlr::NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (NoViableAltException& ex) {
		if (inputState->guessing==0) {

			
					string msg;
					if (LT(1)->getType() == Token::EOF_TYPE)
						msg = "unexpected EOF";
					else
						msg = "unexpected token type";
					throw Error(msg);
				

		} else {
			throw ex;
		}
	}
	catch (ANTLRException& ex) {
		if (inputState->guessing==0) {

			
					throw Error(ex.what());
				

		} else {
			throw ex;
		}
	}
	return val;
}

Handle<ParsedValue>  xParamParser::basic_type() {

	Handle<ParsedValue> val;

	xparam_antlr::RefToken  t = xparam_antlr::nullToken;
	xparam_antlr::RefToken  c = xparam_antlr::nullToken;
	xparam_antlr::RefToken  s = xparam_antlr::nullToken;
	xparam_antlr::RefToken  shell_strings = xparam_antlr::nullToken;
	xparam_antlr::RefToken  parsed_val = xparam_antlr::nullToken;
	
	switch ( LA(1)) {
	case TENTATIVE:
	{
		t = LT(1);
		match(TENTATIVE);
		if ( inputState->guessing==0 ) {

			
					val = Handle<ParsedValue>(new ParsedTentativeValue(t->getText()));
				

		}
		break;
	}
	case CHAR:
	{
		c = LT(1);
		match(CHAR);
		if ( inputState->guessing==0 ) {

			
					char decoded_char = m_decode_char(c->getText());
					val = Handle<ParsedValue>(new ParsedCharValue(decoded_char));
				

		}
		break;
	}
	case STRING:
	{
		s = LT(1);
		match(STRING);
		if ( inputState->guessing==0 ) {

			
					string decoded_string = m_decode_string(s->getText());
					val = Handle<ParsedValue>(new ParsedStringValue(decoded_string));
				

		}
		break;
	}
	case SHELL_STRINGS:
	{
		shell_strings = LT(1);
		match(SHELL_STRINGS);
		if ( inputState->guessing==0 ) {

			
					ParsedValueList strings = m_cut_shell_strings(shell_strings->getText());
					val = Handle<ParsedValue>(new ParsedListValue(strings));
				

		}
		break;
	}
	case PARSED_VALUE:
	{
		parsed_val = LT(1);
		match(PARSED_VALUE);
		if ( inputState->guessing==0 ) {

			
					Token* base_token = parsed_val.get();
					assert(base_token != 0);
					ParsedValueToken *parsed_val_token = dynamic_cast<ParsedValueToken*>(base_token);
					assert(parsed_val_token != 0);
					val = parsed_val_token->getValue();
				

		}
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltException(LT(1), getFilename());
	}
	}
	return val;
}

Handle<ParsedValue>  xParamParser::id_tentative_string() {

	Handle<ParsedValue> val;

	xparam_antlr::RefToken  id = xparam_antlr::nullToken;
	
	id = LT(1);
	match(ID);
	if ( inputState->guessing==0 ) {

		
				std::string encoded_value = 'S' + id->getText();
				val = Handle<ParsedValue>(new ParsedTentativeValue(encoded_value));
			

	}
	return val;
}

Handle<ParsedValue>  xParamParser::compound_value() {

	Handle<ParsedValue> val;

	xparam_antlr::RefToken  tn = xparam_antlr::nullToken;

	
	ParsedValueList args;
	

	
	try {      // for error handling
		tn = LT(1);
		match(TYPENAME);
		match(10);
		args=list_of_values();
		match(11);
		if ( inputState->guessing==0 ) {

			val = Handle<ParsedValue>(new ParsedCompoundValue(tn->getText(),args));

		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					throw Error("while parsing constructor for '" + tn->getText() + "':\n" + ex.what());
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while parsing constructor for '" + tn->getText() + "'");
				

		} else {
			throw ex;
		}
	}
	return val;
}

Handle<ParsedValue>  xParamParser::list_value() {

	Handle<ParsedValue> val;


	
	ParsedValueList values;
	

	
	try {      // for error handling
		match(12);
		values=list_of_values();
		match(13);
		if ( inputState->guessing==0 ) {

			val = Handle<ParsedValue>(new ParsedListValue(values));

		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					throw Error("while reading list:\n" + string(ex.what()));
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while reading list");
				

		} else {
			throw ex;
		}
	}
	return val;
}

Handle<ParsedValue>  xParamParser::map_value() {

	Handle<ParsedValue> val;


	
	ParsedPairList map_items;
	

	
	try {      // for error handling
		match(14);
		map_items=list_of_map_items();
		match(15);
		if ( inputState->guessing==0 ) {

			val = Handle<ParsedValue>(new ParsedMapValue(map_items));

		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					throw Error("while reading map:\n" + string(ex.what()));
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while reading map");
				

		} else {
			throw ex;
		}
	}
	return val;
}

void xParamParser::member_assignment(
	AssignmentListener& listener
) {
	xparam_antlr::RefToken  id = xparam_antlr::nullToken;

	
	Handle<ParsedValue> val;
	

	
	try {      // for error handling
		id = LT(1);
		match(ID);
		match(7);
		val=global_scope_value();
		if ( inputState->guessing==0 ) {

			listener.notify(id->getText(),val);

		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					throw Error("while parsing assignment to parameter '" 
							+ id->getText() + "':\n" + ex.what());
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error parsing assignment to parameter '"
							+ id->getText() + "'");
				

		} else {
			throw ex;
		}
	}
}

void xParamParser::flag_setting(
	AssignmentListener& listener
) {
	xparam_antlr::RefToken  flag = xparam_antlr::nullToken;
	
	flag = LT(1);
	match(FLAG);
	if ( inputState->guessing==0 ) {

		
				string str = flag->getText();
				bool flag_value = (str[0] == '+');
				string flag_name = str.substr(1,str.size()-1);
		
				Handle<ParsedValue> parsed_val(new ParsedBoolValue(flag_value));
		
				listener.notify(flag_name,parsed_val);
			

	}
}

Handle<ParsedValue>  xParamParser::global_scope_value() {

	Handle<ParsedValue> val;


	
	ParsedValueList values;
	

	
	values=non_empty_list_of_values();
	if ( inputState->guessing==0 ) {

		
				if (values.size() == 1) { // it's a single value
					val = values[0];
				}
				else { // it's a list of values
					val = Handle<ParsedValue>(new ParsedListValue(values));
				}
			

	}
	return val;
}

ParsedValueList  xParamParser::non_empty_list_of_values() {

	ParsedValueList list;


	
	Handle<ParsedValue> val;
	

	
	try {      // for error handling
		val=value();
		if ( inputState->guessing==0 ) {

			list.push_back(val);

		}
		{
		for (;;) {
			if ((LA(1)==16)) {
				match(16);
				val=value();
				if ( inputState->guessing==0 ) {

					list.push_back(val);

				}
			}
			else {
				goto _loop20;
			}
			
		}
		_loop20:;
		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					if (!list.empty())
						throw Error("while parsing element " 
								+ m_int_to_string(list.size())
								+ " of value list:\n" + ex.what());
					else
						throw;
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while parsing element "
							+ m_int_to_string(list.size())
							+ " of value list:\n" + ex.what());
				

		} else {
			throw ex;
		}
	}
	return list;
}

ParsedValueList  xParamParser::list_of_values() {

	ParsedValueList list;

	
	switch ( LA(1)) {
	case 11:
	case 13:
	{
		break;
	}
	case URL:
	case ID:
	case TYPENAME:
	case 12:
	case 14:
	case TENTATIVE:
	case CHAR:
	case STRING:
	case SHELL_STRINGS:
	case PARSED_VALUE:
	{
		list=non_empty_list_of_values();
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltException(LT(1), getFilename());
	}
	}
	return list;
}

ParsedPairList  xParamParser::list_of_map_items() {

	ParsedPairList map_items;

	
	switch ( LA(1)) {
	case 15:
	{
		break;
	}
	case URL:
	case ID:
	case TYPENAME:
	case 12:
	case 14:
	case TENTATIVE:
	case CHAR:
	case STRING:
	case SHELL_STRINGS:
	case PARSED_VALUE:
	{
		map_items=non_empty_list_of_map_items();
		break;
	}
	default:
	{
		throw xparam_antlr::NoViableAltException(LT(1), getFilename());
	}
	}
	return map_items;
}

ParsedPairList  xParamParser::non_empty_list_of_map_items() {

	ParsedPairList map_items;


	
	ParsedPair item;
	

	
	try {      // for error handling
		item=map_item();
		if ( inputState->guessing==0 ) {

			map_items.push_back(item);

		}
		{
		for (;;) {
			if ((LA(1)==16)) {
				match(16);
				item=map_item();
				if ( inputState->guessing==0 ) {

					map_items.push_back(item);

				}
			}
			else {
				goto _loop24;
			}
			
		}
		_loop24:;
		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					if (!map_items.empty())
						throw Error("while parsing pair " 
								+ m_int_to_string(map_items.size())
								+ " of map:\n" + ex.what());
					else
						throw;
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while parsing pair "
							+ m_int_to_string(map_items.size())
							+ " of map:\n" + ex.what());
				

		} else {
			throw ex;
		}
	}
	return map_items;
}

ParsedPair  xParamParser::map_item() {

	ParsedPair item;


	
	Handle<ParsedValue> item_key;
	Handle<ParsedValue> item_value;
	

	
	try {      // for error handling
		item_key=value();
		match(17);
		item_value=value();
		if ( inputState->guessing==0 ) {

			item = make_pair(item_key,item_value);

		}
	}
	catch (Error& ex) {
		if (inputState->guessing==0) {

			
					throw Error("while parsing key=>value pair:\n" 
							+ string(ex.what()));
				

		} else {
			throw ex;
		}
	}
	catch (RecognitionException& ex) {
		if (inputState->guessing==0) {

			
					throw Error("syntax error while parsing key=>value pair:\n" 
							+ string(ex.what()));
				

		} else {
			throw ex;
		}
	}
	return item;
}

const char* xParamParser::_tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\";\"",
	"URL",
	"ID",
	"\"=\"",
	"FLAG",
	"TYPENAME",
	"\"(\"",
	"\")\"",
	"\"[\"",
	"\"]\"",
	"\"{\"",
	"\"}\"",
	"\",\"",
	"\"=>\"",
	"TENTATIVE",
	"CHAR",
	"STRING",
	"SHELL_STRINGS",
	"PARSED_VALUE",
	0
};



ANTLR_END_NAMESPACE
