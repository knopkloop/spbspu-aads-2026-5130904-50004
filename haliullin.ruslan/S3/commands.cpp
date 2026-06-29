#include "commands.hpp"
#include <stdexcept>
#include <limits>
#include <utility>
#include <vector.hpp>

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

void haliullin::Cmd::require(bool condition) const
{
  if (!condition)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void haliullin::Cmd::require(std::istream& in) const
{
  if (!in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
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
  in >> gname;
  require(in);
  require(graphs_.has(gname));

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
  in >> gname >> v;
  require(in);
  require(graphs_.has(gname));

  const Graph& g = graphs_.get(gname);
  require(g.hasVertex(v));

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
  in >> gname >> v;
  require(in);
  require(graphs_.has(gname));

  const Graph& g = graphs_.get(gname);
  require(g.hasVertex(v));
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

void haliullin::Cmd::cmdBind(std::istream& in, std::ostream&)
{
  std::string gname, a, b;
  unsigned long long w;
  in >> gname >> a >> b >> w;
  require(in);
  require(graphs_.has(gname));

  Graph g = graphs_.get(gname);
  g.addEdge(a, b, w);
  graphs_.get(gname).swap(g);
}

void haliullin::Cmd::cmdCut(std::istream& in, std::ostream&)
{
  std::string gname, a, b;
  unsigned long long w;
  in >> gname >> a >> b >> w;
  require(in);
  require(graphs_.has(gname));

  Graph g = graphs_.get(gname);
  g.cutEdge(a, b, w);
  graphs_.get(gname).swap(g);
}

void haliullin::Cmd::cmdCreate(std::istream& in, std::ostream&)
{
  std::string gname;
  in >> gname;
  require(in);
  require(!graphs_.has(gname));

  size_t k;
  in >> k;
  require(in);

  Graph g;
  for (size_t i = 0; i < k; ++i)
  {
    std::string v;
    in >> v;
    require(in);
    g.addVertex(v);
  }
  graphs_.add(gname, g);
}

void haliullin::Cmd::cmdMerge(std::istream& in, std::ostream&)
{
  std::string newname, old1, old2;
  in >> newname >> old1 >> old2;
  require(in);
  require(!graphs_.has(newname));
  require(graphs_.has(old1) && graphs_.has(old2));
  graphs_.add(newname, graphs_.get(old1).merge(graphs_.get(old2)));
}

void haliullin::Cmd::cmdExtract(std::istream& in, std::ostream&)
{
  std::string newname, oldname;
  in >> newname >> oldname;
  require(in);
  require(!graphs_.has(newname));
  require(graphs_.has(oldname));

  size_t k;
  in >> k;
  require(in);

  Vector< std::string > verts;
  for (size_t i = 0; i < k; ++i)
  {
    std::string v;
    in >> v;
    require(in);
    verts.pushBack(v);
  }
  const Graph& old = graphs_.get(oldname);
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    require(old.hasVertex(verts[i]));
  }
  graphs_.add(newname, old.extract(verts));
}
