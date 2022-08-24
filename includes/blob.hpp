#pragma once

#include <string>
#include <utility>

class Blob {
public:
    explicit Blob(std::string_view);

    virtual constexpr std::string_view type() { return "blob"; }
    [[nodiscard]] virtual std::string to_s() const { return std::string{m_data}; }

    void set_oid(std::string oid) { m_oid = std::move(oid); }
    [[nodiscard]] std::string_view get_oid() const { return m_oid; }

private:
    std::string_view m_data;
    std::string m_oid;
};
