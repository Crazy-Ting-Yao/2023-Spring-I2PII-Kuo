#include<iostream>
#include<queue>
#include<set>
#include<algorithm>
class Board{
    public:
        int x;
        int y;
        int bd[3][3];
        Board(){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    std::cin>>bd[i][j];
                    if(!bd[i][j]){
                        x = i;
                        y = j;
                    }
                }
            }
        }
};

struct cmp{
    bool operator()(const Board &a, const Board &b){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(a.bd[i][j]-b.bd[i][j]) 
                    return a.bd[i]>b.bd[i];
        return false;
    }
};

bool solvable(const Board &b){
    int count = 0;
    for(int i=0;i<8;i++){
        if(!b.bd[i/3][i%3]) continue;
        for(int j=i+1;j<9;j++){
            if(b.bd[j/3][j%3]){
                if(b.bd[i/3][i%3]>b.bd[j/3][j%3])
                    count++;
            }
        }
    }
    return !(count&1);
}

bool done(const Board &b){
    int cnt = 1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==2&&j==2) return true;
            else if(b.bd[i][j]!=cnt++) return false;
        }
    }
}

int main(){
    int n;
    std::cin>>n;
    while(n--){
        Board board;
        if(!solvable(board)){
            std::cout<<"You'd better skip this game."<<std::endl;
            continue;
        }
        if(done(board)){
            std::cout<<"You can solve it within 0 steps."<<std::endl;
            continue;
        }
        std::queue<std::pair<Board,int>> q;
        std::set<Board,cmp> s;
        q.push(std::make_pair(board,0));
        s.insert(board);
        int steps=-1;
        while(!q.empty()){
            Board current = q.front().first;
            int curstep = q.front().second+1;
            if(curstep==15) break;
            q.pop();
            if(current.x<2){
                Board tmp = current;
                std::swap(tmp.bd[current.x][current.y], tmp.bd[current.x+1][current.y]);
                tmp.x++;
                if(done(tmp)){
                    steps = curstep;
                    break;
                }
                if(s.insert(tmp).second) q.push(std::make_pair(tmp,curstep));
            }
            if(current.y<2){
                Board tmp = current;
                std::swap(tmp.bd[current.x][current.y], tmp.bd[current.x][current.y+1]);
                tmp.y++;
                if(done(tmp)){
                    steps = curstep;
                    break;
                }
                if(s.insert(tmp).second) q.push(std::make_pair(tmp,curstep));                
            }
            if(current.x){
                Board tmp = current;
                std::swap(tmp.bd[current.x][current.y], tmp.bd[current.x-1][current.y]);
                tmp.x--;
                if(done(tmp)){
                    steps = curstep;
                    break;
                }
                if(s.insert(tmp).second) q.push(std::make_pair(tmp,curstep));
            }
            if(current.y){
                Board tmp = current;
                std::swap(tmp.bd[current.x][current.y], tmp.bd[current.x][current.y-1]);
                tmp.y--;
                if(done(tmp)){
                    steps = curstep;
                    break;
                }
                if(s.insert(tmp).second) q.push(std::make_pair(tmp,curstep));
            }
        }
        if(steps==-1) std::cout<<"You'd better skip this game."<<std::endl;
        else std::cout<<"You can solve it within "<<steps<<" steps."<<std::endl;
    }
}