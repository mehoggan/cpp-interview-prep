/**
 * Q1: Given a list of farms with attributes “name”, “crop”, and “size”,
 * return a list of the top two farms by size for each crop.  
 */
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

struct Crop
{
  Crop() :
    name_(""),
    yield_(0)
  {}

  Crop(const std::string &name, std::size_t yield) :
    name_(name),
    yield_(yield)
  {};

  friend std::ostream &operator<<(std::ostream &out, const Crop &crop)
  {
    out << "{" << crop.name_ << ", " << crop.yield_ << "}";
    return out;
  };

  std::string name_;
  std::size_t yield_;
};

struct Farm
{
  Farm(const std::string &name, const std::vector<Crop> &crops) :
    name_(name),
    crops_(crops)
  {};

  bool contains_crop(const std::string &name) const
  {
    std::vector<Crop>::const_iterator it = std::find_if(
      crops_.cbegin(),
      crops_.cend(),
      [&](const Crop &crop) {
        return crop.name_ == name;
      });
    return it != crops_.end();
  }

  void get_crop(const std::string &name, Crop &out) const
  {
    auto it = std::find_if(crops_.begin(), crops_.end(),
      [&](const Crop &crop) {
        return crop.name_ == name;
      });

    if (it == crops_.end()) {
      throw std::runtime_error(std::string("Failed to find") + name);
    } else {
      out = *it;
    }
  }

  friend std::ostream &operator<<(std::ostream &out, const Farm &farm)
  {
    out << farm.name_ << " ==> [";
    std::copy(farm.crops_.begin(), farm.crops_.end(),
      std::ostream_iterator<Crop>(out, ", "));
    out << "]";
    return out;
  };

  std::string name_;
  std::vector<Crop> crops_;
};

void print_farms(const std::vector<Farm> &farms)
{
  auto farm_ioit = std::ostream_iterator<Farm>(std::cout, "\n");
  std::copy(farms.cbegin(), farms.cend(), farm_ioit);
}

void analyze_farms(const std::vector<Farm> &farms)
{
  std::set<std::string> available_crops;
  std::cout << "Original farms = " << std::endl;
  print_farms(farms);
  std::cout << "****************" << std::endl;
  std::for_each(farms.cbegin(), farms.cend(), [&](const Farm &farm) {
      std::for_each(farm.crops_.cbegin(), farm.crops_.cend(),
        [&](const Crop &crop) {
          available_crops.insert(crop.name_);
        });
    });

  std::for_each(available_crops.begin(), available_crops.end(),
    [&](const std::string &crop) {
      std::vector<Farm> filtered;
      std::copy_if(farms.cbegin(), farms.cend(), std::back_inserter(filtered),
        [&](const Farm &farm) {
          return farm.contains_crop(crop);
        });
      std::sort(filtered.begin(), filtered.end(),
        [&](const Farm &farm_a, const Farm &farm_b) -> bool {
          Crop ca;
          farm_a.get_crop(crop, ca);
          Crop cb;
          farm_b.get_crop(crop, cb);
          return ca.yield_ > cb.yield_; 
        });
      std::vector<Farm> answer_for_crop;
      for (std::size_t i = 0; i < filtered.size() && i < 2; ++i) {
        answer_for_crop.push_back(filtered[i]);
      }
      std::cout << crop << std::endl;
      print_farms(answer_for_crop);
      std::cout << "============" << std::endl;
  });
}

void make_farms(std::vector<Farm> &farms)
{
  std::vector<Crop> adams_crops {
    Crop("corn", 100),
    Crop("soybeans", 70)
  };
  farms.push_back(Farm("adams", adams_crops));
  std::vector<Crop> adair_crops {
    Crop("soybeans", 50),
    Crop("wheat", 206),
    Crop("coffee", 36)
  };
  farms.push_back(Farm("adair", adair_crops));
  std::vector<Crop> benton_crops {
    Crop("soybeans", 90)
  };
  farms.push_back(Farm("benton", benton_crops));
  std::vector<Crop> boone_crops {
    Crop("corn", 75),
    Crop("coffee", 39)
  };
  farms.push_back(Farm("boone", boone_crops));
  std::vector<Crop> carroll_crops {
    Crop("wheat", 200)
  };
  farms.push_back(Farm("carroll", carroll_crops));
  std::vector<Crop> creation_crops {
    Crop("corn", 90),
    Crop("coffee", 40)
  };
  farms.push_back(Farm("creation", creation_crops));
  std::vector<Crop> dansplot_crops {
    Crop("soybeans", 55)
  };
  farms.push_back(Farm("dansplot", dansplot_crops));
  std::vector<Crop> edgars_crops {
    Crop("soybeans", 95)
  };
  farms.push_back(Farm("edgars", edgars_crops));
  std::vector<Crop> everlast_crops {
    Crop("corn", 70),
    Crop("coffee", 8)
  };
  farms.push_back(Farm("everlast", everlast_crops));
  std::vector<Crop> greenacres_crops {
    Crop("wheat", 205)
  };
  farms.push_back(Farm("greenacres", greenacres_crops));
}

int main(int, char *[])
{
  std::vector<Farm> farms;
  make_farms(farms);
  analyze_farms(farms);
  return EXIT_SUCCESS;
}

