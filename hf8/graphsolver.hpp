#ifndef HF08_GRAPHSOLVER_HPP
#define HF08_GRAPHSOLVER_HPP

#include "vector"
#include "map"
using namespace std;

struct Pontok {
    int x;
    int y;
};

class GraphSolver{
private:
    vector<Pontok> graf;
    int startG;
    int endG;
    bool lehet_ut = false;


public:
    GraphSolver(int start, int target) {
        if(start < 1 || target < 1){
            cout << "hibas bemenet" <<endl;
        }

        graf.push_back({start,0});
        graf.push_back({0,target});

        startG = start;
        endG = target;






    }
    ~GraphSolver(){
        graf.clear();
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
        } else{

            graf.push_back({node1,node2});

            for (int i = 0; i < graf.size()-1; ++i) {
                if(graf[i].y == node2){

                    lehet_ut = true;
                    //ha valami csatlakozik a vegehez onnantol nezni kell hogy van e ut

                }
                if(lehet_ut == true){

                    int akt = endG;
                    bool voltakt = true;
                    while (voltakt == true){
                        voltakt = false;
                        for (int j = 0; j < graf.size()-1; ++j) {

                            if(graf[i].y == akt){
                                akt = graf[i].x;
                                voltakt = true;
                                cout << akt <<endl;
                            }


                        }


                    }




                }



            }




        }



    }
};


#endif //HF08_GRAPHSOLVER_HPP
