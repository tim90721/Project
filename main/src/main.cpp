#include <stdlib.h>
#include <QApplication>

#include "mainGUI.h"
#include "includefile.h"
#include "include_log.h"

void initialize_log(){
    try{
        auto console_log = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_log->set_level(spdlog::level::info);
        console_log->set_pattern("[Project-Logging] [%@] [ %^%l%$ ] %v");

        auto trace_log = std::make_shared<spdlog::sinks::basic_file_sink_mt>("./log/trace_log.log", true);
        trace_log->set_level(spdlog::level::trace);
        trace_log->set_pattern("[%Y-%m-%d %T] [Project-Logging] [%@] [ %^%l%$ ] %v");

        auto debug_log = std::make_shared<spdlog::sinks::basic_file_sink_mt>("./log/debug_log.log", true);
        debug_log->set_level(spdlog::level::debug);
        debug_log->set_pattern("[Project-Logging] [%@] [ %^%l%$ ] %v");

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(console_log);
        sinks.push_back(trace_log);
        sinks.push_back(debug_log);

        auto combined = std::make_shared<spdlog::logger>("multi sinks", begin(sinks), end(sinks));
        combined->set_level(spdlog::level::trace);
        spdlog::register_logger(combined);

        spdlog::set_default_logger(combined);
        SPDLOG_TRACE("start logging");
    }
    catch(const spdlog::spdlog_ex& ex){
        printf("log initialization failed\n");
        abort();
    }
}

int main(int argc, char *argv[]){
    initialize_log();
    QApplication a(argc, argv);
    MainGUI gui;
    gui.move(100, 100);
    gui.show();
    return a.exec();
}
