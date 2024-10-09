
#include "AVL_flights.hpp"

void createNewFlight(flight *fl, std::string fligthNum, std::string compName, std::string distan,std::string depar, std::string date, std::string time, int places)
{
    fl->numOfFlight = fligthNum;
    fl->company = compName;
    fl->destination = distan;
    fl->departure = depar;
    fl->dateOfFlight = date;
    fl->timeOfFlight = time;
    fl->totalPlaces = places;
    fl->freePlaces = places;
    
}

int height(tree* r)
{
    if (r) return r->h;
    else return 0;

}

int bfactor(tree* r)
{
    return height(r->right) - height(r->left);
}

void fixh(tree* r)
{
    int hl = height(r->left);
    int hr = height(r->right);
    if (hl > hr) r->h = hl + 1;
    else r->h = hr + 1;
}

tree* rightrotate(tree* p)
{
    tree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixh(p);
    fixh(q);
    return q;
}

tree* leftrotate(tree* q)
{
    tree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixh(q);
    fixh(p);
    return p;
}

tree* balance(tree* r)
{
    fixh(r);
    if (bfactor(r) == 2)
    {
        if (bfactor(r->right) < 0)
            r->right = rightrotate(r->right);
        return leftrotate(r);
    }
    if (bfactor(r) == -2)
    {
        if (bfactor(r->left) > 0)
            r->left = leftrotate(r->left);
        return rightrotate(r);
    }
    return r;
}

bool SravnenieOfFligth(string s1, string s2)
{

    for (int i = 0; i < s1.length(); i++)
        if ((unsigned char)s1[i] < (unsigned char)s2[i])
            return true;
        
        return false;
}

bool RavnoOfFligth(string s1, string s2)
{

    for (int i = 0; i < s1.length(); i++)
        if ((unsigned char)s1[i] != (unsigned char)s2[i])
            return false;
        
        return true;
}

tree* insertTree(tree* r, flight *val)
{
    if (!r || r->value.destination.empty()) return new tree(*val);
    if (SravnenieOfFligth(val->numOfFlight, r->value.numOfFlight)) r->left = insertTree(r->left, val);
    else r->right = insertTree(r->right, val);
    return balance(r);
}

tree* findmin(tree* r)
{
    /*if (r->left) findmin(r->left);
    else return r;*/
    
    while (r->left != NULL){
        r = r->left;
    }
    return r;
}

tree* removemin(tree* r)
{
    if (!r->left) return r->right;
    r->left = removemin(r->left);
    return balance(r);
}

tree* eraseTreeElem(tree* rr, string numb)
{
    if (!rr) return 0;
    if (SravnenieOfFligth(numb, rr->value.numOfFlight)) rr->left = eraseTreeElem(rr->left, numb);
    else if (!SravnenieOfFligth(numb, rr->value.numOfFlight) && !RavnoOfFligth(numb, rr->value.numOfFlight)) rr->right = eraseTreeElem(rr->right, numb);
    else
    {
        tree* l = rr->left;
        tree* r = rr->right;
        delete rr;
        if (!r) return l;
        tree* min = findmin(r);
        min->right = removemin(r);
        min->left = l;
        return balance(min);
    }
    return balance(rr);
}

void showtree(tree* r, int l)
{
    if (r)
    {
        showtree(r->right, l + 1);
        for (int i = 1; i <= l; i++) cout << "   " << " ";
        cout << r->value.numOfFlight << endl;
        showtree(r->left, l + 1);
    }
}

void deleteAllTree(tree* r){
    
    if (r && !r->value.destination.empty())
    {
        deleteAllTree(r->left);
        deleteAllTree(r->right);
        delete r;
    }
}

void badCharHeuristic(std::string s, int badchar[charSize])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < charSize; i++)
        badchar[i] = -1;
 
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < s.length(); i++)
        badchar[(int) s[i]] = i;
}
 

void showFlight(tree *r, std::string str)
{
    if (!r) return;
    
    showFlight(r->left, str);
    bool f = searchHelp(r->value.numOfFlight, str);
    if (f)
    {
        std::cout << "Номер авиарейса: " << r->value.numOfFlight << endl;
        std::cout << "Название компании: " << r->value.company << endl;
        std::cout << "В " << r->value.destination << endl;
        std::cout << "Из " << r->value.departure << endl;
        std::cout << "Дата полета: " << r->value.dateOfFlight << endl;
        std::cout << "Время полета: " << r->value.timeOfFlight << endl;
        std::cout << "Всего мест: " << r->value.totalPlaces << endl;
        std::cout << "Свободных мест: " << r->value.freePlaces << endl;
        return;
    }
    showFlight(r->right, str);
    
    return;
}

bool searchHelp(std::string txt, std::string str)
{
    int m = str.length();
    int n = txt.length();
    
    int badchar[charSize];
    
    badCharHeuristic(str, badchar);
    
    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;
        
        while (j >= 0 && str[j] == txt[s + j])
            j--;
        
        if (j < 0)
        {
            
            return true;
        }
        
        else
            s += max(1, j - badchar[txt[s + j]]);
    }
    return false;
   
}

bool searchByFlightNum(tree *r, std::string str)
{
    if (!r) return false;
    bool f = false;
    
    if (!f) f = searchByFlightNum(r->left, str);
    if (!f) f = searchHelp(r->value.numOfFlight, str);
    if (f) return true;
    if (!f) f = searchByFlightNum(r->right, str);
    
    return f;
}

