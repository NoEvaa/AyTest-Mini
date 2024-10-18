#include <aytestm.hpp>
#include <iostream>
#include <source_location>

#define AA(macro, ...) 
#define CHECK(...)

// 4567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

namespace aytest_mini {
class TestContext;
class TestCase;

class TestExpr {
public:
    explicit TestExpr(std::source_location const & src_loc) : m_src_loc(src_loc) {} 

    TestExpr & bindExpr(ExprInfo const & expr_info) {
        m_expr = expr_info;
        return *this;
    }

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
    
private:
    std::source_location m_src_loc;

    ExprInfo    m_expr;
    EvalInfo    m_eval;
    HandlerInfo m_handler;
};

bool testNoThrow(ExprInfo const & einfo) {
    try {
        einfo();
    } catch (TestFailure const & e) {
        return false;
    } catch (...) {
        return false;
    }
    return true;
}


}

int main()
{
    

    [](){

    }();

    auto ei = AYTTM_EXPRINFO(1 < 2);
    std::cout << ei.expression() << std::endl;

    std::cout << ei() << std::endl;

    auto sl = AYTTM_SRC_LOC;
    std::cout << sl.file_name() << std::endl;
    std::cout << sl.line() << std::endl;
    std::cout << 0 << std::endl;
    return 0;
}

