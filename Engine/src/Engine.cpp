#include "../Engine.hpp"

Engine::Engine(const sf::VideoMode& vid_mode, const std::string& game_title) {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(vid_mode, game_title));
  this->game_title_ = game_title;
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

Engine::Engine() {
  this->window_ = std::unique_ptr<sf::RenderWindow>(
      new sf::RenderWindow(sf::VideoMode(1280, 720), "Untiled Game"));
  this->game_title_ = "Untitled Game";
  this->garbage_collector_ =
      std::unique_ptr<GarbageCollector>(new GarbageCollector);

  Run();
}

void Engine::Run() {
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
}

void Engine::Render() {
  for (auto object = this->tag_objects_.begin();
       object != this->tag_objects_.end(); object++) {
    if (object->first.flag_render) {
      std::vector<std::unique_ptr<GameObject>>* tagged_objects =
          object->second.get();
      for (unsigned int i = 0; i < tagged_objects->size(); i++) {
        this->window_->draw(*((*tagged_objects)[i]->tag_object->GetSprite()));
      }
    }
  }
}