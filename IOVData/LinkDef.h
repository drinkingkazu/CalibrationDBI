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

#pragma link C++ class lariov::ChData<string >+;
#pragma link C++ class lariov::ChData<float  >+;
#pragma link C++ class lariov::ChData<double >+;
#pragma link C++ class lariov::ChData<short  >+;
#pragma link C++ class lariov::ChData<int    >+;
#pragma link C++ class lariov::ChData<long   >+;
#pragma link C++ class lariov::ChData<unsigned short  >+;
#pragma link C++ class lariov::ChData<unsigned int    >+;
#pragma link C++ class lariov::ChData<unsigned long   >+;
#pragma link C++ class std::vector< lariov::ChData<string > >+;
#pragma link C++ class std::vector< lariov::ChData<float  > >+;
#pragma link C++ class std::vector< lariov::ChData<double > >+;
#pragma link C++ class std::vector< lariov::ChData<short  > >+;
#pragma link C++ class std::vector< lariov::ChData<int    > >+;
#pragma link C++ class std::vector< lariov::ChData<long   > >+;
#pragma link C++ class std::vector< lariov::ChData<unsigned short  > >+;
#pragma link C++ class std::vector< lariov::ChData<unsigned int    > >+;
#pragma link C++ class std::vector< lariov::ChData<unsigned long   > >+;

#pragma link C++ class lariov::Snapshot<string >+;
#pragma link C++ class lariov::Snapshot<float  >+;
#pragma link C++ class lariov::Snapshot<double >+;
#pragma link C++ class lariov::Snapshot<short  >+;
#pragma link C++ class lariov::Snapshot<int    >+;
#pragma link C++ class lariov::Snapshot<long   >+;
#pragma link C++ class lariov::Snapshot<unsigned short  >+;
#pragma link C++ class lariov::Snapshot<unsigned int    >+;
#pragma link C++ class lariov::Snapshot<unsigned long   >+;
#pragma link C++ class std::vector< lariov::Snapshot<string > >+;
#pragma link C++ class std::vector< lariov::Snapshot<float  > >+;
#pragma link C++ class std::vector< lariov::Snapshot<double > >+;
#pragma link C++ class std::vector< lariov::Snapshot<short  > >+;
#pragma link C++ class std::vector< lariov::Snapshot<int    > >+;
#pragma link C++ class std::vector< lariov::Snapshot<long   > >+;
#pragma link C++ class std::vector< lariov::Snapshot<unsigned short  > >+;
#pragma link C++ class std::vector< lariov::Snapshot<unsigned int    > >+;
#pragma link C++ class std::vector< lariov::Snapshot<unsigned long   > >+;

#pragma link C++ class lariov::SnapshotCollection<string >+;
#pragma link C++ class lariov::SnapshotCollection<float  >+;
#pragma link C++ class lariov::SnapshotCollection<double >+;
#pragma link C++ class lariov::SnapshotCollection<short  >+;
#pragma link C++ class lariov::SnapshotCollection<int    >+;
#pragma link C++ class lariov::SnapshotCollection<long   >+;
#pragma link C++ class lariov::SnapshotCollection<unsigned short  >+;
#pragma link C++ class lariov::SnapshotCollection<unsigned int    >+;
#pragma link C++ class lariov::SnapshotCollection<unsigned long   >+;

//#pragma link C++ class lariov::Snapshot<string>+;
//#pragma link C++ class std::vector<lariov::Snapshot<string> >+;
//#pragma link C++ class lariov::SnapshotCollection<string>+;
//ADD_NEW_CLASS ... do not change this line
#endif
