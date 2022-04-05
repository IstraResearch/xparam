
Usage: progname <param1>=<val1> <param2>=<val2> -<flag1> -no_<flag2>...
Use any unambiguous prefix of the parameter names
In case of multiple assignment to the same parameter, the last holds.

Name         Type                     I/O Default Value Description 
====         ====                     === ============= =========== 
p            pair<goose,double>        I  [ required ]              
v            vector<goose>             I  [ required ]              
vp           vector<goose*>            I  [ required ]              
vcp          vector<const goose*>      I  [ required ]              
l            list<goose>               I  [ required ]              
lp           list<goose*>              I  [ required ]              
lcp          list<const goose*>        I  [ required ]              
str_map      map<goose,string>         I  [ required ]              
bot_map      map<goose,bottle>         I  [ required ]              
bot_ptr_map  map<goose,bottle*>        I  [ required ]              
bot_cptr_map map<goose,const bottle*>  I  [ required ]              
