/**
 * \file SnapshotCollection.h
 *
 * \ingroup IOVDB
 * 
 * \brief Class def header for a class SnapshotCollection
 *
 * @author kterao
 */

/** \addtogroup IOVDB

    @{*/
#ifndef IOVDB_SNAPSHOTCOLLECTION_H
#define IOVDB_SNAPSHOTCOLLECTION_H

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

    const std::vector<lariov::Snapshot<T> >& SnapshotArray() const
    { return _snapshot_v; }

    const std::string& Folder() const { return _folder; }

    void Merge(const SnapshotCollection& ss_v)
    { for(auto const& ss : ss_v.SnapshotArray()) Append(ss); }

    void Append(const lariov::Snapshot<T>& snapshot)
    {
      if(_folder != snapshot.Folder())
	throw IOVDBError("You cannot store different folders to one collection!");
      auto iter = _snapshot_v.rbegin();
      size_t ctr=0;
      while(iter != _snapshot_v.rend() && snapshot.Start() <= (*iter).End()) {
	if(!ctr && !((*iter).Compat(snapshot)))
	  throw IOVDBError("Incompatible Snapshot cannot be added!");
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

#endif
/** @} */ // end of doxygen group 

