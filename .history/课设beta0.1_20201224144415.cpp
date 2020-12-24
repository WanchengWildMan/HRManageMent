#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#define four 20000;
#define three 15000;
#define two 8000;
#define one 4000;
using namespace std;
string JOBS[] = {" ", "����", "���۾���", "��ְ������Ա", "��ְ����Ա"};
int PLUS_STEP_NUM;
double PLUS_RATE[7];
double MONEY_PER_HOUR;
double MONEY_MANAGER, MONEY_SALEMANAGER;
template <typename T>
bool findElement(T* arr,T x,int len){
  for(int i=1;i<)
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
  Staff() {}
  Staff(string job1, string name1, double money1,
        int number1)  //���캯����ʼ��һ����Ա
  {
    job = job1;
    name = name1;
    number = number1;
    money = money1;
  }
  ~Staff();
  static int sum;  //����static���͵�sum ���Ʊ������
};
Staff::~Staff() {}

class Main  //�ܵĿ���̨   ������Ա����Ա�����vector��������
            //ͨ���ڲ��������и��ֲ���
{
 public:
  vector<Staff> Peo;

 public:
  Main() {}
  void Promote();   //��ְ����
  void Show();      //��ʾ����Ϣ
  void Look();      //����
  void Increase();  //����һ����Ա
  void Delete();    //ɾ��һ����Ա
  void all();
  void write();  //�����ݴ���txt�ļ�
  void read();
  void InputPlus();
  int Sum()  //��ʾ��˾����
  {
    return Peo.size();
  }
};

