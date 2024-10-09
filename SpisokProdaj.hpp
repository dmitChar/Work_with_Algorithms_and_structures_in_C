
#ifndef SpisokProdaj_hpp
#define SpisokProdaj_hpp

#include <iostream>
#include <string>
#include "AVL_flights.hpp"

struct spisok{

    std::string passport;
    std::string flightNum;
    std::string ticketNum;
    
    spisok *prev;
    spisok *next;
};

class List
 {
     spisok *Head, *Tail;
     std::string storage[1500];
     int countOfTickets;
 public:
     List():Head(NULL),Tail(NULL){
         countOfTickets = 0;
     };
    ~List();
     inline void addSellTicket(std::string pas, std::string flight);
     inline void showAllTickets();
     inline void sort();
     inline bool searchByPasInTickets(std::string numb);
     inline void delTicketsByFlight(std::string fl);
     inline std::string ticketCreate();
     inline bool delTicketsByFlightAndPas(std::string fl, std::string);
     inline bool checkTickets();
     inline bool searchByFlightInTickets(std::string numb);
     inline void delAllTickets(tree *);
     inline bool delTicketsByPas(std::string pas, tree*);
 };

inline void Swap(spisok* left, spisok* right);


#endif
