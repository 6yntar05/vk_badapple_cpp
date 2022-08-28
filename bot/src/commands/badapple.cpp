#include <iostream>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>

#include "commands/badapple.hpp"

#include "cpp_vk_lib/vk/events/message_new.hpp"
#include "cpp_vk_lib/vk/methods/basic.hpp"
#include "cpp_vk_lib/vk/methods/message_constructor.hpp"
#include "cpp_vk_lib/vk/methods/constructor.hpp"
#include "simdjson.h"
#include "spdlog/spdlog.h"

// Video rasterization properties
int size_x=20, size_y=15;
std::vector<std::string> symbols {"⬛","◾","▫️","▫️","◽","⬜"};
int denominator = (255/symbols.size()) + 1;

std::ostringstream stream_frame;
std::string json_feedback;
simdjson::dom::parser parser;
simdjson::dom::element element;
bool remains_edit = false;
bool fail = false;
int msg_id;

std::string send(int64_t peer_id, std::string_view text, bool mentions_flag) {
    spdlog::trace(
        "call messages::send: peer_id={}, text={}, mentions_flag={}",
        peer_id,
        text,
        mentions_flag);

    return vk::method::group_constructor()
        .method("messages.send")
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .param("random_id", "0")
        .perform_request();
}

std::string edit(int64_t peer_id, std::string_view text, int msg_id, bool mentions_flag) {
    spdlog::trace(
        "call messages::send: peer_id={}, text={}, mentions_flag={}",
        peer_id,
        text,
        mentions_flag);

    return vk::method::group_constructor()
        .method("messages.edit")
        .param("message_id", std::to_string(msg_id))
        .param("peer_id", std::to_string(peer_id))
        .param("message", text)
        .param("random_id", "0")
        .perform_request();
}

namespace bot {

void command::badapple(const vk::event::message_new& event, const std::vector<std::string_view>&) {

    bool ret;
    cv::VideoCapture capture;
    cv::Mat frame;
    std::string path = "./badapple.webm";
    int skip_frames = 20;

    capture.open(path);
    if (!capture.isOpened()) {
        std::cerr << "[ERROR] Unnable to open badapple video!\n";
    }

    while (true) {
        auto start_time = std::chrono::steady_clock::now();

        ret = capture.read(frame);
        if (!ret || frame.empty()) {
            std::cerr << "Failed to grab frame\n";
            break;
        }
        cv::resize(frame, frame, cv::Size(size_x, size_y), 0, 0, false);
        // Construct image
        for (int x=0; x<size_y; x++){
            for (int y=0; y<size_x; y++) {
                stream_frame << symbols[ (ushort)frame.at<cv::Vec3b>(x,y)[0] / denominator ];
            }; stream_frame << std::endl;
        }

        if (!remains_edit) {
            // Send msg first
            json_feedback = send(event.peer_id(), stream_frame.str(), 1);
            std::cerr << json_feedback << std::endl;
            element = parser.parse(json_feedback);
            msg_id = element["response"].get_int64();
            if (!fail)
                // If not first, continue send by frames
                remains_edit = true;

        } else {
            json_feedback = edit(event.peer_id(), stream_frame.str(), msg_id, 1);
            std::cerr << json_feedback << std::endl;
            element = parser.parse(json_feedback);

            try {
                // If error_code = 9 => spam control
                int cap = element["error"]["error_code"].get_int64();
                if (cap == 9) {
                    // Continue send by frames
                    remains_edit = false;
                    fail = true;
                }
            } catch (simdjson::simdjson_error& e) {
                // No errors
                std::cout << e.error() << std::endl;
            }

        }

        // Clear frame
        stream_frame.str("");
        stream_frame.clear();

        // Skip frame and fit frametime
        for (int i=0; i<skip_frames; i++) {
            capture.read(frame);
        }
        auto stop_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);
        std::this_thread::sleep_for(std::chrono::milliseconds((34 * (1+skip_frames)) - elapsed_ns.count()));
    }

}

}// namespace bot
