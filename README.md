# ИСПОЛЬЗОВАНИЕ СТРУКТУР ДАННЫХ И АЛГОРИТМОВ ПРИ РАЗРАБОТКЕ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ИНФОРМАЦИОННОЙ СИСТЕМЫ ПРОДАЖИ АВИАБИЛЕТОВ
## О программе
  Программа представляет собой консольное приложение, реализующее информационную систему аэропорта, в функции которой входит работа с данными о пассажирах, об авиарейсах, относящихся к данному аэропорту, и с данными о билетах на рейсы.
## Использованные структуры данных и алгоритмы
- Вид списка - Линейный двунаправленный
- Метод хеширования - Закрытое с квадратичным опробованием
- Метод сортировки - шейкерная
- Метод обхода дерева - обратный
- Алгоритм поиска слова в тексте - Боуера-Мура
## Реализация структуры данных
  - Данные о пассажирах хранятся в структуре (хеш-таблица) Table
`  struct Table {
    passenger value;
    bool used;
};`
- Данные о авиарейсах хранятся в структуре (АВЛ-дерево) tree
`  struct tree {
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
};`
- Данные об авиабилетах хранятся в структуре (список) spisok
`struct spisok {
    std::string passport;
    std::string flightNum;
    std::string ticketNum;
    spisok* prev;
    spisok* next;
};`

## Реализованные функции
1.	Добавление нового пассажира
2.	Удаление данных о пассажире
3.	Просмотр всех зарегестрированных пассажиров
4.	Очистка данных о пассажирах
5.	Поиск пассажира по номеру пасспорта
6.	Поиск пассажира по его ФИО
7.	Добавление нового рейса
8.	Удаление рейса
9.	Удаление всех рейсов
10.	 Просмотр всех рейсов
11.	 Поиск рейса по его номеру
12.	 Поиск рейса по фрагменту названия аэропорта прибытия
13.	 Регистрация продажи билета пассажиру
14.	 Регистрация возврата билета
15.	 Выход из программы

## Главное меню приложения
![image](https://github.com/user-attachments/assets/38de4c44-f39f-41a8-aee4-c2f271fcfffc)




