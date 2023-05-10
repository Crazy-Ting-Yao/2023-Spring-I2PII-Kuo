#include <iostream>
#include <string>
using namespace std;

class Guest {
public:
	Guest();
	Guest(string s, int m, int ski);
	~Guest();
	string get_name();
	int get_money();
	int get_skill();
	void Win(int m);
	
private:
	string name;
	int money;
	int skill;
};

class Casino {
public:
	Casino();
	~Casino();
	void GuestEnter(string s, int m, int ski);
	void Win(string s, int m);
	void EndDay();
	void Result();
	
private:
	int guest_num;
	Guest *guest[1009];
	
	int income;
	int list_num;
	string blacklist[1009];
};

using namespace std;

int n;
Casino casino = {};

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		string op;
		int q;
		
		cin >> op >> q;
		for (int j = 0; j < q; ++ j) {
			cin >> op;
			if (op == "Guest") {
				string name; 
				int money, skill;
				cin >> name >> money >> skill;
				casino.GuestEnter(name, money, skill);
			} 
			else if (op == "Win") {
				string name;
				int money;
				cin >> name >> money;
				casino.Win(name, money);
			}
		}
		casino.EndDay();
	}
	casino.Result();
}

Guest::Guest(){}
Guest::Guest(string s, int m, int ski) {name = s, money = m; skill = ski;}
Guest::~Guest() {}
string Guest::get_name() {return name;}
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m; }

Casino::Casino(){}
Casino::~Casino(){}
void Casino::GuestEnter(string s, int m, int ski){
    for(int i=0;i<guest_num;i++) if(s==guest[i]->get_name()) return;
    for(int i=0;i<list_num;i++) if(s==blacklist[i]) return;
    guest[guest_num++] = new Guest(s,m,ski);
}
void Casino::Win(string s, int m){
    for(int i=0;i<list_num;i++) if(s==blacklist[i]) return;
    for(int i=0;i<guest_num;i++){
        if(s==guest[i]->get_name()){
            if(m>0){
                income-=m;
                guest[i]->Win(m);
                if(2*guest[i]->get_skill()<m) blacklist[list_num++] = s;
            }
            else{
                if(guest[i]->get_money()<(-m)){
                    income+=guest[i]->get_money();
                    blacklist[list_num++] = s;
                }
                else{
                    income-=m;
                    guest[i]->Win(m);
                }

            }
            return;
        }
    }
}
void Casino::EndDay(){
    for(int i=0;i<guest_num;i++) delete guest[i];
    guest_num = 0;
}
void Casino::Result(){
    std::cout<<income<<std::endl;
    for(int i=0;i<list_num;i++) std::cout<<blacklist[i]<<endl;
}