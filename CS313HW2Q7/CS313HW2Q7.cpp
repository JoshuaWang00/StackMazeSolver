// CS313HW2Q7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <stack>

using namespace std;

class choice{
public:
    int direction = 0; //1=up 2=right 3=left 4=down
    //coordinates where a choice is made
    int x; int y;

    choice(int x1, int y1) {
        x = x1;
        y = y1;
        direction = 0;
    };
};

//second matrix to avoid repeats when backtracking
bool checked[5][5];
void findPath(int maze[5][5]) {
    stack<choice> path;
    //coordinates of current location
    //when first making this I mistakenly mixed rows and columns, so c actually represents rows and r represents columns
    int c, r = 0;
    //first choice happens at start of the matrix 0,0
    choice current(0, 0);
    path.push(current);
    //while the goal has not been reached
    
    while (maze[path.top().x][path.top().y] != 2) {
        //check if the very first choice has been popped, meaning that no valid path could be found

        if (path.empty() == true) {
            cout << "No valid path could be found.";
            return;
        }
        choice current = path.top();
        current.direction++;
        int dir = current.direction;

        c = current.x; r = current.y;
        //if we happened to pop, a new direction is set for the latest choice

        path.pop();
        path.push(current);

        
            //up
        if (dir == 1) {
                //in order, we see a viable position if we've never been to the upwards spot, the upward position in the column is not out of bounds(negative), and is not defined as a wall(0)
                if (checked[c - 1][r] == 0 && c - 1 >= 0 && maze[c - 1][r] >= 1) {

                    choice up(c - 1, r);
                    //once we make a choice to go to the next spot, there is no need to enter it again because we will end up checking all viable positions from that spot, and so we must avoid it if we backtrack 
                    checked[c - 1][r] = true;
                    path.push(up);
                   
                }
            }
            //right
        if (dir == 2) {
                if (checked[c][r + 1] == 0 && r + 1 < 5 && maze[c][r + 1] >= 1) {

                    choice right(c, r + 1);
                    checked[c][r + 1] = true;
                    path.push(right);
                    
                }
            }

            //left

        if (dir == 3) {
                if (checked[c][r - 1] == 0 && r - 1 >= 0 && maze[c][r - 1] >= 1) {

                    choice left(c, r - 1);
                    checked[c][r - 1] = true;
                    path.push(left);
                   
                }
            }

            //down
        if (dir == 4) {
                if (checked[c + 1][r] == 0 && c + 1 < 5 && maze[c + 1][r] >= 1) {

                    choice down(c + 1, r);
                    checked[c + 1][r] = true;
                    path.push(down);
                   
                }
            }
        // backtrack to the last choice when all directions are incompatible
        if (dir == 5) {

                path.pop();
               
            }
        }
    

    if (maze[path.top().x][path.top().y] == 2) {
        cout << "Path Found! ";
        stack<choice> readablePath;
        //reverse the stack to print directions in chronological order
        for (int i = path.size(); i > 0; i--) {
            readablePath.push(path.top());            
            path.pop();
        }
        while (!readablePath.empty()) {            
           int d = readablePath.top().direction;
           switch (d) {
           case 1: cout << "up ";
               break;
           case 2: cout << "right ";
               break;
           case 3: cout << "left ";
               break;
           case 4: cout << "down ";
               break;
           }
           readablePath.pop();

        }


    }
}

int main(){    
    //matrix that represents a maze, with 0 representing a wall, 1 a path, and 2 the goal
   
    int maze[5][5] = {
    {1, 0, 1, 0, 1 },
    {1, 1, 1, 0, 1 },
    {1, 0, 1, 1, 1 },
    {1, 0, 1, 0, 1 },
    {1, 1, 0, 2, 1 },
    };
    
    for (int i = 0;i<5;i++){
        for (int j = 0; j < 5; j++) {
            cout << maze[i][j] << " ";
        
        }
       cout << endl;

    }

    findPath(maze);
    
    return 0;
}


