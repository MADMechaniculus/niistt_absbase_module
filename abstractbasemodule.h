#ifndef ABSTRACTBASEMODULE_H
#define ABSTRACTBASEMODULE_H

#include "typeimpls.h"
#include "telemetryflow.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

class AbstractBaseModule
{
protected:
    boost::uuids::uuid identifier;
    std::queue<taskPh_t> taskQueue;
    std::mutex queueMx;
    std::atomic<bool> stopFlag{false};

    /**
     * @brief Указатель на телеметрический поток, куда будет скидываться вся телеметрия модуля
     */
    TelemetryFlow * tlmFlow{nullptr};

    /**
     * @brief Обработка запросов в очереди запросов приложения
     */
    void processQueue(int err);

    /**
     * @brief Метод добавления сообщения в поток телеметрии для учёта состояния указателя на поток телеметрии
     * @param message Сообщения модуля
     */
    void eFlow(std::string message);

public:
    /**
     * @brief Конструктор модуля
     */
    AbstractBaseModule();
    
    /**
     * @brief Виртуальный дестркутор для безопасностиы
     */
    virtual ~AbstractBaseModule() {}

    /**
     * @brief Процедура инициализации модуля
     * @return Код выполнения операции
     */
    virtual int init() = 0;

    /**
     * @brief Главная функция модуля
     * @return Код выполнения операции
     */
    virtual int start() = 0;

    /**
     * @brief Процедура деинициализации
     * @return Код выполнения операции
     */
    virtual int deinit() = 0;

    /**
     * @brief Прерывание работы модуля
     */
    void stop();

    /**
     * @brief Проверка состояния модуля
     * @return True - остановлен, false - нет
     */
    bool isStoped(void) const;

    /**
     * @brief Добавление задачи для приложения в очередь задач
     * @param func Задача для приложения
     * @return Future на результат выполнения задачи
     */
    std::future<void> pushTask(std::function<void()> &&func);

    /**
     * @brief Связыание модуля с потоком телеметрии
     * @param ptr Указатель на поток телеметрии
     */
    void connectTlmFlow(TelemetryFlow * ptr);

    /**
     * @brief Получение идентификатора модуля
     * @return UUID
     */
    const boost::uuids::uuid & getId(void);

};

#endif // ABSTRACTBASEMODULE_H
