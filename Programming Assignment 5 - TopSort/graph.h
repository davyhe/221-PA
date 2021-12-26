#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;
using std::endl;
using std::priority_queue;
using std::queue;
using std::unordered_map;

//edits to this are likely not needed
template <class T>
struct Vertex
{
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree;                                 // Part 2: number of nodes pointing in
  int top_num;                                  // Part 2: topological sorting number
  Vertex(T l = T()) : label(l) { top_num = 0; } //Part 1
  // You may include default constructor optionally.
};

// optional, but probably helpful
template <class T>
ostream &operator<<(ostream &o, Vertex<T> v)
{
  //o<<v.label;
  for (int i = 0; i < v.adj_list.size(); i++)
  {
    o << v.adj_list[i] << " ";
  }
  o << endl;
  return o;
};

template <class T>
class VertexCompare
{
public:
  //will be called as a < operator
  bool operator()(Vertex<T> v1, Vertex<T> v2)
  {
    //TODO - implement
    return v1.top_num > v2.top_num;
  }
};

// std::priority_queue may take takes three template parameters: <Type, ContainerType, Functor>
// syntax for custom compare functor
// Refer the instructions PDF last section for more information

// template<class T>
// class VertexCompare
// {
// public:
//   bool operator()(Vertex<T> v1, Vertex<T> v2){
//     //todo - implement here
//     return false;
//   }
// };

template <class T>
class Graph
{
private:
  //c++ stl hash table

  unordered_map<T, Vertex<T>> node_set;
  //Use other data fields if needed
public:
  Graph(){};  //No modification needed to default constructor. Can be used optionally if needed.
  ~Graph(){}; //No modification needed to destructor. Can be used optionally if needed.

  // build a graph - refer the instructions PDF for more information.
  void buildGraph(istream &input)
  {
    string line = "";
    while (getline(input, line))
    {
      if (line == "")
      {
        return;
      }
      std::istringstream one(line);
      T vex;
      one >> vex;

      Vertex<T> node(vex);

      T temp;
      while (one >> temp)
      {
        node.adj_list.push_back(temp);
      }
      node_set.insert(make_pair(vex, node));
      //node_set[vex] = node;
    }
  }

  // display the graph into o - refer the instructions PDF for more information.
  void displayGraph(ostream &o)
  {
    for (auto i : node_set)
    {
      o << i.first << ": " << i.second;
    }
  }

  //return the vertex at label, else throw any exception  - refer the instructions PDF for more information.
  Vertex<T> at(T label)
  {
    if (node_set.size() == 0 || node_set.find(label) == node_set.end())
    {
      throw std::invalid_argument("");
    }
    Vertex<T> v = node_set[label];
    return v;
  }

  //return the graph size (number of verticies)
  int size()
  {
    return node_set.size();
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  // Part 2
  bool topological_sort()
  {
    queue<T> q;
    int count = 0;
    //Vertex <T> v;
    for (auto &v : node_set)
    {
      if (v.second.indegree == 0)
        q.push(v.first);
    }
    while (!q.empty())
    {
      T vex = q.front();
      q.pop();
      //cout<<"vex: "<< vex<< " count: "<<count<<endl;
      node_set.at(vex).top_num = count++;

      for (auto &w : node_set.at(vex).adj_list)
      {
        if ((--node_set.at(w).indegree) == 0)
          q.push(w);
      }
    }

    if (count != node_set.size())
    {
      return false;
    }
    return true;
  }

  // find indegree
  // Part 2
  void compute_indegree()
  {
    for (auto &v : node_set)
    {
      v.second.indegree = 0;
    }
    for (auto &v : node_set)
    {
      for (auto &w : v.second.adj_list)
      {
        node_set.at(w).indegree++;
      }
    }
  }

  /*
count how many time a element show on the vertex
Ex: Vertex#1: 2, 3, 4   Vertex#2: 3, 4
Thus, indegree for the number 3 and 4 is two, and the indegree for the number 2 is one.
*/

  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream &o, bool addNewline = true)
  {
    //TODO - implement things here
    cout << endl;
    priority_queue <Vertex <T>, vector <Vertex <T>>, VertexCompare <T>> pq;
    for(auto &v : node_set){
      pq.push(v.second);
    }
    while(!pq.empty()){
      auto v=pq.top();
      o << v.label << " ";
      pq.pop();// v *logv
    }

    if (addNewline)
    {
      o << '\n';
    };
  }; // Part 2
};

#endif
