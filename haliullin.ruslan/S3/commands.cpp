#include <stdexcept>
#include <limits>
#include <utility>
#include "commands.hpp"
#include "vector.hpp"

haliullin::Cmd::Cmd()
{
  commands_.add("graphs", &Cmd::cmdGraphs);
  commands_.add("vertexes", &Cmd::cmdVertexes);
  commands_.add("outbound", &Cmd::cmdOutbound);
  commands_.add("inbound", &Cmd::cmdInbound);
  commands_.add("bind", &Cmd::cmdBind);
  commands_.add("cut", &Cmd::cmdCut);
  commands_.add("create", &Cmd::cmdCreate);
  commands_.add("merge", &Cmd::cmdMerge);
  commands_.add("extract", &Cmd::cmdExtract);
}

void haliullin::Cmd::loadGraphs(std::istream& file)
{
  std::string graphName;
  size_t edgeCount;
  while (file >> graphName >> edgeCount)
  {
    Graph g;
    for (size_t i = 0; i < edgeCount; ++i)
    {
      std::string from, to;
      unsigned long long weight;
      file >> from >> to >> weight;
      g.addEdge(from, to, weight);
    }
    graphs_.add(graphName, std::move(g));
  }
}

bool haliullin::Cmd::getCommand(const std::string& name, func_t& out) const
{
  if (!commands_.has(name))
  {
    return false;
  }
  out = commands_.get(name);
  return true;
}

void haliullin::Cmd::cmdGraphs(std::istream&, std::ostream& out)
{
  Vector< std::string > names;
  for (auto it = graphs_.cbegin(); it != graphs_.cend(); ++it)
  {
    names.pushBack((*it).first);
  }
  names.insSort();
  for (size_t i = 0; i < names.getSize(); ++i)
  {
    out << names[i] << '\n';
  }
  if (names.getSize() == 0)
  {
    out << '\n';
  }
}

void haliullin::Cmd::cmdVertexes(std::istream& in, std::ostream& out)
{
  std::string gname;
  if (!(in >> gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g = graphs_.get(gname);
  Vector< std::string > verts = g.getVertexes();
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    out << verts[i] << '\n';
  }
  if (verts.getSize() == 0)
  {
    out << '\n';
  }
}

void haliullin::Cmd::cmdOutbound(std::istream& in, std::ostream& out)
{
  std::string gname, v;
  if (!(in >> gname >> v))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g = graphs_.get(gname);
  if (!g.hasVertex(v))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  auto res = g.getOutbound(v);
  if (res.getSize() == 0)
  {
    out << '\n';
  }
  else
  {
    for (size_t i = 0; i < res.getSize(); ++i)
    {
      out << res[i].first;
      for (size_t w = 0; w < res[i].second.getSize(); ++w)
      {
        out << ' ' << res[i].second[w];
      }
      out << '\n';
    }
  }
}

void haliullin::Cmd::cmdInbound(std::istream& in, std::ostream& out)
{
  std::string gname, v;
  if (!(in >> gname >> v))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  const Graph& g = graphs_.get(gname);
  if (!g.hasVertex(v))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  auto res = g.getInbound(v);
  if (res.getSize() == 0)
  {
    out << '\n';
  }
  else
  {
    for (size_t i = 0; i < res.getSize(); ++i)
    {
      out << res[i].first;
      for (size_t w = 0; w < res[i].second.getSize(); ++w)
      {
        out << ' ' << res[i].second[w];
      }
      out << '\n';
    }
  }
}

void haliullin::Cmd::cmdBind(std::istream& in, std::ostream& out)
{
  std::string gname, a, b;
  unsigned long long w;
  if (!(in >> gname >> a >> b >> w))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph g = graphs_.get(gname);
  g.addEdge(a, b, w);
  graphs_.get(gname).swap(g);
}

void haliullin::Cmd::cmdCut(std::istream& in, std::ostream& out)
{
  std::string gname, a, b;
  unsigned long long w;
  if (!(in >> gname >> a >> b >> w))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(gname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph g = graphs_.get(gname);
  if (!g.cutEdge(a, b, w))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  graphs_.get(gname).swap(g);
}

void haliullin::Cmd::cmdCreate(std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (graphs_.has(name))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  size_t k;
  if (!(in >> k))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph g;
  for (size_t i = 0; i < k; ++i)
  {
    std::string v;
    if (!(in >> v))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    g.addVertex(v);
  }
  graphs_.add(name, g);
}

void haliullin::Cmd::cmdMerge(std::istream& in, std::ostream& out)
{
  std::string newname, old1, old2;
  if (!(in >> newname >> old1 >> old2))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (graphs_.has(newname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(old1) || !graphs_.has(old2))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  graphs_.add(newname, graphs_.get(old1).merge(graphs_.get(old2)));
}

void haliullin::Cmd::cmdExtract(std::istream& in, std::ostream& out)
{
  std::string newname, oldname;
  if (!(in >> newname >> oldname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (graphs_.has(newname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!graphs_.has(oldname))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  size_t k;
  if (!(in >> k))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Vector< std::string > verts;
  for (size_t i = 0; i < k; ++i)
  {
    std::string v;
    if (!(in >> v))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    verts.pushBack(v);
  }
  const Graph& old = graphs_.get(oldname);
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    if (!old.hasVertex(verts[i]))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
  }
  graphs_.add(newname, old.extract(verts));
}
