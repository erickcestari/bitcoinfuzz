#define _GNU_SOURCE
#include <dlfcn.h>
#include <span>
#include <stdexcept>

#include "module.h"

namespace bitcoinfuzz {
namespace module {

// Function pointer types
typedef bool (*descriptor_parse_fn)(const char *);
typedef bool (*miniscript_parse_fn)(const char *);

// Static members to hold library handle and function pointers
static void *lib_handle = nullptr;
static descriptor_parse_fn rust_descriptor_parse = nullptr;
static miniscript_parse_fn rust_miniscript_parse = nullptr;

Rustminiscript::Rustminiscript(void) : BaseModule("Rustminiscript") {
  if (lib_handle == nullptr) {
    // Load library with RTLD_LOCAL to keep symbols private.
    // Symbol isolation works because cdylib statically links dependencies.
    lib_handle = dlopen("./librust_miniscript_lib.so", RTLD_NOW | RTLD_LOCAL);
    if (!lib_handle) {
      throw std::runtime_error(std::string("dlopen failed: ") + dlerror());
    }

    // Load function pointers
    rust_descriptor_parse =
        (descriptor_parse_fn)dlsym(lib_handle, "rust_miniscript_descriptor_parse");
    if (!rust_descriptor_parse) {
      dlclose(lib_handle);
      lib_handle = nullptr;
      throw std::runtime_error(
          std::string("dlsym rust_miniscript_descriptor_parse failed: ") +
          dlerror());
    }

    rust_miniscript_parse =
        (miniscript_parse_fn)dlsym(lib_handle, "rust_miniscript_miniscript_parse");
    if (!rust_miniscript_parse) {
      dlclose(lib_handle);
      lib_handle = nullptr;
      throw std::runtime_error(
          std::string("dlsym rust_miniscript_miniscript_parse failed: ") +
          dlerror());
    }
  }
}

std::optional<bool> Rustminiscript::descriptor_parse(std::string str) const {
  // Skip some descriptors
  if ((str.find("raw") != std::string::npos) ||
      (str.find("combo") != std::string::npos))
    return std::nullopt;
  return rust_descriptor_parse(str.c_str());
}

std::optional<bool> Rustminiscript::miniscript_parse(std::string str) const {
  return rust_miniscript_parse(str.c_str());
}

} // namespace module
} // namespace bitcoinfuzz
