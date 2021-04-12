#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

enum Cell{ x='x', z='o', Empty='E' };

enum State{ RUNNING, HUMAN_WIN='1', AI_WIN='2', DRAW='3' };

struct Game{
    vector<vector<Cell>> f;
    int turn;
    int size;
    State state;
    Cell HUMAN;
    Cell AI;
};

inline void clear(){
    system("cls");
}

void startGame(Game& g){
    g.size = 3;
    g.f.resize(g.size);
    for(int i = 0; i < g.size; i++) g.f[i].resize(g.size);
    for(int y = 0; y < g.size; y++) for(int x = 0; x < g.size ; x++) g.f[y][x] = Empty;
    g.state = RUNNING;
    bool flag;
    cout<<"choose your side(x-1/o-0)"<<'\n';
    cin>>flag;
    if(flag) {
        g.HUMAN = x;
        g.AI = z;
    }
    else {
        g.HUMAN = z;
        g.AI = x;
    }
    g.turn = 0;
}

void ShowField(const Game& g){
    for(int i = 0; i < g.size; i++){
        cout<<"|";
        for(int j = 0; j < g.size; j++) cout<<char(g.f[i][j])<<"|";
        cout<<'\n';
    }
    cout<<'\n';
    cout<<"HUMAN -- "<<char(g.HUMAN)<<'\n';
    cout<<"AI    -- "<<char(g.AI)<<'\n';
}

bool WinCheck(Game& g){
    bool flag = 0;
    bool temp = 1;
    for(int i = 0; i < g.size && !flag; i++){
        for(int j = 0; j < g.size && !flag; j++) {
            if(g.f[i][j] != g.f[i][0] || g.f[i][i] == Empty) temp = 0;
        }
        if(temp) flag = 1;
        temp = 1;
    }
    if(flag) return flag;

    for(int i = 0; i < g.size && !flag; i++){
        for(int j = 0; j < g.size && !flag; j++) {
            if(g.f[j][i] != g.f[j][0] || g.f[j][i] == Empty) temp = 0;
        }
        if(temp) flag = 1;
        temp = 1;
    }
    if(flag) return flag;

    for(int i = 1; i < g.size; i++) if(g.f[i][i] != g.f[0][0] || g.f[i][i] == Empty) temp = 0;
    if(temp) return temp;
    temp = 1;
    for(int i = 1;i < g.size; i++) if(g.f[g.size-i-1][i] != g.f[g.size-1][0] || g.f[g.size-1][0] == Empty) temp = 0;
    if(temp) return temp;
    return flag;
}

void HumanStep(Game& g){
    bool flag = 1;
    cout<<"enter position of next figure"<<'\n';
    while(flag){
        int x,y;
        cin>>x>>y, x--, y--;
        if(g.f[y][x] != Empty) cout<<"This cell is already occupated\n";
        else g.f[y][x] = g.HUMAN, flag = 0;
    }
    int k = 0;
    for(int i = 0;i < g.size; i++) for(int j = 0; j < g.size; j++) if(g.f[i][j] == Empty) k++;
    if(WinCheck(g)){
        g.state = HUMAN_WIN;
        cout<<char(g.HUMAN)<<" won"<<'\n';
    }
    else if(!k){
        g.state = DRAW;
        cout<<"The forces were equal\n";
    }
}

void AIStep(Game& g){
    int n = g.size;
    bool flag = 0, printed = 0, enter_flag=0;
    int xw,yw,xl,yl;

    srand(time(NULL));
    while(!enter_flag){
        yl = rand()%n;
        xl = rand()%n;
        if(g.f[yl][xl] == Empty)enter_flag=1;
    }

    for(int i = 0;i < n && !flag; i++){
        for(int j = 0; j < n; j++){
            if(g.f[i][j] == Empty){
                int ca=0, ch=0;
                for(int l = 0; l < n; l++) {
                    if (g.f[i][l] == g.AI) ca++;
                    if (g.f[i][l] == g.HUMAN) ch++;
                }
                if(ca+1 == n) yw = i, xw = j, flag = 1;
                if(ch+1 == n) yl = i, xl = j;
            }
        }
    }
    if(flag && !printed) g.f[yw][xw] = g.AI, printed=1;

    for(int i = 0; i < n && !flag; i++){
        for(int j = 0; j < n; j++){
            if(g.f[i][j] == Empty){
                int ca = 0, ch = 0;
                for(int l = 0; l < n; l++){
                    if(g.f[l][j] == g.AI) ca++;
                    if(g.f[l][j] == g.HUMAN) ch++;
                }
                if(ca+1 == n) yw = i, xw = j, flag = 1;
                if(ch+1 == n) yl = i, xl = j;
            }
        }
    }
    if(flag && !printed) g.f[yw][xw] = g.AI, printed=1;

    for(int i=0; i<n; i++) {
        int ca = 0, ch = 0;
        if(g.f[i][i] == Empty){
            for(int l = 0; l < n; l++){
                if(g.f[l][l] == g.AI) ca++;
                if(g.f[l][l] == g.HUMAN) ch++;
            }
        }
        if(ca+1 == n) yw = i, xw = i, flag = 1;
        if(ch+1 == n) yl = i, xl = i;
    }
    if(flag && !printed) g.f[yw][xw] = g.AI, printed=1;

    for(int i=0; i<n; i++) {
        int ca = 0, ch = 0;
        if(g.f[n-i-1][i] == Empty){
            for(int l = 0; l < n; l++){
                if(g.f[n-l-1][l] == g.AI) ca++;
                if(g.f[n-l-1][l] == g.HUMAN) ch++;
            }
        }
        if(ca+1 == n) yw = n-i-1, xw = i, flag = 1;
        if(ch+1 == n) yl = n-i-1, xl = i;
    }
    if(flag && !printed) g.f[yw][xw] = g.AI, printed=1;

    if(!printed) g.f[yl][xl] = g.AI;
    int k = 0;
    for(int i = 0;i < g.size; i++) for(int j = 0; j < g.size; j++) if(g.f[i][j] == Empty) k++;
    if(WinCheck(g)){
        g.state = AI_WIN;
        cout<<char(g.AI)<<" won"<<'\n';
    }
    else if(!k){
        g.state = DRAW;
        cout<<"The forces were equal\n";
    }
}

int main() {
    Game game;
    startGame(game);
    while(game.state == RUNNING){
        if(game.turn % 2){
            if(game.HUMAN == x) HumanStep(game);
            else AIStep(game);
        }
        else{
            if(game.HUMAN == 0) HumanStep(game);
            else AIStep(game);
        }
        clear();
        ShowField(game);
        game.turn++;
    }
    cout<<char(game.state)<<'\n';
    system("pause");
    return 0;
}
