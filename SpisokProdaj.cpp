
#include "SpisokProdaj.hpp"
#include "AVL_flights.hpp"

void List::addSellTicket(std::string pas, std::string flight)
{
    spisok *temp = new spisok;               //Выделение памяти под новый элемент структуры
    temp->next = NULL;                   //Указываем, что изначально по следующему адресу пусто
    temp->passport = pas;
    temp->ticketNum = ticketCreate();
    temp->flightNum = flight;
    countOfTickets++;
    
    if (Head != NULL)                    //Если список не пуст
    {
        temp->prev = Tail;               //Указываем адрес на предыдущий элемент в соотв. поле
        Tail->next = temp;               //Указываем адрес следующего за хвостом элемента
        Tail = temp;                     //Меняем адрес хвоста
    }
    else //Если список пустой
    {
        temp->prev = NULL;               //Предыдущий элемент указывает в пустоту
        Head = Tail = temp;              //Голова=Хвост=тот элемент, что сейчас добавили
    }
    
    std::cout << "Билет был успешно продан! Номер вашего билета: "<< temp->ticketNum << std::endl;
    
    sort();
}

void List::showAllTickets()
{
    spisok *temp=Head;
    while (temp != NULL)
    {
        std::cout << "Паспорт № " << temp->passport << std::endl;
        std::cout << "Номер рейса: " << temp->flightNum <<  std::endl;
        std::cout << "Номер билета: " << temp->ticketNum << std::endl << std::endl;
        temp = temp->next;
    }
}

void List::delAllTickets(tree *r)
{
    spisok *temp = Head;
    spisok *t = NULL;
 
    while (temp)
    {
        countOfTickets--;
        if (temp == Head)
        {
            r = increacePlaces(r, temp->flightNum);
            if (Tail == temp) Head = Tail = nullptr;
            else
            {
                Head = temp->next;
                Head->prev = nullptr;
            }
        }
        else if (temp == Tail)
        {
            Tail = temp->prev;
            Tail->next = nullptr;
        }
        else if(temp)
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        
        std::cout << "Пассажир с билетом " << temp->ticketNum << ", ваш авиарейс под номером " << temp->flightNum << " был отменен!" << std::endl;
        
        t = temp->next;
        delete temp;
        temp = t;
        
        
    }
    
}

std::string List::ticketCreate()
{
    bool flag = false;
    std::string s;
    
    while (flag == false){
        flag = true;
        s = "";
        int temp[9];
        
        for (int i = 0; i < 9; i++){
            temp[i] = rand() % 9;
            s += std::to_string(temp[i]);
        }
        
        if (countOfTickets != 0 )
        {
            for (int i = 0; i < countOfTickets; i++)
            {
                if (storage[i] == s)
                {
                    flag = false;
                    break;
                }
            }
            
        }
        
    }
        storage[countOfTickets] = s;
        return storage[countOfTickets];
}


void List::delTicketsByFlight(std::string fl)
{
    spisok *temp = Head;
    spisok *t = NULL;
    bool flag = false;
    std::string a[1000];
    int count = 0;
    while (temp)
    {
        if (temp->flightNum == fl)
        {
            countOfTickets--;
            if (temp == Head)
            {
                if (Tail == temp) Head = Tail = nullptr;
                else
                {
                    Head = temp->next;
                    Head->prev = nullptr;
                }
            }
            else if (temp == Tail)
            {
                Tail = temp->prev;
                Tail->next = nullptr;
            }
            else if(temp)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            if (count == 0){
                std::cout << "Пассажирам с номерами билетов: " << std::endl;
                a[count] = temp->ticketNum;
                count++;
            }
            else
            {
                a[count] = temp->ticketNum;
                count++;
            }
            
            t = temp->next;
            delete temp;
            temp = t;
        }
        
    }
    if (count != 0)
    {
        for (int i = 0; i< count; i++){
            std::cout << a[i] << std::endl;
        }
        std::cout << "приносим свои извинения. Ваш авиарейс под номером " << fl << " был отменен!" << std::endl;
    }
    
}

