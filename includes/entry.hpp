#pragma once

#include <string>
#include <utility>

#include "blob.hpp"

class Entry : public Blob {
public:
    explicit Entry(const std::string_view& name, const std::string_view& oid) : m_name{name},
                                                                                Blob("") {
        set_oid(std::string{oid});
    }
    [[nodiscard]] std::string_view get_name() const { return m_name; }
    bool operator<(const Entry& b) const { return m_name < b.m_name; }

private:
    std::string m_name;
};