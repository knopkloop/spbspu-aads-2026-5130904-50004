#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include "AppCore.hpp"

namespace haliullin
{
  class FileManager
  {
  public:
    static void save(const std::string& filename, const AppCore& core);
    static AppCore load(const std::string& filename);
  };
}

#endif
