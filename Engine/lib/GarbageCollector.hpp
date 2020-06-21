#ifndef GARBAGECOLLECTOR_HPP_
#define GARBAGECOLLECTOR_HPP_

#include "TagObjects.hpp"

class GarbageCollector {
 public:
  //
  // Data Members
  //
  bool flag_require_cleaning = false;

  //
  // Structors
  //
  GarbageCollector(){};
  ~GarbageCollector(){};

  //
  // Public Functions
  //
  void Clean(){};
  void AddGarbage(TagObjects* object){};

 private:
  /*Member vars*/;
};

#endif  // GARBAGECOLLECTOR_HPP_
