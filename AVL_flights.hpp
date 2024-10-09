

#ifndef AVL_flights_hpp
#define AVL_flights_hpp

#include <string>
#include <iostream>
#include <fstream>
#include "checkFile.cpp"

using namespace std;

struct flight
{
    std::string numOfFlight;
    std::string company;
    std::string destination;
    std::string departure;
    std::string dateOfFlight;
    std::string timeOfFlight;
    int totalPlaces;
    int freePlaces;
    
};

struct tree
{
    flight value;
    int h;
    tree* left;
    tree* right;
    tree(flight v)
    {
        value = v;
        left = right = NULL;
        h = 1;
        
    }
};

const int charSize = 255;


inline int height(tree* r);
inline int bfactor(tree* r);
inline void fixh(tree* r);
inline tree* rightrotate(tree* p);
inline tree* leftrotate(tree* q);
inline tree* balance(tree* r);
inline tree* insertTree(tree* r, flight *val);
inline tree* findmin(tree* r);
inline tree* removemin(tree* r);
inline tree* eraseTreeElem(tree*, std::string);
inline void showtree(tree* r, int l);
inline void createNewFlight(flight *fl, std::string fligthNum, std::string compName, std::string distan,std::string depar, std::string date, std::string time, int places);
inline void deleteAllTree(tree* r);
inline bool searchByFlightNum(tree *r, std::string str);
inline bool searchHelp(std::string txt, std::string str);
inline void badCharHeuristic(std::string s, int badchar[charSize]);
inline tree* readF(tree *r);
inline bool SravnenieOfFligth(string s1, string s2);
inline bool CheckOnExistFlights(tree *r, string str);
inline bool CheckOnExistHelper(string s1, string s2);
inline void showFlight(tree *r, std::string str);
inline void searchByDest(tree *r, std::string str);
inline bool searchByDestHelper(tree *r, std::string str);
inline tree *reducePlaces(tree *r, std::string str);
inline bool checkOnFreePlaces(tree *r, std::string str);
inline tree *increacePlaces(tree *rr, std::string str);
inline bool RavnoOfFligth(string s1, string s2);
inline tree *decrecePlaces(tree *rr, std::string str);


#endif /* AVL_flights_hpp */
