#include <iostream>
#include <mesos/executor.hpp>
#include <chrono>
#include <thread>
#include <stout/duration.hpp>
#include <stout/os.hpp>

using namespace mesos;

using std::cout;
using std::endl;
using std::string;


class CliExecutor : public Executor
{
public:
  virtual ~CliExecutor() {}

  virtual void registered(ExecutorDriver* driver,
                          const ExecutorInfo& executorInfo,
                          const FrameworkInfo& frameworkInfo,
                          const SlaveInfo& slaveInfo)
  {
    cout << "Registered UNIX CLI executor on " << slaveInfo.hostname() << endl;
  }

  virtual void reregistered(ExecutorDriver* driver,
                            const SlaveInfo& slaveInfo)
  {
    cout << "Re-registered UNIX CLI executor on " << slaveInfo.hostname() << endl;
  }

  virtual void disconnected(ExecutorDriver* driver) {}

  virtual void launchTask(ExecutorDriver* driver, const TaskInfo& task)
  {
    cout << "Starting UNIX CLI task " << task.task_id().value() << endl;

    TaskStatus status;
    status.mutable_task_id()->MergeFrom(task.task_id());
    status.set_state(TASK_RUNNING);

    driver->sendStatusUpdate(status);

    // This is where one would perform the requested task.
    sleepFor(5);

    cout << "Finishing task " << task.task_id().value() << endl;

    status.mutable_task_id()->MergeFrom(task.task_id());
    status.set_state(TASK_FINISHED);

    driver->sendStatusUpdate(status);
  }

  void sleepFor(int time) {
    auto start = std::chrono::high_resolution_clock::now();
    std::chrono::seconds sec(time);
    std::this_thread::sleep_for(sec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";
  }

  virtual void killTask(ExecutorDriver* driver, const TaskID& taskId) {}
  virtual void frameworkMessage(ExecutorDriver* driver, const string& data) {}
  virtual void shutdown(ExecutorDriver* driver) {}
  virtual void error(ExecutorDriver* driver, const string& message) {}
};


int main(int argc, char** argv)
{
  CliExecutor executor;
  MesosExecutorDriver driver(&executor);
  return driver.run() == DRIVER_STOPPED ? 0 : 1;
}
