#define AYTESTM_CONFIG_MAIN
#include <aytestm.hpp>

#if 1
TEST_CASE("check true") {
    CHECK(true);
}
TEST_CASE("check false") {
    CHECK(false);
}
TEST_CASE("check") {
    CHECK(0 < 1);
    CHECK(0 > 1);
}

TEST_CASE("require true") {
    REQUIRE(true);
}
TEST_CASE("require false") {
    REQUIRE(false);
}
TEST_CASE("require") {
    REQUIRE(0 < 1);
    REQUIRE(0 > 1);
    CHECK(false);
}

namespace {
inline bool throwTest() {
    throw std::runtime_error{"throw test"};
    return false;
}
inline bool nothrowTest() {
    return false;
}
}

TEST_CASE("check throw") {
    CHECK_THROWS(throwTest());
    CHECK_THROWS(nothrowTest());
}
TEST_CASE("require throw") {
    REQUIRE_THROWS(throwTest());
    REQUIRE_THROWS(nothrowTest());
    CHECK(false);
}
TEST_CASE("check nothrow") {
    CHECK_NOTHROW(nothrowTest());
    CHECK_NOTHROW(throwTest());
}
TEST_CASE("check") {
    CHECK(throwTest());
    REQUIRE(throwTest());
    CHECK(false);
}
TEST_CASE("require nothrow") {
    REQUIRE_NOTHROW(nothrowTest());
    REQUIRE_NOTHROW(throwTest());
    CHECK(false);
}

TEST_CASE("check throw as") {
    CHECK_THROWS_AS(std::string, throwTest());
    CHECK_THROWS_AS(std::runtime_error, throwTest());
}
TEST_CASE("require throw as") {
    REQUIRE_THROWS_AS(std::runtime_error, throwTest());
    REQUIRE_THROWS_AS(std::string, throwTest());
    CHECK(false);
}

TEST_CASE("section") {
    CHECK(0 != 0);
    SECTION("sec1") {
        CHECK(false);
    }
    SECTION("sec2") {
        REQUIRE(false);
        CHECK(false);
    }
    SECTION("sec3") {
        CHECK(false);
        SECTION("sec3-1") {
            CHECK(false);
        }
    }
    CHECK(1 != 1);
}
#else
int pow2(int x) { return x * x; }

TEST_CASE("case 1") {
    CHECK(pow2(1) == 1);
    CHECK(pow2(2) == 4);
    CHECK(pow2(10) == 100);
    CHECK(pow2(1) + 1 == 3);
    CHECK_THROWS(pow2(0));
}
#endif

