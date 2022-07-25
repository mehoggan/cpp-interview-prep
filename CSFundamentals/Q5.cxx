/**
 * Q5: Find celebrity farmer (Moderate) 
 * Find the celebrity in a list of farmers.  
 * A farmer is a celebrity if he or she doesn't know anyone else in the list
 * but everyone else in the list knows him or her.  
 * You are provided the function knows(farmerA, farmerB), which takes two
 * farmers and returns true if farmerA knows farmerB, false otherwise. 
 */
#include <cstdlib>
#include <cstdint>
#include <list>
#include <iostream>
#include <vector>

struct Relation
{
  std::size_t name_;
  std::vector<std::size_t> knows_;
};

std::vector<Relation> relations;

typedef std::tuple<std::size_t, std::size_t> KnowsKnown_t;

void populate_relations()
{
  relations.push_back({1, std::vector<std::size_t>{2, 3, 4}});
  relations.push_back({2, std::vector<std::size_t>{1, 3, 4}});
  relations.push_back({3, std::vector<std::size_t>{1, 2, 4}});
  relations.push_back({4, std::vector<std::size_t>{1, 2, 3}});
}

/**
 * farmer_0 The farmer who knows the other.
 * farmer_1 The farmer who is known.
 */
bool knows(const std::size_t &farmer_0, const std::size_t &farmer_1)
{
  const std::size_t index = farmer_0 - 1;

  return std::find_if(relations[index].knows_.begin(),
    relations[index].knows_.end(),
    [&](const std::size_t &other)
    {
      return other == farmer_1;
    }) != relations[index].knows_.end();

  return true;
}

void print_celebrity_farmer(const std::vector<KnowsKnown_t> &relations_counts)
{
  bool found = false;
  std::size_t farmer = 0;
  std::for_each(relations_counts.cbegin(), relations_counts.cend(),
    [&](const KnowsKnown_t &relations_count)
    {
      std::cout << std::get<0>(relations_count) << ", "
        << std::get<1>(relations_count) << std::endl;
      if (std::get<0>(relations_count) == 0 &&
        std::get<1>(relations_count) == relations.size() - 1) {
        std::cout << " Your celebrity farmer is " <<  (farmer + 1)
          << std::endl;
        found = true;
      }
      ++farmer;
    });

  if (not found) {
    std::cerr << "Did not find a celebrity!!!" << std::endl;
  }
}

int main(int, char *[])
{
  populate_relations();

  std::vector<KnowsKnown_t> table;
  table.resize(relations.size());
  std::for_each(table.begin(), table.end(),
    [&](KnowsKnown_t &relation_count) {
      relation_count = std::make_pair(0ull, 0ull);
    });

  for (std::size_t i = 0; i < relations.size(); ++i) {
    for (std::size_t j = 0; j < relations.size(); ++j) {
      if (knows(relations[i].name_, relations[j].name_)) {
        ++(std::get<0>(table[i])); // i knows j
        ++(std::get<1>(table[j])); // j is known by i
      }
    }
  }

  print_celebrity_farmer(table);

  return EXIT_SUCCESS;
}
