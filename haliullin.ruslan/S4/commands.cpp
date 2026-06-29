#include "commands.hpp"
#include <fstream>
#include <stdexcept>
#include <limits>

haliullin::Cmd::Cmd()
{
  commands_.push("print", &Cmd::cmdPrint);
  commands_.push("complement", &Cmd::cmdComplement);
  commands_.push("intersect", &Cmd::cmdIntersect);
  commands_.push("union", &Cmd::cmdUnion);
}

void haliullin::Cmd::loadFromFile(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file");
  }

  std::string datasetName;
  while (file >> datasetName)
  {
    SingleDataset dataset;
    int key;
    std::string value;
    while(file >> key >> value)
    {
      dataset.push(key, value);
    }

    if (file.fail())
    {
      file.clear();
    }
    datasets_.push(datasetName, dataset);
  }
  file.close();
}

void haliullin::Cmd::processCmd(std::istream& in, std::ostream& out)
{
  std::string command;
  while (in >> command)
  {
    auto it = commands_.find(command);
    if (it == commands_.end())
    {
      out << "<INVALID COMMAND>\n";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }

    func_t func = it->second;
    try
    {
      (this->*func)(in, out);
    }
    catch (const std::logic_error& e)
    {
      out << e.what() << '\n';
    }
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  if (!in.eof())
  {
    throw std::runtime_error("Bad input");
  }
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

void haliullin::Cmd::cmdPrint(std::istream& in, std::ostream& out)
{
  std::string datasetName;
  in >> datasetName;
  require(in);

  auto it = datasets_.find(datasetName);
  require(it != datasets_.end());

  const auto& dataset = it->second;
  if (dataset.isEmpty())
  {
    out << "<EMPTY>\n";
    return;
  }

  out << datasetName;
  for (auto cit = dataset.cbegin(); cit != dataset.cend(); ++cit)
  {
    out << " " << cit->first << " " << cit->second;
  }
  out << "\n";
}

void haliullin::Cmd::cmdComplement(std::istream& in, std::ostream&)
{
  std::string newName, leftName, rightName;
  in >> newName >> leftName >> rightName;
  require(in);

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  require(leftIt != datasets_.end() && rightIt != datasets_.end());

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    if (right.find(cit->first) == right.cend())
    {
      result.push(cit->first, cit->second);
    }
  }
  datasets_.push(newName, result);
}

void haliullin::Cmd::cmdIntersect(std::istream& in, std::ostream&)
{
  std::string newName, leftName, rightName;
  in >> newName >> leftName >> rightName;
  require(in);

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  require(leftIt != datasets_.end() && rightIt != datasets_.end());

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    if (right.find(cit->first) != right.cend())
    {
      result.push(cit->first, cit->second);
    }
  }
  datasets_.push(newName, result);
}

void haliullin::Cmd::cmdUnion(std::istream& in, std::ostream&)
{
  std::string newName, leftName, rightName;
  in >> newName >> leftName >> rightName;
  require(in);

  auto leftIt = datasets_.find(leftName);
  auto rightIt = datasets_.find(rightName);
  require(leftIt != datasets_.end() && rightIt != datasets_.end());

  const auto& left = leftIt->second;
  const auto& right = rightIt->second;
  SingleDataset result;

  for (auto cit = left.cbegin(); cit != left.cend(); ++cit)
  {
    result.push(cit->first, cit->second);
  }
  for (auto cit = right.cbegin(); cit != right.cend(); ++cit)
  {
    if (left.find(cit->first) == left.cend())
    {
      result.push(cit->first, cit->second);
    }
  }
  datasets_.push(newName, result);
}
