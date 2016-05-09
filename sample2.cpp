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

  void set_Promise(int val)
  {
    p.set(val);
    cout<< "Value set" << endl;
  }

  Future<int> factorial( )
  {

     int res=1;
     int N =  print_promise().get();
     for(int i=1; i<=N; i++)
     res*=i;
     cout<<"Result is:" << res <<endl;

   return Promise<int>(res).future();
  }

  Future<int> print_promise()
  {
     return p.future();
  }

private:

  Promise<int> p;

};

int main()
{
  MyProcess myprocess;

  PID<MyProcess> myp_pid = spawn(&myprocess);
  cout <<"myprocess is created...... " << myp_pid << endl;

   process::dispatch(myp_pid, &MyProcess::set_Promise, 4);

   Future<int> f = process::dispatch(myp_pid, &MyProcess::print_promise);
   cout <<"Promise set : = " << f.get() << endl;

  Future<int> res =  process::dispatch(myp_pid, &MyProcess::factorial);
  // process::dispatch(myp_pid, &MyProcess::set_Promise, 4);
  cout <<" res is = " << res.get() << endl;

  return 0;

}
