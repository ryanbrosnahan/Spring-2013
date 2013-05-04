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

bool vectComp(std::vector<elephant> A, std::vector<elephant> B) {
    return (A.size() > B.size());
}

void printSV(std::vector< std::vector<elephant> > outer) {

    for(int i = 0; i < outer.size(); ++i) {
        std::cout << outer[i][0].index << " weight: " << outer[i][0].weight << " IQ: " << outer[i][0].iq << std::endl;

        for(int j = 1; j < outer[i].size(); ++j)
            std::cout << "  ---->  " << outer[i][j].index << " weight: " << outer[i][j].weight << " IQ: " << outer[i][j].iq << std::endl;
    }
}

/*
  returns the index of the largest sized subvector, given a reference to see which ones we are
  finding the "max" of. This would make more sense if done recursively. returns -1 if the reference
  has no subvector.
 */
int max(std::vector< std::vector<elephant > > vect, int ref) {

    // figure out which ones are being searched
    std::vector<int> ops;
    if (ref == -1)
        for (int i = 0; i < vect.size(); i++)
            ops.push_back(i);
    else
        for (int i = 1; i < vect[ref].size(); i++)
            ops.push_back(vect[ref][i].index);

    // for testing, prints out the subvectors from which we would look for the largest
    for(auto n = ops.begin(); n < ops.end(); ++n)
        std::cout << "ops: " << *n << std::endl;

    // if the reference subvector has no arrows going to it
    if(ops.size() == 0)
        return -1;

    // find the max of the given choices
    int max = ops[0];
    for(auto i = ops.begin(); i < ops.end(); ++i) {
        std::cout << "temp max = " << max <<std::endl;
        if( vect[*i].size() > vect[max].size())
            max = *i;
    }


}



void getLongest() {

    std::cout << "Generating DAG: " << std::endl << std::endl;

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

    std::sort(forwardList.begin(), forwardList.end(), vectComp);

    printSV(forwardList);
    // to store the result
    std::vector<elephant> bestPath;

    bestPath.push_back(forwardList[0][0]);


}




int main() {
    getData();
    getLongest();
    return 0;
}

