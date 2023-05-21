#include "tasks_rk2.h"
#include <iostream>
int Node::countNodes=0;
Node::Node(){
    listChilds.Head= nullptr;
    name=countNodes;
    ishere=false;
}
Node:: ~Node(){
    parent= nullptr;
    countNodes=0;
    ishere=false;
}
Graph::Graph() {
    head=new Node;
    head->parent= nullptr;
}
Node *Graph::BFS_1(Node *first, std::ofstream &flog) {
        Node* ukz=first;
        Fifo<Node*> stack;
        while(ukz->listChilds.Head!= nullptr){
            flog<<ukz->name<<"{";
            LinkNodes<Node*>* temp =ukz->listChilds.Head;
            while(temp!= nullptr){
                flog << temp->nameNode->name;
                if(temp->next!= nullptr) {
                    flog << ",";
                }
                stack.addToEnd(temp->nameNode);
                temp=temp->next;
            }
            flog<<"}\n";
            if(stack.datalen==0) {
                ukz = ukz->listChilds.Head->nameNode;
            }else{
                stack.getFromEnd(ukz);
            }

        }

}

Node *Graph::DFS_1(Node *first, std::ofstream &flog) {
    if(first->listChilds.Head!= nullptr){
        flog<<first->name<<"{";
        LinkNodes<Node*>* temp = first->listChilds.Head;
        while (temp!= nullptr){
            if(temp->nameNode->ishere==false){
                DFS_1(temp->nameNode,flog);
                flog<<"}";
            }
            temp=temp->next;
        }
    }else{
        flog<<first->name;
        first->ishere=true;
        return first->parent;
    }
}

void Graph::BFS_tree_1(Node *first, int number, Fifo<Node *> &stack) {
    for (int i = 0; i < number; ++i) {
        Node::countNodes++;
        Node* boxx = new Node;
        boxx->parent=first;
        first->listChilds.addToEnd(boxx);
        stack.addToEnd(boxx);
    }
}

Node *Graph::BFS_tree(int number) {
    Fifo<Node*> stack;
    int count =number;
    for (int i = 0; i < number; ++i) {
        Node::countNodes++;
        Node* boxx = new Node;
        boxx->parent=head;
        head->listChilds.addToEnd(boxx);
        stack.addToEnd(boxx);
    }
    int brave=count;
    while(count>-1) {
        for (int i = 0; i < brave; ++i) {
            Node *korob;
            stack.getFromEnd(korob);
            BFS_tree_1(korob, count-1, stack);
        }
        brave=brave*(count-1);
        count--;
    }
}

void Graph::DFS_tree(Node *first, int number) {
    Node* temp=first;
    int counter = number;
    for (int i = 0; i < counter; ++i) {
        Node::countNodes++;
        Node* boxx = new Node;
        boxx->parent=temp;
        first->listChilds.addToEnd(boxx);
        DFS_tree(boxx,counter-1);
    }
}

Node *Graph::DFS_search(Node *first, int number, std::pair<bool, std::list<int>> &p_val){
    if(first->listChilds.Head== nullptr){
        if(first->name==number){
            p_val.first=true;
            p_val.second.push_back(first->name);
            return first;
        }
    }
    LinkNodes<Node*>* temp=first->listChilds.Head;
    while(temp!= nullptr){
        if(temp->nameNode->name==number){
            p_val.first=true;
            p_val.second.push_back(temp->nameNode->name);
            break;
        }
        DFS_search(temp->nameNode,number,p_val);
        if(p_val.first==true){
            p_val.second.push_back(temp->nameNode->name);
            break;
        }
        temp=temp->next;
    }
}

void Graph::DFS() {
    std::ofstream flog;
    flog.open("dfs_res.txt",std::ios::out);
    DFS_1(head,flog);
    flog.close();
}

void Graph::BFS() {
    std::ofstream flog;
    flog.open("bfs_res.txt",std::ios::out);
    BFS_1(head,flog);
    flog.close();
}
int Graph::buildTreeDFS(int countNodes) {
    DFS_tree(head,countNodes);
    return Node::countNodes;
}

int Graph::buildTreeBFS(int countNodes) {
    BFS_tree(countNodes);
    return Node::countNodes;
}
Graph::Graph(int number) {
    head=new Node;
    head->parent= nullptr;
    if(number&1) {
        DFS_tree(head,number);
    }else{
        BFS_tree(number);
    }
}

std::pair<bool, std::list<int>> Graph::search_DFS(int nameNode) {
    std::pair<bool,std::list<int>> base;
    base.first= false;
    LinkNodes<Node*>* temp= head->listChilds.Head;
    if(nameNode==0){
        base.second.push_back(head->name);
        base.first=true;
        return base;
    }
    while(temp!= nullptr){
        if(temp->nameNode->name==nameNode){
            base.first=true;
            base.second.push_back(temp->nameNode->name);
            break;
        }
        DFS_search(temp->nameNode,nameNode,base);
        if(base.first==true){
            base.second.push_back(temp->nameNode->name);
            break;
        }
        temp=temp->next;
    }
    if(base.first==true) {
        base.second.push_back(head->name);
    }
    return base;
}

std::pair<bool, std::list<int>> Graph::search_BFS(int nameNode) {
    std::pair<bool,std::list<int>> base;
    base.first=false;
    Fifo<Node*> stack;
    Node* first=head;
    if(nameNode==0){
        base.second.push_back(head->name);
        base.first=true;
        return base;
    }
    while(first->listChilds.Head!= nullptr){
        LinkNodes<Node*>* temp =first->listChilds.Head;
        while(temp!= nullptr){
            if(temp->nameNode->name==nameNode){
                base.first=true;
                base.second.push_back(temp->nameNode->name);
                break;
            }
            stack.addToEnd(temp->nameNode);
            temp=temp->next;
        }
        if(base.first==true){
            Node* sec_temp=temp->nameNode->parent;
            while (sec_temp!=head){
                base.second.push_back(sec_temp->name);
                sec_temp=sec_temp->parent;
            }
            base.second.push_back(head->name);
            break;
        }
        if(stack.datalen==0) {
            first = first->listChilds.Head->nameNode;
        }else{
            stack.getFromEnd(first);
        }
    }
    return base;
}

int Graph::destruct(Node *first) {
    if(first->listChilds.Head!= nullptr){
        LinkNodes<Node*>* temp = first->listChilds.Head;
        while (temp!= nullptr){
            if(temp->nameNode->ishere==false){
                destruct(temp->nameNode);
            }
            temp=temp->next;
        }
    }else{
        LinkNodes<Node*>*go=first->listChilds.Head;
        while(first->listChilds.Head!= nullptr){
            first->listChilds.Head=go->next;
            delete go;
        }
        go= nullptr;
        return 0;
    }
}

Graph::~Graph() {
    destruct(head);
}

//
// Created by User on 21.05.2023.
//
