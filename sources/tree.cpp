#include "../includes/tree.hpp"

#include <fmt/format.h>
#include <folly/String.h>
#include <folly/io/Cursor.h>
#include <folly/io/IOBufQueue.h>

[[nodiscard]] std::string Tree::to_s() const {
    folly::IOBuf buf{};
    folly::io::Appender app(&buf, 20);

    for (auto& entry: m_entries) {
        app.push(folly::StringPiece{s_mode});
        app.push(folly::StringPiece{entry.get_name()});
        auto out = std::vector<uint8_t>{};
        folly::unhexlify(entry.get_oid(), out);
        app.push(out.data(), out.size());
    }
    std::string res{};
    buf.appendTo(res);
    return res;
}