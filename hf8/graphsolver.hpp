#ifndef HF08_GRAPHSOLVER_HPP
#define HF08_GRAPHSOLVER_HPP

#include "vector"
#include "map"
using namespace std;
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")
struct Pontok {
    int x;
    int y;
};

class GraphSolver{
private:
    vector<Pontok> graf;
    int startG;
    int endG;
    int akt;
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
        //copy
        graf =_other.graf;
        startG = _other.startG;
        endG = _other.endG;
        akt = _other.akt;
        lehet_ut =_other.lehet_ut;

    }
    GraphSolver& operator= (const GraphSolver& _other){
        // Assignment operator
        if (this != &_other) {  //figyelni kell hogy ne legyen megfeleltetes sajat megaval
            this->graf =_other.graf; //egyik graf megfeleltetese a masiknak
            this->startG = _other.startG;
            this->endG = _other.endG;
            this->akt = _other.akt;
            this->lehet_ut =_other.lehet_ut;




        }
        return *this;

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

            for (int i = 0; i < graf.size(); ++i) {
                if (endG == graf[i].y && endG == node2 ) {
                    //cout << node2 <<endl;
                    graf[i].x = node1;
                    lehet_ut = true;
                    //ha valami csatlakozik a vegehez onnantol nezni kell hogy van e ut

                }
            }


                if(lehet_ut == true){

                     akt = endG;

                    bool voltakt = true;
                    while (voltakt == true){
                        voltakt = false;
                        for (int j = 0; j < graf.size(); ++j) {

                            if(graf[j].y == akt){
                                //cout << akt <<endl;
                                akt = graf[j].x;
                                //cout << akt << "utana" <<endl;
                                voltakt = true;

                            }


                        }


                    }




                }



        }
        if(akt == startG){
            return true;
        } else{
            return false;
        }

    }
};


#endif //HF08_GRAPHSOLVER_HPP
