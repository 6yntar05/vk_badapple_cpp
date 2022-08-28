#ifndef BOT_UTILS_STRING_UTILS_H
#define BOT_UTILS_STRING_UTILS_H

#include <string>

namespace bot {
namespace string_util {

std::string cut_first(std::string_view str);
std::string get_first(std::string_view str);

}// namespace string_util
}// namespace bot

#endif// BOT_UTILS_STRING_UTILS_H
