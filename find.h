#ifndef FIND
#pragma once
#include "Matrix.h"
#include "RBTreeRealisation.h"
#include "Node_List.h"
#include <iostream>
#include <fstream>


struct ElementString
{
public:
	string departure—ity;
	string cityOfArrival;
	double flightPrice;
	double flightPriceReturn;

	ElementString(string departure—ity, string cityOfArrival, double flightPrice, double flightPriceReturn)
	{
		this->departure—ity = departure—ity;
		this->cityOfArrival = cityOfArrival;
		this->flightPrice = flightPrice;
		this->flightPriceReturn = flightPriceReturn;
	}
	ElementString()
	{
		this->departure—ity = "";
		this->cityOfArrival = "";
		this->flightPrice = 0.0;
		this->flightPriceReturn = 0.0;

	}
};

Map<string, int> createMapWithNumCity(Node_List<ElementString>& createEl)
{
	Map<string, int>* mapOfElem = new Map<string, int>();

	auto newElementMap = createEl.create_iterator();
	int check = 0;

	while (newElementMap->has_next())
	{
		ElementString str = newElementMap->next();

		mapOfElem->Insert(str.departure—ity, check);
		check++;

		mapOfElem->Insert(str.cityOfArrival, check);
		check++;
	}
	delete newElementMap;
	return *mapOfElem;
}



Node_List<string> ParsString(string str, string delimiter = ";")
{
	Node_List<string> ParsingLines;
	int head = 0;
	int ending = str.find(delimiter);
	while (ending != -1)
	{
		ParsingLines.PushBack(str.substr(head, ending - head));
		head = ending + delimiter.size();
		ending = str.find(delimiter, head);
	}
	ParsingLines.PushBack(str.substr(head, ending - head));
	return ParsingLines;
}
Matrix matrixCreate(Node_List<ElementString>& matrixEl, Map<string, int>& matrica)
{
	Matrix* newmatrix = new Matrix(matrica.size);

	auto itr = matrixEl.create_iterator();
	while (itr->has_next())
	{
		ElementString edge = itr->next();
		int numDeparture—ity = matrica.Find(edge.departure—ity);
		int numCityOfArrival = matrica.Find(edge.cityOfArrival);
		newmatrix->matrix[numDeparture—ity][numCityOfArrival] = edge.flightPrice;
	}
	delete itr;

	return *newmatrix;
}
Node_List<ElementString> ListOfPars(string InputName)
{
	Node_List<ElementString> listOfPars;
	string str;
	ifstream inputFile;
	inputFile.open(InputName);

	cout << "Input file : \n";
	while (getline(inputFile, str))
	{
		cout << str << "\n";
		Node_List<string> newSrting = ParsString(str, ";");
		auto newElementOfString = newSrting.create_iterator();
		string city1 = newElementOfString->next();
		string city2 = newElementOfString->next();
		string price1 = newElementOfString->next();
		string price2 = newElementOfString->next();
		delete newElementOfString;
		if (price2 == "N/A") {
			ElementString newELString(city1, city2, stod(price1), 0);
			listOfPars.PushBack(newELString);
		}
		else {
			if (price2 == "N/A") {
				ElementString newEdge(city1, city2, 0, stod(price2));
				listOfPars.PushBack(newEdge);
			}
			else {
				ElementString newEdge(city1, city2, stod(price1), stod(price2));
				listOfPars.PushBack(newEdge);
			}

		}


	}inputFile.close();
	return listOfPars;
}
Matrix createMatrixForFWAlg(Node_List<ElementString>& ticketsList, Map<string, int>& cityNumerics)
{
	Matrix* graph = new Matrix(cityNumerics.size);

	for (int i = 0; i < graph->size; i++)
	{
		graph->matrix[i][i] = 0;
	}

	auto ticket_itr = ticketsList.create_iterator();
	while (ticket_itr->has_next())
	{
		ElementString ticket = ticket_itr->next();

		int numCity1 = cityNumerics.Find(ticket.departure—ity);
		int numCity2 = cityNumerics.Find(ticket.cityOfArrival);


		graph->matrix[numCity1][numCity2] = ticket.flightPrice;

		graph->matrix[numCity2][numCity1] = ticket.flightPriceReturn;
	}
	delete ticket_itr;

	return *graph;
}
void Algoritm_Floyda_Warshalla(Matrix& matrixIn, Matrix& matrixWay)
{
	int size = matrixIn.size;
	double** matrix = matrixIn.matrix;
	double** pathMatrix = matrixWay.matrix;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				pathMatrix[i][j] = i;
			}
			else if (matrix[i][j] == -1)
			{
				pathMatrix[i][j] = -1;
			}
			else
			{
				pathMatrix[i][j] = j;
			}
		}
	}

	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i == j)
				{
					matrix[i][j] = i;
				}
				else
					if (matrix[i][j] > (matrix[i][k] + matrix[k][j]))
					{
						matrix[i][j] = matrix[i][k] + matrix[k][j];
						pathMatrix[i][j] = k;
					}
			}
		}
	}
}

double findingFullPrice(Node_List<ElementString>& list, string city1, string city2)
{
	Map<string, int> numOfCity = createMapWithNumCity(list);
	int size = numOfCity.size;
	int Òity1 = numOfCity.Find(city1);
	int Òity2 = numOfCity.Find(city2);
	double fullPrice;
	Matrix matrica = createMatrixForFWAlg(list, numOfCity);
	Matrix matricaForAlg(size);
	Algoritm_Floyda_Warshalla(matrica, matricaForAlg);


	double findingPrice = matrica.matrix[Òity1][Òity2];
	fullPrice = findingPrice;



	return fullPrice;
}
#endif