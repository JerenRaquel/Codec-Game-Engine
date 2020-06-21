/*	Jeren Raquel
 *	==Codec Game Engine==
 *	Just a personal project to learn how to create a game engine using SFML
 *as a graphics and sound backing. End goal is a working 2D game engine.
 */
#include "Engine/Engine.hpp"

void Engine::Awake() { LoadTagObjectBatch("Sprite.txt"); }
void Engine::Start() {}
void Engine::Update() {
  TranslateTags("Boomerang",
                [](const TagObjects* obj, const sf::Vector2i& screen_size) {
                  if (obj->GetTransform()->position.x > 300 &&
                      obj->GetTransform()->position.x < 600) {
                    return sf::Vector2f(2, 0);
                  }
                  return sf::Vector2f(1, 0);
                });
}

int main(int argc, char** argv) { Engine engine; }
