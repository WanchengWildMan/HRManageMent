#include <bits/stdc++.h>

using namespace std;
#define inf 0x3f3f3f3f
#define JOB_SORT_NUM 4
string JOBS[] = {" ", "经理", "销售经理", "兼职技术人员", "兼职推销员"};

int PLUS_STEP_NUM = 3;
double PLUS_RATE[7] = {0.3, 0.4, 0.5};
double PLUS_BOUND[7] = {0, 10000, 20000, 30000};
double MONEY_PER_HOUR = 100;  //初始时薪100
double MONEY_MANAGER = 20000, MONEY_SALEMANAGER = 15000;

template <typename T>
inline int findElement(T *arr, T x, int len) {
  for (int i = 1; i <= len; i++) {
    if (arr[i] == x) return i;
  }
  return 0;
}
inline int intRead() {
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
  return x;
}
inline int stoi(char *s) {
  int x = 0;
  for (int i = 0; i < strlen(s); i++) {
    x = x * 10 + s[i] - '0';
  }
  return x;
}
inline string to_string(int x) {
  string s, ds;
  s = "";
  ds = "0";
  int l = 1;
  while (l <= x) l *= 10;
  l /= 10;
  while (l) {
    ds[0] = (x / l) + '0';
    s += ds;
    x %= l;
    l /= 10;
  }
  return s;
}
class Person {
 public:
  string name;  //名字
  bool sex;     // 1男
};
class Staff : public Person  //定义一个人员的类
{
 public:
  string job;  //职位
  int jobid;
  int number;    //编号
  double money;  //工资
  double hours;
  double plusmoney;
  double salevolume;
  Staff() { money = hours = plusmoney = salevolume = 0; }
  Staff(string job1, string name1, double money1,
        int number1)  //构造函数初始化一个人员
  {
    job = job1;
    name = name1;
    number = number1;
    money = money1;
    hours = plusmoney = salevolume = 0;
    jobid = findElement(JOBS, job1, 4);
  }
  ~Staff() {}

  static int sum;  //这是static类型的sum 控制编号数字
};
ostream &operator<<(ostream &o, const Staff &s) {
  o << setw(0) << "编号：" << s.number << setw(15) << "姓名：" << s.name
    << setw(15) << "职位：" << s.job << setw(15);
  return o;
}
class Function {
 public:
  string functionname;
};

class Main {
  //总的控制台   控制人员；人员存放在vector的容器中
  //通过内部函数进行各种操作
 public:
  vector<Staff> Peo;

 public:
  Main() {}
  void Promote();             //升职函数
  void ShowRewardtheMonth();  //显示总信息
  void Look();                //查找
  void Increase();            //增加一个成员
  void Delete();              //删除一个成员
  void delete_all();
  void write();  //讲数据存入txt文件
  void ReadFromFile();
  void InputReward();
  void Show_all();
  int Sum()  //显示公司人数
  {
    return Peo.size();
  }
} M;

