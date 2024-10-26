#define AYTESTM_CONFIG_MAIN
#include <aytestm.hpp>

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
inline void throwTest() {
    throw std::runtime_error{"throw test"};
}
inline void nothrowTest() {}
}

TEST_CASE("check throw") {
    CHECK_THROW(throwTest());
    CHECK_THROW(nothrowTest());
}
TEST_CASE("require throw") {
    REQUIRE_THROW(throwTest());
    REQUIRE_THROW(nothrowTest());
    CHECK(false);
}

TEST_CASE("check nothrow") {
    CHECK_NOTHROW(nothrowTest());
    CHECK_NOTHROW(throwTest());
}
TEST_CASE("require nothrow") {
    REQUIRE_NOTHROW(nothrowTest());
    REQUIRE_NOTHROW(throwTest());
    CHECK(false);
}

TEST_CASE("check throw as") {
    CHECK_THROW_AS(std::string, throwTest());
    CHECK_THROW_AS(std::runtime_error, throwTest());
}
TEST_CASE("require throw as") {
    REQUIRE_THROW_AS(std::runtime_error, throwTest());
    REQUIRE_THROW_AS(std::string, throwTest());
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

