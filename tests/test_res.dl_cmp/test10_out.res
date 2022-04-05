Testing constructors...
v = vector<everything>([everything("From bool"),everything("From char"),everything("From unsigned char"),everything("From short"),everything("From unsigned short"),everything("From int"),everything("From unsigned int"),everything("From unsigned int"),everything("From long"),everything("From long"),everything("From unsigned long"),everything("From unsigned long"),everything("From unsigned long"),everything("From unsigned long"),everything("From double"),everything("From float"),everything("From string"),everything("From long long"),everything("From unsigned long long"),everything("From vector of bool"),everything("From vector of char"),everything("From vector of unsigned char"),everything("From vector of short"),everything("From vector of unsigned short"),everything("From vector of int"),everything("From vector of unsigned int"),everything("From vector of unsigned int"),everything("From vector of long"),everything("From vector of long"),everything("From vector of unsigned long"),everything("From vector of unsigned long"),everything("From vector of unsigned long"),everything("From vector of unsigned long"),everything("From vector of long long"),everything("From vector of unsigned long long"),everything("From vector of double"),everything("From vector of float"),everything("From vector of string")])
;
Testing conversions...
vb = vector<bool>([true,true])
vc = vector<char>(['\x01','\x01'])
vuc = vector<uchar>([uchar('\x01'),uchar('\x01')])
vs = vector<short>([short(1),short(1)])
vus = vector<ushort>([ushort(1U),ushort(1U)])
vi = vector<int>([1,1])
vui = vector<uint>([1U,1U])
vl = vector<long>([1L,1L])
vul = vector<ulong>([1UL,1UL])
vll = vector<longlong>([longlong(49L),longlong(49L),longlong(1L),longlong(1L),longlong(1L),longlong(1L),longlong(1L),longlong(1L),longlong(1L),longlong(1L),longlong(1L)])
vull = vector<ulonglong>([ulonglong(49UL),ulonglong(49UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL),ulonglong(1UL)])
vf = vector<float>([1.0F,1.0F])
vd = vector<double>([1.0,1.0])
;
