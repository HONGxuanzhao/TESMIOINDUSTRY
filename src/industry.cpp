#include "adapter.h"
#include <set>
namespace Industry {
using namespace Adapter;
struct Factors {double input=1,output=1,efficiency=1,utilities=1;};
inline Factors global;
inline std::map<std::string,Factors> groups;
inline bool workshop=false;
Factors Load(const std::string& section){return {Setting(section,"input_multiplier",1),Setting(section,"output_multiplier",1),Setting(section,"efficiency_multiplier",1),Setting(section,"utility_multiplier",1)};}
std::string Classify(const std::string& path,const std::vector<std::string>& lines){
 std::set<std::string> outs,ins;std::string type;
 for(auto& l:lines){std::istringstream s(l);std::string cmd,res;double v;s>>cmd;if(cmd.find("$TYPE_")==0)type=cmd;if(cmd=="$PRODUCTION"&&s>>res>>v)outs.insert(res);if(cmd=="$CONSUMPTION"&&s>>res>>v)ins.insert(res);}
 if(outs.empty()||type=="$TYPE_FARM"||type=="$TYPE_FIELD"||type=="$TYPE_PRODUCTION_LINE")return {};
 if(type.find("$TYPE_MINE_")==0){if(type.find("WATER")!=std::string::npos)return "water";if(type=="$TYPE_MINE_WOOD")return "wood";return "extraction";}
 if(type=="$TYPE_POWERPLANT"||type=="$TYPE_HEATING_PLANT")return "energy";
 if(type=="$TYPE_WATER_TREATMENT"||type=="$TYPE_SEWAGE_TREATMENT")return "water";
 if(type!="$TYPE_FACTORY")return {};
 for(auto& in:ins)if(in.find("waste_")==0)return "recycling";
 if(path.find("/waste_")!=std::string::npos)return "recycling";
 for(auto& o:outs){
  if(o=="coal"||o=="iron"||o=="bauxite"||o=="gravel")return "ore_processing";
  if(o=="asphalt"||o=="concrete"||o=="cement"||o=="bricks"||o=="prefabpanels")return "construction_materials";
  if(o=="steel"||o=="aluminium"||o=="alumina")return "metallurgy";
  if(o=="fuel"||o=="bitumen"||o=="chemicals"||o=="plastics"||o=="fertiliser"||o=="fertiliser_liquid"||o=="explosives")return "chemicals";
  if(o=="uranium"||o=="yellowcake"||o=="uf6"||o=="nuclearfuel")return "nuclear";
  if(o=="mcomponents")return "mechanical";
  if(o=="ecomponents"||o=="eletronics")return "electronics";
  if(o=="boards"||o=="wood")return "wood";
  if(o=="food"||o=="meat"||o=="alcohol"||o=="livestock")return "food";
  if(o=="fabric"||o=="clothes")return "textiles";
 }return "other_factory";
}
bool Accepts(const std::string& p){
 if(p.size()<4||p.substr(p.size()-4)!=".ini")return false;
 if(p.find("media_soviet/buildings_types/")!=std::string::npos)return true;
 return workshop&&(p.find("workshop/")!=std::string::npos||p.find("workshop_wip/")!=std::string::npos||p.find("media_soviet/tesmio/")!=std::string::npos);
}
std::string Transform(const std::string& path,const std::string& bytes){
 auto lines=Lines(bytes);auto category=Classify(path,lines);if(category.empty())return bytes;
 auto f=groups.at(category);auto file=fs::path(Wide(path)).stem().string();auto over=Load("building."+file);
 double E=global.efficiency*f.efficiency*over.efficiency,I=global.input*f.input*over.input,O=global.output*f.output*over.output,U=global.utilities*f.utilities*over.utilities;
 bool changed=false;
 for(auto& l:lines){std::istringstream s(l);std::string cmd,res;double v;if(!(s>>cmd>>res>>v))continue;
  double mult=1;if(cmd=="$PRODUCTION"&&res!="vehicles")mult=E*O;else if(cmd=="$CONSUMPTION"&&res!="vehicles")mult=E*I;else if(cmd=="$CONSUMPTION_PER_SECOND")mult=E*U;
  if(mult==1)continue;if(!std::isfinite(v)||v<0||!std::isfinite(v*mult)||v*mult>1e9)throw std::runtime_error("recipe value out of range");
  std::string tail;std::getline(s,tail);l=cmd+" "+res+" "+Num(v*mult)+tail;changed=true;
 }
 return changed?Join(lines):bytes;
}
int Init(const TsmHost* h,TsmPluginInfo* info){
 if(!info||!ValidHost(h))return 1;info->name="TESMIOINDUSTRY";info->version="0.1.0";
 try{Setup(h,info->name);enabled=Toggle("industry","enabled",1);if(!enabled){H->log("TESMIOINDUSTRY disabled; no hooks installed");return 0;}workshop=Toggle("industry","include_workshop",0);global=Load("global");
  for(auto c:{"extraction","ore_processing","construction_materials","metallurgy","chemicals","nuclear","mechanical","electronics","wood","food","textiles","energy","water","recycling","other_factory"})groups[c]=Load(c);
  accepts=Accepts;transform=Transform;H->log("TESMIOINDUSTRY ready: 15 categories; global input=%g output=%g efficiency=%g utilities=%g; workshop=%d",global.input,global.output,global.efficiency,global.utilities,workshop);return 0;
 }catch(const std::exception& e){enabled=false;H->log("TESMIOINDUSTRY configuration rejected: %s",e.what());return 1;}
}
}
extern "C" __declspec(dllexport) unsigned TsmPluginApiVersion(){return TSM_API_VERSION;}
extern "C" __declspec(dllexport) int TsmPluginInit(const TsmHost* h,TsmPluginInfo* i){return Industry::Init(h,i);}
extern "C" __declspec(dllexport) int TsmPluginStart(){return Adapter::Start();}
