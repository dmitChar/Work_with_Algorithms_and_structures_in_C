
#include "hashFunction.cpp"
#include "AVL_flights.cpp"
#include "SpisokProdaj.cpp"


int main() {
    setlocale(LC_ALL, "ru");
    const int length = 1000;
    Keys* k = new Keys[length];
    tree *r = NULL;
    List *tickets = new List;
    flight *fl = new flight;
    init(k, length);
    passenger pas;
    std::string des = "";
    std::string p = "";
    int choise = 0;
    int deepChoice = 0;
    int a = 0;
    
    
    
    
   while (true)
   {
       std::cout << "====== ГЛАВНОЕ МЕНЮ ======" << endl;
       
       std::cout << "1. Добавление нового пассажира" << endl;
       std::cout << "2. Удаление данных о пассажире" << endl;
       std::cout << "3. Просмотр всех зарегистрированных пассажиров " << endl;
       std::cout << "4. Очистка данных о пассажирах " << endl;
       std::cout << "5. Поиск пассажира по «номеру паспорта» " << endl;
       std::cout << "6. Поиск пассажира по его ФИО" << endl;
       
       std::cout << "7. Добавление нового рейса" <<endl;
       std::cout << "8. Удаление авиарейса" << endl;
       std::cout << "9. Удаление всех авиарейсов" << endl;
       std::cout << "10. Просмотр всех авиарейсов" << endl;
       std::cout << "11. Поиск авиарейса по «номеру авиарейса»" << endl;
       std::cout << "12. Поиск авиарейса по фрагментам названия аэропорта прибытия" << endl;
       
       std::cout << "13. Регистрация продажи билета пассажиру" << endl;
       std::cout << "14. Регистрация возврата билета" << endl;
       //std::cout << "15. Чтение данных из файла" << endl;
       std::cout << "15. Выход из программы" << endl;
       
       cout << endl << "Выберите номер главного меню: ";
       choise = CheckMainChoise(16);
       
       switch (choise)
       {
               
           case 1:
               std::cout << "Введите номер паспорта. Строка должна быть формата «NNNN-NNNNNN»: ";
               pas.numOfPassp = CheckPassport();
               while (searchByPasport(k, length, pas.numOfPassp)){
                   std::cout << "Введеные серия и номер паспорта уже существуют! Повторите ввод: ";
                   pas.numOfPassp = CheckPassport();
               }
               std::cout << "Введите место регистрации паспорта: ";
               pas.placeOfPas = CheckPlaceOfPass();
               
               std::cout << "Введите дату регистрации паспорта: ";
               pas.dateOfPas = CheckDate();
               
               std::cout << "Введите свою ФИО: ";
               pas.fio = CheckFIO();
               
               std::cout << "Введите свою дату рождения: ";
               pas.dateOfBirth = CheckDateOfBirth(pas.dateOfPas);
               
               a = HashFunction(pas.numOfPassp, length);
               Add(k, a, pas, length);
               std::cout<< "Пассажир успешно добавлен!" << endl;
               Show(k, length);
               break;
               
           case 2:
               if (!tableIsEmpty(k, length)){
                   Show(k, length);
                   std::cout << "Введите номер паспорта пассажира, которого хотите удалить: ";
                   des = CheckPassport();
                   if (DelElem(k, length, des))
                   {
                       tickets->delTicketsByPas(des, r);
                       
                       std::cout << "Пассажир с номером паспорта " << des << " был успешно удален!" << endl;
                       
                   }
                   else std::cout << "Не было найдено пассажира с введнным номером паспорта!" << endl;
               }
               else std::cout << "Удаление невозможно! Сначала добавьте хотя бы одного пассажира!" << endl;
               
               break;
               
           case 3:
               if (!tableIsEmpty(k, length))
                   Show(k, length);
               else std::cout << "Отсутсвуют данные об пассажирах! " << endl;
               break;
               
           case 4:
               if (!tableIsEmpty(k, length))
               {
                   delAllTable(k, length);
                   tickets->delAllTickets(r);
                   std::cout << "Данные обо всех пассажирах были удалены!" << endl;
               }
               else std::cout << "Удаление невозмножно при отсутсвии данных! Сначала введите данные хотя бы об одном пассажире!" << endl;
               break;
               
           case 5:
               Show(k, length);
               std::cout << "Введите номер паспорта пассажира, которого хотите просмотреть: ";
               des = CheckPassport();
               if (!searchByPasport(k, length, des)) std::cout << "Пассажира с введенным номером паспорта не найдено!" << endl;
               else {
                   showOnePassanger(k, length, des);
                   if(!tickets->searchByPasInTickets(des))
                       std::cout << "Пассажир не зарегестрирован ни на один рейс" << endl;
               }
               
               break;
               
               
           case 6:
               if (!tableIsEmpty(k, length)){
                   std::cout << "Введите ФИО пассажира, которого хотите просмотреть: ";
                   des = CheckFIO();
                   if (!searchByFIO(k, length, des))
                       std::cout << "Не было найдено пассажиров с заданными ФИО" << endl;
                   else
                   {
                       p = getPasByFIO(k, length, des);
                       tickets->searchByPasInTickets(p);
                   }
               }
               break;
               
           case 7:
               std::cout <<"Введите номер авиарейса. Строка должна быть формата «AAA-NNN»:";
               fl->numOfFlight = CheckFlightNumber();
               
               while (CheckOnExistFlights(r, fl->numOfFlight))
               {
                   std::cout << "Введеный номер авиарейса уже существует! Повторите ввод: ";
                   fl->numOfFlight = CheckFlightNumber();
               }
               
               std::cout <<"Введите место отправления:";
               fl->departure = CheckDepar();
               
               std::cout << "Введите направление рейса: ";
               fl->destination = CheckDest(fl->departure);
               
               std::cout <<"Введите название авиакомпании:";
               fl->company = CheckCompanyName();
               
               std::cout <<"Введите дату полета:";
               fl->dateOfFlight = CheckDate();

               std::cout <<"Введите количество мест:";
               fl->totalPlaces = fl->freePlaces = CheckPlaces();
               
               r = insertTree(r, fl);
               
               cout << "Новый рейс успешно добавлен!" << endl;
               break;
               
           case 8:
               if (r && !r->value.destination.empty())
               {
                   std::cout <<"Введите номер авиарейса, который хотите удалить. Строка должна быть формата «AAA-NNN»:";
                   fl->numOfFlight = CheckFlightNumber();
                   
                   if (!CheckOnExistFlights(r, fl->numOfFlight))
                   {
                       std::cout << "Введеного номера авиарейса не существует!" << endl;
                       break;
                   }
                   else
                   {
                       if (tickets->checkTickets())
                       {
                           if (tickets->searchByFlightInTickets(fl->numOfFlight))
                               tickets->delTicketsByFlight(fl->numOfFlight);
                       }
                       
                       r = eraseTreeElem(r, fl->numOfFlight);
                       std::cout << "Авиарейс успешно удален! " << endl;
                   }
               }
               else std::cout << "Не введено ни одного авиарейса!" << endl;
               break;
               
           case 9:
               if (r && !r->value.destination.empty())
               {
                   deleteAllTree(r);
                   tickets->delAllTickets(r);
                   std::cout << "Все авиарейсы успешно удалены!" << endl;
               }
               else std::cout << "Не введено ни одного авиарейса!" << endl;
                   
               break;
               
           case 10:
               if (r && !r->value.destination.empty())
                   showtree(r, 0);
               else std::cout << "Не введено ни одного авиарейса!" << endl;
               break;
               
           case 11:
               if (r && !r->value.destination.empty())
               {
                   std::cout <<"Введите номер авиарейса, который хотите найти. Строка должна быть формата «AAA-NNN»:";
                   fl->numOfFlight = CheckFlightNumber();
                   if (!searchByFlightNum(r, fl->numOfFlight))
                       std::cout << "Введенный авиарейс не был найден" << endl;
                   else {
                       showFlight(r, fl->numOfFlight);
                   }
                   
               }
               else std::cout << "Не введено ни одного авирейса!" << endl;
               break;
               
           case 12:
               std::cout << "Введите название аэропорта прибытия полностью или его часть: ";
               getline(std::cin, des);
               if (searchByDestHelper(r, des))
                   searchByDest(r, des);
               else std::cout << "Не найдено ни одного аэропорта отправления" << endl;
               break;
               
           case 13:
               if (!tableIsEmpty(k, length) && r && !r->value.destination.empty())
               {
                   std::cout << "Введите номер паспорта пассажира, для котроого требуется оформить билет: "; des = CheckPassport();
                   if (!searchByPasport(k, length, des))
                       std::cout << "Не было найдено пассажира с заданным номером паспорта" << endl;
                   else
                   {
                       std::cout <<"Введите номер авиарейса, на который требуется оформить билет. Строка должна быть формата «AAA-NNN»: ";
                       fl->numOfFlight = CheckFlightNumber();
                       
                       if (!searchByFlightNum(r, fl->numOfFlight))
                           std::cout << "Введенный авиарейс не был найден" << endl;
                       else
                       {
                           if (checkOnFreePlaces(r, fl->numOfFlight)){
                               
                               tickets->addSellTicket(des, fl->numOfFlight);
                               r = reducePlaces(r, fl->numOfFlight);
                           }
                           else std::cout << "На данном авиарейсе больше нет свободных мест!" << endl;
                           
                       }
                       
                   }
               }
               else std::cout << "Невозможно оформить билет, так как не были введены данные о пассажирах или авиарейсах! " << endl;
               break;
               
           case 14:
               if (!tickets->checkTickets()) std::cout << "Еще не было продано ни одного билета! Возврат невозможен" << endl;
               else
               {
                   tickets->showAllTickets();
                   std::cout << "Введите номер паспорта пассажира, для котроого требуется вернуть билет: "; des = CheckPassport();
                   if (!searchByPasport(k, length, des))
                       std::cout << "Не было найдено пассажира с заданным номером паспорта" << endl;
                   else
                   {
                       if (!tickets->searchByPasInTickets(des))
                           std::cout << "Для данного пассажира не было продано ни одного билета" << endl;
                       else
                       {
                           std::cout <<"Введите номер авиарейса, на котором требуется вернуть билет. Строка должна быть формата «AAA-NNN»: ";
                           fl->numOfFlight = CheckFlightNumber();
                           
                           if (!searchByFlightNum(r, fl->numOfFlight))
                               std::cout << "Введенный авиарейс не был найден" << endl;
                           else{
                           
                               if (tickets->delTicketsByFlightAndPas(fl->numOfFlight,des))
                               {
                                   std::cout << "Билет был успешно возвращен!" << endl;
                                   r = increacePlaces(r, fl->numOfFlight);
                               }
                               else std::cout << "У данного пассажира не было билета на этот рейс" << endl;
                               
                           }
                           
                       }
                       
                   }
                   
               }
               break;
               
           case 16:
               std::cout << "Чтение каких данных вы хотите выполнить?" << endl;
               std::cout << "1. Чтение рейсов" << endl;
               std::cout << "2. Чтение пассажиров" << endl;
               std::cout << "3. Выход в главное меню" << endl;
               std::cout << "Выберите пункт меню: ";
               deepChoice = CheckMainChoise(3);
               
               switch (deepChoice){
                   case 1:
                       r = readF(r);
                       break;
                   case 2:
                       readF(k, length);
                       break;
                   case 3:
                       break;
               }
               break;
               
           case 15:
               exit(0);
               break;
               
               
 
       }
   }
    return 0;
}
