#include "../Engine.hpp"

//
// Structors
//
Engine::Engine() {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(1280, 720), "Untiled Game"));
  this->window_size_ = sf::Vector2i(1280, 720);
  this->game_title_ = "Untitled Game";
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

Engine::Engine(const unsigned int width, const unsigned int height,
               const std::string& game_title) {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(width, height), game_title));
  this->window_size_ = sf::Vector2i(width, height);
  this->game_title_ = game_title;
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

Engine::~Engine() {}

//
// Loading Functions
//
void Engine::LoadNewObject(const std::string& tag,
                           const std::string& file_location,
                           const Transform& transform) {
  if (this->tag_objects_.count(tag)) {
    this->tag_objects_[tag]->AddObject(
        new TagObjects(file_location, transform));
  } else {
    this->tag_objects_.insert({tag, new TaggedVector});
    this->tag_objects_[tag]->AddObject(
        new TagObjects(file_location, transform));
  }
}

void Engine::LoadNewObject(const std::string& tag,
                           const std::string& file_location,
                           const Transform& transform, const sf::IntRect& uv) {
  if (this->tag_objects_.count(tag)) {
    this->tag_objects_[tag]->AddObject(
        new TagObjects(file_location, transform, uv));
  } else {
    this->tag_objects_.insert({tag, new TaggedVector});
    this->tag_objects_[tag]->AddObject(
        new TagObjects(file_location, transform, uv));
  }
}

void Engine::LoadTagObjectBatch(const std::string& file_location) {
  std::ifstream file;
  file.open(file_location);
  if (!file) {
    this->error_handler_->ThrowError("Can't read " + file_location);
  }

  std::string buffer;
  std::stringstream parser;
  unsigned int sprites_read = 1;
  // File content
  std::string tag;
  std::string sprite_location;
  Transform transform;
  bool flag_use_UVs;
  int x, y, w, h;

  std::cout << "Loading Sprites from " << file_location << std::endl;
  while (getline(file, buffer)) {
    parser = std::stringstream(buffer);

    // Get info
    ParseData(parser, tag);
    ParseData(parser, sprite_location);
    ParseData(parser, transform);
    ParseData(parser, flag_use_UVs);
    if (flag_use_UVs) {
      ParseData(parser, x);
      ParseData(parser, y);
      ParseData(parser, w);
      ParseData(parser, h);
    }
    // Set Data
    if (flag_use_UVs) {
      LoadNewObject(tag, sprite_location, transform, sf::IntRect(x, y, w, h));
    } else {
      std::cout << "Using default UVs for sprite " << sprites_read << std::endl;
      LoadNewObject(tag, sprite_location, transform);
    }
    sprites_read++;
  }
  std::cout << "Finished reading " << sprites_read - 1 << " sprites from "
            << file_location << std::endl;
}

//
// Manipulation Functions
//
void Engine::TranslateTags(const std::string& tag,
                           const sf::Vector2f& translate_distance) {
  // Flag the renderer to draw new frames
  this->flag_render_update = true;
  // Check if the tag exist
  if (this->tag_objects_.count(tag)) {
    // Pointer to the object holding the GameObjects
    TaggedVector* tagged_vector = this->tag_objects_[tag];
    // Set the render flag
    tagged_vector->SetRenderFlag(true);
    // Get all the objects with the tag
    std::vector<TagObjects*>* objects = tagged_vector->GetObjects();
    // Loop through each tagged object
    for (unsigned int i = 0; i < objects->size(); i++) {
      // Check if the object exist
      if ((*objects)[i]->CheckIfDead()) {
        continue;
      }

      // Create a temp object to point to the tagged object
      TagObjects* temp = (*objects)[i];
      // Set the new position
      temp->SetPosition(temp->GetTransform()->position + translate_distance);
    }
  } else {
    // Tagged objects don't exist
    this->error_handler_->ThrowWarning(
        "Tag: " + tag + " does not exist.\nSkipping translation step...");
  }
}
void Engine::TranslateTags(const std::string& tag,
                           TranslateFunc translation_function) {
  // Flag the renderer to draw new frames
  this->flag_render_update = true;
  // Check if the tag exist
  if (this->tag_objects_.count(tag)) {
    // Pointer to the object holding the GameObjects
    TaggedVector* tagged_vector = this->tag_objects_[tag];
    // Set the render flag
    tagged_vector->SetRenderFlag(true);
    // Get all the objects with the tag
    std::vector<TagObjects*>* objects = tagged_vector->GetObjects();
    // Cache a translation distance var
    sf::Vector2f translation_distance;
    // Loop through each tagged object
    for (unsigned int i = 0; i < objects->size(); i++) {
      // Check if the object exist
      if ((*objects)[i]->CheckIfDead()) {
        continue;
      }

      // Create a temp object to point to the tagged object
      TagObjects* temp = (*objects)[i];
      // Get the translation distance
      translation_distance = translation_function(temp, this->window_size_);
      // Set the new position
      temp->SetPosition(temp->GetTransform()->position + translation_distance);
    }
  } else {
    // Tagged objects don't exist
    this->error_handler_->ThrowWarning(
        "Tag: " + tag + " does not exist.\nSkipping translation step...");
  }
}

template <typename T>
T Engine::Lerp(const T& start_position, const T& end_position, const float& t) {
  return (1 - t) * start_position + t * end_position;
}

//
// Helper Functions
//
const ErrorHandler& Engine::ErrorHandle() const noexcept {
  return *((this->error_handler_).get());
}

//
// Private Functions
//
void Engine::Run() {
  sf::Clock clock;
  try {
    Awake();
    Start();

    sf::Event window_event;
    while (this->window_->isOpen()) {
      while (this->window_->pollEvent(window_event)) {
        if (window_event.type == sf::Event::Closed) {
          this->window_->close();
        }
      }

      Update();

      if (flag_render_update) {
        this->flag_render_update = false;
        Render();
      }

      this->window_->display();

      if (this->garbage_collector_->flag_require_cleaning) {
        this->garbage_collector_->Clean();
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
}

void Engine::Render() {
  this->window_->clear();
  // Loop through each tag
  for (auto tag = this->tag_objects_.begin(); tag != this->tag_objects_.end();
       tag++) {
    // Check if that group of objects needs to be rendered
    if (tag->second->CheckForRender()) {
      // Copy the vector pointer
      std::vector<TagObjects*>* tagged_vector = tag->second->GetObjects();
      // Loop through the vector of pointers
      for (unsigned int i = 0; i < tagged_vector->size(); i++) {
        // Draw
        this->window_->draw(*((*tagged_vector)[i]->GetSprite()));
      }
    } else {
      continue;
    }
  }
}

template <typename T>
void Engine::ParseData(std::stringstream& parser, T& token) {
  if (!parser) {
    this->error_handler_->ThrowError("Unable to parse data of type: " +
                                     std::string(typeid(T).name()));
  }
  parser >> token;
}