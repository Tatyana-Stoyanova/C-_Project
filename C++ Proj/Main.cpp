#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <ctime>
#include <list>
#include <fstream>
#include <string>
#include <sstream>


class dynamicArray {
private: //access specifier
	int size = 0; // razmer na 1 maluk array
	int globalSize = 0;
	int index = 0; // index na posledno suzdaden maluk array
	int elements = 0; // obsht broi zapisani elementi
	int*** array = NULL;

public: //access specifier
	dynamicArray() {
		size = 1000;
		globalSize = 1000;
		array = new int** [globalSize];
		array[0] = new int* [size];
		index = 0;
	}
	~dynamicArray() {
		delete[]** array;
		delete[]* array;
		delete[] array;
	}
	void AddElement(int value) {
		int i = elements / size;
		int j = elements % size;
		if (i < globalSize) {
			if (i != 0 && j == 0) {
				newSubArray(i);
			}
			*(*(array + i) + j) = new int;
			*(*(*(array + i) + j)) = value;
			elements++;
		}
	}
	void newSubArray(int i) {
		array[i] = new int* [size];
		index++;
	}

	void print() {
		for (int i = 0; i < ceil(elements/size); i++) {
			for (int j = 0; j < size; j++) {
				if (*array[i][j]) {
					std::cout << "array[" << i << "][" << j << "]=" << *array[i][j] << std::endl;
				}
			}
		}
	}

	void printElementWithIndex(int index) {
		std::cout << "Element with index " << index << "has value " << getElement(index) << std::endl;

	}

	int findElement(int value) { //returns index
		for (int i = 0; i < ceil(elements/size); i++) {
			for (int j = 0; j < size; j++) {
				if (*array[i][j]==value) {
					std::cout << "array[" << i << "][" << j << "]=" << *array[i][j] << std::endl;
					int numEl =  i*size + j;
					return numEl;
				}
			}
		}
		return -1;
	}

	int getElement(int index) {
		if (index < elements) {
			int i = index / size;
			int j = index % size;
			return *array[i][j];
		}
		std::cout << "Invalid index" << std::endl;
		return -1;
	}

	void setElement(int index, int newValue) {
		if (index < elements) {
			int i = index / size;
			int j = index % size;
			*array[i][j] = newValue;
		}
		else {
			std::cout << "Invalid index" << std::endl;
		}
	}
	int getStructSize() {
		return size * globalSize;
	}
};

struct node
{	
	dynamicArray* current; // data
	node* next; // Pointer to next el
};

class DynamicArrayList {
private:
	node** indexes;
	node* head;
	std::list <node*> p;
	node* currEl;
	int numbers;
	int structs;
	int size;
	FILE* f = NULL;
	int* filearr;
	int* readfile;

public:
	DynamicArrayList() {
		size = 5;
		indexes = new node * [size];
		currEl = new node;
		currEl->current = new dynamicArray;
		indexes[0] = new node;
		indexes[0] = currEl;
		structs = 1;
		currEl->next = NULL;
		numbers = 0;
		p.push_back(currEl);
	}
	~DynamicArrayList() {
		delete[] * indexes;
		p.~list();
	}

	void addElement(int value) {
		if (isFull(currEl) && numbers % currEl->current->getStructSize() == 0) {
			currEl->next = new node;
			currEl->next->current = new dynamicArray;
			currEl = currEl->next;
			indexes[structs] = new node;
			indexes[structs] = currEl;
			structs++;
			currEl->next = NULL;
			p.push_back(currEl);
			currEl->current->AddElement(value);
			numbers++;
		}
		else {
			currEl->current->AddElement(value);
			numbers++;
		}
		if (structs >= size) {
			node** temp = new node * [size];
			for (int i = 0; i < size; i++) {
				temp[i] = new node;
			}
			temp = indexes;
			indexes = new node * [structs * 5];
			for (int i = 0; i < structs * 5; i++) {
				indexes[i] = new node;
				indexes[i] = temp[i];
			}
			delete[] * temp;
			delete[] temp;
			size = structs * 5;
		}
	}
	bool isFull(node* structur) {
		if (structur->current->getStructSize() <= numbers) {
			return 1;
		}
		return 0;
	}

