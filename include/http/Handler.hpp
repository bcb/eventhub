#ifndef INCLUDE_HTTP_HANDLER_HPP_
#define INCLUDE_HTTP_HANDLER_HPP_

#include <memory>
#include <string>

#include "Connection.hpp"
#include "ConnectionWorker.hpp"
#include "HandlerContext.hpp"
#include "TopicManager.hpp"
#include "http/Parser.hpp"
#include "http/Response.hpp"

namespace eventhub {
namespace http {

class Handler final {
public:
  static void HandleRequest(HandlerContext&& ctx, Parser* req, RequestState reqState);

private:
  Handler() {}
  ~Handler() {}

  static void _handlePath(HandlerContext& ctx, Parser* req);
  static bool _websocketHandshake(HandlerContext& ctx, Parser* req);
  static void _badRequest(HandlerContext& ctx, const std::string reason, int statusCode = 400);
  static void _setCorsHeaders(Parser* req, Response& resp);
};

} // namespace http
} // namespace eventhub

#endif // INCLUDE_HTTP_HANDLER_HPP_
