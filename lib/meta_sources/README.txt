Note:
The description below assumes all scripts are
run from the meta_sources directory.

****************************************
1) perl generated registration calls 
****************************************

usage: ctor_code_gen.pl max_args
where max_args is the maximum number of ctor arguments 
to be supported by XParam (originally 13).

output: xpv_ctor_imp.h, xpv_reg_ctor_imp.h

For these files to take effect, they should be moved
to directory ../xparam/.

****************************************
2) parsers 
****************************************

usage: update_parsers.pl

runs antlr to generate the parsers and lexers, and moves the
output files (sources and include files) to their directories.

****************************************
3) resetting registration calls
****************************************

usage: update_ctors.pl
runs "ctor_code_gen.pl" to return the maximum number of
constructor arguments supported back to 13, then
copies the files to their required location (../xparam/).
This files is handy in XParam maintainance.

****************************************
4) resetting all
****************************************

usage: update_all.pl
runs "update_ctors.pl" followed by "update_parsers.pl".
This causes the maximal number of constructor arguments
to be 13, and updates the parser used by XParam to be the
parser described by the ANTLR ".g" files.
This file, too, is very handy in maintaining XParam.

