#include <chrono>
#include <iostream>
#include <thread>

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>


using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

class ServerProcess : public process::Process<ServerProcess> {

public:

  ServerProcess() : ProcessBase("server") {}

 void initialize() {
  route(
      "/logout",
      "logout from server",
      [this] (Request request) {
        this->logout_server();
        return OK("Logged out, can't access the endpoint       ");
  });

 }

  Future<bool> disconnected() {
    cout << "Shall we disconnect? " << endl;
    return shouldQuit.future();
  }

  void logout_server() {
    cout << "Logging out from server..." << endl;
    this->shouldQuit.set(true);
  }
private:
  Promise<bool> shouldQuit;
};

int main() {
  
  int retCode;
  ServerProcess simpleProcess;
  
  // Initialize libprocess
  //process::initialize("server"); //Not required if constructor is inherited with ProcessBase("server")
  
  process::PID<ServerProcess> pid = process::spawn(simpleProcess);

  cout << "Running Server on http://" << process::address().ip << ":"
       << process::address().port << "/server" << endl
       << "Use /logout to terminate server..." << endl;
  cout << "Waiting for it to terminate..." << endl;

  Future<bool> disconnect  = simpleProcess.disconnected();
  disconnect.await();

  // wait for the server to complete the request
  std::this_thread::sleep_for(seconds(2));

  if (!disconnect.get()) {
    cerr << "The server encountered an error and is exiting now" << endl;
    retCode = EXIT_FAILURE;
  } else {
    cout << "Disconnected" << endl;
    retCode = EXIT_SUCCESS;
  }
  cout << "retCode = " << retCode <<endl;

  process::terminate(simpleProcess);
  process::wait(simpleProcess);

  return 0;
}
 