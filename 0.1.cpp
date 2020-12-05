#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define MANAGER_MAX_SIZE 100
#define PartTimeTechnologyer_MAX_SIZE 100
#define DataBase_MAX_SIZE 1000
class Person {
 public:
  int id;
  int level;
  string name;
  virtual void UpdateLevel();
  virtual double GetMoney() {}
  Person();
  Person(int, int, string);
  bool operator<(Person& b) { return this->id < b.id; }
};
class AllTimeWorker : public Person {
 public:
  double FixedMoney;
  int months;
  AllTimeWorker();
  ~AllTimeWorker();
  virtual void AllTimeWorking() { months++; }  //输出
  virtual double GetMoney();                   //拿月薪后清零
};
class PartTimeWorker : public Person {
 public:
  double HourlyMoney;
  int hours;
  PartTimeWorker();
  ~PartTimeWorker();
  virtual void PartTimeWorking() { hours++; }  //每次工作后输出时长
  virtual double GetMoney();                   //拿时薪后清零
};
class Manager : public AllTimeWorker {
 public:
  Manager();
  Manager(int, int, string);
  Manager(Person);
  ~Manager();
};
class PartTimeTechnologyer : public PartTimeWorker {
 private:
  /* data */
 public:
  PartTimeTechnologyer(/* args */);
  PartTimeTechnologyer(Person);
  ~PartTimeTechnologyer();
  void UpdateLevel();
  double GetMoney();
  void PartTimeWorking(int h = 1);
};
class SaleManager : public AllTimeWorker {
 private:
  /* data */
 public:
  double PlusMoney;
  double SalesVolume;
  SaleManager(/* args */);
  SaleManager(Person);
  ~SaleManager();
  void Updatelevel();
  void AllTimeWorking() {}
  //销售额+提成
};
class PartTimeSalesMan : public PartTimeWorker {
 private:
  /* data */
 public:
  PartTimeSalesMan(/* args */);
  PartTimeSalesMan(Person);
  ~PartTimeSalesMan();
};

template <typename T>
class DataBase {
 public:
  int num;
  T Table[DataBase_MAX_SIZE];
  int idnum;
  int ManagerNum;
  int PartTimeTechnologyerNum;
  int SalesMananagerNum;
  Manager Group_Manager[MANAGER_MAX_SIZE];
  PartTimeTechnologyer
      Group_PartTimeTechnologyer[PartTimeTechnologyer_MAX_SIZE];
  DataBase();
  ~DataBase();
  void insert(T);
  void remove(T);
  void remove(int);
  void remove(string);
  void modify();
};
class TotalDataBase {
 public:
  DataBase<Manager> Group_Manager;
  DataBase<PartTimeTechnologyer> Group_PartTimeTechnologyer;
  DataBase<SaleManager> Group_SaleManager;
} TotalDB;

Person::Person() {}
Person::Person(int id, int level, string name)
    : id(id), level(level), name(name) {}
void Person::UpdateLevel() { this->level++; }
Manager::Manager() {}
Manager::Manager(Person per) {
  this->id = per.id;
  this->level = per.level;
  this->name = per.name;
}
Manager::~Manager() {}
PartTimeTechnologyer::PartTimeTechnologyer() {}
PartTimeTechnologyer::PartTimeTechnologyer(Person per) {
  this->id = per.id;
  this->level = per.level;
  this->name = per.name;
  this->hours = 0;
}
PartTimeTechnologyer::~PartTimeTechnologyer() {}
void PartTimeTechnologyer::UpdateLevel() {
  Manager newManager(this->id, this->level + 1, this->name);
  TotalDB.Group_Manager.insert(newManager);
  TotalDB.Group_PartTimeTechnologyer.remove(*this);
}
SaleManager::SaleManager(/* args */) {}
SaleManager::SaleManager(Person per) {}
SaleManager::~SaleManager() {}

PartTimeSalesMan::PartTimeSalesMan(/* args */) {}
PartTimeSalesMan::~PartTimeSalesMan() {}

template <typename T>

// id->
//