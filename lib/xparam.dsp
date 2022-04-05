# Microsoft Developer Studio Project File - Name="xparam" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=xparam - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xparam.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xparam.mak" CFG="xparam - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xparam - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "xparam - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xparam - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release-bin"
# PROP Intermediate_Dir "Release-obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "antlr" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "xparam - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "antlr" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "xparam - Win32 Release"
# Name "xparam - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\antlr\src\ANTLRException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\ASTFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\ASTRefCount.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\BaseAST.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\BitSet.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CharBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CharScanner.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CommonAST.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CommonASTWithHiddenTokens.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CommonHiddenStreamToken.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\CommonToken.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\DynamicLoaderLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\DynamicLoaderParser.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\InputBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\LexerSharedInputState.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\LLkParser.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\MismatchedCharException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\MismatchedTokenException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\NoViableAltException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\NoViableAltForCharException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\ParserSharedInputState.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\RecognitionException.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\String.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\Token.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TokenBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TokenStreamBasicFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TokenStreamHiddenTokenFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TokenStreamSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TreeParser.cpp
# End Source File
# Begin Source File

SOURCE=.\antlr\src\TreeParserSharedInputState.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\TypeNameLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\TypeNameParser.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_file_utils.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_loader.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_param_imp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_paramset.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_parsed_types.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_bool.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_char.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_double.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_float.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_int.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_long.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_long_double.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_long_long.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_null.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_raw_bytes.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_short.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_string.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_tentative.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_unsigned_char.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_unsigned_int.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_unsigned_long.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_unsigned_long_long.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_unsigned_short.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_value_list.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_regtype_value_tuple.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_saver.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_sstream.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_value_list.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_value_sink.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_value_source.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_value_source_imp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xp_value_tuple.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xParamLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xParamParser.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_common_regcom.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_const_registry.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_conversions.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_convweight.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_ctor.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_dijkstra_queue.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_dynamic_loader.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_dynamic_loader_parser.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_hvl_registry.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_lexer_methods.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_parser_methods.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_registry.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_scheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_template_fooler.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_tentative.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_type.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_typed_tuple_registry.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_value_imp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\xpv_value_management_facade.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\antlr\antlr\ANTLRException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\AST.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ASTArray.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ASTFactory.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ASTNULLType.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ASTPair.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ASTRefCount.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\BaseAST.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\BitSet.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CharBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CharScanner.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CharStreamException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CharStreamIOException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CircularQueue.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CommonAST.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CommonASTWithHiddenTokens.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CommonHiddenStreamToken.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\CommonToken.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\config.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\DynamicLoaderLexer.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\DynamicLoaderLexerTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\DynamicLoaderParser.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\DynamicLoaderParserTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\InputBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\LexerSharedInputState.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\LLkParser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\MismatchedCharException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\MismatchedTokenException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\NoViableAltException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\NoViableAltForCharException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\Parser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\ParserSharedInputState.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\RecognitionException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\RefCount.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\SemanticException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\String.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\Token.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenBuffer.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStream.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamBasicFilter.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamHiddenTokenFilter.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamIOException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamRecognitionException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamRetryException.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TokenStreamSelector.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TreeParser.hpp
# End Source File
# Begin Source File

SOURCE=.\antlr\antlr\TreeParserSharedInputState.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\TypeNameLexer.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\TypeNameLexerTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\TypeNameParser.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\TypeNameParserTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_config.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_error.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xp_file_utils.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_handle.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_hvl.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_loader.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_param.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_param_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_paramset.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_paramset_manip.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_parsed_types.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_parser.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_raw_bytes.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xp_regtype_char_body_output.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xp_regtype_real_output.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_saver.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_singleton.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xp_sstream.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_type_compare.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_type_tag.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_typed_tuple.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_typed_value_map.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_user_namespace.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_list.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_management.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_management_facade.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_sink.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_sink_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_source.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_source_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xp_value_tuple.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xparam.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xparam_extend.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xParamLexer.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\xParamLexerTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\xParamParser.hpp
# End Source File
# Begin Source File

SOURCE=.\src_include\xParamParserTokenTypes.hpp
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_arg_def.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_arg_passers.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_common_regcom.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_const.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_const_registry.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_conversions.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_convweight.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_copier.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_copier_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_ctor.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_ctor_imp.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_dijkstra_queue.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_direct_output.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_dtor.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_dtor_imp.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_dynamic_loader.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_dynamic_loader_parser.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_enum_registry.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_extend_namespace.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_facade_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_hvl_creator.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_hvl_creator_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_hvl_registry.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_iconv.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_iconv_imp.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_link_patch.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_output.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_output_functor.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_parsed_value_token.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_class.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_const.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_conversion.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_ctor.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_ctor_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_enum.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_hvl.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_inheritance.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_list.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_macros.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_map.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_output.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_pair.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_set.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_typed_tuple.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_typed_value_map.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_reg_vector.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_regcom.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_registry.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_scheduler.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_subobject_output.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_template_fooler.h
# End Source File
# Begin Source File

SOURCE=.\src_include\xpv_tentative.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_type.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_typed_tuple_creator.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_typed_tuple_creator_imp.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_typed_tuple_registry.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_untyped_null.h
# End Source File
# Begin Source File

SOURCE=.\xparam\xpv_value_imp.h
# End Source File
# End Group
# End Target
# End Project
