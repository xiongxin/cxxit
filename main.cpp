#include <cstdio>
#include <deque>
#include <filesystem>
#include <fmt/format.h>
#include <folly/Hash.h>
#include <iostream>
#include <list>
#include <ranges>
#include <string>

#include "./inculdes/workspace.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  std::deque<std::string_view> ARGV{argv + 1, argv + argc};
  std::string_view command = ARGV.front();
  ARGV.pop_front();
  switch (folly::hash::fnv32(command.data())) {
  case folly::hash::fnv32("init"): {
    auto path = ARGV.begin() != ARGV.end() ? fs::path{ARGV.front()}
                                           : fs::current_path();
    auto root_path = fs::absolute(path);
    auto git_path = root_path / ".rit";

    for (std::string_view dir : {"objects", "refs"}) {
      try {
        fs::create_directories(git_path / dir);
      } catch (fs::filesystem_error &filesystem_error) {
        fmt::print(stderr, "fatal: {}\n", filesystem_error.what());
        return 1;
      }
    }

    fmt::print("Initialized empty Jit repository in {}\n", git_path.string());
    return 0;
  }
  case folly::hash::fnv32("commit"): {
    auto root_path = fs::current_path();
    auto git_path = root_path / ".rit";
    auto db_path = root_path / ".objects";

    Workspace workspace{root_path.string()};

    for (auto &p : workspace.list_files()) {
      fmt::print("{}\n", p.string());
    }
  }
  default:
    fmt::print("jit {} is not a jit command\n", command);
    return 1;
  }
}
