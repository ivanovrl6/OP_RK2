//
// Created by User on 21.05.2023.
//

#ifndef RK2_OP_TASKS_RK2_H
#define RK2_OP_TASKS_RK2_H
#include "Data.h"
struct Node{
    Node();
    Node* parent;
    LinkedList<Node*> listChilds;
    bool ishere;
    int name;
    static int countNodes;
    ~Node();
};
class Graph{
private:
    Node*head;
    Node* BFS_1(Node* first,std::ofstream& flog);

    Node* DFS_1(Node* first,std::ofstream& flog);

    void BFS_tree_1(Node* first, int number,Fifo<Node*> &stack);

    Node* BFS_tree(int number) ;

    Node* DFS_tree(Node* first, int number);

    Node* DFS_search(Node* first,int number, std::pair<bool,std::list<int>>& p_val);
public:
    void DFS();

    void BFS();

    int buildTreeDFS(int countNodes);

    int buildTreeBFS(int countNodes);

    Graph(int number);

    std::pair<bool, std::list<int>> search_DFS(int nameNode);

    std::pair<bool, std::list<int>> search_BFS(int nameNode);
};

#endif //RK2_OP_TASKS_RK2_H
