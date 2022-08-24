#pragma once

#include <folly/File.h>
#include <folly/FileUtil.h>
#include <folly/Random.h>
#include <folly/Range.h>
#include <folly/ScopeGuard.h>
#include <folly/String.h>
#include <folly/compression/Compression.h>
#include <folly/io/Cursor.h>
#include <folly/io/IOBufQueue.h>
#include <folly/ssl/OpenSSLHash.h>

#include <filesystem>
#include <set>
#include <string>
#include <utility>

#include "blob.hpp"

namespace fs = std::filesystem;

class Database {
    fs::path m_pathname;
    void write_object(const std::string_view& oid, folly::IOBuf* buf);

public:
    explicit Database(fs::path pathname) : m_pathname{std::move(pathname)} {}
    void store(Blob&);
};
