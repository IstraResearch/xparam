#ifndef XPARAM_CONFIG_H
#define XPARAM_CONFIG_H

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

/*
 * defines compiler specific settings
 */

#ifdef __GNUC__
#define OS_UNIX
#endif

// #if _MSC_VER >= 1200
#ifdef _MSC_VER

#if _MSC_VER >= 1200
#define OS_WINDOWS
#define NO_TEMPLATE_FRIENDS
#define BEFORE_IS_INT
#define XPARAM_STATIC_LIB
#define NO_DYNAMIC_LOADING
#define NO_LONG_LONG
#else
#error Compiler version prior to VC6 not supported
#endif // _MSC_VER >= 1200
#endif // _MSC_VER

#endif // XPARAM_CONFIG_H
