/*	Jeren Raquel
 *	==Codec Game Engine==
 *	Just a personal project to learn how to create a game engine using SFML
 *as a graphics and sound backing. End goal is a working 2D game engine.
 */
#include "Engine/Engine.hpp"

void Engine::Awake() { LoadTagObjectBatch("Sprite.txt"); }
void Engine::Start() {}
void Engine::Update() {}

int main(int argc, char **argv) { Engine engine; }
