
#include "../includes/commit.hpp"

#include <fmt/format.h>

[[nodiscard]] std::string Commit::to_s() const {
    return fmt::format("tree {}\n\n{}", m_tree, m_message);
}