#include "../lib/TagObjects.hpp"

#include <SFML/Graphics.hpp>
#include <stdexcept>

//
// Transform Overloading
//
std::istream& operator>>(std::istream& in, Transform& transform) {
  float x_position, y_position;
  float rotation;
  float x_scale, y_scale;
  in >> x_position >> y_position >> rotation >> x_scale >> y_scale;

  if (!in) {
    throw std::runtime_error("Unable to parse transform correctly...");
  }

  transform.position = sf::Vector2f(x_position, y_position);
  transform.rotation = rotation;
  transform.scale = sf::Vector2f(x_scale, y_scale);

  return in;
}

std::ostream& operator<<(std::ostream& out, const Transform& transform) {
  out << "Position: (" << transform.position.x << ", " << transform.position.y
      << ")\n";
  out << "Rotation: " << transform.rotation << "\n";
  out << "Scale: (" << transform.scale.x << ", " << transform.scale.y << ")"
      << std::endl;
  return out;
}

//
// Structors
//
TagObjects::TagObjects() {
  this->sprite_ = nullptr;
  this->texture_ = nullptr;
  this->transform_ = std::unique_ptr<Transform>(new Transform);
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location) {
  this->sprite_ = std::unique_ptr<sf::Sprite>(new sf::Sprite);
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  this->transform_ = std::unique_ptr<Transform>(new Transform);
  if (!this->texture_->loadFromFile(file_location)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_.get()));
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location,
                       const Transform& transform) {
  this->sprite_ = std::unique_ptr<sf::Sprite>(new sf::Sprite);
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  this->transform_ = std::unique_ptr<Transform>(new Transform);
  if (!this->texture_->loadFromFile(file_location)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_.get()));
  SetTransform(transform);
}

TagObjects::TagObjects(const std::string& file_location, const sf::IntRect uv) {
  this->sprite_ = std::unique_ptr<sf::Sprite>(new sf::Sprite);
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  this->transform_ = std::unique_ptr<Transform>(new Transform);
  if (!this->texture_->loadFromFile(file_location, uv)) {
    throw std::runtime_error("Error: Unable to load " + file_location);
  }

  this->sprite_->setTexture(*(this->texture_.get()));
  this->sprite_->setTextureRect(uv);
  SetTransform({sf::Vector2f(0, 0), 0, sf::Vector2f(1, 1)});
}

TagObjects::TagObjects(const std::string& file_location,
                       const Transform& transform, const sf::IntRect uv) {
  this->sprite_ = std::unique_ptr<sf::Sprite>(new sf::Sprite);
  this->texture_ = std::unique_ptr<sf::Texture>(new sf::Texture);
  this->transform_ = std::unique_ptr<Transform>(new Transform);
  if (!this->texture_->loadFromFile(file_location, uv)) {
    throw std::runtime_error("Error: Unable to load from" + file_location);
  }
  this->sprite_->setTexture(*(this->texture_.get()));
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

const bool TagObjects::CheckIfDead() const noexcept {
  return this->flag_deleted_;
}

// * Setters
void TagObjects::SetTransform(const Transform& transform) noexcept {
  // Set the global data
  this->transform_->position = transform.position;
  this->transform_->rotation =
      transform.rotation < 360 ? transform.rotation : transform.rotation - 360;
  this->transform_->scale = transform.scale;

  // Set the local data
  this->sprite_->setPosition(this->transform_->position);
  this->sprite_->setRotation(this->transform_->rotation);
  this->sprite_->setScale(this->transform_->scale);
}

void TagObjects::SetPosition(const sf::Vector2f& new_position) noexcept {
  this->transform_->position = new_position;
  this->sprite_->setPosition(new_position);
}

void TagObjects::SetRotation(const float& new_rotation) noexcept {
  this->transform_->rotation = new_rotation;
  this->sprite_->setRotation(new_rotation);
}

void TagObjects::SetScale(const sf::Vector2f& new_scale) noexcept {
  this->transform_->scale;
  this->sprite_->setScale(new_scale);
}

//
// Private Functions
//