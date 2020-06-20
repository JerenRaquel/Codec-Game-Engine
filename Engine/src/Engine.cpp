#include "../Engine.hpp"

#include <fstream>
#include <stdexcept>

//
// Structors
//
Engine::Engine(const sf::VideoMode& vid_mode, const std::string& game_title) {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(vid_mode, game_title));
  this->window_size_ = sf::Vector2i(vid_mode.width, vid_mode.height);
  this->game_title_ = game_title;
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

Engine::Engine() {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(1280, 720), "Untiled Game"));
  this->window_size_ = sf::Vector2i(1280, 720);
  this->game_title_ = "Untitled Game";
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

//
// Loading Functions
//
void Engine::LoadNewObject(const std::string& tag,
                           const sf::Vector2f position) {}
void Engine::LoadTagObjectBatch(const std::string& file_location) {
  std::ifstream file;
  file.open(file_location);
  if (!file) {
    this->error_handler_->ThrowError("Can't read " + file_location);
  }
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
      std::vector<std::unique_ptr<GameObject>>* tagged_objects =
          object->second.get();
      for (unsigned int i = 0; i < tagged_objects->size(); i++) {
        this->window_->draw(*((*tagged_objects)[i]->GetObject()->GetSprite()));
      }
    }
  }
}