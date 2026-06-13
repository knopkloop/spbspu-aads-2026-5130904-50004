#ifndef IOGUARD_HPP
#define IOGUARD_HPP

#include <ios>

namespace haliullin::detail
{
  class IOGuard
  {
  public:
    IOGuard(std::basic_ios< char >& s):
      s_(s),
      precision_(s.precision()),
      width_(s.width()),
      fmt_(s.flags()),
      fill_(s.fill())
    {}

    ~IOGuard()
    {
      s_.precision(precision_);
      s_.width(width_);
      s_.flags(fmt_);
      s_.fill(fill_);
    }

  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags fmt_;
    char fill_;
  };
}

#endif
