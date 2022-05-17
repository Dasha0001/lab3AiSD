#include <string>
#include <iostream>
#include "Node_List.h"
#include "find.h"

using namespace std;

int main()
{

	Node_List<ElementString> ListforMove = ListOfPars("input.txt");


	double Price = findingFullPrice(ListforMove, "SPB", "KIROW");

	cout << "Price " << Price << endl;


}