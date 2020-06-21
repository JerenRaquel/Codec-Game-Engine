#include "../lib/TaggedVector.hpp"

//
// Structors
//
TaggedVector::TaggedVector() noexcept {
  this->flag_render = true;
  this->game_objects_ = new std::vector<TagObjects*>;
}

TaggedVector::~TaggedVector() noexcept {
  for (unsigned int i = 0; i < this->game_objects_->size(); i++) {
    delete (*this->game_objects_)[i];
  }
  delete this->game_objects_;
}

//
// Public Functions
//
// * Getters
std::vector<TagObjects*>* TaggedVector::GetObjects() const noexcept {
  return this->game_objects_;
}

const bool TaggedVector::CheckForRender() const noexcept {
  return this->flag_render;
}

// * Setters
void TaggedVector::AddObject(TagObjects* new_object) noexcept {
  this->game_objects_->push_back(new_object);
}

void TaggedVector::SetRenderFlag(bool state) noexcept {
  this->flag_render = state;
}
