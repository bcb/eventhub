#include "topic.hpp"
#include "common.hpp"
#include "connection.hpp"
#include "websocket_response.hpp"
#include <memory>
#include <string>

using namespace std;

namespace eventhub {
void Topic::addSubscriber(std::shared_ptr<Connection>& conn) {
  std::lock_guard<std::mutex> lock(_subscriber_lock);

  _subscriber_list.push_back(weak_ptr<Connection>(conn));
  DLOG(INFO) << "Connection " << conn->getIP() << " subscribed to " << _id;
}

void Topic::publish(const string& data) {
  for (auto wptr_subscriber : _subscriber_list) {
    auto subscriber = wptr_subscriber.lock();

    if (!subscriber) {
      continue;
    }

    DLOG(INFO) << "Publish " << data;
    WebsocketResponse ws_frame(data);
    subscriber->write(ws_frame.ws_format());
  }
}

size_t Topic::garbageCollect() {
  std::lock_guard<std::mutex> lock(_subscriber_lock);

  for (auto it = _subscriber_list.begin(); it != _subscriber_list.end();) {
    if (!it->lock()) {
      it = _subscriber_list.erase(it);
    } else {
      it++;
    }
  }

  return _subscriber_list.size();
}
} // namespace eventhub
