#ifndef TAGOBJECTS_HPP_
#define TAGOBJECTS_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>

struct Transform {
  sf::Vector2f position;
  float rotation;
  sf::Vector2f scale = sf::Vector2f(1, 1);
  friend std::istream& operator>>(std::istream& in, Transform& transform);
  friend std::ostream& operator<<(std::ostream& out,
                                  const Transform& transform);
};

class TagObjects {
 public:
  //
  // Structors
  //
  TagObjects();
  TagObjects(const std::string& file_location);
  TagObjects(const std::string& file_location, const Transform& transform);
  TagObjects(const std::string& file_location, const sf::IntRect uv);
  TagObjects(const std::string& file_location, const Transform& transform,
             const sf::IntRect uv);
  ~TagObjects(){};

  //
  // Public Functions
  //
  // * Getters
  const sf::Sprite* GetSprite() const noexcept;
  const sf::Texture* GetTexture() const noexcept;
  const Transform* GetTransform() const noexcept;
  // * Setters
  void SetTransform(const Transform& transform) noexcept;
  void SetPosition(const sf::Vector2f& new_position) noexcept;
  void SetRotation(const float& new_rotation) noexcept;
  void SetScale(const sf::Vector2f& new_scale) noexcept;
  // * Opertators

 private:
  //
  // Private Data Members
  //
  // * Data
  std::unique_ptr<sf::Sprite> sprite_;
  std::unique_ptr<sf::Texture> texture_;
  std::unique_ptr<Transform> transform_;
  // * Flags

  //
  // Private Functions
  //
};

#endif  // TAGOBJECTS_HPP_
