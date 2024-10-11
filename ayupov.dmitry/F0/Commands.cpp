#include "Commands.hpp"

#include <iostream>
#include <string>
#include <iterator>

#include "Additional.hpp"

void ayupov::doHelp(std::ostream& out)
{
  out << "Available commands: \n";
  out << "create <dictionary> - creates new empty <dictionary>\n";
  out << "insert <dictionary> <word> <translation> - inserts new <word> with <translation> to <dictionary>\n";
  out << "search <dictionary> <word> - prints translations of chosen <word> from <dictionary>\n";
  out << "print <dictionary> - prints <dictionary>\n";
  out << "deleteword <dictionary> <word> - deletes chosen <word> from <dictionary>\n";
  out << "deletetranslation <dictionary> <word> <translation> - deletes <translation> of the <word> from <dictionary>\n";
  out << "deletedictionary <dictionary> - deletes <dictionary>\n";
  out << "same <dictionary> <dictionary> - compares <dictionaries>\n";
  out << "merge <dictionary> <dictionary> <name> - creates a <dictionary> from the other two\n";
  out << "intersection <dictionary> <dictionary> <name> - creates a <dictionary> from the other two\n";
  out << "size <dictionary> - prints number of words in <dictionary>\n";
  out << "import <file> <dictionary> - reads data from <file> to <dictionary>\n";
  out << "export <file> <dictionary> - writes data from <dictionary> to <file>\n";
}

void ayupov::doCreate(std::map< std::string, ARDictionary>& dicts, std::istream& in)
{
  std::string newName = "";
  in >> newName;
  if (dicts.find(newName) != dicts.end())
  {
    throw std::logic_error("ALREADY EXISTS");
  }
  ARDictionary newDict;
  dicts[newName] = newDict;
}

void ayupov::doInsert(std::map< std::string, ARDictionary >& dicts, std::istream& in)
{
  std::string dictionary = "";
  std::string word = "";
  std::string translation = "";
  in >> dictionary >> word >> translation;
  isDict(dicts, dictionary);
  if (!dicts.at(dictionary).insert(word, translation))
  {
    throw std::logic_error("INVALID COMMAND");
  }
}

void ayupov::doSearch(const std::map< std::string, ARDictionary >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictionary = "";
  std::string word = "";
  in >> dictionary >> word;
  isDict(dicts, dictionary);
  auto translation = dicts.at(dictionary).search(word);
  if (!translation)
  {
    throw std::logic_error("INAVALID COMMAND");
  }
  std::copy((*translation).begin(), (*translation).end(), std::ostream_iterator<std::string>(out, " "));
  out << "\n";
}
