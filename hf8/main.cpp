#include "woodpecker.hpp"
#include "graphsolver.hpp"
/*
TEST("Simple graph") {
    GraphSolver graphSolver = GraphSolver(1,4);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,2), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,5), true);
}

TEST("Simple graph copy") {
    GraphSolver graphSolver = GraphSolver(1,4);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,2), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    GraphSolver g2(graphSolver);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,5), true);
    CHECK_EQ(g2.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(g2.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(g2.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(g2.exitsAfterPathAdded(3,5), true);
}
TEST("Simple graph assignment") {
    GraphSolver graphSolver = GraphSolver(1,4);
    GraphSolver g2(6,12);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,2), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    g2 = graphSolver;
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,5), true);
    CHECK_EQ(g2.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(g2.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(g2.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(g2.exitsAfterPathAdded(3,5), true);
}
TEST("Simple graph move") {
    GraphSolver graphSolver = GraphSolver(1,4);
    GraphSolver g2(42,25);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,2), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    g2 = std::move(graphSolver);
    CHECK_EQ(g2.exitsAfterPathAdded(2,3), false);
    CHECK_EQ(g2.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(g2.exitsAfterPathAdded(3,4), true);
    CHECK_EQ(g2.exitsAfterPathAdded(3,5), true);
}

TEST("Simple2") {
    GraphSolver graphSolver = GraphSolver(1,2);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,4), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,2), true);
}
*/
TEST("Graph 2") {
    GraphSolver graphSolver = GraphSolver(2,8);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,4), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(9,7), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(6,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,1), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(4,6), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(8,7), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(5,9), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,8), true);
}
/*
TEST("Graph 3") {
    GraphSolver graphSolver = GraphSolver(5,6);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(5,2), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(6,4), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,8), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,1), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(8,1), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,8), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(9,1), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,9), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(8,10), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(9,10), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,11), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(12,11), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(12,13), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(13,4), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,4), true);
}


TEST("Graph 4") {
    GraphSolver graphSolver = GraphSolver(1,2);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,4), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(6,5), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,8), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(9,10), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(7,10), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(9,8), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(3,7), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(4,6), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(5,9), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(1,3), false);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(2,5), true);
    CHECK_EQ(graphSolver.exitsAfterPathAdded(8,5), true);
}
*/
WOODPECKER_TEST_MAIN()