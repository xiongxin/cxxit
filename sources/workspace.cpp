//
// Created by xiongxin on 8/16/22.
//
#include "../inculdes/workspace.h"

#include <algorithm>
#include <fmt/format.h>
#include <folly/FileUtil.h>

Workspace::Workspace(std::string_view pathname) { this->pathname = pathname; }

std::vector<fs::path> Workspace::list_files() {
  fs::directory_iterator directory_iterator = fs::directory_iterator(pathname);

  std::vector<fs::path> res{};

  for (auto &p : fs::directory_iterator(pathname)) {
    auto is_ignore = false;
    for (auto &ig : IGNORE) {
      if (p.path() == (pathname / ig)) {
        is_ignore = true;
      }
    }
    if (!is_ignore) {
      res.push_back(p.path());
    }
  }

  return res;
}

std::string Workspace::read_file(const char *path) {
  std::string res{};
  folly::readFile(path, res);

  return res;
}
