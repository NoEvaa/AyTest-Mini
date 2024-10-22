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
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <functional>
#include <source_location>

#define AYTTM_CAT(a, b)  a##b
#define AYTTM_CAT1(a, b) AYTTM_CAT(a, b)
#define AYTTM_CAT2(a, b) AYTTM_CAT1(a, b)

#define AYTTM_BUILTIN(_n) AYTTM_CAT(__aytestm__builtin__, _n)

#define AYTTM_SRC_LOC std::source_location::current()

#define AYTTM_EXPRINFO_BOOL(...)                                                                   \
    aytest_mini::ExprInfo([&]() { return static_cast<bool>(__VA_ARGS__); }, #__VA_ARGS__)
#define AYTTM_EXPRINFO_VOID(...)                                                                   \
    aytest_mini::ExprInfo([&]() { static_cast<void>(__VA_ARGS__); return true; }, #__VA_ARGS__)




namespace aytest_mini {
namespace detail {
constexpr char const * kStrEmpty = "";
constexpr char const * kStrTab   = "  ";
}
typedef struct test_exception {
    test_exception() = default; 
    explicit test_exception(std::string const & msg) : m_msg(msg) {}
    std::string const & what() const noexcept {
        return m_msg;
    }
private:
    std::string m_msg;
} TestException;
typedef struct test_termination : TestException {
    test_termination() = default;
    explicit test_termination(std::string const & msg) : TestException(msg) {}
} TestTermination;
typedef struct test_output : TestException {
    explicit test_output(std::string const & msg) : TestException(msg) {}
} TestOutput;

namespace detail {
inline std::ostream & outputToStream(std::ostream & ost, std::source_location const & src_loc) {
    ost << src_loc.file_name() << "(" << src_loc.line() << ")";
    return ost;
}

inline std::string getExceptionInfo() {
    try {
        auto ep = std::current_exception();
        if (ep) {
            std::rethrow_exception(ep);
        }
    } catch (test_exception const & e) {
        return e.what();
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
    explicit FuncInfo(Func _fn, std::string_view str_info = std::string_view{ kStrEmpty })
        : m_fn(_fn), m_str_info(str_info) {}
    operator bool() const {
        return bool(m_fn);
    }
    bool operator()(auto... args) const {
        if (m_fn) {
            return m_fn(args...);
        }
        assert(0);
        return false;
    }
    std::string_view const & info() const {
        return m_str_info;
    }
private:
    Func             m_fn;
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
            throw TestException{"No test expression."};
        }
        bool b_res = m_eval ? m_eval(m_expr) : m_expr();
        return m_handler ? m_handler(b_res) : b_res;
    }

    std::ostream & outputToStream(std::ostream & ost) {
        bool b_has_handler = m_handler.info().size();
        bool b_has_eval    = m_eval.info().size();
        if (b_has_handler) {
            ost << m_handler.info();
            if (b_has_eval) {
                ost << '_';
            }
        }
        if (b_has_eval) {
            ost << m_eval.info();
        }
        if (b_has_handler || b_has_eval) {
            ost << "( " << m_expr.info() << " )";
        } else {
            ost << m_expr.info();
        }
        return ost;
    }
 
private:
    ExprInfo    m_expr;
    EvalInfo    m_eval;
    HandlerInfo m_handler;
};

struct TestCount {
    std::size_t total_  = 0;
    std::size_t passed_ = 0;
    std::size_t failed_ = 0;

    TestCount & operator+=(TestCount const & rhs) {
        total_  += rhs.total_;
        passed_ += rhs.passed_;
        failed_ += rhs.failed_;
        return *this;
    }
};

class TestCase {
public:
    virtual ~TestCase() = default;

    void AYTTM_BUILTIN(setName)(char const * case_name) {
        m_name = case_name;
    }
    void AYTTM_BUILTIN(setSrcLoc)(std::source_location const & src_loc) {
        m_src_loc = src_loc;
    }

    virtual void AYTTM_BUILTIN(run)() = 0;

    std::ostream & AYTTM_BUILTIN(outputToStream)(std::ostream & ost) {
        detail::outputToStream(ost, m_src_loc) << std::endl;
        ost << "TEST CASE: " << m_name;
        return ost;
    }

private:
    std::string_view     m_name;
    std::source_location m_src_loc;
    TestCount            m_cnt;
};

using TestCases = std::vector<std::shared_ptr<TestCase>>;

inline bool handleRequire(bool b) {
    if (!b) {
        throw TestTermination{};
    }
    return true;
}
inline bool evalNoThrow(ExprInfo const & expr) {
    try {
        return expr();
    } catch (...) {
        return false;
    }
}
inline bool evalThrow(ExprInfo const & expr) {
    try {
        expr();
    } catch (...) {
        return true;
    }
    return false;
}
template <typename ExTy>
bool evalThrowAs(ExprInfo const & expr) {
    try {
        expr();
    } catch (ExTy const &) {
        return true;
    }
    return false;
}
}
