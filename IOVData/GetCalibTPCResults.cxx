#ifndef GETCALIBTPCRESULTS_CXX
#define GETCALIBTPCRESULTS_CXX

#include "GetCalibTPCResults.h"

namespace lariov {

  GetCalibTPCResults::GetCalibTPCResults(const std::string infile)
    : _f(nullptr)
    , _snapshotColl(nullptr)
  {

    // Open TFile with info
    if (_f) delete _f;
    _f = new TFile(infile.c_str());
    std::cout << "File was opened" << std::endl;
    
    // Create SnapshotCollection
    if (_snapshotColl) delete _snapshotColl;
    _snapshotColl = new SnapshotCollection<std::string>("CalibrationsTPC");
    std::cout << "SnapshotCollection was created with folder name: "
	      << _snapshotColl->Folder() << std::endl;

  }

  void GetCalibTPCResults::PrepareTrees(){

    // Get the trees
    GetTrees();
    // Set Branch addresses for TTrees & variables
    SetBranchAddresses();

  }

  void GetCalibTPCResults::GetTimeStamp(){

    // Now loop over Data TTree entries
    int nentries = _tData->GetEntries();
    // First (and only) entry will sync _time variable
    _tData->GetEntry(0);
    

  }

  void GetCalibTPCResults::WriteSnapshotColl(TFile *fout, TTree *tree){

    if (!fout)
      fout = new TFile("out.root","RECREATE"); 
    if (!tree)
      tree = new TTree("data_tree","");
    

    _snapshotColl->Write(*tree);
    tree->Write();
    fout->Close();

    return;
  }

  void GetCalibTPCResults::FillSnapshot(float ASICgain, float shT){

    std::vector<std::string> snapshot_fieldnames = {"pedestal","RMS","Area Gain","Amp Gain"};
    std::vector<std::string> snapshot_fieldtypes = {"float","float","float","float"};
    std::cout << "Creating Snapshot...";
    Snapshot<std::string> thissnap("CalibrationsTPC",snapshot_fieldnames,snapshot_fieldtypes);
    // Set time for snapshot
    thissnap.Reset(_time);
    std::cout << "\t...Done creating Snapshot!" << std::endl;
    // Set Snapshot Time

    // Create a map of <ChData, chnum>
    std::map<int, ChData<std::string> > ChDataMap;


    // Now loop over Data TTree entries
    int nentries = _tData->GetEntries();
    for (int n=0; n < nentries; n++){
      // Make sure ASIC gain & Shaping time are what we want
      _tData->GetEntry(n);
      if ( (_asicgainD != ASICgain) || (_shapingtD != shT) || (_vin != 0) ) continue;
      ChData<std::string> thisData;
      thisData.reserve(4);
      thisData.Channel(_chnumD);
      thisData.push_back(std::to_string(_pedestal));
      thisData.push_back(std::to_string(_rmsnoise));
      ChDataMap[_chnumD] = thisData;
      //sPedestal.push_back(thisData);
    }// Loop over all entries

    // Now loop over Gain TTree entries
    nentries = _tGain->GetEntries();
    for (int n=0; n < nentries; n++){
      // Mkae sure ASIC gain and shaping time are what we want
      _tGain->GetEntry(n);
      if ( (_asicgainG != ASICgain) || (_shapingtG != shT) ) continue;
      // Assume ChData for this channel was created
      // if we cannot find it skip for now
      if ( ChDataMap.find(_chnumG) == ChDataMap.end() ) continue;
      ChDataMap[_chnumG].push_back(std::to_string(_amplgain));
      ChDataMap[_chnumG].push_back(std::to_string(_areagain));
      std::cout << "Channel: " << _chnumG << std::endl
		<< "pedestal: " << ChDataMap[_chnumG][0]
		<< "\tnoise: " << ChDataMap[_chnumG][1]
		<< "\tamp G: " << ChDataMap[_chnumG][2]
		<< "\tarea G: " << ChDataMap[_chnumG][3] << std::endl << std::endl;
      // Finally push back to snapshot collection
      thissnap.push_back(ChDataMap[_chnumG]);
    }
    
    // Now append the Snapshot to the SnapshotCollection
    _snapshotColl->Append(thissnap);
  }


  void GetCalibTPCResults::GetTrees(){

    std::cout << "Getting trees...";
    TDirectoryFile *fDir = (TDirectoryFile*)_f->Get("CalibrationTPC");
    _tData = (TTree*)fDir->Get("fDataTree");
    _tGain = (TTree*)fDir->Get("fGainTree");
    _tRun = (TTree*)fDir->Get("fRunTree");
    if (!_tData){
      std::cout << "Data Tree not found...Exiting." << std::endl;
      return;
    }
    if (!_tGain){
      std::cout << "Gain Tree not found...Exiting." << std::endl;
      return;
    }
    if (!_tRun){
      std::cout << "Run Tree not found...Exiting." << std::endl;
      return;
    }
    std::cout << "\t...Done getting trees!" << std::endl;    

    return;
  }


  void GetCalibTPCResults::SetBranchAddresses(){

    // set branch address for variables in TTree we want to extract
    std::cout << "Setting Branch addresses for Data Tree...";
    _tData->SetBranchAddress("_subrun",&_subrunD);
    _tData->SetBranchAddress("_chNum",&_chnumD);
    _tData->SetBranchAddress("_pedestal",&_pedestal);
    _tData->SetBranchAddress("_RMSnoise",&_rmsnoise);
    _tData->SetBranchAddress("_ASICgain",&_asicgainD);
    _tData->SetBranchAddress("_shapingTime",&_shapingtD);
    _tData->SetBranchAddress("_Vin",&_vin);
    std::cout << "\t...Done setting branch addresses!" << std::endl;

    std::cout << "Setting Branch addresses for Gain Tree...";
    _tGain->SetBranchAddress("_chNum",&_chnumG);
    _tGain->SetBranchAddress("_ampGain",&_amplgain);
    _tGain->SetBranchAddress("_areaGain",&_areagain);
    _tGain->SetBranchAddress("_asicGain",&_asicgainG);
    _tGain->SetBranchAddress("_shapingT",&_shapingtG);
    std::cout << "\t...Done setting branch addresses!" << std::endl;

    std::cout << "Setting Branch addresses for Run Tree...";
    _tGain->SetBranchAddress("_timeMin",&_time);
    std::cout << "\t...Done setting branch addresses!" << std::endl;

  }    

}

#endif
