#ifndef find
#pragma once

#include "RBTreeRealisation.h"
#include "NodeList.h"
#include <iostream>
#include <fstream>
#include <string>
#include"Matrix.h"
using namespace std;

struct ElementString
{
public:
	string nodeStart;
	string nodeFinish;
	double bandwidth;
	

	ElementString(string start, string finish, double mass)
	{
		this->nodeStart = start;
		this->nodeFinish = finish;
		this->bandwidth = mass;
	
	}
	ElementString()
	{
		this->nodeStart = "";
		this->nodeFinish = "";
		this->bandwidth = 0.0;
		

	}
};

Node_List<string> ParsString(string str, string delimiter = " ")
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

Node_List<ElementString> ListOfPars(string input)
{
	Node_List<ElementString> edgeList;

	ifstream finput;
	finput.open(input);

	string str;
	while (getline(finput, str))
	{
		Node_List<string> newEdgeSrting = ParsString(str, " ");

		auto str = newEdgeSrting.create_iterator();
		string start = str->next();
		string finish = str->next();
		string mass = str->next();;
		delete str;

		ElementString element(start, finish, stod(mass));
		edgeList.PushBack(element);
	}

	finput.close();
	return edgeList;
}

Map<string, int> createMapWithNum(Node_List<ElementString>& createEl)
{
	Map<string, int>* mapOfElem = new Map<string, int>();

	auto tmpIterator = createEl.create_iterator();
	int check = 0;

	while (tmpIterator->has_next())
	{
		ElementString edge = tmpIterator->next();

		try
		{
			mapOfElem->Insert(edge.nodeStart, check);
			check++;
		}
		catch (const std::exception&) {}

		try
		{
			mapOfElem->Insert(edge.nodeFinish, check);
			check++;
		}
		catch (const std::exception&) {}
	}
	delete tmpIterator;

	return *mapOfElem;
}

Matrix createMatrixForAlg(Node_List<ElementString>& list, Map<string, int>& numElem)
{
	Matrix* matrica = new Matrix(numElem.size);

	auto itr = list.create_iterator();
	while (itr->has_next())
	{
		ElementString edge = itr->next();
		int startEl = numElem.Find(edge.nodeStart);
		int finishEl = numElem.Find(edge.nodeFinish);
		matrica->matrix[startEl][finishEl] = edge.bandwidth;
	}
	delete itr;

	return *matrica;
}

bool BFSForEdmondsKarp(Matrix& matrica, int startEl, int finishEl, int* parent)
{
	bool* visited = new bool[matrica.size];
	for (int i = 0; i < matrica.size; i++)
		visited[i] = false;

	Queue<int> queueEl;
	queueEl.Push(startEl);
	visited[startEl] = true;
	parent[startEl] = -1;

	while (!queueEl.isEmpty()) {
		int i = queueEl.front();
		queueEl.pop();

		for (int j = 0; j < matrica.size; j++) {
			if (visited[j] == false && matrica.matrix[i][j] > 0) {
				if (j == finishEl) {
					parent[j] = i;
					return true;
				}

				queueEl.Push(j);
				parent[j] = i;
				visited[j] = true;
			}
		}
	}

	return false;
}

double TheEdmondsKarpAlgorithm(Node_List<ElementString>& list, string startingEl, string finishEl)
{
	Map<string, int> numElem = createMapWithNum(list);
	int size = numElem.size;
	int elMatrixStart = numElem.Find(startingEl);
	int elMatrixFinish = numElem.Find(finishEl);

	Matrix adjacencyMatrix = createMatrixForAlg(list, numElem);

	int sizeForAlg = adjacencyMatrix.size;
	
	int* previous = new int[size];

	double findingMaxWay = 0.0;

	while (BFSForEdmondsKarp(adjacencyMatrix, elMatrixStart, elMatrixFinish, previous))
	{
		double cMin = INT_MAX;
		for (int i = elMatrixFinish; i != elMatrixStart; i = previous[i])
		{
			int j = previous[i];


			if (cMin <= adjacencyMatrix.matrix[j][i])
				cMin = cMin;
			else
				cMin = adjacencyMatrix.matrix[j][i];
		}

		for (int i = elMatrixFinish; i != elMatrixStart; i = previous[i])
		{
			int j = previous[i];
			adjacencyMatrix.matrix[j][i] -= cMin;
			adjacencyMatrix.matrix[i][j] += cMin;
		}

		findingMaxWay += cMin;
	}



	return findingMaxWay;
}
#endif // !find