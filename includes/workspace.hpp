#pragma once

#include <array>
#include <filesystem>
#include <set>
#include <string>

namespace fs = std::filesystem;

class Workspace {
public:
    explicit Workspace(fs::path pathname);
    std::set<fs::path> list_files();
    static std::string read_file(const fs::path& path);

private:
    fs::path m_pathname;
    std::set<fs::path> m_ignores;
};
