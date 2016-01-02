/**
 * Support the detection of Nvidia GPGPUs
 * author: Raymond Tay
 * date  : 26 August 2015
 */

#include <mesos/mesos.hpp>
#include <mesos/module.hpp>

#include <mesos/module/isolator.hpp>

#include <mesos/slave/isolator.hpp>

#include <stout/try.hpp>

#include "slave/containerizer/isolators/posix.hpp"
#include "slave/flags.hpp"

using namespace mesos;

using mesos::internal::slave::Flags;
using mesos::internal::slave::PosixCpuIsolatorProcess;
using mesos::internal::slave::PosixMemIsolatorProcess;

using mesos::slave::Isolator;


// The sole purpose of this function is just to exercise the
// compatibility logic.
static bool compatible()
{
  return true;
}


static Isolator* createGpuIsolator(const Parameters& parameters)
{
  Flags flags;
  Try<Isolator*> result = PosixCpuIsolatorProcess::create(flags);
  if (result.isError()) {
    return NULL;
  }
  return result.get();
}


// Declares a GPU Isolator module named 'org_apache_mesos_TestGpuIsolator'.
mesos::modules::Module<Isolator> org_apache_mesos_TestGpuIsolator(
    MESOS_MODULE_API_VERSION,
    MESOS_VERSION,
    "Apache Mesos",
    "modules@mesos.apache.org",
    "Test GPU Isolator module.",
    compatible,
    createGpuIsolator);
