#ifndef HF08_GRAPHSOLVER_HPP
#define HF08_GRAPHSOLVER_HPP

#include "vector"
#include "map"
using namespace std;

struct Pontok {
    double x;
    double y;
};

class GraphSolver{
private:
    vector<Pontok> graf;
    int start;
    int end;

public:
    GraphSolver(int start, int target) {
        if(start < 1 || target < 1){
            cout << "hibas bemenet" <<endl;
        }





    }
    ~GraphSolver(){
        //TODO
    }
    GraphSolver(const GraphSolver& _other){
        // Copy konstruktor
        //TODO
    }
    GraphSolver& operator= (const GraphSolver& _other){
        // Assignment operator
        //TODO
    }
    GraphSolver& operator= (GraphSolver&& _other)  noexcept {
        // Move assignment operator
        //TODO
    }
    bool exitsAfterPathAdded(int node1, int node2) {
        if(node1 < 1 || node2 < 1){
            return false;
        }

        //TODO
    }
};


#endif //HF08_GRAPHSOLVER_HPP
