include_directories(
    ${LW_BIG_INCLUDE_DIRS}
    )

add_library(${LW_BIG_LIBRARIES}
    # bignum_converter.cpp
    bignum.cpp
    
    ${LW_BIG_INCLUDE_DIRS}/bignum.hpp
    ${LW_BIG_INCLUDE_DIRS}/bignum_defs.hpp
    ${LW_BIG_INCLUDE_DIRS}/bignum_converter.hpp
)