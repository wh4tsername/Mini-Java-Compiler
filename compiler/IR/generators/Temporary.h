#pragma once

#include <string>

namespace IRT {
class Temporary {
 public:
  Temporary();
  explicit Temporary(std::string name);
  std::string ToString() const;

  bool operator==(const Temporary& other) const;
  bool operator!=(const Temporary& other) const;

 private:
  std::string name_;
  static int counter_;
};
}
