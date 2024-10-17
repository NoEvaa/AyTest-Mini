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
#include <string>
#include <ostream>
#include <functional>
#include <source_location>

#define AYTTM_SRC_LOC std::source_location().current()

//#define AYTEST_EXPRINFO(_handler, ...)                                         \
//  aytest::detail::ExprInfo([&]() { return static_cast<bool>(__VA_ARGS__); },   \
//                           #__VA_ARGS__, _handler)

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

struct ExprInfo {
    std::function<bool(void)> expr_;
    
    std::string expr_str_;
    std::string handle_str_;

    ExprInfo(std::function<bool(void)> _expr, char const * expr_str, char const * handle_str)
        : expr_(_expr), expr_str_(expr_str), handle_str_(handle_str) {}

    operator bool() const {
        assert(expr_);
        return bool(expr_);
    }

    bool operator()() const {
        assert(expr_);
        return expr_();
    }
};

inline std::ostream & operator<<(std::ostream & ost, ExprInfo const & einfo) {
    ost << einfo.handle_str_ << "( " << einfo.expr_str_ << " )";
    return ost;
}
}
}
