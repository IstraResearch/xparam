avalon = 5
avalanche = vector<string>(["a","b"])
output_only = 17
;
avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c", ...
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
Got following error - 
while parsing assignment to parameter 'aval':
Reference to parameter aval is ambiguous. Candidates are: avalon, avalanche.
WARNING: Assignment to parameter aval was ignored. Reference to parameter aval is ambiguous. Candidates are: avalon, avalanche.
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche [default] = vector<string>(["one","two"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["one","two"])
output_only = 17
;
WARNING: Assignment to parameter aval was ignored. Reference to parameter aval is ambiguous. Candidates are: avalon, avalanche.
--------------------------------------------------
Values of input parameters:
avalon [unassigned]
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

Got following error - 
No value given for required parameter avalon.
Got following error - 
while parsing assignment to parameter 'b':
No match for parameter 'b'.
WARNING: Assignment to parameter b was ignored. No match for parameter 'b'.
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche = vector<string>(["c","d"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["c","d"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche [default] = vector<string>(["one","two"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["one","two"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon = 5
avalanche [default] = vector<string>(["one","two"])
input_only [default] = 5
--------------------------------------------------

avalon = 5
avalanche = vector<string>(["one","two"])
output_only = 17
;
--------------------------------------------------
Values of input parameters:
avalon [unassigned]
avalanche = vector<string>(["e","f","g"])
input_only [default] = 5
--------------------------------------------------

Got following error - 
No value given for required parameter avalon.
--------------------------------------------------
Values of input parameters:
avalon [unassigned]
avalanche = vector<string>(["h"])
input_only [default] = 5
--------------------------------------------------

Got following error - 
No value given for required parameter avalon.