void Main::ReadFromFile()  //读取
{
  // cout << "*               公司人员管理系统                   *" << endl
  FILE *fp = fopen("a.txt", "r");
  {
    int num;
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++) {
      char s1[40], s2[40], numb[40], mon[40];
      fscanf(fp, "%s%s%s%s", s1, s2, numb, mon);
      Staff p1;
      p1.job = s1;
      p1.name = s2;
      p1.number = stoi(numb);
      p1.money = stoi(mon);
      Peo.push_back(p1);
      cout << "名字：" << s1 << setw(15) << "编号：" << num << setw(15)
           << "职务：" << s2 << setw(15) << "工资：" << mon << endl;
    }
  }
}
void Main::delete_all()  //删除全部
{
  vector<Staff>::iterator w;
  if (Peo.size() == 0)
    cout << "删除失败\n";
  else {
    cout << "总人数是" << Peo.size() << endl;
    for (w = Peo.begin(); w != Peo.end(); w++) {
      w = Peo.erase(w);
      w--;
    }
    cout << "删除成功" << endl;
  }
}
void Main::Show_all() {
  cout << "1.根据职位排序" << endl;
  cout << "2.根据编号排序" << endl;
  int opr;
  opr = intRead();
  while (opr < 1 || opr > 2) {
    cout << "请输入合法的选项!" << endl;
    opr = intRead();
  }
  if (opr == 1) {
    for (int k = 1; k <= JOB_SORT_NUM; k++)
      for (int i = 0; i < Peo.size(); i++) {
        if (Peo[i].jobid == k) cout << Peo[i] << endl;
      }
  } else {
    for (int i = 0; i < M.Peo.size(); i++) {
      cout << Peo[i] << endl;
    }
  }
}
void Main::write()  //存入txt文件模块
{
  // string str="月底工资账单总览*";
  FILE *fp = fopen("a.txt", "w");
  fprintf(fp, "%d\n", Peo.size());
  for (int i = 0; i < Peo.size(); i++) {
    fprintf(fp, "%s %s %d %d\n", Peo[i].job.c_str(), Peo[i].name.c_str(),
            Peo[i].number, Peo[i].money);
  }
  cout << "copy成功" << endl;  //每次打开文件后最后都要关掉，不然存不进去
}
void Main::Promote()  //升职模块
{
  string name1;             //升职人员的名字
  string zhiwu;             //所升的职务
  double money1, upnum, j;  //升职后的工资
  cout << "请输入要升职的人数：" << endl;
  cin >> upnum;
  if (upnum == 0 || Peo.size() == 0 || upnum > Peo.size()) {
    cout << "人数不合法或无人员!操作失败\n";
    return;
  }
  bool ok = 0;
  for (int i = 1; i <= upnum; i++) {
    cout << "请输入第" << i << "升职人的名字" << endl;
    cin >> name1;
    int matchnum = 0;
    for (j = 0; j < Peo.size(); j++)
      if (Peo[j].name == name1) {
        matchnum++;
        cout << "匹配到结果" << matchnum << endl;
        cout << "请选择升职的职位" << endl;
        for (int j = 1; j <= JOB_SORT_NUM; j++) {
          cout << setw(9) << j << "." << JOBS[j] << endl;
        }
        int opr;
        opr = intRead();
        while (opr < 1 || opr > JOB_SORT_NUM) {
          cout << "请输入正确的选项!" << endl;
          opr = intRead();
        }
        Peo[j].job = JOBS[opr];
        Peo[j].jobid = opr;  //同时修改
        ok = 1;
      }
  }
  if (!ok)
    //没有此人的判断条件有三个 1.输入的人数为0  2.输入的人数超过总人数
    // 3.输入的名字没有存在
    cout << "没有此人" << endl;
}
void Main::ShowRewardtheMonth()  //   显示工资模块
{
  cout << "                    月底工资账单总览                      " << endl;
  for (int i = 0; i < Peo.size(); i++) {
    cout << "名字：" << Peo[i].name << setw(15) << "编号：" << Peo[i].number
         << setw(15) << "职务：" << Peo[i].job << setw(15) << "工资："
         << Peo[i].money << endl;
    if (Peo[i].jobid == 2 || Peo[i].jobid == 4) {
      cout << setw(15) << "销售额" << Peo[i].salevolume << setw(15)
           << "提成:" << Peo[i].plusmoney << endl;
    } else if (Peo[i].jobid == 3) {
      cout << setw(15) << "工作时长" << Peo[i].hours << endl;
    }
  }
  if (Peo.size() == 0) cout << "无人员" << endl;
}
void Main::Look()  //查找模块
{
  string name1;
  cout << "请输入要查找人的姓名:" << endl;
  cin >> name1;
  bool fnd = 0;
  for (int i = 0; i < Peo.size(); i++)
    if (Peo[i].name == name1) {
      fnd = 1;
      cout << "名字：" << Peo[i].name << setw(15) << "编号：" << Peo[i].number
           << setw(15) << "职务：" << Peo[i].job << setw(15) << "工资："
           << Peo[i].money;
    }
  if (!fnd) cout << "没有此人" << endl;
}
void Main::Increase()  //增加人员模块
{
  string name1;
  string job1;
  int numb;
  cout << "请输入要增加的人数：" << endl;
  cin >> numb;
  for (int i = 1; i <= numb; i++) {
    cout << "请输入第" << i << "个人的名字：" << endl;
    cin >> name1;
    cout << "请输入职务：" << endl;
    cout << "     1.经理" << endl;
    cout << "     2.销售经理" << endl;
    cout << "     3.兼职技术人员" << endl;
    cout << "     4.兼职推销员" << endl;
    int opt;
    opt = intRead();
    while (opt <= 0 || opt > 4)
      cout << "请输入正确的选项" << endl, opt = intRead();
    job1 = JOBS[opt];
    Staff::sum++;
    Staff ch(job1, name1, 0, Staff::sum);
    Peo.push_back(ch);
  }
}
void Main::Delete()  //删除模块
{
  string name1Orid;
  int numb, sum;
  cout << "请输入要删除的人数：" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "操作失败\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "请输入要删除的第" << i << "个人的姓名或编号：" << endl;
    cin >> name1Orid;
    bool digit = 0;
    if (isdigit(name1Orid[0])) digit = 1;
    string take;
    bool ok = 0;
    for (int j = 0; j < Peo.size(); j++) {
      sum = Peo.size();
      if (digit)
        take = to_string(Peo[j].number);
      else
        take = Peo[j].name;
      cout << Peo[j] << endl;
      if (take == name1Orid) {
        cout << "是否删除y/n？" << endl;
        char modify;
        cin >> modify;
        while (modify != 'y' && modify != 'n') cin >> modify;
        if (modify == 'n') continue;
        Peo.erase(Peo.begin() + j);
        cout << "删除成功" << endl;
        ok = 1;
      }
    }
    if (!ok) cout << "没有此人！" << endl;
  }
}
class Financial : public Function {
 public:
  Financial() { functionname = "Finacial"; }
  inline int CalcPlus(int Sales) {
    int pos = 0;
    for (int i = 0; i < PLUS_STEP_NUM; i++) {
      if (PLUS_BOUND[i] <= Sales && Sales < PLUS_BOUND[i + 1]) {
        return PLUS_RATE[i] * 1.0 * Sales;
      }
    }
  }
  inline double qStaticMoney(int id) {
    if (id > 3) {
      cout << "只有经理和销售经理才有固定工资" << endl;
      return 0;
    }
    return (id == 1 ? MONEY_MANAGER : MONEY_SALEMANAGER);
  }
  inline double GetMoneyByJob(Staff &worker, double salevolumeOrhours = 0) {
    if (worker.jobid == 1) {
      worker.money = MONEY_MANAGER;
    }
    if (worker.jobid == 2) {
      worker.money = MONEY_SALEMANAGER + CalcPlus(salevolumeOrhours);
      worker.plusmoney = CalcPlus(salevolumeOrhours);
      worker.salevolume = salevolumeOrhours;
    }
    if (worker.jobid == 3) {
      worker.hours = salevolumeOrhours;
      worker.money = worker.hours * MONEY_PER_HOUR;
    }
    if (worker.jobid == 4) {
      worker.money = worker.plusmoney = CalcPlus(salevolumeOrhours);
      worker.salevolume = salevolumeOrhours;
    }
  }
  void ModifyRewardMethod() {
    cout << "是否修改经理月薪？ y/n" << endl;
    char modify;
    cin >> modify;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      MONEY_MANAGER = intRead();
    }
    cout << "是否修改提成率？y/n" << endl;
    cin >> modify;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      cout << "请输入提成阶段数：" << endl;
      PLUS_STEP_NUM = intRead();
      while (PLUS_STEP_NUM > 5)
        cout << "提成阶段数超出最高限制！请重新输入！" << endl,
            PLUS_STEP_NUM = intRead();
      for (int i = 1; i <= PLUS_STEP_NUM; i++) {
        cout << "第" << i << "阶段:" << endl;
        cin >> PLUS_RATE[i];
      }
      PLUS_RATE[PLUS_STEP_NUM + 1] = inf;
    }
    cout << "是否修改时薪？y/n" << endl;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      cout << "请输入时薪" << endl;
      MONEY_PER_HOUR = intRead();
      while (MONEY_PER_HOUR <= 0) {
        cout << "请输入合法的时薪！" << endl, MONEY_PER_HOUR = intRead();
      }
    }
  }
  void SendReward();
} FinancialModule;

