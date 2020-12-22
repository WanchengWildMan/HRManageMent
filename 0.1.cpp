#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define MANAGER_MAX_SIZE 100
#define PartTimeTechnologyer_MAX_SIZE 100
#define Table_MAX_SIZE 1000
#define PartTimeSalesMan_MAX_SIZE 1000
#define SalesManager_MAX_SIZE 1000
const int MANAGER = 1, PARTTIME_TECHNOLOGER = 2, SALESMANAGER = 3,
          PARTTIME_SALESMAN = 4;
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
  void UpdateLevel();
  void AllTimeWorking();

  //销售额+提成
};
class PartTimeSalesMan : public PartTimeWorker {
 private:
  /* data */
 public:
 double SalesVolume;
  PartTimeSalesMan(/* args */);
  PartTimeSalesMan(Person);
  ~PartTimeSalesMan();
  void UpdateLevel();
  double GetMoney();//销售额提成
};

template <typename T>
class Table {
 public:
  int num;
  int idnum;
  int TypeId;
  T table[Table_MAX_SIZE];
  Table();
  ~Table();
  void insert(T);
  void remove(T);  //根据
  void modify();
  string query();
};
template <typename T>
Table ::insert(T peo) {
  int i = num;
  while (table[i].id > peo.id && i) table[i + 1] = table[i], i--;
  table[i + 1] = peo;
  num++;
}
template <typename T>
Table ::remove(T peo) {
  int id = peo.id;
  int pos = lower_bound(table + 1, table + 1 + num, id) - table;
  for (int i = pos; i < num; i--) {
    table[i] = table[i + 1];
  }
  num--;
}
Table ::remove(int id) {
  int pos = lower_bound(table + 1, table + 1 + num, id) - table;
  if (table[pos].id != id) {
    cout << "未找到工号为" << id << "的员工！" << endl;
    return;
  }
  for (int i = pos; i < num; i--) {
    table[i] = table[i + 1];
  }
  num--;
}
Table::remove(string name) {
  bool ok = 0;
  for (int i = 1; i <= num; i++) {
    if (table[i].name == name) {
      ok = 1;
      break;
    }
  }
  if (!ok) {
    cout << "未找到姓名为" << name << "的员工！" << endl;
  }
}
template <typename T>
class TotalTable {
 public:
  Table<Manager> Group_Manager;
  Table<PartTimeTechnologyer> Group_PartTimeTechnologyer;
  Table<SaleManager> Group_SaleManager;
  Table<PartTimeSalesMan> Group_PartTimeSalesMan;
  void insert(T, int);  //第二个参数标识类别
  void remove(int);     //根据id
  void remove(string);  //根据人名
} TotalDB;

TotalTable::insert(T peo, int type) {
  if (type == MANAGER) {
    Group_Manager.insert(peo);
  } else if (type == PARTTIME_TECHNOLOGER) {
    Group_PartTimeTechnologyer.insert(peo);
  } else if (type == SALESMANAGER) {
    Group_SaleManager.insert(peo);
  } else {
    Group_PartTimeSalesMan.insert(peo);
  }
}
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
SaleManager::SaleManager(Person per) {
  this->id = per.id;
  this->level = per.level;
  this->name = per.name;
}
SaleManager::~SaleManager() {}
PartTimeSalesMan::PartTimeSalesMan(/* args */) {}
PartTimeSalesMan::~PartTimeSalesMan() {}
PartTimeSalesMan::GetMoney() {}
class Menu {
 private:
  const int SEARCH = 1, ADD = 2, MODIFY = 3, DELETE = 4;

 public:
  int num;
  string OperationName[10];
  Menu(/* args */);
  Menu(int);
  Menu(Menu&);
  ~Menu();

  virtual bool CheckValid(int);
  virtual void PrintList();  //操作号及名称
  virtual void SelectOperation() {}
  virtual void Present();  //
};

Menu::Menu(/* args */) {}
Menu::Menu(int num) : num(num) {}
Menu::Menu(Menu& m) {
  for (int i = 1; i <= m.num; i++) {
    OperationName[i] = m.OperationName;
  }
}
Menu::~Menu() {}
Menu::CheckValid(int opr) {
  if (opr > num || num <= 0) return 0;
  return 1;
}
Menu::PrintList() {
  for (int i = 1; i <= num; i++) {
    cout << i << "." << OperationName[i] << endl;
  }
}
class BaseMenu : public : Menu {
 public:
  const BYNAME = 1, BYJOB = 2, BYID = 3;
};
BaseMenu::SelectOperation() {
  cin >> opr;
  if (CheckValid(opr)) {
    if (opr == SEARCH) {
    }
  } else if (opr == ADD) {
  } else if (opr == MODIFY) {
    Menu tmpmenu;
    tmpmenu.PrintList();

  } else if (opr == DELETE) {
    //选择根据什么删除（姓名，职位，工号）
    //新开一个菜单
    //选择
  }
}

template <typename T>

// id->
//