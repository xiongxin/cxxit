#include "../includes/workspace.hpp"

#include <folly/FileUtil.h>

#include <iterator>
#include <range/v3/all.hpp>
#include <utility>


Workspace::Workspace(fs::path pathname) : m_pathname{std::move(pathname)},
                                          m_ignores{
                                                  {".idea"},
                                                  {".git"},
                                                  {".rit"},
                                                  {"cmake-build-debug"}} {
}

std::set<fs::path> Workspace::list_files() {
    std::set<fs::path> res{};
    std::set<fs::path> paths{};
    ranges::for_each(fs::directory_iterator(m_pathname),
                     [&](auto&& entry) { return paths.insert(fs::relative(entry.path(), m_pathname)); });
    ranges::set_difference(paths, m_ignores, std::inserter(res, res.begin()));

    return res;
}

std::string Workspace::read_file(const fs::path& path) {
    std::string res{};
    if (folly::readFile(path.c_str(), res)) {
        return res;
    }

    return "";
}
