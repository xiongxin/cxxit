#include "../includes/database.hpp"

#include <folly/FileUtil.h>
#include <folly/Random.h>
#include <folly/Range.h>
#include <folly/String.h>
#include <folly/compression/Compression.h>
#include <folly/io/Cursor.h>
#include <folly/io/IOBufQueue.h>
#include <folly/ssl/OpenSSLHash.h>

#include <array>
#include <string>

void Database::store(Blob& blob) {
    auto string = blob.to_s();
    folly::IOBuf buf{};
    folly::io::Appender app(&buf, 20);
    app.push(folly::StringPiece{blob.type()});
    app.write(' ');
    auto size = std::to_string(string.size());
    app.push(folly::StringPiece{size});
    app.write((uint8_t) 0);
    app.push(folly::StringPiece{string});
    auto out = std::array<uint8_t, 20>{};
    folly::ssl::OpenSSLHash::sha1(folly::range(out), buf);
    blob.set_oid(folly::hexlify(out));
    write_object(blob.get_oid(), &buf);
}

void Database::write_object(const std::string_view& oid, folly::IOBuf* buf) {
    auto object_path = m_pathname / oid.substr(0, 2) / oid.substr(2);
    auto dirname = object_path.parent_path();
    if (!fs::exists(dirname)) create_directories(dirname);
    auto tmp_path = dirname / std::to_string(folly::Random::rand32());
    auto codec = folly::io::getCodec(folly::io::CodecType::ZLIB,
                                     folly::io::COMPRESSION_LEVEL_FASTEST);
    auto compressed = codec->compress(buf);
    folly::ByteRange byteRange{compressed->data(), compressed->length()};
    folly::writeFile(byteRange, tmp_path.c_str());
    rename(tmp_path, object_path);
}
