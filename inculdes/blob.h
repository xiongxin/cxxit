#pragma once

#include <string>

class Blob {
public:
  Blob(const char *);

  constexpr std::string_view type() { return "blob"; }
  std::string_view to_s() { return std::string_view(data); }

private:
  const char *data;
};
