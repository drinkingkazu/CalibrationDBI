/**
 * \file SnapshotCollection.h
 *
 * \ingroup IOVData
 * 
 * \brief Class def header for a class SnapshotCollection
 *
 * @author kterao
 */

/** \addtogroup IOVData

    @{*/
#ifndef IOVDATA_SNAPSHOTCOLLECTION_H
#define IOVDATA_SNAPSHOTCOLLECTION_H

#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include "Snapshot.h"

namespace lariov {
  /**
     \class SnapshotCollection
     User defined class SnapshotCollection ... these comments are used to generate
     doxygen documentation!
  */
  template <class T>
  class SnapshotCollection {
    
  public:
    
    /// Default constructor
    SnapshotCollection(const std::string folder="noname");
    
    /// Default destructor
    virtual ~SnapshotCollection(){}

    void Append(const lariov::Snapshot<T>& snapshot)
    {
      if(_folder != snapshot.Folder())
	throw IOVDataError("You cannot store different folders to one collection!");
      auto iter = _snapshot_v.rbegin();
      size_t ctr=0;
      while(iter != _snapshot_v.rend() && snapshot.Start() <= (*iter).End()) {
	if(!ctr && !((*iter).Compat(snapshot.FieldName(),snapshot.FieldType())))
	  throw IOVDataError("Incompatible Snapshot cannot be added!");
	++iter;
	++ctr;
      }	
      if(ctr)
	std::cout << "Overriding " << ctr 
		  << " elements (start time is earlier than those previous ones)!"
		  << std::endl;
      _snapshot_v.push_back(snapshot);
    }

    void Write(TTree& t) const;

    void Read(TFile& f);

  private:

    std::vector<lariov::Snapshot<T> > _snapshot_v;
    std::string _folder;
  };

}

//template class std::vector<lariov::Snapshot<std::string> >;
template class lariov::SnapshotCollection<std::string>;

#endif
/** @} */ // end of doxygen group 

