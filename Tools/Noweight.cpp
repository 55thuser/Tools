#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;
class Node{
    public:
    int weight;
    int nodeNum;
    vector<int> edges;
    bool visited = false;
    double avgEdge;
    Node(){

    }
    ~Node(){

    }
    int getDist(int x){
        return edges[x];
    }
    void calcAvgEdge(){
        int total = 0;
        for(int i =0; i<edges.size(); i++){
            if(nodeNum != i){
                total += edges[i];
            }
        }
        avgEdge = ((double)total)/(edges.size());
    }
    int oppertunity(int i){
        //cout<<"CALC: "<<avgEdge-edges[i];
        return avgEdge-edges[i];
    }
};


vector<Node*> readFile(string filename){
    vector<Node*> toReturn;
    ifstream file(filename,ios::in);
    if (file.good()){
        string str;
        int nodeNum =0;
        while(getline(file, str)){
            Node *toAdd = new Node;
            toAdd->nodeNum = nodeNum;
            istringstream ss(str);
            int num;
            while(ss >> num){
                toAdd->edges.push_back(num);
            // ... you now get a number ...
            }
            toReturn.push_back(toAdd);
            nodeNum++;
        }
    }
    return toReturn;
}
vector<Node*> format(vector<Node*> &Nodes){
    for(int i = 0; i<Nodes.size(); i++){
        for(int j = i+1; j<Nodes.size(); j++){
            Nodes[i]->edges.push_back(Nodes[j]->edges[i]);
        }
        Nodes[i]->calcAvgEdge();
    }
    return Nodes;
}
void printNodes(vector<Node*> &Nodes){
    for(int i = 0; i<Nodes.size(); i++){
        cout<<"N"<<Nodes[i]->nodeNum<<" AvgEdge: "<<Nodes[i]->avgEdge<<endl;
        for(int j = 0; j<Nodes[i]->edges.size(); j++){
            cout<<Nodes[i]->edges[j]<<" ";
        }
        cout<<endl;
    }
    return;
}

void printOrder(vector<int> order){
    for(int i = 0; i<order.size(); i++){
        cout<<"N"<<order[i]<<" ";
    }
    cout<<endl;
    return;
}

int oppertuneRec(vector<Node*> Nodes, vector<int> &order){
    double currMaxOpper;
    Node* currNode = Nodes[order[order.size()-1]];
    int currContender;
    if(order.size()==Nodes.size()){
        return currNode->edges[0];
    }
    bool init = false;
    int dist;
    for(int i = 0; i<Nodes.size(); i++){
        if((i != currNode->nodeNum) && !(Nodes[i]->visited)){
            if(init){
                if(currMaxOpper<(Nodes[i]->oppertunity(currNode->nodeNum)+currNode->oppertunity(i))){
                    currContender = i;
                    currMaxOpper = (Nodes[i]->oppertunity(currNode->nodeNum)+currNode->oppertunity(i));
                    //cout<<"CHECK";
                }
            }
            else{
                init = true;
                currMaxOpper = (Nodes[i]->oppertunity(currNode->nodeNum)+currNode->oppertunity(i));
                currContender = i;
                //cout<<i;
            }
        }
    }
    order.push_back(currContender);
    Nodes[currContender]->visited = true;
    dist = currNode->edges[currContender];
    //cout<<currContender<<"?";
    return (dist+oppertuneRec(Nodes, order));
    
}
vector<int> oppertune(vector<Node*> Nodes, int &distance){
    //cout<<"HERE";
    vector<int> order;
    Node* start = Nodes[0];
    start->visited = true;
    order.push_back(start->nodeNum);
    distance = oppertuneRec(Nodes, order);
    return order;
}
int NNRec(vector<Node*> Nodes, vector<int> &order){
    int minDist;
    Node* currNode = Nodes[order[order.size()-1]];
    int currContender;
    if(order.size()==Nodes.size()){
        return currNode->edges[0];
    }
    bool init = false;
    int dist;
    for(int i = 0; i<Nodes.size(); i++){
        if((i != currNode->nodeNum) && !(Nodes[i]->visited)){
            if(init){
                if(minDist>currNode->edges[i]){
                    currContender = i;
                    minDist = currNode->edges[i];
                    //cout<<"CHECK";
                }
            }
            else{
                init = true;
                minDist = currNode->edges[i];
                currContender = i;
                //cout<<i;
            }
        }
    }
    order.push_back(currContender);
    Nodes[currContender]->visited = true;
    dist = currNode->edges[currContender];
    //cout<<currContender<<"?";
    return (dist+NNRec(Nodes, order));
    
}
vector<int> NN(vector<Node*> Nodes, int &distance){
    //cout<<"HERE";
    vector<int> order;
    Node* start = Nodes[0];
    start->visited = true;
    order.push_back(start->nodeNum);
    distance = NNRec(Nodes, order);
    return order;
}

int main(){
    string filename = "Size100.graph";
    vector<Node*> Nodes = readFile(filename);
    Nodes = format(Nodes);
    //printNodes(Nodes);
    
    //cout<<"CHECK";
    int oppertuneDist;
    //cout<<"CHECK";
    vector<int> oppertuneOrder;
    oppertuneOrder = NN(Nodes, oppertuneDist);
    //cout<<oppertuneOrder[0];
    printOrder(oppertuneOrder);
    cout<<"Distance: "<<oppertuneDist;
}