#ifndef HF08_GRAPHSOLVER_HPP
#define HF08_GRAPHSOLVER_HPP

#include "vector"
#include "map"
using namespace std;
//
struct Pontok {
    int x;
    int y;
};

class GraphSolver{
private:
    vector<Pontok> graf;
    int startG = -1;
    int endG = -1;

    bool lehet_ut = false;



public:
    GraphSolver(int start, int target) {
        if(start < 1 || target < 1){
            cout << "hibas bemenet" <<endl;
        }

        //graf.push_back({start,0});
        //graf.push_back({0,target});

        startG = start;
        endG = target;






    }
    ~GraphSolver(){

        graf.clear();
        startG = -1;
        endG = -1;

        lehet_ut = false;

    }
    GraphSolver(const GraphSolver& _other){
        //copy
        graf =_other.graf;
        startG = _other.startG;
        endG = _other.endG;

        lehet_ut =_other.lehet_ut;

    }
    GraphSolver& operator= (const GraphSolver& _other){
        // Assignment operator
        if (this != &_other) {  //figyelni kell hogy ne legyen megfeleltetes sajat megaval
            this->graf =_other.graf; //egyik graf megfeleltetese a masiknak
            this->startG = _other.startG;
            this->endG = _other.endG;

            this->lehet_ut =_other.lehet_ut;




        }
        return *this;

    }
    GraphSolver& operator= (GraphSolver&& _other)  noexcept {   //jobb mint a másolás, mert ez csak a mutatokat csereli meg
        // Move assignment operator
        //egyik grafbol pontok atmozgatasa a masikba
        if (this != &_other) {  //figyelni kell hogy ne legyen megfeleltetes sajat megaval
            this->graf =std::move(_other.graf); //egyik graf megfeleltetese a masiknak

            this->startG = std::move(_other.startG);    //ezek lehet nem is kellenek?
            this->endG = std::move(_other.endG);

            this->lehet_ut =std::move(_other.lehet_ut);

            //masik graf uritese a biztonsag kedveert

            _other.graf.clear();
            _other.startG = -1;
            _other.endG = -1;

            _other.lehet_ut = false;





        }
        return *this;



    }
    bool exitsAfterPathAdded(int node1, int node2) {
        if(node1 < 1 || node2 < 1){
            return false;
        } else{

            graf.push_back({node1,node2});
            graf.push_back({node2,node1});

            for (size_t i = 0; i < graf.size(); ++i) {
                if (endG == graf[i].y && endG == node2 ) {
                    //cout << node2 <<endl;
                    //graf[i].x = node1;
                    lehet_ut = true;
                    //ha valami csatlakozik a vegehez onnantol nezni kell hogy van e ut

                }
                if (endG == graf[i].x && endG == node1 ) {
                    lehet_ut = true;

                }

            }


            if(lehet_ut == true){
               // cout << node1  <<node2<<endl;


                for (size_t j = 0; j < graf.size(); ++j) {

                    //cout << graf[j].x  << "x" << graf[j].y << "y" <<endl;
                    if ((graf[j].x == endG && graf[j].y == startG) || (graf[j].y == endG && graf[j].x ==startG)) {  //a legegyszerübb eset, ha a ket pont eleve ossze van kotve

                        return true;
                    }
                }



                vector<int> akt;
                akt.push_back(endG);
                int aktszam = 0;

                bool voltakt = true;
                vector<int> voltindex;
                voltindex.clear();


                while (voltakt == true){
                    voltakt = false;
                    for (size_t j = 0; j < graf.size(); ++j) {

                        if(graf[j].y == akt[aktszam]){
                            bool nemvolt = true;
                            for (size_t i = 0; i < voltindex.size(); ++i) {

                                if(int(j) == voltindex[i]){
                                    nemvolt = false;
                                    i = voltindex.size();
                                }


                            }
                            if(nemvolt == true){
                               // cout << akt[aktszam] <<endl;
                                akt.push_back(graf[j].x);
                                aktszam = aktszam +1;
                                //cout << akt << "utana" <<endl;
                                voltakt = true; //ha talalunk egyet akkor kilepunk a for cikulsbol

                                voltindex.push_back(j);
                                if(int(j)-1 > -1 && graf[j].x == graf[j-1].y && graf[j].y == graf[j-1].x){
                                    voltindex.push_back(j-1);
                                   // cout << "most volt: " << graf[j].x  << "x" << graf[j].y << "y" <<endl;
                                   // cout << "es meg torlom: " << graf[j-1].x  << "x" << graf[j-1].y << "y" <<endl;

                                }
                                if(j+1 < graf.size() && graf[j].x == graf[j+1].y && graf[j].y == graf[j+1].x){
                                    voltindex.push_back(j+1);
                                    //cout << "most volt: " << graf[j].x  << "x" << graf[j].y << "y" <<endl;
                                    //cout << "es meg torlom: " << graf[j+1].x  << "x" << graf[j+1].y << "y" <<endl;

                                }



                                j = graf.size();
                            }
                            if(akt[aktszam] == startG){
                                return true;
                            }

                        }


                    }
                    if(voltakt == false && aktszam > 0){
                        akt.pop_back();
                        aktszam = aktszam -1;
                        voltakt = true;

                    }



                }




            }



        }

            return false;//nem talalt semmit


    }
};


#endif //HF08_GRAPHSOLVER_HPP