#include <bits/stdc++.h>

using namespace std;
#define inf 0x3f3f3f3f
#define JOB_SORT_NUM 4
string JOBS[] = {" ", "����", "���۾���", "��ְ������Ա", "��ְ����Ա"};

int PLUS_STEP_NUM = 3;
double PLUS_RATE[7] = {0.3, 0.4, 0.5};
double PLUS_BOUND[7] = {0, 10000, 20000, 30000};
double MONEY_PER_HOUR = 100;  //��ʼʱн100
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
  string name;  //����
  bool sex;     // 1��
};
class Staff : public Person  //����һ����Ա����
{
 public:
  string job;  //ְλ
  int jobid;
  int number;    //���
  double money;  //����
  double hours;
  double plusmoney;
  double salevolume;
  Staff() { money = hours = plusmoney = salevolume = 0; }
  Staff(string job1, string name1, double money1,
        int number1)  //���캯����ʼ��һ����Ա
  {
    job = job1;
    name = name1;
    number = number1;
    money = money1;
    hours = plusmoney = salevolume = 0;
    jobid = findElement(JOBS, job1, 4);
  }
  ~Staff() {}

  static int sum;  //����static���͵�sum ���Ʊ������
};
ostream &operator<<(ostream &o, const Staff &s) {
  o << setw(0) << "��ţ�" << s.number << setw(15) << "������" << s.name
    << setw(15) << "ְλ��" << s.job << setw(15);
  return o;
}
class Function {
 public:
  string functionname;
};

class Main {
  //�ܵĿ���̨   ������Ա����Ա�����vector��������
  //ͨ���ڲ��������и��ֲ���
 public:
  vector<Staff> Peo;

 public:
  Main() {}
  void Promote();             //��ְ����
  void ShowRewardtheMonth();  //��ʾ����Ϣ
  void Look();                //����
  void Increase();            //����һ����Ա
  void Delete();              //ɾ��һ����Ա
  void delete_all();
  void write();  //�����ݴ���txt�ļ�
  void ReadFromFile();
  void InputReward();
  void Show_all();
  int Sum()  //��ʾ��˾����
  {
    return Peo.size();
  }
} M;

