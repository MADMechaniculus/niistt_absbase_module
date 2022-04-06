#include "telemetryflow.h"


TelemetryFlow::TelemetryFlow() {
    this->empty.store(msgQueue.empty());
}

bool TelemetryFlow::isEmpty() const {
    return empty;
}

TelemetryMessage TelemetryFlow::dequeue() {
    boost::lock_guard<boost::mutex>(this->queueMx);
    if (empty)
        throw std::runtime_error("Flow queue is empty");
    TelemetryMessage msg(this->msgQueue.front());
    this->msgQueue.pop();
    empty.store(this->msgQueue.empty());
    return msg;
}

void TelemetryFlow::enqueue(TelemetryMessage &msg) {
    boost::lock_guard<boost::mutex>(this->queueMx);
    this->msgQueue.emplace(msg);
    empty.store(this->msgQueue.empty());
}

void TelemetryFlow::enqueue(TelemetryMessage &&msg) {
    boost::lock_guard<boost::mutex>(this->queueMx);
    this->msgQueue.push(msg);
    empty.store(this->msgQueue.empty());
}