bool searchByDestHelper(tree *r, std::string str)
{
    if (!r) return false;
    bool f = false;
    
    if (!f) f = searchByDestHelper(r->left, str);
    f = searchHelp(r->value.destination, str);
    if (f) return true;
    if (!f) f = searchByDestHelper(r->right, str);
    
    return f;
}

void searchByDest(tree *r, std::string str)
{
    if (!r) return;
    
    searchByDest(r->left, str);
    
    if (searchHelp(r->value.destination, str))
    {
        std::cout << "Номер авиарейса: " << r->value.numOfFlight << endl;
        std::cout << "Название компании: " << r->value.company << endl;
        std::cout << "В " << r->value.destination << endl;
        std::cout << "Из " << r->value.departure << endl;
        std::cout << "Дата полета: " << r->value.dateOfFlight << endl;
        std::cout << "Время полета: " << r->value.timeOfFlight << endl;
        std::cout << "Всего мест: " << r->value.totalPlaces << endl;
        std::cout << "Свободных мест: " << r->value.freePlaces << endl << endl;
        
    }
    searchByDest(r->right, str);
    
    return;
    
}

bool CheckOnExistHelper(string s1, string s2){
    
    for (int i = 0; i < s1.length(); i++)
        if (s1[i] != s2[i])
            return false;
    
    return true;
}

bool CheckOnExistFlights(tree *r, string str){
    if (!r || r->value.destination.empty()) return false;
    bool f = false;
    
    if (!f) f = searchByFlightNum(r->left, str);
    if (!f) f = CheckOnExistHelper(r->value.numOfFlight, str);
    if (f) return true;
    if (!f) f = searchByFlightNum(r->right, str);
    
    return f;
}

tree *reducePlaces(tree *rr, std::string str){
    
    if (!rr) return 0;
    if (rr->value.numOfFlight == str){
        rr->value.freePlaces = rr->value.freePlaces - 1;
        
        return rr;
    }
    else if (!SravnenieOfFligth(rr->value.numOfFlight, str)) rr->left = reducePlaces(rr->left, str);
    else if (SravnenieOfFligth(rr->value.numOfFlight, str)) rr->right = reducePlaces(rr->right, str);
    
    return balance(rr);

}
tree *increacePlaces(tree *rr, std::string str){
    if (!rr) return 0;
    if (rr->value.numOfFlight == str){
        rr->value.freePlaces = rr->value.freePlaces + 1;
        
        return rr;
    }
    else if (!SravnenieOfFligth(rr->value.numOfFlight, str)) rr->left = increacePlaces(rr->left, str);
    else if (SravnenieOfFligth(rr->value.numOfFlight, str)) rr->right = increacePlaces(rr->right, str);
    
    return balance(rr);
}

bool checkOnFreePlaces(tree *r, std::string str)
{
    if (!r) return false;
    bool f = false;
    
    if (!f) f = checkOnFreePlaces(r->left, str);
    if (r->value.numOfFlight == str)
    {
        if (r->value.freePlaces > 0)
            f = true;
        else f = false;
        std::cout << "Количество свободных мест = " <<r->value.freePlaces << endl;
        return f;
    }
    if (f) return true;
    if (!f) f = checkOnFreePlaces(r->right, str);
    
    return f;
}


tree* readF(tree *r) {
    ifstream fin("flightsRead.txt");
    string number, comp, dest, dep, date, time, places;

    int check = 0;
    bool flag = false;
    bool result = false;

    if (!fin.is_open()) {
        cout << "Файл не найден!" << endl;
        return r;
    }


    if (r != NULL && !r->value.destination.empty() )
    {
        while (!flag)
        {
            cout << "Список не пустой! Что вы хотите с ним сделать?" << endl << "1.Записать новые элементы и удалить старые" << endl << "2.Добавить к текущим" << endl;
            cout << "Выберите один из пунктов: ";
            cin >> check;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail());
                check = -1;
            }
            switch (check) {
                case 1:
                    deleteAllTree(r);
                    flag = true;
                    break;
                    
                case 2:
                    flag = true;
                    break;
                    
                default:
                    cout << "Некорректный ввод. Попробуйте снова!" << endl;
                    system("pause");
                    system("cls");
            }
        }
        flag = false;
    }
    while (!fin.eof())
    {

        getline(fin, number, ';');
        if (!CorrectFlightNumber(number)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;

        }

        getline(fin, comp, ';');
        if (!CorrectCompanyName(comp)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }

        getline(fin, dest, ';');
        if (!CorrectDest(&dest)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, dep, ';');
        if (!CorrectDest(&dep)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, time, ';');
        if (!CorrectTime(time)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, date, ';');
        if (!CorrectDate(date)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, places);
        if (!CorrectPlaces(stoi(places))) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        if (number != "")
        {
            flag = true;
            if (CorrectFlightNumber(number) && CorrectCompanyName(comp) && CorrectDest(&dest) && CorrectDest(&dep) && CorrectTime(time) && CorrectDate(date) && CorrectPlaces(stoi(places)))
            {
                
                if (!CheckOnExistFlights(r, number)){
                    flight* temp = new flight;
                    createNewFlight(temp, number, comp, dest, dep, date, time, stoi(places));
                    r = insertTree(r, temp);
                    
                }
                else result = true;
            }

        }
    }
    if (flag) {
        if (!result)
            cout << "Чтение из файла завершено! Все элементы добавлены!" << endl;
        else
            cout << "Чтение из файла завершено! Не все элементы были добавлены! Проверьте исходный файл" << endl;
    }

    else
        cout << "Не было найдено элементов для записи!" << endl;
    return r;
}

