#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <queue>

using std::vector;
using std::set;
using std::list;
using std::cout;
using std::endl;

// A state contains seven components:
// The first three components denote the current numbers of
// wolves, goats and cabbages at the left bank of the river.
// The fourth to sixth components denote the current numbers
// of wolves, goats and cabbages at the right bank.
// The seventh component denotes the location of the boat:
// 1 means "left bank" and -1 means "right bank".
using State = vector<int>;
class Crossing
{
private:
    vector<int> _items;     // wolves, goats and cabbages
                           // we use vector<int> as a tuple (int, int, int)
                           // the first integer indicates the number of wolves
                           // the second integer indicates the number of goats
                           // the third integer indicates the number of cabbages.
    set<list<State>> _paths;  // trial paths in progress
    set<State> _explored;     // explored states
    set<list<State>> _solutions;
public:
    // specify the numbers of wolves, goats and cabbages
    Crossing(vector<int> np): _items {np} { }
    // the starting point of your implementation
    void solve();
    // extend to other possible states from a certain state
    set<State> extend(State s);
    // may use s[6] to indicate the direction of move
    State Go(State s, int wolf, int goat, int cabbage);
    // check the validity of a state
    bool valid(State s);
    // check if all people are at the right bank
    bool found(State s);
    void show_solutions() {
        for (auto path : _solutions) {
            for (auto s : path) {
                if (!s.empty()) {
                    cout << "(" << s[0] << ", " << s[1] << ", " << s[2] << ")";
                    cout << "(" << s[3] << ", " << s[4] << ", " << s[5] << ")";
                    if (s[6]==1) cout << " left\n";
                    else cout << " right\n";
                }
            }
            cout << "done" << endl;
        }
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    int X, Y, Z; //Number of wolves, goats and cabbages
    cin >> X >> Y >> Z;
    Crossing p({X, Y, Z});
    p.solve();
    p.show_solutions();
}
// the starting point of your implementation
void Crossing::solve(){
    queue<list<State>> paths;
    vector<int> start_state = {_items[0], _items[1], _items[2], 0, 0, 0, 1};
    paths.push({start_state});
    do{ 
        list<State> current = paths.front();
        paths.pop();
        for(auto &it: current) _explored.insert(it);
        set<State> next_states = extend(current.back());
        for(auto &it: next_states){
            current.push_back(it);
            if(found(it)) _solutions.insert(current);
            else paths.push(current);
            current.pop_back();
        }
        _explored.clear();
    }while(!paths.empty());
}
// extend to other possible states from a certain state
set<State> Crossing::extend(State s){
    set<State> ret;
    State tmp = Go(s, 1, 0 ,0);
    if(valid(tmp) && _explored.find(tmp)==_explored.end()) ret.insert(tmp);
    tmp = Go(s, 0, 1 ,0);
    if(valid(tmp) && _explored.find(tmp)==_explored.end()) ret.insert(tmp);
    tmp = Go(s, 0, 0 ,1);
    if(valid(tmp) && _explored.find(tmp)==_explored.end()) ret.insert(tmp);
    tmp = Go(s, 0, 0 ,0);
    if(valid(tmp) && _explored.find(tmp)==_explored.end()) ret.insert(tmp);
    return ret;
}
// may use s[6] to indicate the direction of move
State Crossing::Go(State s, int wolf, int goat, int cabbage){
    State ret;
    if(s[6]) ret = {s[0]-wolf, s[1]-goat, s[2]-cabbage, s[3]+wolf, s[4]+goat, s[5]+cabbage, 0};
    else ret = {s[0]+wolf, s[1]+goat, s[2]+cabbage, s[3]-wolf, s[4]-goat, s[5]-cabbage, 1};
    return ret;
}
// check the validity of a state
bool Crossing::valid(State s){
    if(s[6]){
        if((s[3]<=s[4] || s[4]==0) && (s[4]<=s[5] || s[5]==0) && s[3]>=0 && s[4] >=0 && s[5] >=0) return true;
        return false;
    }
    else{
        if((s[0]<=s[1] || s[1]==0) && (s[1]<=s[2] || s[2]==0) && s[0]>=0 && s[1] >=0 && s[2] >=0) return true;
        return false;
    }
}
// check if all people are at the right bank
bool Crossing::found(State s){
    if(s[0] || s[1] || s[2] || s[6]) return false;
    return true;
}