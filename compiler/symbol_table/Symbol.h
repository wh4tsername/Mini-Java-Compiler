#pragma once

#include <string>

class Symbol {
 public:
  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;

  std::string GetName() const;

  Symbol() = default;
  explicit Symbol(std::string name);
  Symbol(const Symbol& other) = default;

 private:
  std::string name_;
};

namespace std {
template <>
struct hash<Symbol> {
  std::size_t operator()(const Symbol& other) const {
    return hash<string>()(other.GetName());
  }
};
}
