//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace lariov+;
#pragma link C++ enum  lariov::ValueType_t+;
#pragma link C++ class lariov::IOVDataError+;
#pragma link C++ class lariov::ChData<string>+;
#pragma link C++ class std::vector< lariov::ChData<string> >+;
#pragma link C++ class lariov::Snapshot<string>+;
//ADD_NEW_CLASS ... do not change this line
#endif