void Financial::SendReward() {
  for (int i = 0; i < M.Peo.size(); i++) {
    double salevolumeOrHours;
    Staff worker = M.Peo[i];
    cout << worker << endl;
    if (M.Peo[i].jobid == 1)
      cout << JOBS[1] << ":固定月薪 " << MONEY_MANAGER << endl,
          salevolumeOrHours = 0;
    else if (M.Peo[i].jobid == 2 || M.Peo[i].jobid == 4) {
      cout << "请输入当月销售额:" << endl;
      salevolumeOrHours = intRead();
      while (salevolumeOrHours < 0)
        cout << "请输入合法的销售额！" << endl, salevolumeOrHours = intRead();

    } else {  //技术人员
      cout << "请输入当月工作时长:" << endl;
      salevolumeOrHours = intRead();
      while (salevolumeOrHours < 0)
        cout << "请输入合法的工作时长！" << endl, salevolumeOrHours = intRead();
    }
    GetMoneyByJob(M.Peo[i], salevolumeOrHours);
  }
}
int Staff::sum = 0;
int main() {
  system("mode con cols=150 lines=30");
  system("color 3f");
  while (1) {
    system("cls");
    cout << "*---------------------------------------------------------------"
            "-*"
            "\n";
    cout << "*                          公司人员管理系统           "
            "   *"
         << endl;
    cout << "*                          1/增加人员及其个人信息               "
            "  "
            "  *"
         << endl;
    cout << "*                          2/删除人员及其个人信息               "
            "  "
            "  *"
         << endl;
    cout << "*                          3/删除全部人员及其个人信息           "
            "  "
            "   *"
         << endl;
    cout << "*                          4/查找人员及其个人信息               "
            "  "
            "  *"
         << endl;
    cout << "*                          5/显示全部人员个人信息                "
            "  *"
         << endl;
    cout << "*                          6/公司人员总数                       "
            "  "
            " *\n";
    cout << "*                          7/升职操作                           "
            "  "
            " *"
         << endl;
    cout << "*                          8/月底发薪                     "
            "  *"
         << endl;
    cout << "*                          9/月底工资账单总览                   "
            "  "
            "  *"
         << endl;
    cout << "*                          10/修改发薪方式                       "
            "  *"
         << endl;
    cout << "*                          11/信息整合保存成a.txt文件           "
            "   "
            "   *"
         << endl;
    cout << "*                          12/读取a.txt文件                     "
            "   "
            "  *"
         << endl;
    cout << "----------------------------------------------------------------"
            "--"
            "-*"
         << endl;
    cout << "请输入操作选项" << endl;
    int opr;
    opr = intRead();
    switch (opr) {
      case 1:
        M.Increase();
        break;
      case 2:
        M.Delete();
        break;
      case 3:
        M.delete_all();
        break;
      case 4:
        M.Look();
        break;
      case 5:
        M.Show_all();
        break;
      case 6:
        cout << "公司总人数:" << M.Sum() << endl;
        break;
      case 7:
        M.Promote();
        break;
      case 8:  //月底发薪
        FinancialModule.SendReward();
        break;
      case 9:
        M.ShowRewardtheMonth();
        break;
      case 10:
        FinancialModule.ModifyRewardMethod();
        break;
      case 11:
        M.write();
        break;
      case 12:
        M.ReadFromFile();
        break;
      default:
        cout << "请输入正确的选项！" << endl;
        break;
    }
    system("pause");  //按任意键继续，实现了画面冻结
    getchar();
  }
}