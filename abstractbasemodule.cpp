#include "abstractbasemodule.h"

AbstractBaseModule::AbstractBaseModule() : identifier(boost::uuids::random_generator()())
{
}

void AbstractBaseModule::stop()
{
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

std::future<void> AbstractBaseModule::pushTask(\
        std::function<void ()> &&func) {
    std::future<void> ret;
    std::lock_guard<std::mutex>(this->queueMx);
    if (this->taskQueue.size() < 100) {
        std::promise<void> prm;
        ret = prm.get_future();
        this->taskQueue.emplace(std::move(prm), func);
    }
    return ret;
}

void AbstractBaseModule::connectTlmFlow(TelemetryFlow *ptr) {
    this->tlmFlow = ptr;
}
