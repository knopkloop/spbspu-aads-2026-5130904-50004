#ifndef APPCORE_HPP
#define APPCORE_HPP

#include <string>
#include <ostream>
#include "RobinHashTable.hpp"
#include "MurMurHash.hpp"
#include "SocialGraph.hpp"
#include "Vector.hpp"

namespace haliullin
{
  class AppCore
  {
  public:
    using PhoneBook = RobinHashTable< std::string, std::string, MurMurHash, std::equal_to< std::string > >;
    using BookTable = RobinHashTable< std::string, PhoneBook, MurMurHash, std::equal_to< std::string > >;
    using SpamTable = RobinHashTable< std::string, size_t, MurMurHash, std::equal_to< std::string > >;
    using RecommendationResult = std::pair< SocialGraph, Vector< std::pair< std::string, double > > >;

    AppCore();
    void swap(AppCore& other) noexcept;

    void createBook(const std::string& name);
    void removeBook(const std::string& name);
    void addContact(const std::string& book, const std::string& number, const std::string& name);
    void removeContact(const std::string& book, const std::string& number);
    void renameBook(const std::string& oldName, const std::string& newName);
    void mergeBooks(const std::string& newName, const std::string& book1, const std::string& book2);
    void copyContact(const std::string& fromBook, const std::string& toBook, const std::string& number);

    void showBook(const std::string& book, std::ostream& out) const;
    void showContact(const std::string& book, const std::string& number, std::ostream& out) const;

    void reportSpam(const std::string& number);
    void grade(const std::string& from, const std::string& to, double value);
    void showConnections(const std::string& number, const std::string& mode, std::ostream& out) const;
    void disconnect(const std::string& from, const std::string& to);
    RecommendationResult recommend(const std::string& book, const std::string& number, double minRating,
      size_t maxSpam, size_t depth) const;

    const BookTable& getBooks() const;
    const SpamTable& getSpam() const;
    const SocialGraph& getGraph() const;

  private:
    BookTable books_;
    SpamTable spam_;
    SocialGraph graph_;

    PhoneBook& getBook(const std::string& name);
    const PhoneBook& getBook(const std::string& name) const;
  };
}

#endif
