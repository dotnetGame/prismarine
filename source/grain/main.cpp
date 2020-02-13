// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "thrift-gen/CallService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace prismarine;

class CallServiceHandler : virtual public CallServiceIf {
 public:
  CallServiceHandler() {
    // Your initialization goes here
  }

  void call(ReturnItem& _return, const std::vector<ValueItem> & params) {
    // Your implementation goes here
    printf("call\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<CallServiceHandler> handler(new CallServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new CallServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
