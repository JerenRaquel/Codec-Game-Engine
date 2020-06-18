#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "lib/GarbageCollector.hpp"
#include "lib/TagObjects.hpp"

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

struct CollisionArguements {};

class Engine {
 public:
  //
  // Constructors
  //
  Engine();
  Engine(const sf::VideoMode& vid_mode, const std::string& game_title);
  ~Engine(){};

  //
  // Public functions
  //
  void Start();
  void Awake();
  void Update();

  //
  // Manipulation Functions
  //
  void TranslateTags(const std::string& tag,
                     const sf::Vector2f& translate_distance,
                     const CollisionArguements& collision_arguements);

 private:
  //
  // Member Data
  //
  std::unique_ptr<sf::RenderWindow> window_;
  std::string game_title_;
  std::map<Tags, std::unique_ptr<std::vector<std::unique_ptr<GameObject>>>,
           TagComp>
      tag_objects_;
  std::unique_ptr<GarbageCollector> garbage_collector_;
  bool flag_render_update = false;

  //
  // Private Functions
  //
  void Run();
  void Render();
};

#endif  // ENGINE_HPP_
