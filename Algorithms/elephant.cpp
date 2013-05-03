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

/*
  Gets the data from the file and loads it into a global vector, elephants.
 */
void getData() {

    std::ifstream infile("e.in");

    int i = 1;
    int tempw;
    int tempiq;
    while(infile >> tempw >> tempiq) {
        elephant tempEle;
        tempEle.weight = tempw;
        tempEle.iq = tempiq;
        tempEle.index = i;
        elephants.push_back(tempEle);
        i++;
    }
}

/*
  For testing purposes, lists all elements that were read form e.in
 */
void printV() {
    for(std::vector<elephant>::iterator i = elephants.begin(); i != elephants.end(); ++i)
        std::cout << i->index << " weight: " << i->weight << " IQ: " << i->iq << std::endl;
}

/*
  Used to compare elephants. returns 1 if A > B
 */
bool greaterThan(elephant A, elephant B) {
    return ( (A.weight > B.weight) && (A.iq < B.iq) );
}

void printSV(std::vector< std::vector<elephant> > outer) {

    for(int i = 0; i < outer.size(); ++i) {
        std::cout << outer[i][0].index << " weight: " << outer[i][0].weight << " IQ: " << outer[i][0].iq << std::endl;

        for(int j = 1; j < outer[i].size(); ++j)
            std::cout << "  ---->  " << outer[i][j].index << " weight: " << outer[i][j].weight << " IQ: " << outer[i][j].iq << std::endl;
    }
}


void getLongest() {
    std::vector< std::vector<elephant > >  forwardList;

    // the outer part of forwardList
    for(int i = 0; i < elephants.size(); ++i) {

        // the inner part of forwardList
        std::vector<elephant> tempInner;
        tempInner.push_back(elephants[i]);

        // for every elephant
        for(int j = 0; j < elephants.size(); ++j) {

            if (i == j) continue;

            // if the current elephant is larger than the first
            if ( greaterThan(tempInner.front(), elephants[j]) )
                tempInner.push_back(elephants[j]);
        }

        forwardList.push_back(tempInner);
    }

    printSV(forwardList);



}


int main() {
    getData();
    getLongest();
    return 0;
}

