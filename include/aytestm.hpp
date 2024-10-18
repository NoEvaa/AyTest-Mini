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

#define AYTTM_SRC_LOC std::source_location::current()

#define AYTTM_EXPRINFO(...)                                                                        \
    aytest_mini::ExprInfo([&]() { return static_cast<bool>(__VA_ARGS__); }, #__VA_ARGS__)


namespace aytest_mini {
namespace detail {
constexpr char const * kStrEmpty = "";
constexpr char const * kStrTab   = "    ";
}
typedef struct test_failure_exception {
    test_failure_exception() = default;
    
    explicit test_failure_exception(char const * msg) : m_p_msg(msg) {}

    char const * what() const noexcept {
        return m_p_msg ? m_p_msg : detail::kStrEmpty;
    }

private:
    char const * m_p_msg = nullptr;
} TestFailure;

namespace detail {
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

template <typename Func>
class FuncInfo {
public:
    FuncInfo() = default;

    explicit FuncInfo(Func _fn, std::string_view str_info = std::string_view{kStrEmpty})
        : m_fn(_fn), m_str_info(str_info) {}

    operator bool() const {
        return bool(m_fn);
    }

    bool operator()(auto... args) const {
        assert(m_fn);
        return m_fn(args...);
    }

    std::string_view const & info() const {
        return m_str_info;
    }

private:
    Func m_fn;

    std::string_view m_str_info;
};
}

using ExprInfo    = detail::FuncInfo<std::function<bool(void)>>;
using EvalInfo    = detail::FuncInfo<std::function<bool(ExprInfo const &)>>;
using HandlerInfo = detail::FuncInfo<std::function<bool(bool)>>;

class TestExpr {
public:
    explicit TestExpr(ExprInfo const & expr_info) : m_expr(expr_info) { }

    TestExpr & bindEval(EvalInfo const & eval_info) {
        m_eval = eval_info;
        return *this;
    }

    TestExpr & bindHandler(HandlerInfo const & handler_info) {
        m_handler = handler_info;
        return *this;
    }

    bool run() const {
        if (!m_expr) {
            throw TestFailure{};
        }
        bool b_res = m_eval ? m_eval(m_expr) : m_expr();
        return m_handler ? m_handler(b_res) : b_res;
    }

    std::ostream & toStream(std::ostream & ost) {
        if (m_handler.info().size()) {
            ost <<  m_handler.info() << "( ";
        }
        if (m_eval.info().size()) {
            ost <<  m_eval.info() << "( ";
        }
        ost << m_expr.info();
        if (m_eval.info().size()) {
            ost << " )";
        }
        if (m_handler.info().size()) {
            ost << " )";
        }
        return ost;
    }
    
private:
    ExprInfo    m_expr;
    EvalInfo    m_eval;
    HandlerInfo m_handler;
};


}
