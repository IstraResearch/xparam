/*	Copyright (C) 2001,2002,2003 Ronnie Maor and Michael Brand */

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
