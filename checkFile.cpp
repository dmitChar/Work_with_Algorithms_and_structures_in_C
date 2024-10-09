
#include "checkFile.hpp"

int CheckMainChoise(int n)
{
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    int s;
    std::cin >> s;
    while (std::cin.fail() || std::cin.get() != '\n' || s < 1 || s>n)
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Ошибка ввода! Попробуйте снова: ";
        std::cin >> s;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

std::string CheckDest(std::string depar) {
    std::string s;
    getline(std::cin, s);
    while (!CorrectDest(&s) || s == depar) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введено некорректное направление! Попробуйте снова: ";
        getline(std::cin, s);

    }
    return s;
}

bool CorrectDest(std::string* de) {
    std::string dest = *de;

    if (dest.size() < 2)
        return false;
    if ((unsigned char)dest[0] < 65 || (unsigned char)dest[0] > 122)
        return false;

    if ((unsigned char)dest[0] <= 122 && (unsigned char)dest[0] > 96) {
        dest[0] -= 32;
        *de = dest;
    }

    for (unsigned int i = 1; i < dest.size(); i++) {

        if ((unsigned char)dest[i] < 65 && ((unsigned char)dest[i] != 32 && (unsigned char)dest[i] != 45))
            return false;
        if (((unsigned char)dest[i - 1] == 32 || (unsigned char)dest[i - 1] == 45) && ((unsigned char)dest[i] < 65 || (unsigned char)dest[i] > 96)) {
            if (!((unsigned char)dest[i] == 110 && (unsigned char)dest[i + 1] == 110) || dest.size() - i < 5)
                return false;
        }

        if ((unsigned char)dest[i - 1] > 64 && ((unsigned char)dest[i] < 91 && (unsigned char)dest[i] > 64))
            return false;
    }
    return true;
}

