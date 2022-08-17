//
// Created by xiongxin on 8/16/22.
//

#ifndef CXXIT_WORKSPACE_H
#define CXXIT_WORKSPACE_H

#include <filesystem>
#include <ranges>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Workspace {
public:
  Workspace(std::string_view pathname);
  std::vector<fs::path> list_files();
  std::string read_file(const char *path);

private:
  fs::path pathname;
  std::array<std::string_view, 3> IGNORE{".git", ".vscode", ".rit"};
};

#endif // CXXIT_WORKSPACE_H
