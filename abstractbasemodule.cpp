#include "abstractbasemodule.h"

AbstractBaseModule::AbstractBaseModule() : identifier(boost::uuids::random_generator()())
{
}

void AbstractBaseModule::stop()
{
    this->eFlow("Module " + boost::uuids::to_string(this->identifier) + " has stopped");
    this->stopFlag.store(true);
}

bool AbstractBaseModule::isStoped() const {
    return this->stopFlag;
}

void AbstractBaseModule::processQueue(int err) {
    if (err == 0) {
        try {
            if (!this->taskQueue.empty()) {
                std::lock_guard<std::mutex>(this->queueMx);
                this->taskQueue.front().second();
                this->taskQueue.front().first.set_value();
                this->taskQueue.pop();
            }
        }  catch (std::exception & ex) {
            this->taskQueue.front().first.set_exception(\
                        std::make_exception_ptr(ex));
        }
    } else {
        this->taskQueue.front().first.set_exception(\
                    std::make_exception_ptr(\
                        std::runtime_error("Module extern error")\
                        )\
                    );
    }
}

void AbstractBaseModule::eFlow(std::string message) {
    if (this->tlmFlow != nullptr) {
        this->tlmFlow->enqueue(TelemetryMessage::createMessage(message));
    }
}

std::future<void> AbstractBaseModule::pushTask(\
        std::function<void ()> &&func) {
    std::future<void> ret;
    std::lock_guard<std::mutex>(this->queueMx);
    if (this->taskQueue.size() < 100) {
        std::pair<std::promise<void>, std::function<void()>> temp;
        ret = temp.first.get_future();
        temp.second = func;
        this->taskQueue.push(std::move(temp));
    }
    return ret;
}

void AbstractBaseModule::connectTlmFlow(TelemetryFlow *ptr) {
    this->tlmFlow = ptr;
}

const boost::uuids::uuid &AbstractBaseModule::getId() {
    return this->identifier;
}
