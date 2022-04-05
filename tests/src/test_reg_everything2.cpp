#pragma warning (disable: 4786)

#include <string>
#include <xparam_extend.h>
#include "../include/test_reg_everything2.h"

using namespace xParam;
using namespace std;

PARAM_BEGIN_REG

PARAM_CLASS(everything2);
param_ctor(TypeTag<everything2>(),ByVal<bool>("b"));
param_ctor(TypeTag<everything2>(),ByVal<char>("c"));
param_ctor(TypeTag<everything2>(),ByVal<unsigned char>("uc"));
param_ctor(TypeTag<everything2>(),ByVal<short>("s"));
param_ctor(TypeTag<everything2>(),ByVal<unsigned short>("us"));
param_ctor(TypeTag<everything2>(),ByVal<int>("i"));
param_ctor(TypeTag<everything2>(),ByVal<unsigned int>("ui"));
param_ctor(TypeTag<everything2>(),ByVal<long>("l"));
param_ctor(TypeTag<everything2>(),ByVal<unsigned long>("ul"));
param_ctor(TypeTag<everything2>(),ByVal<float>("f"));
param_ctor(TypeTag<everything2>(),ByVal<double>("d"));
param_ctor(TypeTag<everything2>(),ByVal<long double>("ld"));
param_ctor(TypeTag<everything2>(),ConstRef<string>("s"));

param_ctor(TypeTag<everything2>(),ConstRef<vector<bool> >("vb"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<char> >("vc"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<unsigned char> >("vuc"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<short> >("vs"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<unsigned short> >("vus"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<int> >("vi"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<unsigned int> >("vui"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<long> >("vl"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<unsigned long> >("vul"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<float> >("vf"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<double> >("vd"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<long double> >("vld"));
param_ctor(TypeTag<everything2>(),ConstRef<vector<string> >("vs"));

param_output<everything2,everything2_output>();
param_vector<everything2>();

PARAM_END_REG

