#include "telemetrytypes.h"


TelemetryMessage::TelemetryMessage(boost::posix_time::ptime timestamp, std::string message) : \
    timeStamp(timestamp), msg(message) {}

TelemetryMessage::TelemetryMessage(const TelemetryMessage &msg) {
    this->msg = msg.msg;
    this->timeStamp = msg.timeStamp;
}

TelemetryMessage TelemetryMessage::createMessage(std::string msg) {
    return TelemetryMessage(boost::posix_time::second_clock::local_time(), msg);
}

std::string TelemetryMessage::stringify() {
    std::ostringstream time;
    time << this->timeStamp;
    std::string ret = "[" + time.str() + "] -> " + this->msg;
    return ret;
}
