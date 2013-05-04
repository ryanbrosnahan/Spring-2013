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
 Takes a vector of the longest path of elephants and writes it to the file (reversing the order)
 */
void writeout(std::vector<elephant> vec) {
    std::ofstream outfile("e.out");
    outfile << vec.size() << '\n';

    int size = vec.size();
    for(int i = 0; i < size ; ++i) {
        outfile << vec.back().index << '\n';
        vec.pop_back();
    }

    outfile.close();
}


/*
  For testing purposes, lists all elements that were read form e.in
 */
void printV() {
    for(auto i = elephants.begin(); i != elephants.end(); ++i)
        std::cout << i->index << " weight: " << i->weight << " IQ: " << i->iq << std::endl;
}

void printV(std::vector<elephant> vec) {
    for(auto i = vec.begin(); i != vec.end(); ++i)
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
        for (auto j = vect[ref].begin()+1; j < vect[ref].end(); j++)
            ops.push_back(j->index);

    // for testing, prints out the subvectors from which we would look for the largest
    for(auto n = ops.begin(); n < ops.end(); ++n)
        //std::cout << "ops: " << *n << std::endl;

    // if the reference subvector has no arrows going to it
    if(ops.size() == 0)
        return -1;

    // find the max of the given choices, which is the first that matches ANY ops
    for(int i = 0; i < vect.size(); ++i) {
        for(int j = 0; j < ops.size(); ++j) {
            if(vect[i][0].index == ops[j])
                return i;
        }
    }
    return -2;

}

/*
 unused
 */
int find(std::vector< std::vector<elephant > >  vec, int ref) {
    int index;
    for(int i = 0; i < vec.size(); ++i)
        if (vec[i][0].index == ref)
            index = i;
}

/*
 Takes the data found from e.in and figures out the order
 */
void getLongest() {

    // Creates the DAG and cout's the result; used for testing only
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

    // sorting makes it much easier to work with and reduces searching time in the future, resulting in a net
    // improvement in performance
    std::sort(forwardList.begin(), forwardList.end(), vectComp);

    printSV(forwardList);
    std::cout << std::endl;

    // The dynamic programming part, stick the elephants on the ordered vector in the right order
    std::vector<elephant> ordered;

    int i = -1;
    while(true) {
        i = max(forwardList, i);
        if (i == -2) break;
        ordered.push_back(forwardList[i][0]);
    }

    std::cout << "The final order (in reverse):" << std::endl;
    printV(ordered);
    writeout(ordered);


}


int main() {
    getData();
    getLongest();
    return 0;
}

