#ifndef TAGOBJECTS_HPP_
#define TAGOBJECTS_HPP_

#include <memory>

struct GameObject {
  unsigned int object_id;
  std::unique_ptr<TagObjects> tag_object;
};

struct Tags {
  std::string name;
  bool flag_render = true;
};

struct TagComp {
  bool operator()(Tags a, Tags b) { return a.name < b.name; }
};

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
