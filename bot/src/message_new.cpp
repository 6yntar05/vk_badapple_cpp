#include "message_handler.hpp"

#include "cpp_vk_lib/runtime/string_utils/implementation/split.hpp"

#include "spdlog/spdlog.h"

void bot::message_handler::process(vk::event::message_new&& event) const
{
    spdlog::info("Message event: {} from {}", event.text(), event.peer_id());

    const std::string command = string_util::get_first(event.text());
    if (!event.has_action() && commands_.find(command) != commands_.end()) {
        commands_.at(command)(
            event,
            runtime::string_utils::whitespace_split(string_util::cut_first(event.text())));
    }
}

bot::message_handler& bot::message_handler::on_command(std::string_view trigger, const command_callback_t& callback)
{
    commands_.emplace(trigger, callback);
    return *this;
}