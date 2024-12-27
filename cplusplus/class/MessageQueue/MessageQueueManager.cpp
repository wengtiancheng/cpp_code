#include "MessageQueueManager.h"
#include <algorithm>

// Message 类的实现

Message::Message(const char *d, int p) {
    // TODO: Task 1-1
    this->data = new char[strlen(d) + 1];
    memcpy(data, d, sizeof(char) * (strlen(d) + 1));
    this->priority = p;
}

Message::Message(Message &&other) noexcept {
    // TODO: Task 1-2
    data = other.data;
    priority = other.priority;
    other.data = nullptr;
}

Message &Message::operator=(Message &&other) noexcept {
    // TODO: Task 1-2
    if(this != &other) {
        delete[] data;
        data = other.data;
        priority = other.priority;
        other.data = nullptr;
    }
    return *this;
}

Message::~Message() {
    delete[] data;
}

// MessageQueueManager 类的实现
MessageQueueManager::MessageQueueManager() {}

void MessageQueueManager::addMessage(Message m) {
    // TODO: Task 2

    auto it = std::find_if(messages.begin(), messages.end(), [&m](const Message& message) {
        return m.priority < message.priority;
    });
    messages.insert(it, std::move(m));
}

MessageQueueManager::MessageQueueManager(MessageQueueManager &&other) noexcept {
    // TODO: Task 3-1
    messages = std::move(other.messages);
}

MessageQueueManager &
MessageQueueManager::operator=(MessageQueueManager &&other) noexcept {
    // TODO: Task 3-2
    if(this != &other) {
        messages.clear();
        messages = std::move(other.messages);

    }
    return *this;
}

void MessageQueueManager::printMessages() const {
    for (const auto &msg : messages) {
        std::cout << "Message: " << msg.data << ", Priority: " << msg.priority
                  << std::endl;
    }
}

MessageQueueManager::~MessageQueueManager() {
    std::cout << "Destructing MessageQueueManager" << std::endl;
}