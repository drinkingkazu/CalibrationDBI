/**
 * \file WebData.h
 *
 * \ingroup WebDBI
 * 
 * \brief Class def header for a class WebData
 *
 * @author kterao
 */

/** \addtogroup WebDBI

    @{*/
#ifndef WEBDB_WEBDATA_H
#define WEBDB_WEBDATA_H

#include <iostream>
#include <vector>
#include <TTimeStamp.h>

namespace webdb {
  enum ValueType_t {
    kSTRING,
    kBOOL,
    kINT,
    kUINT,
    kSHORT,
    kUSHORT,
    kLONG,
    kULONG,
    kFLOAT,
    kDOUBLE,
    kTIMESTAMP,
    kUNKNOWN
  };

  typedef std::vector<std::string> Row_t;
  typedef std::vector<Row_t> Table_t;

  class WebReader;
  /**
     \class WebData
     User defined class WebData ... these comments are used to generate
     doxygen documentation!
  */
  class WebData{
    friend class WebReader;
  public:
    
    /// Default constructor
    WebData(std::string name="noname" );

    /// Default destructor
    ~WebData(){}

    const std::string& Name() const;
    const TTimeStamp&  Start() const;
    const TTimeStamp&  End()   const;

    bool   Valid(const TTimeStamp& ts) const;
    size_t NRows()    const;
    size_t NColumns() const;

    const std::string& FieldName(const size_t column) const;
    ValueType_t        FieldType(const size_t column) const;
    const std::vector<webdb::ValueType_t>& FieldType() const;
    const std::vector<std::string>& FieldName() const;
    const Row_t& Row(const size_t n) const;
    const std::string& Field(const size_t row, 
			     const size_t column) const;
  private:

    void Reset (const TTimeStamp& iov_start,
		const TTimeStamp& iov_end,
		const std::vector<std::string>& field_name,
		const std::vector<std::string>& field_type);

    void Reserve (size_t n);
    void Append  (const Row_t& row);

  private:

    std::string _name;
    TTimeStamp  _iov_start;
    TTimeStamp  _iov_end;
    Table_t     _table;
    std::vector<std::string> _field_name;
    std::vector<webdb::ValueType_t> _field_type;

  };
}

#endif
/** @} */ // end of doxygen group 

