//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// For ChDataToy
#pragma link C++ class lariov::ChDataToy+;
#pragma link C++ class std::vector<lariov::ChDataToy>+;
#pragma link C++ class lariov::Snapshot<lariov::ChDataToy>+;
#pragma link C++ class std::vector<lariov::Snapshot<lariov::ChDataToy> >+;
#pragma link C++ class lariov::SnapshotCollection<lariov::ChDataToy>+;

//#pragma link C++ class lariov::GetCalibTPCResults+;
//ADD_NEW_CLASS ... do not change this line
#endif



