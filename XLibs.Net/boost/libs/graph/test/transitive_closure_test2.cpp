#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <iostream>
using namespace std;

using namespace boost;
typedef adjacency_list<> graph_t;

int main(int argc, char *argv[]) {
  graph_t g(5),g_TC;

  add_edge(0,2,g);
  add_edge(1,0,g);
  add_edge(1,2,g);
  add_edge(1,4,g);
  add_edge(3,0,g);
  add_edge(3,2,g);
  add_edge(4,2,g);
  add_edge(4,3,g);

  transitive_closure(g,g_TC);

  cout << "original graph: 0->2, 1->0, 1->2, 1->4, 3->0, 3->2, 4->2, 4->3" 
       << endl;
  cout << "transitive closure: ";
  graph_t::edge_iterator i,iend;
  for(tie(i,iend) = edges(g_TC);i!=iend;++i) {
    cout << source(*i,g_TC) << "->" << target(*i,g_TC) << " ";
  }
  cout << endl;
}
