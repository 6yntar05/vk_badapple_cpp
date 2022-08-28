#ifndef BOT_MESSAGE_HANDLER_HPP
#define BOT_MESSAGE_HANDLER_HPP

#include "string_utils.hpp"

#include "cpp_vk_lib/vk/events/message_new.hpp"

#include <map>
#include <functional>

namespace bot {

class message_handler
{
    using command_callback_t = std::function<void(const vk::event::message_new&, const std::vector<std::string_view>&)>;

public:
    void process(vk::event::message_new&& event) const;

    message_handler& on_command(std::string_view trigger, const command_callback_t& callback);

private:
    std::map<std::string, command_callback_t> commands_{};
};

}// namespace bot

#endif// BOT_MESSAGE_HANDLER_HPP