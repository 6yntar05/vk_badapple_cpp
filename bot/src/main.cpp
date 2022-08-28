#include "commands/badapple.hpp"

#include "message_handler.hpp"

#include "cpp_vk_lib/vk/config/config.hpp"
#include "cpp_vk_lib/vk/long_poll/long_poll.hpp"
#include "cpp_vk_lib/runtime/setup_logger.hpp"

#include "spdlog/spdlog.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./vk_badapple_cpp <config.json>" << std::endl;
        exit(-1);
    }

    using namespace bot;
    vk::config::load(argv[1]);
    runtime::setup_logger(spdlog::level::level_enum::trace);
    spdlog::info("workers: {}", vk::config::num_workers());

    bot::message_handler msg_handler;
    msg_handler.on_command("/badapple", bot::command::badapple);
    asio::io_context io_ctx;
    vk::long_poll api(io_ctx);
    api.on_event(vk::event::type::message_new, [&msg_handler](const vk::event::common& event) {
        msg_handler.process(event.get_message_new());
    });
    api.run();
}
