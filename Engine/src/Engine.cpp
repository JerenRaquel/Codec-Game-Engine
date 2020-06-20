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

Engine::~Engine() {
  for (auto map_it = this->tag_objects_.begin();
       map_it != this->tag_objects_.end(); map_it++) {
    for (auto vect_it = map_it->second->begin();
         vect_it != map_it->second->end(); vect_it++) {
      delete *vect_it;
    }
    delete map_it->second;
  }
}

//
// Loading Functions
//
void Engine::LoadNewObject(const Tags& tag, const std::string& file_location,
                           const Transform& transform) {
  if (this->tag_objects_.count(tag)) {
    this->tag_objects_[tag]->push_back(
        new GameObject(file_location, transform));
  } else {
    this->tag_objects_.insert({tag, new std::vector<GameObject*>});
    this->tag_objects_[tag]->push_back(
        new GameObject(file_location, transform));
  }
}

void Engine::LoadNewObject(const Tags& tag, const std::string& file_location,
                           const Transform& transform, const sf::IntRect& uv) {
  if (this->tag_objects_.count(tag)) {
    this->tag_objects_[tag]->push_back(
        new GameObject(file_location, transform, uv));
  } else {
    this->tag_objects_.insert({tag, new std::vector<GameObject*>});
    this->tag_objects_[tag]->push_back(
        new GameObject(file_location, transform, uv));
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
  Tags tag;
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
  for (auto object = this->tag_objects_.begin();
       object != this->tag_objects_.end(); object++) {
    if (object->first.flag_render) {
      std::vector<GameObject*>* tagged_objects = object->second;
      for (unsigned int i = 0; i < tagged_objects->size(); i++) {
        if (!(*tagged_objects)[i]->CheckIfDead()) {
          this->window_->draw(
              *((*tagged_objects)[i]->GetObject()->GetSprite()));
        }
      }
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