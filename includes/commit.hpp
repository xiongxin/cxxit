#pragma once

#include <string>

#include "tree.hpp"

class Commit : public Blob {
public:
    Commit(const std::string_view& tree, const std::string_view& message) : m_tree{tree},
                                                                            m_message{message},
                                                                            Blob("") {}
    [[nodiscard]] std::string to_s() const override;
    constexpr std::string_view type() override { return "commit"; }

private:
    std::string_view m_tree;
    std::string_view m_message;
};