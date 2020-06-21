#ifndef TAGGEDVECTOR_HPP_
#define TAGGEDVECTOR_HPP_

#include <string>
#include <vector>

#include "TagObjects.hpp"

class TaggedVector {
 public:
  //
  // Structors
  //
  TaggedVector() noexcept;
  ~TaggedVector() noexcept;

  //
  // Public Functions
  //
  // * Getters
  std::vector<TagObjects*>* GetObjects() const noexcept;
  const bool CheckForRender() const noexcept;
  // * Setters
  void AddObject(TagObjects* new_object) noexcept;
  void SetRenderFlag(bool state) noexcept;

 private:
  bool flag_render;
  std::vector<TagObjects*>* game_objects_;
};

#endif  // TAGGEDVECTOR_HPP_
