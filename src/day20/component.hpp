#pragma once

#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>

class cComponent
{
public:
  enum eSignal
  {
    E_LOW, E_HIGH
  };

  struct sPulse
  {
    eSignal signal;
    cComponent* from;
    cComponent* to;

    sPulse(const eSignal arg_signal, cComponent* arg_from, cComponent* arg_to);
  };

  cComponent(void);
  cComponent(const std::string arg_name);
  cComponent(const std::string arg_name, std::list<std::string> arg_neighboursByName);

  static std::map<std::string, cComponent*> ParseFile(const std::string arg_path);
  static cComponent* ParseLine(const std::string arg_line);

  void Init(std::map<std::string, cComponent*>& arg_components);
  void RegisterInputNeighbour(cComponent* arg_component);
  virtual void ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse) = 0;
  void Print(void) const;
  std::string GetName(void) const;

protected:
  virtual std::string GetPrefix(void) const = 0;
  virtual void RegisterInputNeighbourExtra(cComponent* arg_component);

  std::string name;
  std::list<std::string> neighboursByName;
  std::set<cComponent*> inputNeighbours;
  std::set<cComponent*> outputNeighbours;

private:
  static void ParseNeighbours(std::list<std::string>& arg_neighbours, const std::string arg_neighboursStr);
};
