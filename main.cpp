#include <fcntl.h>
#include <fmt/format.h>
#include <folly/FileUtil.h>
#include <folly/Hash.h>

#include <cstdio>
#include <deque>
#include <filesystem>
#include <iostream>
#include <list>
#include <string>

#include "./includes/blob.hpp"
#include "./includes/commit.hpp"
#include "./includes/database.hpp"
#include "./includes/workspace.hpp"

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

            for (auto const dir: {"objects", "refs"}) {
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
            auto db_path = git_path / "objects";

            Workspace workspace{root_path};
            Database database{db_path};
            std::set<Entry> entries{};
            for (auto &p: workspace.list_files()) {
                //                fmt::print("{}\n", p.string());
                if (fs::is_regular_file(p)) {
                    auto data = Workspace::read_file(p);
                    auto blob = Blob{data};
                    database.store(blob);
                    entries.insert(Entry{p.string(), blob.get_oid()});
                }
            }
            Tree tree{entries};
            database.store(tree);

            std::string message{};
            std::getline(std::cin, message);

            auto commit = Commit{tree.get_oid(), message};
            database.store(commit);
            auto head_path = git_path / "HEAD";
            folly::writeFile(commit.get_oid(), head_path.c_str());

            fmt::print("[(root-commit) {}] {}", commit.get_oid(), tree.get_oid());
            break;
        }
        default:
            fmt::print("jit {} is not a jit command\n", command);
            return 1;
    }
}
