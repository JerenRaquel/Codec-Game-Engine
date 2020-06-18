#ifndef TAGOBJECTS_HPP_
#define TAGOBJECTS_HPP_

#include <memory>

class TagObjects {
 public:
  //
  // Structors
  //
  TagObjects();
  TagObjects(sf::Sprite new_sprite, sf::IntRect uv);
  ~TagObjects();

  //
  // Public Functions
  //
  sf::Sprite* GetSprite();
  sf::Texture* GetTexture();
  void Remove();
  void RemoveNow();

 private:
  std::unique_ptr<sf::Sprite> sprite_;
  std::unique_ptr<sf::Texture> texture_;
};

#endif  // TAGOBJECTS_HPP_
