//
// Created by zck on 2024/9/1.
//

#ifndef LOG_H
#define LOG_H



#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/attributes/timer.hpp>
#include <cstdio>

void init_logging();



#define LOG_INFO(format, ...)   \
do{                        \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), format, ##__VA_ARGS__); \
    BOOST_LOG_TRIVIAL(info) << buffer << " " <<  __FILE__  << ":" << __LINE__; \
}while(0)


#endif //LOG_H
