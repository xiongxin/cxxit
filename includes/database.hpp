#pragma once

#include <folly/io/Cursor.h>
#include <folly/io/IOBufQueue.h>

#include <filesystem>
#include <set>
#include <string>
#include <utility>

#include "blob.hpp"

namespace fs = std::filesystem;

class Database {
    fs::path m_pathname;
    void write_object(std::string_view oid, folly::IOBuf* buf);

public:
    explicit Database(fs::path pathname) : m_pathname{std::move(pathname)} {}
    void store(Blob&);
};
