#include <bits/stdc++.h>
#define four 20000;
#define three 15000;
#define two 8000;
#define one 4000;
using namespace std;
#define inf 0x3f3f3f3f
string JOBS[] = {" ", "经理", "销售经理", "兼职技术人员", "兼职推销员"};

int PLUS_STEP_NUM;
double PLUS_RATE[7];
double MONEY_PER_HOUR;
double MONEY_MANAGER, MONEY_SALEMANAGER;
inline double qmoney(int id){
  return id==1:MONEY_MANAGER;
  if(id==2)return 
}
template <typename T>
inline int findElement(T *arr, T x, int len) {
  for (int i = 1; i <= len; i++) {
    if (arr[i] == x) return i;
  }
  return 0;
}
inline int intread() {
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
  Staff() {}
  Staff(string job1, string name1, double money1,
        int number1)  //构造函数初始化一个人员
  {
    job = job1;
    name = name1;
    number = number1;
    money = money1;
    jobid = findElement(JOBS, job1, 4);
  }
  ~Staff();
  static int sum;  //这是static类型的sum 控制编号数字
};
Staff::~Staff() {}

class Main  //总的控制台   控制人员；人员存放在vector的容器中
            //通过内部函数进行各种操作
{
 public:
  vector<Staff> Peo;

 public:
  Main() {}
  void Promote();   //升职函数
  void Show();      //显示总信息
  void Look();      //查找
  void Increase();  //增加一个成员
  void Delete();    //删除一个成员
  void all();
  void write();  //讲数据存入txt文件
  void read();
  void InputReward();
  int Sum()  //显示公司人数
  {
    return Peo.size();
  }
};

void Main::read()  //读取
{
  //  char www[200];
  cout << "*               融资股份有限公司人员管理系统                   *"
       << endl;
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
void Main::all()  //删除全部
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
  string name1;  //升职人员的名字 偷懒了 name后面加了个1就算新的名字
  string zhiwu;  //所升的职务
  double money1, numb, j;  //升职后的工资 升职人数 和for循环所用的一个变量j
  cout << "请输入要升职的人数：" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "操作失败\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "请输入第" << i << "升职人的名字" << endl;
    cin >> name1;
    for (j = 0; j < Peo.size(); j++)
      if (Peo[j].name == name1) {
        cout << "请输入要升职的职位" << endl;
        cin >> zhiwu;

        cout << "请输入职位的工资" << endl;
        cin >> money1;
        Peo[j].job = zhiwu;
        Peo[j].money = money1;
      }
    if (j == Peo.size())
      //没有此人的判断条件有三个 1.输入的人数为0  2.输入的人数超过总人数
      // 3.输入的名字没有存在
      cout << "没有此人" << endl;
  }
}
void Main::Show()  //   显示数据模块
{
  cout << "                    月底工资账单总览                      " << endl;
  for (int i = 0; i < Peo.size(); i++) {
    cout << "名字：" << Peo[i].name << setw(15) << "编号：" << Peo[i].number
         << setw(15) << "职务：" << Peo[i].job << setw(15) << "工资："
         << Peo[i].money << endl;
  }
  if (Peo.size() == 0) cout << "无人员" << endl;
}
void Main::Look()  //查找模块
{
  string name1;
  cout << "请输入要查找人的姓名:" << endl;
  cin >> name1;
  for (int i = 0; i < Peo.size(); i++)
    if (Peo[i].name == name1) {
      cout << "名字：" << Peo[i].name << setw(15) << "编号：" << Peo[i].number
           << setw(15) << "职务：" << Peo[i].job << setw(15) << "工资："
           << Peo[i].money;
    }
  cout << "没有此人" << endl;
}
void Main::Increase()  //增加人员模块
{
  string name1;
  string job1;
  double money1;
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
    opt=intread();
    while(opt<=0||opt>4){
      cout<<"请输入正确的选项"<<endl;
      cin>>opt;
    }
    job1=JOBS[opt];
    while (!findElement(JOBS, job1, 4)) {
      cout << "请输入合法的职位！" << endl;
      cin >> job1;
    }
    if()
    Staff::sum++;
    Staff ch(job1, name1, money1, Staff::sum);
    Peo.push_back(ch);
  }
}
void Main::Delete()  //删除模块
{
  string name1;
  int numb, j, sum;
  cout << "请输入要删除的人数：" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "操作失败\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "请输入要删除的第" << i << "个人的姓名：" << endl;
    cin >> name1;
    for (j = 0; j < Peo.size(); j++) {
      sum = Peo.size();
      if (Peo[j].name == name1) {
        Peo.erase(Peo.begin() + j);
        cout << "删除成功" << endl;
        break;
      }
    }
    if (j == sum) cout << "没有此人" << endl;
  }
}
inline int CalcPlus(int Sales) {
  int pos = 0;
  for (int i = 0; i <= PLUS_STEP_NUM; i++) {
    if (PLUS_RATE[i] <= Sales && Sales < PLUS_RATE[i + 1]) {
      return PLUS_RATE[i] * Sales;
    }
  }
}