void Main::ReadFromFile()  //��ȡ
{
  // cout << "*               ��˾��Ա����ϵͳ                   *" << endl
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
      cout << "���֣�" << s1 << setw(15) << "��ţ�" << num << setw(15)
           << "ְ��" << s2 << setw(15) << "���ʣ�" << mon << endl;
    }
  }
}
void Main::delete_all()  //ɾ��ȫ��
{
  vector<Staff>::iterator w;
  if (Peo.size() == 0)
    cout << "ɾ��ʧ��\n";
  else {
    cout << "��������" << Peo.size() << endl;
    for (w = Peo.begin(); w != Peo.end(); w++) {
      w = Peo.erase(w);
      w--;
    }
    cout << "ɾ���ɹ�" << endl;
  }
}
void Main::Show_all() {
  cout << "1.����ְλ����" << endl;
  cout << "2.���ݱ������" << endl;
  int opr;
  opr = intRead();
  while (opr < 1 || opr > 2) {
    cout << "������Ϸ���ѡ��!" << endl;
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
void Main::write()  //����txt�ļ�ģ��
{
  // string str="�µ׹����˵�����*";
  FILE *fp = fopen("a.txt", "w");
  fprintf(fp, "%d\n", Peo.size());
  for (int i = 0; i < Peo.size(); i++) {
    fprintf(fp, "%s %s %d %d\n", Peo[i].job.c_str(), Peo[i].name.c_str(),
            Peo[i].number, Peo[i].money);
  }
  cout << "copy�ɹ�" << endl;  //ÿ�δ��ļ������Ҫ�ص�����Ȼ�治��ȥ
}
void Main::Promote()  //��ְģ��
{
  string name1;             //��ְ��Ա������
  string zhiwu;             //������ְ��
  double money1, upnum, j;  //��ְ��Ĺ���
  cout << "������Ҫ��ְ��������" << endl;
  cin >> upnum;
  if (upnum == 0 || Peo.size() == 0 || upnum > Peo.size()) {
    cout << "�������Ϸ�������Ա!����ʧ��\n";
    return;
  }
  bool ok = 0;
  for (int i = 1; i <= upnum; i++) {
    cout << "�������" << i << "��ְ�˵�����" << endl;
    cin >> name1;
    int matchnum = 0;
    for (j = 0; j < Peo.size(); j++)
      if (Peo[j].name == name1) {
        matchnum++;
        cout << "ƥ�䵽���" << matchnum << endl;
        cout << "��ѡ����ְ��ְλ" << endl;
        for (int j = 1; j <= JOB_SORT_NUM; j++) {
          cout << setw(9) << j << "." << JOBS[j] << endl;
        }
        int opr;
        opr = intRead();
        while (opr < 1 || opr > JOB_SORT_NUM) {
          cout << "��������ȷ��ѡ��!" << endl;
          opr = intRead();
        }
        Peo[j].job = JOBS[opr];
        Peo[j].jobid = opr;  //ͬʱ�޸�
        ok = 1;
      }
  }
  if (!ok)
    //û�д��˵��ж����������� 1.���������Ϊ0  2.�������������������
    // 3.���������û�д���
    cout << "û�д���" << endl;
}
void Main::ShowRewardtheMonth()  //   ��ʾ����ģ��
{
  cout << "                    �µ׹����˵�����                      " << endl;
  for (int i = 0; i < Peo.size(); i++) {
    cout << "���֣�" << Peo[i].name << setw(15) << "��ţ�" << Peo[i].number
         << setw(15) << "ְ��" << Peo[i].job << setw(15) << "���ʣ�"
         << Peo[i].money << endl;
    if (Peo[i].jobid == 2 || Peo[i].jobid == 4) {
      cout << setw(15) << "���۶�" << Peo[i].salevolume << setw(15)
           << "���:" << Peo[i].plusmoney << endl;
    } else if (Peo[i].jobid == 3) {
      cout << setw(15) << "����ʱ��" << Peo[i].hours << endl;
    }
  }
  if (Peo.size() == 0) cout << "����Ա" << endl;
}
void Main::Look()  //����ģ��
{
  string name1;
  cout << "������Ҫ�����˵�����:" << endl;
  cin >> name1;
  bool fnd = 0;
  for (int i = 0; i < Peo.size(); i++)
    if (Peo[i].name == name1) {
      fnd = 1;
      cout << "���֣�" << Peo[i].name << setw(15) << "��ţ�" << Peo[i].number
           << setw(15) << "ְ��" << Peo[i].job << setw(15) << "���ʣ�"
           << Peo[i].money;
    }
  if (!fnd) cout << "û�д���" << endl;
}
void Main::Increase()  //������Աģ��
{
  string name1;
  string job1;
  int numb;
  cout << "������Ҫ���ӵ�������" << endl;
  cin >> numb;
  for (int i = 1; i <= numb; i++) {
    cout << "�������" << i << "���˵����֣�" << endl;
    cin >> name1;
    cout << "������ְ��" << endl;
    cout << "     1.����" << endl;
    cout << "     2.���۾���" << endl;
    cout << "     3.��ְ������Ա" << endl;
    cout << "     4.��ְ����Ա" << endl;
    int opt;
    opt = intRead();
    while (opt <= 0 || opt > 4)
      cout << "��������ȷ��ѡ��" << endl, opt = intRead();
    job1 = JOBS[opt];
    Staff::sum++;
    Staff ch(job1, name1, 0, Staff::sum);
    Peo.push_back(ch);
  }
}
void Main::Delete()  //ɾ��ģ��
{
  string name1Orid;
  int numb, sum;
  cout << "������Ҫɾ����������" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "����ʧ��\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "������Ҫɾ���ĵ�" << i << "���˵��������ţ�" << endl;
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
        cout << "�Ƿ�ɾ��y/n��" << endl;
        char modify;
        cin >> modify;
        while (modify != 'y' && modify != 'n') cin >> modify;
        if (modify == 'n') continue;
        Peo.erase(Peo.begin() + j);
        cout << "ɾ���ɹ�" << endl;
        ok = 1;
      }
    }
    if (!ok) cout << "û�д��ˣ�" << endl;
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
      cout << "ֻ�о�������۾�����й̶�����" << endl;
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
    cout << "�Ƿ��޸ľ�����н�� y/n" << endl;
    char modify;
    cin >> modify;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      MONEY_MANAGER = intRead();
    }
    cout << "�Ƿ��޸�����ʣ�y/n" << endl;
    cin >> modify;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      cout << "��������ɽ׶�����" << endl;
      PLUS_STEP_NUM = intRead();
      while (PLUS_STEP_NUM > 5)
        cout << "��ɽ׶�������������ƣ����������룡" << endl,
            PLUS_STEP_NUM = intRead();
      for (int i = 1; i <= PLUS_STEP_NUM; i++) {
        cout << "��" << i << "�׶�:" << endl;
        cin >> PLUS_RATE[i];
      }
      PLUS_RATE[PLUS_STEP_NUM + 1] = inf;
    }
    cout << "�Ƿ��޸�ʱн��y/n" << endl;
    while (modify != 'y' && modify != 'n') cin >> modify;
    if (modify == 'y') {
      cout << "������ʱн" << endl;
      MONEY_PER_HOUR = intRead();
      while (MONEY_PER_HOUR <= 0) {
        cout << "������Ϸ���ʱн��" << endl, MONEY_PER_HOUR = intRead();
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
      cout << JOBS[1] << ":�̶���н " << MONEY_MANAGER << endl,
          salevolumeOrHours = 0;
    else if (M.Peo[i].jobid == 2 || M.Peo[i].jobid == 4) {
      cout << "�����뵱�����۶�:" << endl;
      salevolumeOrHours = intRead();
      while (salevolumeOrHours < 0)
        cout << "������Ϸ������۶" << endl, salevolumeOrHours = intRead();

    } else {  //������Ա
      cout << "�����뵱�¹���ʱ��:" << endl;
      salevolumeOrHours = intRead();
      while (salevolumeOrHours < 0)
        cout << "������Ϸ��Ĺ���ʱ����" << endl, salevolumeOrHours = intRead();
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
    cout << "*                          ��˾��Ա����ϵͳ           "
            "   *"
         << endl;
    cout << "*                          1/������Ա���������Ϣ               "
            "  "
            "  *"
         << endl;
    cout << "*                          2/ɾ����Ա���������Ϣ               "
            "  "
            "  *"
         << endl;
    cout << "*                          3/ɾ��ȫ����Ա���������Ϣ           "
            "  "
            "   *"
         << endl;
    cout << "*                          4/������Ա���������Ϣ               "
            "  "
            "  *"
         << endl;
    cout << "*                          5/��ʾȫ����Ա������Ϣ                "
            "  *"
         << endl;
    cout << "*                          6/��˾��Ա����                       "
            "  "
            " *\n";
    cout << "*                          7/��ְ����                           "
            "  "
            " *"
         << endl;
    cout << "*                          8/�µ׷�н                     "
            "  *"
         << endl;
    cout << "*                          9/�µ׹����˵�����                   "
            "  "
            "  *"
         << endl;
    cout << "*                          10/�޸ķ�н��ʽ                       "
            "  *"
         << endl;
    cout << "*                          11/��Ϣ���ϱ����a.txt�ļ�           "
            "   "
            "   *"
         << endl;
    cout << "*                          12/��ȡa.txt�ļ�                     "
            "   "
            "  *"
         << endl;
    cout << "----------------------------------------------------------------"
            "--"
            "-*"
         << endl;
    cout << "���������ѡ��" << endl;
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
        cout << "��˾������:" << M.Sum() << endl;
        break;
      case 7:
        M.Promote();
        break;
      case 8:  //�µ׷�н
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
        cout << "��������ȷ��ѡ�" << endl;
        break;
    }
    system("pause");  //�������������ʵ���˻��涳��
    getchar();
  }
}