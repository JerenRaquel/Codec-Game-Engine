#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "lib/ErrorHandler.hpp"
#include "lib/GameObject.hpp"
#include "lib/GarbageCollector.hpp"

struct CollisionArguements {};

class Engine {
 public:
  //
  // Structors
  //
  /* Engine | O(1)
   * Default params: width = 1280, height = 720, game_title = Untitled Game
   *  Constructs the engine class
   */
  Engine();
  /* Engine | O(1)
   * @param width: the width of the screen
   * @param height: the height of the screen
   * @param game_title: the title of the window
   *  Constructs the engine class
   */
  Engine(const unsigned int width, const unsigned int height,
         const std::string& game_title);
  /* ~Engine | O(N*M) where N is the amount of tags and M is the amount of
   objects corrisponding to a tag
   * Cleans up all data.
   */
  ~Engine();

  //
  // GameLogic Functions
  //
  // All function's Big O notation is determined by the game dev using this.
  void Awake();
  void Start();
  void Update();

  //
  // Loading Functions
  //
  /* LoadNewObject | O(1)
   * @param tag: Tag of the object; holds the tag name and if it requires
   rendering
   * @param file_location: the location or name of the sprite to be rendered
   * @param transform: the component representing the posistion, rotation, and
   scale of the sprite
   *  Loads a new tagged object
   */
  void LoadNewObject(const Tags& tag, const std::string& file_location,
                     const Transform& transform);
  /* LoadNewObject | O(1)
   * @param tag: Tag of the object; holds the tag name and if it requires
   rendering
   * @param file_location: the location or name of the sprite to be rendered
   * @param transform: the component representing the posistion, rotation, and
   scale of the sprite
   * @param uv: a four float object to hold the rect information where x & y are
   the posistion in the top left corner and w & h are the width and height of
   the box
   *  Loads a new tagged object
   */
  void LoadNewObject(const Tags& tag, const std::string& file_location,
                     const Transform& transform, const sf::IntRect& uv);
  /* LoadTagObjectBatch | O(N) where N is the amount of lines/objects to be read
   * @param file_location: the location or name of the sprites to be rendered
   *  Loads all the tagged objects listed in a file
   */
  void LoadTagObjectBatch(const std::string& file_location);

  //
  // Manipulation Functions
  //
  // void TranslateTags(const std::string& tag,
  //                    const sf::Vector2f& translate_distance,
  //                    const CollisionArguements& collision_arguements);
  // sf::Vector2f VLerp(const sf::Vector2f start_position,
  //                    const sf::Vector2f end_position, const float distance)

  //
  // Helper Functions
  //
  /* ErrorHandle | O(1)
   *  Returns a const refrence to the internal ErrorHandler class to help with
   * logging errors or messages by the game dev
   */
  const ErrorHandler& ErrorHandle() const noexcept;

 private:
  //
  // Member Data
  //
  // * Data
  std::unique_ptr<sf::RenderWindow> window_;
  std::string game_title_;
  sf::Vector2i window_size_;
  std::map<Tags, std::vector<GameObject*>*, TagComp> tag_objects_;
  // * Internal Objects
  std::unique_ptr<GarbageCollector> garbage_collector_;
  std::unique_ptr<ErrorHandler> error_handler_;
  // * Flags
  bool flag_render_update = true;

  //
  // Private Functions
  //
  /* Run | O(N^2) where N is the checking of the game window being closed
   *  The main logic for the engine that handles the looping and initilization
   * of game dev code. This function also handles error catching.
   */
  void Run();
  /* Render | O(N*M) where N is the amount of tags and M is the amount of
   objects corrisponding to a tag
   *  The main render system. Current system will only rerender if there is a
   need to rerender such as manipulating the physical aspect of a sprite; ie
   position. ! Will be refractored later.
   */
  void Render();
  /* ParserData | O(1)
   *  Parses data from a file and checks to see if the parser has a bad bit
   */
  template <typename T>
  void ParseData(std::stringstream& parser, T& token);
};

#endif  // ENGINE_HPP_
