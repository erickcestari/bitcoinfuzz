#define _GNU_SOURCE
#include <dlfcn.h>
#include <span>
#include <stdexcept>

#include "module.h"

namespace bitcoinfuzz {
namespace module {

// Function pointer type
typedef bool (*descriptor_parse_fn)(const char *);

// Static members to hold library handle and function pointer
static void *lib_handle = nullptr;
static descriptor_parse_fn tiny_descriptor_parse = nullptr;

Tinyminiscript::Tinyminiscript(void) : BaseModule("Tinyminiscript") {
  if (lib_handle == nullptr) {
    // Load library with RTLD_LOCAL to keep symbols private.
    // Symbol isolation works because cdylib statically links dependencies.
    lib_handle = dlopen("./libtiny_miniscript_lib.so", RTLD_NOW | RTLD_LOCAL);
    if (!lib_handle) {
      throw std::runtime_error(std::string("dlopen failed: ") + dlerror());
    }

    // Load function pointer
    tiny_descriptor_parse =
        (descriptor_parse_fn)dlsym(lib_handle, "tiny_miniscript_descriptor_parse");
    if (!tiny_descriptor_parse) {
      dlclose(lib_handle);
      lib_handle = nullptr;
      throw std::runtime_error(
          std::string("dlsym tiny_miniscript_descriptor_parse failed: ") +
          dlerror());
    }
  }
}

std::optional<bool> Tinyminiscript::descriptor_parse(std::string str) const {
  return tiny_descriptor_parse(str.c_str());
}

} // namespace module
} // namespace bitcoinfuzz
