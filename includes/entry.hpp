#pragma once

#include <string>
#include <utility>

#include "blob.hpp"

class Entry : public Blob {
public:
    Entry() = default;
    explicit Entry(std::string_view name, std::string_view oid) : m_name{name} {
        set_oid(std::string{oid});
    }
    [[nodiscard]] std::string_view get_name() const { return m_name; }
    bool operator<(const Entry& b) const { return m_name < b.m_name; }

private:
    std::string m_name;
};
