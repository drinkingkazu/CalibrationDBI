#ifndef IOVDATA_GETCALIBTPCRESULTS_H
#define IOVDATA_GETCALIBTPCRESULTS_H

#include "SnapshotCollection.h"
#include "TDirectoryFile.h"
#include <stdint.h>

namespace lariov {

  class GetCalibTPCResults{

  public:

    // Default constructor
    GetCalibTPCResults(const std::string infile="noname");

    // Default destructor
    virtual ~GetCalibTPCResults(){}
    
    // Now Write snapshot collection to file
    void WriteSnapshotColl(TFile *f=nullptr, TTree *t=nullptr);

    // Get the trees we want
    void GetTrees();
    // Synch Tree branches & variables
    void SetBranchAddresses();
    // Fill Snapshots
    void FillSnapshot(float ASICgain, float shT);
    // Prepare Trees
    void PrepareTrees();
    // Get Time stamp
    void GetTimeStamp();

  private:

    TFile *_f;
    SnapshotCollection<std::string> *_snapshotColl;

    // Variables to sync with Branches
    float _pedestal;
    float _rmsnoise;
    float _asicgainD;
    float _shapingtD;
    float _asicgainG;
    float _shapingtG;
    float _areagain;
    float _amplgain;
    float _vin;
    int   _chnumD;
    int   _subrunD;
    int   _chnumG;
    int   _subrunG;
    uint64_t _time;

    // TTrees to be used from file
    TTree *_tData;
    TTree *_tGain;
    TTree *_tRun;
      
    
  };
  
}

#endif
