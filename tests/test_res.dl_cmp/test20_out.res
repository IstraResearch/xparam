r = rawprinter(false,raw<<<    
>>>)
rb = raw<<<   ttt>>>
;
r = rawprinter(true,vector<uchar>([uchar('\x00'),uchar('\x02'),uchar('\x04'),uchar('\x06'),uchar('\b'),uchar('\n')]))
b = false
rbdata = vector<uchar>([uchar('t'),uchar('t'),uchar('t')])
;