void Main::read()  //��ȡ
{
  //  char www[200];
  cout << "*               ���ʹɷ����޹�˾��Ա����ϵͳ                   *"
       << endl;
  FILE *fp = fopen("a.txt", "r");
  {
    int num;
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++) {
      char s1[40], s2[40], num[40], mon[40];
      fscanf(fp, "%s%s%s%s", s1, s2, num, mon);
      Staff p1;
      p1.job = s1;
      p1.name = s2;
      p1.number = stoi(num);
      p1.money = stoi(num);
      Peo.push_back(p1);
      cout << "���֣�" << s1 << setw(15) << "��ţ�" << num << setw(15)
           << "ְ��" << s2 << setw(15) << "���ʣ�" << mon << endl;
    }
  }
}
void Main::all()  //ɾ��ȫ��
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
  string name1;  //��ְ��Ա������ ͵���� name������˸�1�����µ�����
  string zhiwu;  //������ְ��
  double money1, numb, j;  //��ְ��Ĺ��� ��ְ���� ��forѭ�����õ�һ������j
  cout << "������Ҫ��ְ��������" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "����ʧ��\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "�������" << i << "��ְ�˵�����" << endl;
    cin >> name1;
    for (j = 0; j < Peo.size(); j++)
      if (Peo[j].name == name1) {
        cout << "������Ҫ��ְ��ְλ" << endl;
        cin >> zhiwu;

        cout << "������ְλ�Ĺ���" << endl;
        cin >> money1;
        Peo[j].job = zhiwu;
        Peo[j].money = money1;
      }
    if (j == Peo.size())
      //û�д��˵��ж����������� 1.���������Ϊ0  2.�������������������
      // 3.���������û�д���
      cout << "û�д���" << endl;
  }
}
void Main::Show()  //   ��ʾ����ģ��
{
  cout << "                    �µ׹����˵�����                      " << endl;
  for (int i = 0; i < Peo.size(); i++) {
    cout << "���֣�" << Peo[i].name << setw(15) << "��ţ�" << Peo[i].number
         << setw(15) << "ְ��" << Peo[i].job << setw(15) << "���ʣ�"
         << Peo[i].money << endl;
  }
  if (Peo.size() == 0) cout << "����Ա" << endl;
}
void Main::Look()  //����ģ��
{
  string name1;
  cout << "������Ҫ�����˵�����:" << endl;
  cin >> name1;
  for (int i = 0; i < Peo.size(); i++)
    if (Peo[i].name == name1) {
      cout << "���֣�" << Peo[i].name << setw(15) << "��ţ�" << Peo[i].number
           << setw(15) << "ְ��" << Peo[i].job << setw(15) << "���ʣ�"
           << Peo[i].money;
    }
  cout << "û�д���" << endl;
}
void Main::Increase()  //������Աģ��
{
  string name1;
  string job1;
  double money1;
  int numb;
  cout << "������Ҫ���ӵ�������" << endl;
  cin >> numb;
  for (int i = 1; i <= numb; i++) {
    cout << "�������" << i << "���˵����֣�" << endl;
    cin >> name1;
    cout << "������ְ��" << endl;
    cin >> job1;
    while (findElement(JOBS, job1,4)) {
      cout << "������Ϸ���ְλ��" << endl;
      cin >> job1;
    }
    cout << "�����빤�ʣ�" << endl;
    cin >> money1;
    Staff::sum++;
    Staff ch(job1, name1, money1, Staff::sum);
    Peo.push_back(ch);
  }
}
void Main::Delete()  //ɾ��ģ��
{
  string name1;
  int numb, j, sum;
  cout << "������Ҫɾ����������" << endl;
  cin >> numb;
  if (numb == 0 || Peo.size() == 0 || numb > Peo.size()) {
    cout << "����ʧ��\n";
    return;
  }
  for (int i = 1; i <= numb; i++) {
    cout << "������Ҫɾ���ĵ�" << i << "���˵�������" << endl;
    cin >> name1;
    for (j = 0; j < Peo.size(); j++) {
      sum = Peo.size();
      if (Peo[j].name == name1) {
        Peo.erase(Peo.begin() + j);
        cout << "ɾ���ɹ�" << endl;
        break;
      }
    }
    if (j == sum) cout << "û�д���" << endl;
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

Main::InputPlus() {
  cout << "�Ƿ��޸�����ʣ�y/n" << endl;
  char modify;
  cin >> modify;
  while (modify != 'y' && modify != 'n') cin >> modify;
  if (modify == 'y') {
    cout << "��������ɽ׶�����" << endl;
    cin >> PLUS_STEP_NUM;
    while (PLUS_STEP_NUM > 5) {
      cout << "��ɽ׶�������������ƣ����������룡" << endl;
      cin >> PLUS_STEP_NUM;
    }
    for (int i = 1; i <= PLUS_STEP_NUM; i++) {
      cin >> PLUS_RATE[i];
    }
    PLUS_RATE[PLUS_STEP_NUM + 1] = inf;
  }
  cout << "�Ƿ��޸�ʱн��y/n" << endl;
  while (modify != 'y' && modify != 'n') cin >> modify;
  if (modify == 'y') {
    cout << "������ʱн" << endl;
    cin >> MONEY_PER_HOUR;
    while (MONEY_PER_HOUR <= 0) {
      cout << "������Ϸ���ʱн��" << endl;
      cin >> MONEY_PER_HOUR;
    }
  }
  for (int i = 0; i < Peo.size(); i++) {
    double plus = 0;
    if (Peo[i].jobid == 1) {
      Peo[i].money = MONEY_MANAGER;
      continue;
    }
    cout << "������" << Peo[i].job << " " << Peo[i].name << "��";
    double plusmoney = 0;
    if (Peo[i].jobid == 2) {
      double salevolume;
      cout << "���۶�:" << endl;
      cin >> salevolume;
      while (salevolume < 0) {
        cout << "������Ϸ������۶" << endl;
      }
      plusmoney = CalcPlus(salevolume);
      Peo[i].money = MONEY_SALEMANAGER + plusmoney;
      //+���۶�
      Peo[i].plusmoney = plusmoney;
    }
    if (Peo[i].jobid == 3) {
      cout << "����ʱ��:" << endl;
      double hours;
      cin >> hours;
      while (hours < 0) {
        cout << "������Ϸ��Ĺ���ʱ��" << endl;
      }
      Peo[i].money = Peo[i].hours * MONEY_PER_HOUR;
      Peo[i].hours = hours;
    }
    if (Peo[i].jobid == 4) {
      double salevolume;
      cout << "���۶�:" << endl;
      cin >> salevolume;
      while (salevolume < 0) {
        cout << "������Ϸ������۶" << endl;
      }
      plusmoney = CalcPlus(salevolume);
      Peo[i].money = plusmoney;
      //+���۶�?
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
    cout << "*ע������̶���н��20000��" << setw(15) << "���۾���:15000��"
         << setw(15) << "��ְ������Ա:8000��" << setw(15)
         << "��ְ����Ա:4000��                                          *"
         << endl;
    cout << "*                          ���ʹɷ����޹�˾��Ա����ϵͳ           "
            "   *"
         << endl;
    cout << "*                                  �µ׹����˵�����               "
            "  *"
         << endl;
    cout << "*                          1/������Ա���������Ϣ                 "
            "  *"
         << endl;
    cout << "*                          2/ɾ����Ա���������Ϣ                 "
            "  *"
         << endl;
    cout << "*                          3/ɾ��ȫ����Ա���������Ϣ             "
            "   *"
         << endl;
    cout << "*                          4/������Ա���������Ϣ                 "
            "  *"
         << endl;
    cout << "*                          5/��ְ����                             "
            " *"
         << endl;
    cout << "*                          6/��˾��Ա����                         "
            " *\n";
    cout << "*                          7/�µ׹����˵�����                     "
            "  *"
         << endl;
    cout << "*                          8/��������ϵ��ʽ                       "
            "  *"
         << endl;
    cout << "*                          9/��Ϣ���ϱ����a.txt�ļ�              "
            "   *"
         << endl;
    cout << "*                          A/��ȡa.txt�ļ�                        "
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
        cout << "΢�ţ�1596321���ֻ��ţ�1598321" << endl;
        break;
      case '9':
        M.write();
        break;
      case '5':
        M.Promote();
        break;
      case '6':
        cout << "��˾������:" << M.Sum() << endl;
        break;
      case 'A':
        M.read();
        break;
      default:
        return 0;
    }
    system("pause");  //�������������ʵ���˻��涳��
    getchar();
  }
}