#include <iostream>
#include "tasks_rk2.h"
#include <list>
int main() {
    Graph first;
    first.buildTreeDFS(2);
    first.DFS();
    std::pair<bool, std::list<int>> fir;
    first.search_DFS(1);
    return 0;
}