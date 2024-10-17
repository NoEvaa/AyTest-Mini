/**
 * MIT License
 *
 * Copyright (c) 2024 NoEvaa
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <cassert>
#include <ostream>
#include <string>
#include <string_view>
#include <functional>
#include <source_location>

#define AYTTM_SRC_LOC std::source_location().current()

#define AYTTM_EXPRINFO(...)                                                                        \
    ittm::ExprInfo([&]() { return static_cast<bool>(__VA_ARGS__); }, #__VA_ARGS__)


namespace ittm {
typedef struct test_failure_exception {} TestFailure;

namespace detail {
constexpr char const * kTabStr = "    ";

inline std::ostream & toStream(std::ostream & ost, std::source_location const & src_loc) {
    ost << src_loc.file_name() << "(" << src_loc.line() << ")";
    return ost;
}

inline std::string getExceptionInfo() {
    try {
        auto ep = std::current_exception();
        if (ep) {
            std::rethrow_exception(ep);
        }
    } catch (test_failure_exception const &) {
        return "Test failed.";
    } catch (std::exception const & e) {
        return e.what();
    } catch (...) {
        return "Unknown exception.";
    }
    return "";
}
}

class ExprInfo {
public:
    ExprInfo(std::function<bool(void)> _expr, std::string_view str_expr)
        : m_expr(_expr), m_str_expr(str_expr) {}

    operator bool() const {
        assert(m_expr);
        return bool(m_expr);
    }

    bool operator()() const {
        assert(m_expr);
        return m_expr();
    }

    std::string_view expression() const {
        return m_str_expr;
    }

private:
    std::function<bool(void)> m_expr;

    std::string_view m_str_expr;
};
}
