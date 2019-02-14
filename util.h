#ifndef YT_UTIL_H
#define YT_UTIL_H

#include <regex>
#include <string_view>

namespace yt {
const std::regex DATE_REGEX{
  "\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}(?:.\\d{3})?Z"};

inline bool check_date(std::string_view date_str) {
  return std::regex_match(date_str.begin(), date_str.end(), DATE_REGEX);
}


// BITMASK OPERATORS FOR ENUMS

template<typename Enum>
struct EnableBitMaskOperators {
  static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator|(Enum lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(static_cast<underlying>(lhs) |
                           static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator&(Enum lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(static_cast<underlying>(lhs) &
                           static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator^(Enum lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(static_cast<underlying>(lhs) ^
                           static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator~(Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  return static_cast<Enum>(~static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator|=(Enum& lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  lhs = static_cast<Enum>(static_cast<underlying>(lhs) |
                          static_cast<underlying>(rhs));

  return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator&=(Enum& lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  lhs = static_cast<Enum>(static_cast<underlying>(lhs) &
                          static_cast<underlying>(rhs));

  return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator^=(Enum& lhs, Enum rhs) {
  static_assert(std::is_enum<Enum>::value,
                "Template parameter is not an enum");

  using underlying = typename std::underlying_type<Enum>::type;

  lhs = static_cast<Enum>(static_cast<underlying>(lhs) ^
                          static_cast<underlying>(rhs));

  return lhs;
}

#define ENABLE_BITMASK_OPERATORS(x)             \
  template<>                                    \
  struct EnableBitMaskOperators<x>              \
  {                                             \
    static const bool enable = true;            \
  };

// END OF BITMASK OPERATORS FOR ENUMS

}


#endif // YT_UTIL_H
