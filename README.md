# Ayin Test - Mini

AyTest-Mini is a lightest modern single-header unit testing framework for C++20 and later.

## Quick Start

To get started, all you need is to download the latest version which is just a single header 
and include it in your source files (or add this repository as a git submodule).

### A simple example

Suppose we have a `pow2` function that we want to test:

```c++
#define AYTESTM_CONFIG_MAIN
#include "aytestm.hpp"

int pow2(int x) { return x * x; }

TEST_CASE("case 1") {
    CHECK(pow2(1) == 1);
    CHECK(pow2(2) == 4);
    CHECK(pow2(10) == 100);
}
```

## Tutorial

### Testing Case Macros

- TEST_CASE( case name, ... )

```c++
TEST_CASE("case 1") {
    assertion expression
    assertion expression
    assertion expression
}
```

- SECTION(...)

```c++
TEST_CASE("") {
    SECTION("S1") {
        assertion expression
        assertion expression
    }
    SECTION("S2") {
        assertion expression
        assertion expression
    }
}
```

### Assertion Macros

- CHECK( expression )
- REQUIRE( expression )

Evaluates the expression and check if the result is true.
If an exception is thrown, it is caught, reported, and counted as a failure.

- CHECK_NOTHROW( expression )
- REQUIRE_NOTHROW( expression )

- CHECK_THROWS( expression )
- REQUIRE_THROWS( expression )

- CHECK_THROWS_AS( exception, expression )
- REQUIRE_THROWS_AS( exception type, expression )

Expects that an exception of the specified type is thrown during evaluation of the expression.

### Compile-time Configuration

Macros need to be defined before including the header file.

#### Generating default main function

```c++
#define AYTESTM_CONFIG_MAIN
```

This option can be used to generate a main function automatically.

#### Disabling ANSI color

```c++
#define AYTESTM_DISABLE_ANSI_COLOR
```

This option can be used to disable the output of ANSI color code.

#### Disabling testing macros 

```c++
#define AYTESTM_DISABLE_TEST_MACRO
```

This option can be used to disable the testing macros.

### More

Maybe you can read [Catch2 documentation](https://catch2-temp.readthedocs.io/en/latest/index.html) instead.

## Friendship Link

- [AyTest](https://github.com/NoEvaa/AyTest)

- [catch2](https://github.com/catchorg/Catch2)

- [doctest](https://github.com/doctest/doctest)

- [googletest](https://github.com/google/googletest)

## Authors

- [@NoEvaa](https://github.com/NoEvaa)

## License

[MIT](LICENSE)

