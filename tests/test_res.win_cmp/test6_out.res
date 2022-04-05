Got following error - 
Duplicate definition of parameter 'd'.
Got following error - 
Duplicate definition of parameter 'a'.
Got following error - 
Duplicate definition of parameter 'a'.
a = "Redefinition of a"
;
duck3 = duckling("I am a duckling born of a duckling born of a duckling born of the string \"two integers\".",coordinate(3,5))
duck4 = duckling("I am a duckling born of a duckling born of the string \"two doubles\".",coordinate(3,5))
duck5 = duckling("I am a duckling born of a duckling born of the void.",coordinate(3,5))
duckp3 = duckling("I am a duckling born of a duckling born of a duckling born of the string \"overriding default\".",coordinate(3,5))
duckp4 = duckling(NULL)
duckp5 = duckling(NULL)
;
duck1: I am a duckling born of the void.
duck2: I am a duckling born of the void.
duckp1: duckling(NULL)
duckp2: I am a duckling born of a duckling born of a duckling born of the string "default val".
Got following error - 
while parsing assignment to parameter 'd':
no conversion path found from int ( 7 )  to ducky
I am a ducky born of an integer.
I am a ducky born of the string "hello".
I am a ducky born of the string "hello".
I am a ducky born of the string "the void by a creator".
Got following error - 
while parsing assignment to parameter 'd':
no conversion path found from double ( 3.5 )  to ducky
I am a ducky born of the string "a double by a creator".
