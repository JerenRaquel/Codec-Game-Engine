#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "TagObjects.hpp"

struct Tags {
  std::string name;
  bool flag_render = true;
  friend std::istream& operator>>(std::istream& in, Tags& tag);
};

struct TagComp {
  bool operator()(const Tags& a, const Tags& b) const {
    return a.name < b.name;
  }
};

class GameObject {
 public:
  //
  // Structors
  //
  GameObject();
  GameObject(const std::string& file_location);
  GameObject(const std::string& file_location, const Transform& transform);
  GameObject(const std::string& file_location, const sf::IntRect uv);
  GameObject(const std::string& file_location, const Transform& transform,
             const sf::IntRect uv);
  ~GameObject(){};

  //
  // Public Functions
  //
  // * Getters
  const TagObjects* GetObject() const noexcept;
  const bool CheckIfDead() const noexcept;

 private:
  //
  // Private Data Members
  //
  // * Data
  std::unique_ptr<TagObjects> tag_object_;
  // * Flags
  bool flag_deleted_ = false;
};

#endif  // GAMEOBJECT_HPP_
