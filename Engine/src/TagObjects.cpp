#include "../lib/TagObjects.hpp"

#include <SFML/Graphics.hpp>
#include <stdexcept>

//
// Structors
//
TagObjects::TagObjects() {
  this->sprite_ = nullptr;
  this->texture_ = nullptr;
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location) {
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  if (!this->texture_->loadFromFile(file_location)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_));
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location,
                       const Transform& transform) {
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  if (!this->texture_->loadFromFile(file_location)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_));
  SetTransform(transform);
}

TagObjects::TagObjects(const std::string& file_location, const sf::IntRect uv) {
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  if (!this->texture_->loadFromFile(file_location, uv)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_));
  this->sprite_->setTextureRect(uv);
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location,
                       const Transform& transform, const sf::IntRect uv) {
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  if (!this->texture_->loadFromFile(file_location, uv)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_));
  this->sprite_->setTextureRect(uv);
  SetTransform(transform);
}

//
// Public Functions
//
// * Getters
const sf::Sprite* TagObjects::GetSprite() const noexcept {
  return this->sprite_.get();
}

const sf::Texture* TagObjects::GetTexture() const noexcept {
  return this->texture_.get();
}

const Transform* TagObjects::GetTransform() const noexcept {
  return this->transform_.get();
}

// * Setters
void TagObjects::SetTransform(const Transform& transform) noexcept {
  this->transform_->position = transform.position;
  this->transform_->rotation =
      transform.rotation < 360 ? transform.rotation : transform.rotation - 360;
  this->transform_->scale = transform.scale;
}

//
// Private Functions
//