bool List::delTicketsByPas(std::string pas, tree* r)
{
    spisok *temp = Head;
    spisok *t = NULL;
    bool flag = false;
    while (temp)
    {
        if (temp->passport == pas)
        {
            r = increacePlaces(r, temp->flightNum);
            std::cout << "Авиарейс с номером: " << temp->flightNum << " , пассажир с номером билета " << temp->ticketNum << " отменил свой полет" << endl;
            countOfTickets--;
            flag = true;
            if (temp == Head)
            {
                if (Tail == temp)
                {
                    Head = Tail = nullptr;
                }
                else
                {
                    Head = temp->next;
                    Head->prev = nullptr;
                }
            }
            else if (temp == Tail)
            {
                Tail = temp->prev;
                Tail->next = nullptr;
            }
            else if(temp)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            
            t = temp->next;
            delete temp;
            temp = t;
            flag = true;
        }
        else temp = temp->next;
    }
    return flag;
    
}


bool List::delTicketsByFlightAndPas(std::string fl, std::string pas)
{
    spisok *temp = Head;
    spisok *t = NULL;
    bool flag = false;
    while (temp)
    {
        if (temp->flightNum == fl && temp->passport == pas)
        {
            countOfTickets--;
            flag = true;
            if (temp == Head)
            {
                if (Tail == temp)
                {
                    Head = Tail = nullptr;
                }
                else
                {
                    Head = temp->next;
                    Head->prev = nullptr;
                }
            }
            else if (temp == Tail)
            {
                Tail = temp->prev;
                Tail->next = nullptr;
            }
            else if(temp)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            
            t = temp->next;
            delete temp;
            temp = t;
            return flag;
        }
        else temp = temp->next;
    }
    return flag;
    
}


bool List::searchByPasInTickets(std::string numb){
    spisok *temp = Head;
    bool flag = false;
    while (temp != NULL)
    {
        if (temp->passport == numb ){
            if (!flag) std::cout << "Зарегестрирован на рейсы: " << std::endl;
            std::cout << temp->flightNum << std::endl;
            flag = true;
            
        }
        temp = temp->next;
    }
    return flag;
}

bool List::searchByFlightInTickets(std::string numb){
    spisok *temp = Head;
    bool flag = false;
    while (temp != NULL)
    {
        if (temp->flightNum == numb ){
            
            flag = true;
            return flag;
        }
        temp =  temp->next;
    }
    return flag;
}

void Swap(spisok* left, spisok* right)
{
    spisok* temp = new spisok;

    temp->passport = left->passport;
    temp->flightNum = left->flightNum;
    temp->ticketNum = left->ticketNum;
    
    left->passport = right->passport;
    left->flightNum = right->flightNum;
    left->ticketNum = right->ticketNum;
    
    right->passport = temp->passport;
    right->flightNum = temp->flightNum;
    right->ticketNum = temp->ticketNum;
    delete temp;
}

void List::sort()
{
    if (Head->next){
        
        spisok *leftMark = Head->next;
        spisok *rightMark = Tail->prev;
        
        while (leftMark <= rightMark)
        {
            for (spisok* i = rightMark; i >= leftMark; i = i->prev)
                if (stoi(i->prev->flightNum, nullptr, 0) > stoi(i->flightNum, nullptr, 0)) Swap(i->prev, i);
            leftMark = leftMark->next;
            
            
            for (spisok *i = leftMark; i <= rightMark; i = i->next)
                if (stoi(i->prev->flightNum) > stoi(i->flightNum)) Swap(i->prev, i);
            rightMark = rightMark->prev;
        }
    }
    //else std::cout<< "Сортировка невозможна! Сначала добавьте хотя бы 2 элемента!" << std::endl;
    
}

bool List::checkTickets()
{
    return (countOfTickets > 0);
}

