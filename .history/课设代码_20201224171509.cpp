#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define MANAGER_MAX_SIZE 100
#define PartTimeTechnologyer_MAX_SIZE 100
#define Table_MAX_SIZE 1000
#define PartTimeSalesMan_MAX_SIZE 1000
#define SalesManager_MAX_SIZE 1000
const int MANAGER = 4, PARTTIME_TECHNOLOGER = 2, SALESMANAGER = 3,
          PARTTIME_SALESMAN = 1;
string JOBS[] = {" ", "经理", "销售经理", "兼职技术人员", "兼职推销员"};
double PLUS_RATE[7];
int PLUS_STEP_NUM;
class Person {
 public:
  int id;
  int job;
  string name;
  // virtual void UpdateJob();
  // virtual double GetMoney() {}
  Person();
  Person(int, int, string);
  bool operator<(Person& b) { return this->id < b.id; }
};


class Manager : public Person {
 public:
  Manager();
  Manager(int, int, string);
  Manager(Person);
  ~Manager();
};
class PartTimeTechnologyer : public Person {
 private:
  /* data */
 public:
  double Hours;
  PartTimeTechnologyer(/* args */);
  PartTimeTechnologyer(Person);
  ~PartTimeTechnologyer();
  double GetMoney();
  void PartTimeWorking(int h = 1);
};
class SaleManager : public Person {
 private:
  /* data */
 public:
  double PlusMoney;
  double SalesVolume;
  SaleManager(/* args */);
  SaleManager(Person);
  SaleManager(int, int, string);
  ~SaleManager();
  // void UpdateJob();
  void GetMoney();
  void AllTimeWorking();

  //销售额+提成
};
class PartTimeSalesMan : public Person {
 private:
  /* data */
 public:
 double 
  PartTimeSalesMan(/* args */);
  PartTimeSalesMan(Person);
  PartTimeSalesMan(int, int, string);
  ~PartTimeSalesMan();
  // void UpdateJob();
  inline int CalcPlus(int Sales) {
    int pos = 0;
    for (int i = 0; i <= PLUS_STEP_NUM; i++) {
      if (PLUS_RATE[i] <= Sales && Sales < PLUS_RATE[i + 1]) {
        return PLUS_RATE[i] * Sales;
      }
    }
  }
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
};
template <typename T>
Table ::insert(T peo) {
  int i = num;
  while (table[i].id > peo.id && i) table[i + 1] = table[i], i--;
  table[i + 1] = peo;
  num++;
}
Table ::remove(T peo) {
  int id = peo.id;
  int pos = lower_bound(table + 1, table + 1 + num, peo) - table;
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
;
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
template <typename T>
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
Person::Person(int id, int job, string name)
    : id(id), job(job), name(name) {}
// void Person::UpdateJob() {
//   if (this->job == MANAGER)
//     cout << "已提升至最高级别职位:经理!" << endl;
//   else {
//     this->job++;
//   }
// }
Manager::Manager() {}
Manager::Manager(Person per) {
  this->id = per.id;
  this->job = per.job;
  this->name = per.name;
}
Manager::~Manager() {}
PartTimeTechnologyer::PartTimeTechnologyer() {}

PartTimeTechnologyer::PartTimeTechnologyer(Person per) {
  this->id = per.id;
  this->job = per.job;
  this->name = per.name;
  this->hoursOrSales = 0;
}
PartTimeTechnologyer::~PartTimeTechnologyer() {}
// void PartTimeTechnologyer::UpdateJob() {
//   SaleManager newSaleManager(this->id, this->job + 1, this->name);
//   TotalDB.Group_SaleManager.insert(newSaleManager);
//   TotalDB.Group_PartTimeTechnologyer.remove(*this);
// }
SaleManager::SaleManager(/* args */) {}
SaleManager::SaleManager(Person per) {
  this->id = per.id;
  this->job = per.job;
  this->name = per.name;
}
SaleManager::~SaleManager() {}
// SaleManager::UpdateJob() {
//   Manager newManager(this->id, this->job + 1, this->name);
//   TotalDB.Group_Manager.insert(newManager);
//   TotalDB.Group_SaleManager.remove(*this);
// }
PartTimeSalesMan::PartTimeSalesMan(/* args */) {}
PartTimeSalesMan::~PartTimeSalesMan() {}
PartTimeSalesMan::GetMoney() { this.money += CalcPlus(hoursOrSales); }
template <typename T>
void printPerson(T per) {
  cout << "姓名：" << per.name << setw(15) << "工号：" << per.id << "工资："
       << per.money;
}
void MonthlySum() {
  cout << JOBS[1] << endl;
  for (int i = 1; i <= TotalDB.Group_Manager.num; i++) {
    printPerson(TotalDB.Group_Manager.table[i]);
  }
  cout << JOBS[2] << endl;
  for (int i = 1; i <= TotalDB.Group_SaleManager.num; i++) {
    printPerson(TotalDB.Group_SaleManager.table[i]);
    cout << endl;
  }
  cout << JOBS[3] << endl;
  for (int i = 1; i <= TotalDB.Group_PartTimeTechnologyer) {
    printPerson(TotalDB.Group_PartTimeTechnologyer.table[i]);
  }
  cout << JOBS[4] << endl;
  for (int i = 1; i <= TotalDB.Group_PartTimeSalesMan) {
    printPerson(TotalDB.Group_PartTimeSalesMan.table[i]);
    cout << setw(15) << "鎻愭垚" << TotalDB.Group_PartTimeSalesMan.table[i].<< endl;
  }
}

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
Menu::Present() {
  system("mode con cols=150 lines=30");
  system("color 3f");
  system("cls");
  cout << "*----------------------------------------------------------------*"
          "\n";
  PrintList();
}
class BaseMenu : public Menu {
 public:
  const BYNAME = 1, BYJOB = 2, BYID = 3;
  void init() {
    this->OperationName[] = {" ",
                             "增加人员及其个人信息",
                             "删除人员及其个人信息",
                             "删除全部人员及其个人信息",
                             "查找人员及其个人信息",
                             "升职操作",
                             "公司人员总数",
                             "月底工资账单总览",
                             "信息整合保存成a.txt文件",
                             "读取a.txt文件"};
  }
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
int main() { BaseMenu. }
template <typename T>

// id->
//