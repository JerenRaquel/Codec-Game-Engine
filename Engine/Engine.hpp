#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "lib/ErrorHandler.hpp"
#include "lib/GameObject.hpp"
#include "lib/GarbageCollector.hpp"

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
  // GameLogic Functions
  //
  void Start();
  void Awake();
  void Update();

  //
  // Loading Functions
  //
  void LoadNewObject(const std::string& tag, const sf::Vector2f position);
  void LoadTagObjectBatch(const std::string& file_location);

  //
  // Manipulation Functions
  //
  void TranslateTags(const std::string& tag,
                     const sf::Vector2f& translate_distance,
                     const CollisionArguements& collision_arguements){};
  // sf::Vector2f VLerp(const sf::Vector2f start_position,
  //                    const sf::Vector2f end_position, const float distance)

  //
  // Helper Functions
  //
  const ErrorHandler& ErrorHandle() const noexcept;

 private:
  //
  // Member Data
  //
  // * Data
  std::unique_ptr<sf::RenderWindow> window_;
  std::string game_title_;
  sf::Vector2i window_size_;
  std::map<Tags, std::unique_ptr<std::vector<std::unique_ptr<GameObject>>>,
           TagComp>
      tag_objects_;
  // * Internal Objects
  std::unique_ptr<GarbageCollector> garbage_collector_;
  std::unique_ptr<ErrorHandler> error_handler_;
  // * Flags
  bool flag_render_update = false;

  //
  // Private Functions
  //
  void Run();
  void Render();
};

#endif  // ENGINE_HPP_
