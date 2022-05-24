
#include <iostream>
#include "RBTreeRealisation.h"
#include "NodeList.h"
#include <iostream>
#include <fstream>
#include <string>
#include "find.h"
int main()
{
    Node_List<ElementString> edgeList = ListOfPars("input.txt");
    double findingMaxWay = TheEdmondsKarpAlgorithm(edgeList, "S", "T");
    cout << "findingMaxWay from S to T- " << findingMaxWay;

    return 0;



}
