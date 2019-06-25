#ifndef EVENTHUB_WEBSOCKET_HANDLER_HPP
#define EVENTHUB_WEBSOCKET_HANDLER_HPP

#include "connection.hpp"
#include "connection_worker.hpp"
#include "websocket_request.hpp"
#include <memory>

namespace eventhub {
class WebsocketHandler {
public:
  static void parse(std::shared_ptr<Connection>& conn, char* buf, size_t n_bytes);

private:
  WebsocketHandler(){};
  ~WebsocketHandler(){};

  static void _handleDataFrame(std::shared_ptr<Connection>& conn, WebsocketRequest& req);
  static void _handleControlFrame(std::shared_ptr<Connection>& conn, WebsocketRequest& req);
};
} // namespace eventhub

#endif
