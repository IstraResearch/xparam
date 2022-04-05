Trying duplicate parameters...
Error: Duplicate definition of parameter 'g'.
Trying default multiple assignment mode (last holds)...
Should be: 7
Result:    7
Trying first holds mode...
Should be: 7
Result:    7
Trying 'is error' mode...
Error: while parsing assignment to parameter 'd':
Multiple assignment to parameter d.
Trying last holds mode explicitly...
Should be: 9
Result:    9
Trying switching to first_holds by method...
Should be: 9
Result:    9
Trying switching to is_error by method...
Error: while parsing assignment to parameter 'd':
Multiple assignment to parameter d.
Trying switching to last_holds by method...
Should be: 12
Result:    12
Testing prefix (default) mode...
tom->tomato: tomato
tomato->tomato: tomato
tobacco->tobacco: tobacco
Trying two ambiguities...
Error: Reference to parameter t is ambiguous. Candidates are: tomato, toba.
Error: Reference to parameter tomato_ is ambiguous. Candidates are: tomato_juice, tomato_drink.
Trying no match...
Error: No match for parameter 'time'.
Testing exact mode...
Error: No match for parameter 'tom'.
tomato->tomato: tomato
tobacco->tobacco: tobacco
Trying two ambiguities...
Error: No match for parameter 't'.
Error: No match for parameter 'tomato_'.
Trying no match...
Error: No match for parameter 'time'.
Testing prefix (explicit) mode...
tom->tomato: tomato
tomato->tomato: tomato
tobacco->tobacco: tobacco
Trying two ambiguities...
Error: Reference to parameter t is ambiguous. Candidates are: tomato, toba.
Error: Reference to parameter tomato_ is ambiguous. Candidates are: tomato_juice, tomato_drink.
Trying no match...
Error: No match for parameter 'time'.
Testing exact mode with method...
Error: No match for parameter 'tom'.
tomato->tomato: tomato
tobacco->tobacco: tobacco
Trying two ambiguities...
Error: No match for parameter 't'.
Error: No match for parameter 'tomato_'.
Trying no match...
Error: No match for parameter 'time'.
Testing prefix mode with method...
tom->tomato: tomato
tomato->tomato: tomato
tobacco->tobacco: tobacco
Trying two ambiguities...
Error: Reference to parameter t is ambiguous. Candidates are: tomato, toba.
Error: Reference to parameter tomato_ is ambiguous. Candidates are: tomato_juice, tomato_drink.
Trying no match...
Error: No match for parameter 'time'.
Testing with input...
Should be 21:
Result:   21
Testing param information...
name: tomato_juice
description: boring juice
has given value: 1
has default: 0
was assigned to: 1
is input: 1
is output: 0

name: tomato
description: 
has given value: 1
has default: 1
was assigned to: 0
is input: 1
is output: 1

name: g
description: 
has given value: 0
has default: 0
was assigned to: 0
is input: 1
is output: 0

Testing constants...
should be: 314, 628
Result:    314, 628
Testing import, with persistent foreign paramset...
PS Names: d g tomato tomato_juice tobacco toba tomato_drink member
m was assigned to: 1
Testing that we are still EXACT...
Error: No match for parameter 'm'.
PS2 Names: member
member was assigned to: 1
Should be: 17
Result:    17
Testing import, with intermittent foreign paramset...
PS Names: d g tomato tomato_juice tobacco toba tomato_drink member next
n was assigned to: 1
Should be: 19
Result:    19
Testing for constants of user defined type.
Val-g: goose(15)
Testing constants read from stream.
Stream vals: gooseberry(NO OUTPUT FUNCTION) goose(15)
