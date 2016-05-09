#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>

using namespace std;
using namespace process;
using namespace process::http;
using std::string;


class MyProcess : public Process<MyProcess>
{
public:
  MyProcess() {}
  virtual ~MyProcess() {}

  Future<Nothing> doSomething(const std::string msg)
  {
    std::cout << "Wrapping message: " << msg << std::endl;
    return Nothing();
  }

  Future<int> calc(int lhs, int rhs)
  {
    return Promise<int>(lhs + rhs).future();
  }

private:
  Promise<bool> shouldQuit;
};

int main(int argc, char** argv)
{
  MyProcess process;
  PID<MyProcess> pid = spawn(&process);
  cout <<"process is created #1, " << pid << endl;

  process::dispatch(pid, &MyProcess::doSomething, "test test test");

  MyProcess proc1;
  PID<MyProcess> pid1 = spawn(&proc1);
  cout << "proc is created #2, " << pid1 << endl;

 // Future<int> sum = process::dispatch(pid1, &MyProcess::calc, 99, 101);
  //sum.then([](int n) {
  process::dispatch(pid1, &MyProcess::calc, 99, 101)
  .then([](int n) {
    cout << "99 + 101 = " << n << endl;
    return Nothing();
  });

  //wait(pid);
  cout << "pid is waiting" << endl;
  //wait(pid1);
  cout << "pid1 is waiting" << endl;
 
 return 0;
}
