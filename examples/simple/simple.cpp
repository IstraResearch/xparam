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
  This program looks for input of the type

  simple num=15 name=Mary

  where "Mary" is your name and "15" is the number you're guessing.
  It compares between the number you guessed and the number written
  in the file my_number.txt, and tells you whether you guessed too
  high or too low.
*/

#pragma warning (disable: 4786)

#include <iostream>
#include <fstream>
#include <string>
#include <xparam.h>

using namespace xParam;
using namespace std;

int main(int argc, char* argv[])
{
  xparam_init();

  ParamSet ps;
  int num,my_number;
  string name;
  try {
    ps << "This program asks you to guess an integer between 1-20"
       << "and checks whether it is larger or smaller than the"
       << "integer in file my_number.txt"
       << iParamVar(num,            "num ! The number you've guessed")
       << iParamVar(name,          "name ! Your name",Val("John Doe"))
       << oParamVar(my_number,"my_number ! This is the number in my_number.txt");
    ps.input(argc,argv);
    ifstream ifs("my_number.txt");

    if (!ifs) {
      cerr << "File 'my_number.txt' not found." << endl;
      cerr << "File is expected to be in the current working directory.";
      cerr << endl;
      return 0;
    }

    ifs >> Var(my_number);
    if (my_number<num) {
      cout << name << ", the number you guessed was too large." << endl;
    } else if (my_number>num) {
      cout << name << ", the number you guessed was too small." << endl;
    } else {
      cout << "Congratulations " << name << "! That was my number." << endl;
    }
    cout << ps;
  } catch (Error e) {
    cerr << "Got following error - " << endl << e.what() << endl;
  }
  return 0;
}
