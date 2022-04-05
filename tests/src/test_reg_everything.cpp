#pragma warning (disable: 4786)

#include <xparam_extend.h>
#include <string>
#include "../include/test_reg_everything.h"

using namespace xParam;
using namespace std;

PARAM_BEGIN_REG

PARAM_CLASS(everything);
param_ctor(TypeTag<everything>(),ByVal<bool>("b"));
param_ctor(TypeTag<everything>(),ByVal<char>("c"));
param_ctor(TypeTag<everything>(),ByVal<unsigned char>("uc"));
param_ctor(TypeTag<everything>(),ByVal<short>("s"));
param_ctor(TypeTag<everything>(),ByVal<unsigned short>("us"));
param_ctor(TypeTag<everything>(),ByVal<int>("i"));
param_ctor(TypeTag<everything>(),ByVal<unsigned int>("ui"));
param_ctor(TypeTag<everything>(),ByVal<long>("l"));
param_ctor(TypeTag<everything>(),ByVal<unsigned long>("ul"));
param_ctor(TypeTag<everything>(),ByVal<float>("f"));
param_ctor(TypeTag<everything>(),ByVal<double>("d"));
param_ctor(TypeTag<everything>(),ConstRef<string>("s"));

param_ctor(TypeTag<everything>(),ConstRef<vector<bool> >("vb"));
param_ctor(TypeTag<everything>(),ConstRef<vector<char> >("vc"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned char> >("vuc"));
param_ctor(TypeTag<everything>(),ConstRef<vector<short> >("vs"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned short> >("vus"));
param_ctor(TypeTag<everything>(),ConstRef<vector<int> >("vi"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned int> >("vui"));
param_ctor(TypeTag<everything>(),ConstRef<vector<long> >("vl"));
param_ctor(TypeTag<everything>(),ConstRef<vector<unsigned long> >("vul"));
param_ctor(TypeTag<everything>(),ConstRef<vector<float> >("vf"));
param_ctor(TypeTag<everything>(),ConstRef<vector<double> >("vd"));
param_ctor(TypeTag<everything>(),ConstRef<vector<string> >("vs"));

param_output<everything,everything_output>();
param_vector<everything>();

PARAM_END_REG

