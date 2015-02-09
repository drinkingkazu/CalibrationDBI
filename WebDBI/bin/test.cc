
#include "WebReader.h"
//#include "IOVData/Snapshot.h"
#include <string>

int main()
{
  //lariov::Snapshot<std::string> shot("aho");

  lariov::WebReader<std::string> k("dbdata0.fnal.gov",
				   "8086",
				   "uboonecon_dev");

  TTimeStamp ts;
  ts.SetSec(12347578);
  auto& data = k.Request("pedestals",ts);
  std::cout<<data.NChannels()<<" : "<<data.NFields()<<std::endl;
  for(size_t i=0; i<data.NChannels(); ++i) {
    std::cout<<"Channel: "<<data.Data(i).Channel()<< " ... "<<std::endl;
    for(auto const& str : data.Data(i)) std::cout<<str.c_str()<<std::endl;
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
  std::cout<<"done"<<std::endl;
  std::cout<<std::flush;

  return 0;
}
