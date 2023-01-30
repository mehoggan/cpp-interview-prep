/*
 * Q3.6: Animal Shelter: An animal shelter, which holds only dogs and cats,
 * operates on a strictly "first in, first out" basis. People must adopt either
 * the "oldest" (based on arrival time) of all animals at the shelter, or they
 * selecet whether they would prefer a dog or a cat (and will receive the
 * oldest animal of that type). They cannot select which specific animal they
 * would like. Create the data structure to maintain this system and implement
 * operations such as enqueue, dequeueAny, dequeueDog, and dequeueCat. You may
 * use the built-in LinkedList data structure.
 */

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <future>
#include <iostream>
#include <list>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <uuid/uuid.h>

#include "cpp_utils.hpp"

class Animal
{
public:
  enum class Type
  {
    DOG = 0,
    CAT = 1,
    NONE = 2
  };

  Animal() :
    Animal(Type::NONE)
  {}

  explicit Animal(const Type &type) :
    type_(type)
  {
    uuid_generate(uuid_);
  }

  Type get_type() const
  {
    return type_;
  }

  std::string get_uuid() const
  {
    char uuid_str[37];
    uuid_unparse_lower(uuid_, uuid_str);
    return std::string(uuid_str);
  }

  bool valid() const
  {
    return type_ == Type::CAT || type_== Type::DOG;
  }

  operator std::string() const
  {
    std::string ret;
    if (get_type() == Type::DOG) {
      ret = "{\"type\": \"Dog\", \"uuid\": ";
    } else {
      ret = "{\"type\": \"Cat\", \"uuid\": ";
    }
    ret += (get_uuid() + "}");
    return ret;
  }

private:
  Type type_;
  uuid_t uuid_;
};

class Dog : public Animal
{
  Dog() :
    Animal(Animal::Type::DOG)
  {}
};

class Cat : public Animal
{
  Cat() :
    Animal(Animal::Type::CAT)
  {}
};

class AnimalShelter
{
public:
  typedef std::function<void (Animal&)> Callback_t;

private:
  typedef std::pair<Animal::Type, Callback_t> Promise_t;

private:
  void print_this()
  {
    //=================================================================
    std::cout << "BACK: Kenel (" << kenel_.size() << "):" << std::endl;
    std::cout.flush();
    std::for_each(kenel_.begin(), kenel_.end(),
      [](const Animal &animal)
      {
        std::cout << std::string(animal) << ", " << std::endl; 
        std::cout.flush();
      });
    std::cout.flush();
    std::cout << "BACK: Promises (" << fulfillment_callbacks_.size()
      << "): ";
    std::cout.flush();
    std::for_each(
      fulfillment_callbacks_.begin(), fulfillment_callbacks_.end(),
      [](const Promise_t &promise)
      {
        switch (promise.first) {
        case Animal::Type::DOG: {
          std::cout << "Dog";
          std::cout.flush();
        }
          break;
        case Animal::Type::CAT: {
          std::cout << "Cat";
          std::cout.flush();
        }
          break;
        case Animal::Type::NONE: {
          std::cout << "N/A";
          std::cout.flush();
        }
          break;
        }
        std::cout << ", ";
        std::cout.flush();
      });
    std::cout << std::endl;
    std::cout.flush();
    //=================================================================
  }

public:
  AnimalShelter() :
    run_fulfillment_(true)
  {
    fulfillment_thread_ = std::thread(
      [this]()
      {
        std::cout << "BACK: Starting up backend..." << std::endl;
        std::cout.flush();
        while (run_fulfillment_.load()) {
          std::cout << "BACK: Waiting for fulfillment notification..." <<
            std::endl;
          std::cout.flush();
          std::unique_lock<std::mutex> fullfilment_lock(fulfillment_sync_);
          fulfillment_cv_.wait(fullfilment_lock);
          {
            std::scoped_lock<std::mutex> kenel_lock(kenel_sync_);
            {
              print_this();
              if (not fulfillment_callbacks_.empty()) {
                auto kenel_front_type = kenel_.front().get_type();
                auto fulfillment_type = fulfillment_callbacks_.front().first;
                std::cout << "BACK: Checking if fullfillment can be " <<
                  "met..." << std::endl;
                std::cout.flush();
                if (kenel_front_type  == fulfillment_type) {
                  std::cout << "BACK: Fulfillment met!!!" << std::endl;
                  std::cout.flush();
                  fulfillment_callbacks_.front().second(kenel_.front());
                  kenel_.pop_front();
                  fulfillment_callbacks_.pop_front();
                }
              }
            }
          }
          fullfilment_lock.unlock();
          fulfillment_cv_.notify_one();
        }
        std::cout << "BACK: Backend shutting down..." << std::endl;
        std::cout.flush();
      }
    );

    std::this_thread::sleep_for(std::chrono::seconds(2));
  }

  ~AnimalShelter()
  {
    std::cout << "FRONT: Shelter shutting down..." << std::endl;
    std::cout.flush();
    fulfill_until();
    std::cout << "FRONT: Done fulfilling!" << std::endl;
    std::cout.flush();
    kenel_.erase(kenel_.begin(), kenel_.end());
    std::cout << "FRONT: Removing all callbacks!" << std::endl;
    std::cout.flush();
    fulfillment_callbacks_.erase(fulfillment_callbacks_.begin(),
      fulfillment_callbacks_.end());
    std::cout << "FRONT: Notifiying kenel it is okay to shutdown..." <<
      std::endl;
    std::cout.flush();
    run_fulfillment_.store(false);
    fulfillment_cv_.notify_all();
    std::cout << "FRONT: Waiting for backend to shutdown..." << std::endl;
    std::cout.flush();
    if (fulfillment_thread_.joinable()) {
      fulfillment_thread_.join();
    }
    std::cout << "FRONT: Goodbye, its closing time!" << std::endl;
    std::cout.flush();
  }

