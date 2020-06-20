#include "../lib/GameObject.hpp"

//
// Structors
//
GameObject::GameObject() {
  this->tag_object_ = std::unique_ptr<TagObjects>(new TagObjects());
}

GameObject::GameObject(const std::string& file_location) {
  this->tag_object_ =
      std::unique_ptr<TagObjects>(new TagObjects(file_location));
}

GameObject::GameObject(const std::string& file_location,
                       const Transform& transform) {
  this->tag_object_ =
      std::unique_ptr<TagObjects>(new TagObjects(file_location, transform));
}

GameObject::GameObject(const std::string& file_location, const sf::IntRect uv) {
  this->tag_object_ =
      std::unique_ptr<TagObjects>(new TagObjects(file_location, uv));
}

GameObject::GameObject(const std::string& file_location,
                       const Transform& transform, const sf::IntRect uv) {
  this->tag_object_ =
      std::unique_ptr<TagObjects>(new TagObjects(file_location, transform, uv));
}

//
// Public Functions
//
// * Getters
const TagObjects* GameObject::GetObject() const noexcept {
  if (this->flag_deleted_) {
    return nullptr;
  }
  return this->tag_object_.get();
}

const bool GameObject::CheckIfDead() const noexcept {
  return this->flag_deleted_;
}