#pragma once

#include <string>

namespace IRT {
class Temporary {
 public:
  Temporary();
  explicit Temporary(std::string name);
  std::string ToString() const;

 private:
  std::string name_;
  static int counter_;
};
}
