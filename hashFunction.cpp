
#include "hashFunction.hpp"

using namespace std;

void init(Keys* k, int length)
{
    for (int i = 0; i < length; i++){
        k[i].data = NULL;
    }
   
}

int HashFunction(string key, int length) {
    int n = 0;
    for (int i = 0; i < key.size(); i++) {
        n += pow(int(key[i]), 2);
    }
    n %= length;
    return n;
}

void Show(Keys* k, int length) {
    for (int i = 0; i < length; i++){
        if (k[i].data != NULL && k[i].data->used == true)
            cout << i+1 << ": "<< k[i].data->value.numOfPassp << " " << k[i].data->value.fio << endl;
    }
    
}

void Add(Keys *k, int a, passenger pas, int length){
    if (k[a].data == NULL || k[a].data->used == false) {
        
        Table* temp = new Table;
        
        temp->value.dateOfBirth = pas.dateOfBirth;
        temp->value.numOfPassp = pas.numOfPassp;
        temp->value.fio = pas.fio;
        temp->value.dateOfPas = pas.dateOfPas;
        temp->value.placeOfPas = pas.placeOfPas;
        k[a].data = temp;
        
        k[a].data->used = true;
    }
    else
    {
        int c = 0;
        while (a < length)
        {
            c++;
            a = a + c + c * c;
            if (k[a].data == NULL)
            {
                Table* temp = new Table;
                k[a].data = temp;
                temp->value = pas;
                k[a].data->used = true;
                break;
            }
        }
        cout<<"Элемент не был вставлен"<<endl;
    }
}

bool tableIsEmpty(Keys *k, int length)
{
    for (int i = 0; i< length; i++){
        if (k[i].data != NULL && k[i].data->used == true) return false;
    }
    return true;
}


bool DelElem(Keys* k, int length,  string number) {
    
    int n;
    bool flag = false;
    n = HashFunction(number, length);
    
    Table* temp = k[n].data;
    int c = 0;
    while (n < length)
    {
        if (k[n].data != NULL && k[n].data->used == true){
            delete temp;
            k[n].data->used = false;
            flag = true;
            return flag;
        }
        else{
            c++;
            n += c + c * c;
            temp = k[n].data;
        }
        
    }
    return flag;
}

void delAllTable(Keys *k, int length)
{
    for (int i = 0; i < length; i++){
        if (k[i].data && k[i].data->value.dateOfBirth != ""){
            k[i].data->used = false;
            delete k[i].data;
        }
    }
    
}

void showOnePassanger(Keys *k, int length, std::string numb){
    int n = HashFunction(numb, length);
    Table* temp = new Table;
    temp = k[n].data;
    int c = 0;
    
    while (n < length)
    {
        if (temp != NULL)
        {
            if (temp->value.numOfPassp == numb && temp->used == true){
                std::cout << "Номер паспорта: " << temp->value.numOfPassp << endl;
                std::cout << "Место выдачи: " << temp->value.placeOfPas << endl;
                std::cout << "Дата выдачи: " << temp->value.dateOfPas << endl;
                std::cout << "ФИО: " << temp->value.fio << endl;
                std::cout << "Дата рождения: " << temp->value.dateOfBirth << endl;
                break;
            }
        }
        else
        {
            c++;
            n += c + c * c;
            temp = k[n].data;
        }
        
    }
    
}

std::string getPasByFIO(Keys *k, int length, string numb)
{
    for (int i = 0; i < length; i ++){
        if (k[i].data != NULL && k[i].data->value.fio == numb){
            return k[i].data->value.numOfPassp;
        }
    }
    return " ";
}

bool searchByFIO(Keys *k, int length, string numb){
    int n;
    bool flag = false;
    
    Table* temp = new Table;
    int c = 0;
    temp = k[c].data;
    
    while (c < length)
    {
        if (temp != NULL)
        {
            if (temp->value.fio == numb){
                flag = true;
                std::cout << temp->value.numOfPassp << " " << temp->value.fio << endl;
                
            }
        }
        
        c++;
        temp = k[c].data;
    }
    return flag;
}

bool searchByPasport(Keys *k, int length, string numb){
    
    int n;
    bool flag = false;
    n = HashFunction(numb, length);
    
    Table* temp = new Table;
    temp = k[n].data;
    int c = 0;
    while (n < length)
    {
        if (temp != NULL)
        {
            if (temp->value.numOfPassp == numb){
                flag = true;
                return flag;
            }
        }
        
        c++;
        n += c + c * c;
        temp = k[n].data;
        
    }
    return flag;
}

void readF(Keys *k, int length) {
    ifstream fin("passangersRead.txt");
    string number, place, datePas, name, dob;

    int check = 0;
    int n = 0;
    bool flag = false;
    bool result = false;

    if (!fin.is_open()) {
        cout << "Файл не найден!" << endl;
        return;
    }


    if (!tableIsEmpty(k, length))
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
                    delAllTable(k, length);
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
        if (!CorrectPassport(number)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;

        }

        getline(fin, place, ';');
        if (place == " " || place == "\n" ) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }

        getline(fin, datePas, ';');
        if (!CorrectDate(datePas)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, name, ';');
        if (!CorrectFIO(name)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }
        
        getline(fin, dob);
        if (!CorrectDate(dob)) {
            fin.ignore(0x7fff, '\n');
            result = true;
            continue;
        }

        if (number != "")
        {
            flag = true;
            if (CorrectPassport(number) && CorrectDate(datePas) && CorrectFIO(name) && CorrectDate(dob))
            {
                if (!searchByPasport(k, length, number)){
                    passenger temp;
                    temp.numOfPassp = number;
                    temp.dateOfPas = datePas;
                    temp.fio = name;
                    temp.dateOfBirth = dob;
                    temp.placeOfPas = place;
                    
                    int a = HashFunction(number, length);
                    
                    Add(k, a, temp, length);
                }
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
}