std::string CheckDepar() {
    std::string s;
    getline(std::cin, s);
    while (!CorrectDest(&s)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введен некорректный пункт отправления! Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectCompanyName(std::string str) {
    if (str.size() < 1) return false;

    for (unsigned int i = 0; i < str.size(); i++) {
        if (((unsigned char)str[i] < 65 || (unsigned char)str[i] > 122) && str[i] != ' ')
            return false;
    }
    return true;
}

std::string CheckCompanyName() {
    std::string s;
    getline(std::cin, s);
    while (!CorrectCompanyName(s)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введено некорректное название авакомпании! Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectFlightNumber(std::string str) {
    if (str.size() < 7) return false;

    for (unsigned int i = 0; i < 3; i++)
    {
        if ((unsigned char)str[i] < 65 || (unsigned char)str[i] > 122 ||(unsigned char)str[i] == 91 ||(unsigned char)str[i] == 92 ||(unsigned char)str[i] == 93 ||(unsigned char)str[i] == 94 ||(unsigned char)str[i] == 95 ||(unsigned char)str[i] == 96)
            return false;
    }
    
    if (str[3] != '-') return false;
    
    for (unsigned int i = 4; i < str.length(); i++)
    {
        if ((unsigned char)str[i] < 48 || (unsigned char)str[i] > 57 )
            return false;
    }
    return true;
}

std::string CheckFlightNumber() {
    std::string s;
    getline(std::cin, s);
    while (!CorrectFlightNumber(s)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введен некорректный номер рейса! Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectDate(std::string str)
{
    if (str.size() < 5) return false;
    int array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int index = 0;
    int count = 0;
    int flag = 1;
    
    int month = 0;
    int day = 0;
    std::string year = "";
    
    std::string substr = " ";
        while ((index = str.find(substr, index)) != std::string::npos)
        {
            count++;
            index += substr.length();
        }
    if (count != 2) return false;
    
    substr = " ";
    for (int i = 0; i < str.length()+1; i++)
    {
        if (((unsigned char)str[i] < 48 || (unsigned char)str[i] > 57) && (str[i] != '\0'))
        {
            if (((unsigned char)str[i] < 48 || (unsigned char)str[i] > 57) && str[i] != ' ') return false;
            
        }
        
        if (str[i] != ' ' && str[i] != '\0')
            substr +=str[i];
        
        else
        {
            if (flag == 1){
                day = stoi(substr);
                if (day > 31 || day < 1) return false;
                flag++;
                substr = "";
                continue;
            }
            if (flag == 2){
                month = stoi(substr);
                if (month >12 || month < 1) return false;
                substr = "";
                flag++;
                continue;
            }
            
            if (flag == 3){
                year = substr;
                if (year.size() != 4) {
                    return false;
                }
                if (year[3] == '\0') return false;
                if (stoi(year) == 0) return false;
                if (stoi(year) > 2023 || stoi(year) < 1900) return false;

                    substr = " ";
                    flag++;
                    continue;
                }
            
        }
        
    }
    if (day > array[month-1])
        return false;
    
    return true;
}

std::string CheckDate() {
    std::string s;
    getline(std::cin, s);
    while (!CorrectDate(s)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введена некорректная дата! Дата должна иметь следующий вид: день месяц год. Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}
bool CorrectDateOfBirth(std::string str, std::string birth)
{
    if (str.size() < 5) return false;
    int array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int index = 0;
    int count = 0;
    int flag = 1;
    
    int month = 0;
    int day = 0;
    std::string year = "";
    std::string yearOfBirth = "";
    
    std::string substr = " ";
        while ((index = str.find(substr, index)) != std::string::npos)
        {
            count++;
            index += substr.length();
        }
    if (count != 2) return false;
    
    substr = " ";
    int a = 0;
    
    for (int i = 0; i < birth.length(); i++){
        if (birth[i] == ' ') a++;
        if (a == 2 && birth[i] != ' '){
            yearOfBirth+=birth[i];
        }
    }
    for (int i = 0; i < str.length()+1; i++)
    {
        if (((unsigned char)str[i] < 48 || (unsigned char)str[i] > 57) && (str[i] != '\0'))
        {
            if (((unsigned char)str[i] < 48 || (unsigned char)str[i] > 57) && str[i] != ' ') return false;
            
        }
        
        if (str[i] != ' ' && str[i] != '\0')
            substr +=str[i];
        
        else
        {
            if (flag == 1){
                day = stoi(substr);
                if (day > 31 || day < 1) return false;
                flag++;
                substr = "";
                continue;
            }
            if (flag == 2){
                month = stoi(substr);
                if (month >12 || month < 1) return false;
                substr = "";
                flag++;
                continue;
            }
            
            if (flag == 3){
                year = substr;
                if (year.size() != 4) {
                    return false;
                }
                if (year[3] == '\0') return false;
                if (stoi(year) == 0) return false;
                if (stoi(year) > 2023 || stoi(year) < 1900) return false;
                if (stoi(year) >= stoi(yearOfBirth)) return false;

                    substr = " ";
                    flag++;
                    continue;
                }
            
        }
        
    }
    if (day > array[month-1])
        return false;
    
    return true;
}

std::string CheckDateOfBirth(std::string date) {
    std::string s;
    getline(std::cin, s);
    while (!CorrectDateOfBirth(s, date)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введена некорректная дата рождения! Дата должна иметь следующий вид: день месяц год. Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectTime(std::string str)
{
    if (str.size() > 5) return false;
    int index = 0;
    int c = 0;
    int count = 0;
    std::string substr = ":";
    
    while ((index = str.find(substr, index)) != std::string::npos)
        {
            count++;
            index += substr.length();
        }
    c = str.find(substr, 0);
    
    substr = " ";
    
    if (count != 1) return false;
    
    for (int i = 0; i < c; i++)
    {
        substr += str[i];
        
    }
    
    if (stoi(substr) > 23 || stoi(substr) < 0) return false;
    
    substr = "";
    
    for (int i = c +1; i < str.size(); i++)
    {
        substr += str[i];
    }
    
    if (stoi(substr) > 59 || stoi(substr) < 0) return false;
    
    return true;
}

std::string CheckTime()
{
    std::string s;
    getline(std::cin, s);
    while (!CorrectTime(s)) {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введено некоррктное время! Время должно иметь следующий вид: чч:мм. Попробуйте снова: ";
        getline(std::cin, s);

    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
   
}

bool CorrectPlaces(int a)
{
    if (std::cin.fail() || a < 1)
        return false;
    return true;
}

int CheckPlaces()
{
    int s;
    std::cin >> s;
    while (!CorrectPlaces(s))
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введено некоррктное количество мест! Попробуйте снова: ";
        std::cin >> s;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectPassport(std::string s)
{
    if (s.size() != 11) return false;
    
    if (s[4] != '-') return false;
    
    for (int i = 0; i < s.length(); i++)
    {
        if (((unsigned char)s[i] < 48 || (unsigned char)s[i] > 57) && s[i] != '-') return false;
    }
    
    return true;
}

std::string CheckPassport()
{
    std::string s;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, s);
    while (!CorrectPassport(s))
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введены некорректные серия и номер паспорта. Строка должна быть формата «NNNN-NNNNNN»! Попробуйте снова: ";
        getline(std::cin, s);
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

std::string CheckPlaceOfPass()
{
    std::string s;
    getline(std::cin, s);
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}

bool CorrectFIO(std::string str)
{
    std::string substr = " ";
    int index = 0;
    int count = 0;
    
    while ((index = str.find(substr, index)) != std::string::npos)
        {
            count++;
            index += substr.length();
        }
    
    if (count < 2) return false;
    
    for (int i = 0; i < str.length(); i++)
    {
        if (((unsigned char)str[i] < 65 || (unsigned char)str[i] > 122) && (str[i] != ' ')) return false;
    }
    
    return true;
}

std::string CheckFIO()
{
    std::string s;
    getline(std::cin, s);
    while (!CorrectFIO(s))
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Введены некорректные ФИО. Попробуйте снова: ";
        getline(std::cin, s);
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    return s;
}



