#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <algorithm>

struct elephant {
    int index;
    int weight;
    int iq;
};

std::vector<elephant> elephants;

void getData() {

    std::ifstream infile("e.in");

    int i = 1;
    while(infile.good()) {
        elephant tempEle;
        infile >> tempEle.weight >> tempEle.iq;
        tempEle.index = i;
        elephants.push_back(tempEle);
        i++;
    }
}

void printV() {
    for(std::vector<elephant>::iterator i = elephants.begin(); i != elephants.end(); ++i)
        std::cout << i->index << " weight: " << i->weight << " IQ: " << i->iq << std::endl;
}

bool compare(elephant A, elephant B) {
    if (A.weight == B.weight)
        return A.iq < B.iq;
    if (A.weight < B.weight)
        return 0;
    return 1;
}

void printSV(std::vector<elephant> elephants) {
    std::sort(elephants.begin(), elephants.end(), compare);

    for(std::vector<elephant>::iterator i = elephants.begin(); i != elephants.end(); ++i)
        std::cout << i->index << " weight: " << i->weight << " IQ: " << i->iq << std::endl;
}


void getLongest() {

}


int main() {
    getData();
    printV();
    //printSV(elephants);
    return 0;
}

