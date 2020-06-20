#ifndef ERRORHANDLER_HPP_
#define ERRORHANDLER_HPP_

#include <iostream>

class ErrorHandler {
 public:
  //
  // Public Functions
  //
  void ThrowError(const std::string& error_message) const;
  void ThrowWarning(const std::string& warning_message) const;
  void ThrowMessage(const std::string& message) const;
};

#endif  // ERRORHANDLER_HPP_
