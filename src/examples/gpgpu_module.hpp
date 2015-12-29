/**
 * GPGPU module
 */

#ifndef __GPGPU_MODULE_HPP__
#define __GPGPU_MODULE_HPP__

#include <mesos/mesos.hpp>
#include <mesos/module.hpp>

#include <stout/nothing.hpp>
#include <stout/try.hpp>

// Each module "kind" has a base class associated with it that is
// inherited by the module instances.  Mesos core uses the base
// class interface to bind with the module instances.
// GpGpuModule is a base class for the "GpGpuModule" kind.
class GpGpuModule
{
public:
  GpGpuModule() {}

  // Mesos core will use the base class pointer to delete the module
  // instance (which is a derived object).  The virtual destructor
  // here ensures that the derived destructor is called for any
  // cleanup that may be required for the derived object.
  virtual ~GpGpuModule() {}

  virtual Try<Nothing> initialize(const mesos::Parameters& parameters) = 0;

  virtual int foo(char a, long b) = 0;

  virtual int bar(float a, double b) = 0;

  virtual int baz(int a, int b) = 0;
};


namespace mesos {
namespace modules {

template <>
inline const char* kind<GpGpuModule>()
{
  return "Isolator"; // @see src/module/manager.cpp for symbol: kindToVersion
}


template <>
struct Module<GpGpuModule> : ModuleBase
{
  Module(
      const char* _moduleApiVersion,
      const char* _mesosVersion,
      const char* _authorName,
      const char* _authorEmail,
      const char* _description,
      bool (*_compatible)(),
      GpGpuModule* (*_create)(const Parameters& parameters))
    : ModuleBase(
        _moduleApiVersion,
        _mesosVersion,
        mesos::modules::kind<GpGpuModule>(),
        _authorName,
        _authorEmail,
        _description,
        _compatible),
      create(_create) {}

  GpGpuModule* (*create)(const Parameters& parameters);
};

} // namespace modules {
} // namespace mesos {

#endif // __GPGPU_MODULE_HPP__