void Main::InputReward() {
  cout << "是否修改经理名称？ y/n" << endl;
  char modify;
  cin >> modify;
  while (modify != 'y' && modify != 'n') cin >> modify;
  if (modify == 'y') {
    MONEY_MANAGER = intread();
  }
  cout << "是否修改提成率？y/n" << endl;
  cin >> modify;
  while (modify != 'y' && modify != 'n') cin >> modify;
  if (modify == 'y') {
    cout << "请输入提成阶段数：" << endl;
    cin >> PLUS_STEP_NUM;
    while (PLUS_STEP_NUM > 5) {
      cout << "提成阶段数超出最高限制！请重新输入！" << endl;
      cin >> PLUS_STEP_NUM;
    }
    for (int i = 1; i <= PLUS_STEP_NUM; i++) {
      cin >> PLUS_RATE[i];
    }
    PLUS_RATE[PLUS_STEP_NUM + 1] = inf;
  }
  cout << "是否修改时薪？y/n" << endl;
  while (modify != 'y' && modify != 'n') cin >> modify;
  if (modify == 'y') {
    cout << "请输入时薪" << endl;
    cin >> MONEY_PER_HOUR;
    while (MONEY_PER_HOUR <= 0) {
      cout << "请输入合法的时薪！" << endl;
      cin >> MONEY_PER_HOUR;
    }
  }
  for (int i = 0; i < Peo.size(); i++) {
    double plus = 0;
    if (Peo[i].jobid == 1) {
      Peo[i].money = MONEY_MANAGER;
      continue;
    }
    cout << "请输入" << Peo[i].job << " " << Peo[i].name << "的";
    double plusmoney = 0;
    if (Peo[i].jobid == 2) {
      double salevolume;
      cout << "销售额:" << endl;
      cin >> salevolume;
      while (salevolume < 0) {
        cout << "请输入合法的销售额！" << endl;
      }
      plusmoney = CalcPlus(salevolume);
      Peo[i].money = MONEY_SALEMANAGER + plusmoney;
      //+销售额
      Peo[i].plusmoney = plusmoney;
    }
    if (Peo[i].jobid == 3) {
      cout << "工作时间:" << endl;
      double hours;
      cin >> hours;
      while (hours < 0) {
        cout << "请输入合法的工作时间" << endl;
      }
      Peo[i].money = Peo[i].hours * MONEY_PER_HOUR;
      Peo[i].hours = hours;
    }
    if (Peo[i].jobid == 4) {
      double salevolume;
      cout << "销售额:" << endl;
      cin >> salevolume;
      while (salevolume < 0) {
        cout << "请输入合法的销售额！" << endl;
      }
      plusmoney = CalcPlus(salevolume);
      Peo[i].money = plusmoney;
      //+销售额?
      Peo[i].plusmoney = plusmoney;
      Peo[i].salevolume = salevolume;
    }
  }
}
int Staff::sum = 0;
int main() {
  system("mode con cols=150 lines=30");
  system("color 3f");
  Main M;
  while (1) {
    system("cls");
    cout << "*----------------------------------------------------------------*"
            "\n";
    cout << "*注：经理固定月薪：20000￥" << setw(15) << "销售经理:15000￥"
         << setw(15) << "兼职技术人员:8000￥" << setw(15)
         << "兼职推销员:4000￥                                          *"
         << endl;
    cout << "*                          融资股份有限公司人员管理系统           "
            "   *"
         << endl;
    cout << "*                                  月底工资账单总览               "
            "  *"
         << endl;
    cout << "*                          1/增加人员及其个人信息                 "
            "  *"
         << endl;
    cout << "*                          2/删除人员及其个人信息                 "
            "  *"
         << endl;
    cout << "*                          3/删除全部人员及其个人信息             "
            "   *"
         << endl;
    cout << "*                          4/查找人员及其个人信息                 "
            "  *"
         << endl;
    cout << "*                          5/升职操作                             "
            " *"
         << endl;
    cout << "*                          6/公司人员总数                         "
            " *\n";
    cout << "*                          7/月底工资账单总览                     "
            "  *"
         << endl;
    cout << "*                          8/负责人联系方式                       "
            "  *"
         << endl;
    cout << "*                          9/信息整合保存成a.txt文件              "
            "   *"
         << endl;
    cout << "*                          A/读取a.txt文件                        "
            "  *"
         << endl;
    cout << "------------------------------------------------------------------"
            "-*"
         << endl;
    char num = getchar();
    switch (num) {
      case '1':
        M.Increase();
        break;
      case '2':
        M.Delete();
        break;
      case '3':
        M.all();
        break;
      case '4':
        M.Look();
        break;
      case '7':
        M.Show();
        break;
      case '8':
        cout << "微信：1596321；手机号：1598321" << endl;
        break;
      case '9':
        M.write();
        break;
      case '5':
        M.Promote();
        break;
      case '6':
        cout << "公司总人数:" << M.Sum() << endl;
        break;
      case 'A':
        M.read();
        break;
      default:
        return 0;
    }
    system("pause");  //按任意键继续，实现了画面冻结
    getchar();
  }
}