	void print() {
		/*for (node* k = p.front(); k != NULL; k=k->next) {
			std::cout << "iteration " << i << std::endl;
			k->current->print();
			i++;
		}*/
		for (int i = 0; i < numbers / currEl->current->getStructSize(); i++) {
			std::cout << "iteration " << i << std::endl;
			indexes[i]->current->print();
		}
	}
	int getEl(int index) {
		if (index < numbers) {
			int StructSize = currEl->current->getStructSize();
			int str_num = ((double)index / (double)StructSize);
			return (indexes[str_num]->current->getElement(index % StructSize));
		}
		else {
			std::cout << "Invalid index" << std::endl;
		}

	}
	void setEl(int index, int newValue) {
		if (index < numbers) {
			int StructSize = currEl->current->getStructSize();
			int str_num = ((double)index / (double)StructSize);
			indexes[str_num]->current->setElement(index % StructSize, newValue);
		}
		else {
			std::cout << "Invalid index" << std::endl;
		}
	}
	int findEl(int value) {
		int found_index = -1;
		int StructSize = currEl->current->getStructSize();
		for (int i = 0; i < numbers / currEl->current->getStructSize(); i++) {
			found_index = indexes[i]->current->findElement(value);
			if (found_index != -1) {
				found_index += i * StructSize;
				return found_index;
			}
		}
		return found_index;
	}
	void printElementWithIndex(int index) {
		if (index < numbers) {
			int StructSize = currEl->current->getStructSize();
			int str_num = ((double)index / (double)StructSize);
			std::cout << "Element with index " << index << " has value " << indexes[str_num]->current->getElement(index % StructSize) << std::endl;
		}
		else {
			std::cout << "Invalid index" << std::endl;
		}
	}
	void writeToFile() {
		std::ofstream myfile("example.txt");
		filearr = new int[numbers];
		if (myfile.is_open())
		{
			for (int i = 0; i < numbers; i++) {
				filearr[i] = getEl(i);
				myfile << filearr[i] << std::endl;
			}
			myfile.close();
		}
		else std::cout << "Unable to open file" << std::endl;
	}
	void readFromFile() {
		std::string line;
		std::ifstream myfile("example.txt");
		if (myfile.is_open())
		{
			while (std::getline(myfile, line))
			{
				std::cout << line << '\n';
			}
			myfile.close();
		}
		else std::cout << "Unable to open file"<<std::endl;
	}
};

using namespace std;

int main()
{	
	DynamicArrayList* Elements = new DynamicArrayList();
	for (int i = 0; i < 5000; i++) {
		Elements->addElement(i);
	}
	int ElsIndex4256 = Elements->getEl(4256);
	std::cout << "element with index 4256 has value " << ElsIndex4256 << std::endl;
	Elements->setEl(325, 245);
	std::cout << "element with index 325 has value " << Elements->getEl(325) << std::endl;
	std::cout << "element with value 10621 has index " << Elements->findEl(10621) << std::endl;
	Elements->printElementWithIndex(4769);

	Elements->writeToFile();
	Elements->readFromFile();
	
	/*
	// measure time for accessing elements in a single structure
	dynamicArray opit = dynamicArray();
	for (int k = 0; k < 10000; k++) {
		opit.AddElement(k);
	}
	opit.setElement(20, 20);
	opit.print();
	int findel = opit.findElement(99);
	std::cout << "element with value 99 has index " << findel << std::endl;

	auto start = chrono::steady_clock::now();
	int b = opit.getElement(0);
	auto end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds" << endl;
	cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds" << endl;
	cout << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds" <<endl;


	auto start2 = chrono::steady_clock::now();
	int k = opit.getElement(9999);
	auto end2 = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << " nanoseconds" << endl;
	cout << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds" << endl;
	cout << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count() << " milliseconds" << endl;
	cout << chrono::duration_cast<chrono::seconds>(end2 - start2).count() << " seconds" << endl;
	*/
}