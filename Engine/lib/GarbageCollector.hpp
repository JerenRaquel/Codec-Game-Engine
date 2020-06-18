#ifndef GARBAGECOLLECTOR_HPP_
#define GARBAGECOLLECTOR_HPP_

class GarbageCollector {
 public:
  //
  // Data Members
  //
  bool flag_require_cleaning = false;

  //
  // Structors
  //
  GarbageCollector();
  ~GarbageCollector();

  //
  // Public Functions
  //
  void Clean();
  void AddGarbage(GameObject* object);

 private:
  /*Member vars*/;
};

#endif  // GARBAGECOLLECTOR_HPP_
