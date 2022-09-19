#pragma once

#include <functional>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <utility>

#include "entry.hpp"

class Tree : public Entry {
    std::set<Entry> m_entries;

public:
    constexpr static std::string_view s_mode = "100644";

    explicit Tree(std::set<Entry> entries) : m_entries{std::move(entries)} {}
    [[nodiscard]] std::string to_s() const override;
    constexpr std::string_view type() override { return "tree"; }
};