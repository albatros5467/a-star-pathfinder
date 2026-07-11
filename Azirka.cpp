#include <iostream>
#include <vector>
#include <conio.h>    
#include <windows.h>  
#include <cmath>
#include <queue>

#define up    72
#define down  80
#define left  75
#define right 77
#define space 32
#define esc   27
#define W     87
#define A     65
#define S     83
#define D     68
#define w     119
#define a     97
#define s     115
#define d     100
#define Enter 13

using namespace std;

struct Node {
    COORD coord; 
    int fScore;  

    bool operator<(const Node& other) const {
        return fScore > other.fScore;
    }
};

class Azirka {
private:
    short int N;                 
    short int cursorX;           
    short int cursorY;           
    HANDLE hConsole;             
    vector<vector<int>> grid;    
    vector<vector<int>> gScore;
    vector<vector<COORD>> parent;
    
    void draw() {
        
        CONSOLE_CURSOR_INFO cursorInfo;
        cursorInfo.dwSize = 1;
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(hConsole, coord);

       
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                
                if (i == cursorY && j == cursorX) {
                    SetConsoleTextAttribute(hConsole, 9); 
                    cout << " *";                         
                    SetConsoleTextAttribute(hConsole, 7);
                }
                
                else {
                    if (grid[i][j] == 0) {
                        cout << " ."; 
                    }
                    else if (grid[i][j] == 1) {
                        SetConsoleTextAttribute(hConsole, 12); 
                        cout << " #";                          
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    else if (grid[i][j] == 2) {
                        SetConsoleTextAttribute(hConsole, 10); 
                        cout << " S";                          
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    else if (grid[i][j] == 3) {
                        SetConsoleTextAttribute(hConsole, 11); 
                        cout << " F";                         
                        SetConsoleTextAttribute(hConsole, 7);
                    }
                    else if (grid[i][j] == 4) {
                        SetConsoleTextAttribute(hConsole, 14); 
                        cout << " o";                          
                        SetConsoleTextAttribute(hConsole, 7);  
                    }
                }

                if (j == N - 1) {
                    cout << endl;
                }
            }
        }
    }

    bool handleInput() {
        int key = _getch();
        if (key == esc) return false;

        
        if (key == up || key == W || key == w) { if (cursorY > 0) cursorY--; }
        else if (key == down || key == S || key == s) { if (cursorY < N - 1) cursorY++; }
        else if (key == left || key == A || key == a) { if (cursorX > 0) cursorX--; }
        else if (key == right || key == D || key == d) { if (cursorX < N - 1) cursorX++; }

        else if (key == space || key == Enter) {
 
            if (grid[cursorY][cursorX] == 0 || grid[cursorY][cursorX] == 4) {
                grid[cursorY][cursorX] = 1;
            }
            else if (grid[cursorY][cursorX] == 1) {
                grid[cursorY][cursorX] = 0;
            }
        }
        return true;
    }

public:
    
    Azirka(short int size = 20) {
        N = size;
        cursorX = 1;
        cursorY = 1;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        
        grid.assign(N, vector<int>(N, 0));
        gScore.assign(N, vector<int>(N, 999999));
        parent.assign(N, vector<COORD>(N, { -1, -1 }));
        
        grid[1][1] = 2;     //start    
        grid[N - 1][N - 1] = 3; //finish
    }
    
    COORD findStart() {

        COORD temp = { -1, -1 };
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 2) {
                    temp.X = j;
                    temp.Y = i;
                    return temp;
                }
            }
        }
        return temp;
    }

    COORD findFinish() {
        COORD temp = { -1, -1 }; 
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 3) {
                    temp.X = j; 
                    temp.Y = i; 
                    return temp;
                }
            }
        }
        return temp;
    }

    int hScore(COORD Current,COORD finish) {
        return abs(Current.X - finish.X) + abs(Current.Y - finish.Y);
    }

    int getStepCost(COORD current, COORD neighbor) {
        if (current.X != neighbor.X && current.Y != neighbor.Y) {
            return 14;
        }
        return 10;
    }

    void searchPath() {
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 4) {
                    grid[i][j] = 0;
                }
            }
        }

        COORD finish = findFinish();
        COORD start = findStart();
        
        if (start.X == -1 || finish.X == -1) return;

        gScore.assign(N, vector<int>(N, 999999)); 
        gScore[start.Y][start.X] = 0;            
        priority_queue<Node> openSet;
        
        parent.assign(N, vector<COORD>(N, { -1, -1 }));

        Node startNode;
        startNode.coord = start;
        startNode.fScore = hScore(start, finish);
        openSet.push(startNode);

        vector<vector<bool>> closedSet(N, vector<bool>(N, false));

        
        bool pathFound = false;

        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();
            COORD currCoord = current.coord;

            
            if (currCoord.X == finish.X && currCoord.Y == finish.Y) {
                pathFound = true; 
                break;            
            }

            if (closedSet[currCoord.Y][currCoord.X] == true) {
                continue;
            }

            closedSet[currCoord.Y][currCoord.X] = true;

           
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {

                    if (dx == 0 && dy == 0) {
                        continue;
                    }

                    COORD neighbor;
                    neighbor.X = currCoord.X + dx;
                    neighbor.Y = currCoord.Y + dy;

                    
                    if (neighbor.X >= 0 && neighbor.X < N && neighbor.Y >= 0 && neighbor.Y < N &&
                        grid[neighbor.Y][neighbor.X] != 1 &&
                        closedSet[neighbor.Y][neighbor.X] == false)
                    {
                        int tentative_g = gScore[currCoord.Y][currCoord.X] + getStepCost(currCoord, neighbor);

                        if (tentative_g < gScore[neighbor.Y][neighbor.X]) {
                            parent[neighbor.Y][neighbor.X] = currCoord;
                            gScore[neighbor.Y][neighbor.X] = tentative_g;
                            int f = tentative_g + hScore(neighbor, finish);

                            Node neighborNode;
                            neighborNode.coord = neighbor;
                            neighborNode.fScore = f;
                            openSet.push(neighborNode);
                        }
                    }
                }
            }
        }

       
        if (pathFound) {
            COORD curr = parent[finish.Y][finish.X];
            
            while (!(curr.X == start.X && curr.Y == start.Y) && curr.X != -1 && curr.Y != -1) {

                if (grid[curr.Y][curr.X] == 0) {
                    grid[curr.Y][curr.X] = 4;
                }
                curr = parent[curr.Y][curr.X];
            }
        }
    }

    void run() {
        
        system("cls");

        while (true) {
            
            searchPath();
            draw();

            if (!handleInput()) {
                break; 
            }
        }
    }
};

int main() {
    
    Azirka simulation(25);

    simulation.run();

    return 0;
}