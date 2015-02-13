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
#pragma link C++ class lariov::IOVDBError+;
#pragma link C++ class lariov::ColumnDef+;
#pragma link C++ class lariov::TableDef+;

//#pragma link C++ class lariov::GetCalibTPCResults+;
//ADD_NEW_CLASS ... do not change this line
#endif



