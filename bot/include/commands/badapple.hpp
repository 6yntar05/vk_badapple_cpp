#ifndef BOT_COMMANDS_HELLO_WORLD_HPP
#define BOT_COMMANDS_HELLO_WORLD_HPP

#include <vector>
#include <string>

namespace vk::event {
class message_new;
}// namespace vk::event

namespace bot::command {

void badapple(const vk::event::message_new& event, const std::vector<std::string_view>& args);

}// namespace bot::command

#endif //BOT_COMMANDS_HELLO_WORLD_HPP
