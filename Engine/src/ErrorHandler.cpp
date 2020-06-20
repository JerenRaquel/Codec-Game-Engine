#include "../lib/ErrorHandler.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

void ErrorHandler::ThrowError(const std::string& error_message) const {
  throw std::runtime_error("Error: " + error_message);
}

void ErrorHandler::ThrowWarning(const std::string& warning_message) const {
  std::cout << "Warning: " + warning_message << std::endl;
}

void ErrorHandler::ThrowMessage(const std::string& message) const {
  std::cout << message << std::endl;
}