  bool empty() const
  {
    std::scoped_lock<std::mutex> kenel_lock(kenel_sync_);
    return kenel_.empty();
  }

  void enqueue(const Animal &animal)
  {
    {
      std::scoped_lock<std::mutex> kenel_lock(kenel_sync_);
      std::cout << "FRONT: Enqueueing " << std::string(animal) << std::endl;
      std::cout.flush();
      if (not is_supported(animal)) {
        throw std::runtime_error("Non supported animal brought into shelter!");
      } else if (contains(animal)) {
        throw std::runtime_error(std::string("Animal Shelter already ") +
          "contains an animal " + std::string("with id = ") +
          animal.get_uuid());
      } else {
        kenel_.push_back(animal);
      }
    }
    fulfill_until();
  }

  Animal dequeue_any()
  {
    Animal ret;
    {
      std::cout << "FRONT: Dequeuing..." << std::endl;
      std::cout.flush();
      std::scoped_lock<std::mutex> kenel_lock(kenel_sync_);
      if (kenel_.empty()) {
        throw std::runtime_error("There are no more animals in the shelter!");
      } 

      ret = kenel_.front();
      kenel_.pop_front();
    }
    fulfill_until();
    return ret;
  }

  void request_animal_type(
    const Animal::Type &type,
    const Callback_t &callback)
  {
    {
      std::scoped_lock<std::mutex> fullfilment_lock(fulfillment_sync_);
      fulfillment_callbacks_.push_back({type, callback});
    }
    fulfill_until();
  }

  friend std::ostream &operator<<(std::ostream &out, const AnimalShelter &obj)
  {
    std::scoped_lock<std::mutex> kenel_lock(obj.kenel_sync_);
    out << "FRONT: Shelter = [" << std::endl;
    for (const Animal &animal : obj.kenel_) {
      out << "\t" << std::string(animal) << "," << std::endl;;
    }
    out << "]";
    return out;
  }

private:
  bool can_fulfill() const
  {
    std::scoped_lock<std::mutex> fulfillment_lock(fulfillment_sync_);
    std::scoped_lock<std::mutex> kenel_lock(kenel_sync_);
    if (fulfillment_callbacks_.empty() || kenel_.empty()) {
      return false;
    } else if (fulfillment_callbacks_.front().first !=
      kenel_.front().get_type()) {
      return false;
    } else {
      return true;
    }
  }

  void fulfill()
  {
    if (not empty()) {
      std::cout << "FRONT: Notify fullment thread..." << std::endl;
      std::cout.flush();
      fulfillment_cv_.notify_one();

      std::cout << "FRONT: Waiting on backend..." << std::endl;
      std::cout.flush();
      {
        std::unique_lock<std::mutex> fulfillment_lock(fulfillment_sync_);
        fulfillment_cv_.wait(fulfillment_lock);
      }
      std::cout << "FRONT: Backend finished operation." << std::endl;
      std::cout.flush();
    }
  }

  void fulfill_until()
  {
    std::cout.flush();
    while (can_fulfill()) {
      fulfill();
    }
  }

  bool is_supported(const Animal &animal)
  {
    return (animal.get_type() == Animal::Type::DOG ||
      animal.get_type() == Animal::Type::CAT);
  }

  bool contains(const Animal &animal)
  {
    std::list<Animal>::const_iterator it = std::find_if(
      kenel_.cbegin(), kenel_.cend(),
      [&](const Animal &a)
      {
        return a.get_uuid() == animal.get_uuid();
      });
    return it != kenel_.end();
  }

private:
  std::list<Animal> kenel_;
  mutable std::mutex kenel_sync_;

  std::list<Promise_t> fulfillment_callbacks_;
  std::thread fulfillment_thread_;
  std::atomic_bool run_fulfillment_;
  mutable std::mutex fulfillment_sync_;
  mutable std::condition_variable fulfillment_cv_;
};

int main(int, char *[])
{
  constexpr Animal::Type CAT = Animal::Type::CAT;
  constexpr Animal::Type DOG = Animal::Type::DOG;

  AnimalShelter shelter;
  shelter.enqueue(Animal(DOG));
  shelter.enqueue(Animal(DOG));
  shelter.enqueue(Animal(DOG));
  shelter.enqueue(Animal(CAT));
  shelter.enqueue(Animal(CAT));
  std::cout << shelter << std::endl;
  std::cout.flush();

  {
    std::string name = "Jenny";
    auto callback = [&name](const Animal &animal)
      {
        std::cout << "FRONT: " << name << " just got a "
          << std::string(animal) << std::endl;
        std::cout.flush();
      };
    shelter.request_animal_type(DOG, callback);
  }

  // {
  //   std::string name = "Jonny";
  //   Animal oldest = shelter.dequeue_any();
  //   std::cout << "FRONT: " << name << " just got a "
  //     << std::string(oldest) << std::endl;
  //   std::cout.flush();
  //   std::cout << shelter << std::endl;
  //   std::cout.flush();
  // }

  // {
  //   std::string name = "Peter";
  //   Animal oldest = shelter.dequeue_any();
  //   std::cout << "FRONT: " << name << " just got a "
  //     << std::string(oldest) << std::endl;
  //   std::cout.flush();
  //   std::cout << shelter << std::endl;
  //   std::cout.flush();
  // }

  // {
  //   std::string name = "Mark";
  //   Animal oldest = shelter.dequeue_any();
  //   std::cout << "FRONT: " << name << " just got a "
  //     << std::string(oldest) << std::endl;
  //   std::cout.flush();
  //   std::cout << shelter << std::endl;
  //   std::cout.flush();
  // }

  return EXIT_SUCCESS;
}
