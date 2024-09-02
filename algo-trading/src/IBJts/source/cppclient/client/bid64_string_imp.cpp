#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <limits>
#include <sstream>
#include <string>
#include <cstdio>

// Define Decimal as uint64_t for simplicity
typedef uint64_t Decimal;

extern "C" Decimal __bid64_from_string(const char* str, unsigned int rounding_mode, unsigned int* status) {
    auto x = std::stod(str);
    uint64_t v = 1000*1000*1000;
    return v * x;
    // Define status codes
    const unsigned int STATUS_OK = 0;
    const unsigned int STATUS_INVALID_INPUT = 1;
    const unsigned int STATUS_OVERFLOW = 2;
    const unsigned int STATUS_UNDERFLOW = 3;

    // Check if the input string is null or empty
    if (!str || std::strlen(str) == 0) {
        if (status) *status = STATUS_INVALID_INPUT;
        return 0;
    }

    // Use strtod to convert string to double, but you can replace it with a more complex conversion if needed
    char* endPtr = nullptr;
    double value = std::strtod(str, &endPtr);

    // Check for conversion errors
    if (endPtr == str) {
        if (status) *status = STATUS_INVALID_INPUT;
        return 0;
    }

    // Apply rounding mode (simplified)
    switch (rounding_mode) {
        case 0:  // Round to nearest (simplified for this example)
            value = std::round(value);
            break;
        case 1:  // Round towards zero
            value = (value > 0) ? std::floor(value) : std::ceil(value);
            break;
        // Add more rounding modes as needed
    }

    // Check for overflow or underflow
    if (value > std::numeric_limits<Decimal>::max()) {
        if (status) *status = STATUS_OVERFLOW;
        return 0;
    } else if (value < std::numeric_limits<Decimal>::min()) {
        if (status) *status = STATUS_UNDERFLOW;
        return 0;
    }

    // If all is good, set status to OK
    if (status) *status = STATUS_OK;

    // Convert the double to a Decimal (uint64_t in this example)
    return static_cast<Decimal>(value);
}

extern "C" double __bid64_to_binary64(Decimal value, unsigned int , unsigned int*)
{
    double v = 1000.0*1000.0*1000.0;
    v = value/v;
    return v;
}

extern "C" void __bid64_to_string(char* buffer, Decimal value, unsigned int* status) {
     size_t buffer_size = 64;
    double v = 1000.0*1000.0*1000.0;
      v = value/v;
     std::snprintf(buffer, buffer_size, "%f",  v);
     return;
    // Define status codes
    const unsigned int STATUS_OK = 0;
    const unsigned int STATUS_OVERFLOW = 1;
    const unsigned int STATUS_INVALID_BUFFER_SIZE = 2;

    // Ensure the buffer is large enough
    if (buffer_size < 21) { // 20 digits for max uint64_t + 1 for null terminator
        if (status) *status = STATUS_INVALID_BUFFER_SIZE;
        return;
    }

    // Convert the Decimal (uint64_t) to a string
    std::ostringstream oss;
    oss << value;

    // Check if the conversion was successful
    if (oss.fail()) {
        if (status) *status = STATUS_OVERFLOW;
        return;
    }

    // Copy the result into the buffer, ensuring null termination
    std::string result = oss.str();
    if (result.length() >= buffer_size) {
        if (status) *status = STATUS_OVERFLOW;
        return;
    }
    std::strncpy(buffer, result.c_str(), buffer_size);

    // Set the status to OK
    if (status) *status = STATUS_OK;
}

 
 