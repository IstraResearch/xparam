Got following error - 
NoViableAlt
vs = vector<string>(["a"])
t = false
;
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
Got following error - 
NoViableAlt
vs = vector<string>(["a","b"])
t = false
;
vs = vector<string>(["a b"])
t = false
;
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
vs = vector<string>(["a :"])
t = false
;
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
vs = vector<string>([":"])
t = false
;
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
Got following error - 
while parsing assignment to parameter 'vs':
illegal token - 
vs = vector<string>(["a"])
t = false
;
vs = vector<string>(["a","b"])
t = false
;
vs = vector<string>(["a:","b:"])
t = false
;
vs = vector<string>(["a b"])
t = false
;
vs = vector<string>(["c:\\home_dir\\My file\\file-name.txt"])
t = false
;
vs = vector<string>(["/my dir/my file - unix_version.txt"])
t = false
;
vs = vector<string>(["a","b"])
t = true
;
Got following error - 
while parsing assignment to parameter 'vs':
while parsing element 1 of value list:
illegal token - 
