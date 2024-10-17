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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#if 0//ndef AYTEST_DETAIL_EXPR_EVAL_HPP_
#define AYTEST_DETAIL_EXPR_EVAL_HPP_

namespace aytest {
enum class ExprEvalMode {
    kCondition = 0,
    kThrow,
    kNoThrow,
};

namespace detail {
template <ExprEvalMode _mode>
struct ExprEval {
    template <typename... Args>
    bool operator()(Args...) {
        assert(0);
        return false;
    }
};

inline void _evalExprFailed(std::ostream & ost, ExprInfo const & _expr,
                            FileLineInfo const & _finfo) {
    ost << _finfo << ": " << std::endl;
    ost << kTabStr << _expr << std::endl << std::endl;
}

template <>
struct ExprEval<ExprEvalMode::kCondition> {
    template <typename... Args>
    bool operator()(std::ostream & ost, ExprInfo const & _expr,
                    FileLineInfo const & _finfo, Args...) {
        if (!_expr) {
            return false;
        }
        if (_expr()) {
            return true;
        }
        _evalExprFailed(ost, _expr, _finfo);
        return false;
    }
};

template <>
struct ExprEval<ExprEvalMode::kThrow> {
    template <typename... Args>
    bool operator()(std::ostream & ost, ExprInfo const & _expr,
                    FileLineInfo const & _finfo, Args...) {
        if (!_expr) {
            return false;
        }
        try {
            _expr();
            _evalExprFailed(ost, _expr, _finfo);
            return false;
        } catch (...) {
            return true;
        }
        assert(0);
        return false;
    }
};

template <>
struct ExprEval<ExprEvalMode::kNoThrow> {
    template <typename... Args>
    bool operator()(std::ostream & ost, ExprInfo const & _expr,
                    FileLineInfo const & _finfo, Args...) {
        try {
            _expr();
            return true;
        } catch (...) {
            ost << _finfo << ": " << std::endl;
            ost << kTabStr << getExceptionInfo() << std::endl << std::endl;
            return false;
        }
        assert(0);
        return false;
    }
};
} // aytest::detail
} // aytest
#endif
