

#ifndef checkFile_hpp
#define checkFile_hpp

#include <iostream>

inline int CheckMainChoise(int);
inline std::string CheckDest(std::string);
inline bool CorrectDest(std::string*);
inline bool CorrectCompanyName(std::string);
inline std::string CheckCompanyName();
inline bool CorrectFlightNumber(std::string);
inline std::string CheckFlightNumber();
inline std::string CheckDepar();
inline bool CorrectDate(std::string);
inline std::string CheckDate();
inline bool CorrectTime(std::string str);
inline std::string CheckTime();
inline bool CorrectPlaces(int a);
inline int CheckPlaces();
inline std::string CheckPassport();
inline bool CorrectPassport(std::string s);
inline std::string CheckPlaceOfPass();
inline bool CorrectFIO(std::string s);
inline std::string CheckFIO();
inline bool CorrectDateOfBirth(std::string s, std::string ss);
inline std::string CheckDateOfBirth(std::string s);

#endif /* checkFile_hpp */
