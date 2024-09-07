//
// Created by zck on 2024/9/1.
//

#include "log.h"


void init_logging()
{
    // Set up logging to a file
    boost::log::add_file_log
    (
        boost::log::keywords::file_name = "sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024, // Rotate logs when they reach 10 MB
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0), // Rotate logs every day at midnight
        boost::log::keywords::format = "[%TimeStamp%]: %Message%" // Log format
    );

    // Set up logging to the console
    boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%]: %Message%");

    // Add common attributes like timestamp
    boost::log::add_common_attributes();
}
