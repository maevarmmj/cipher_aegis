#ifndef KEYWORDCONTROLEUR_H
#define KEYWORDCONTROLEUR_H

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>
#include <QDir>
#include <filesystem>


enum class GenerateResult{
    Success,
    Error,
    MissingInfo,
};

class PasswordControleur
{

private:
    std::string password;
public:
    PasswordControleur();

    std::string insert_into_string(std::string string, int position, char char_to_insert); // Insert a character in the existing string
    std::string lower_case(std::string keyword, int num_char, int num_upper_letters, int num_spec_char);
    std::string add_numbers(std::string keyword, int num_number);
    std::string upper_case(std::string keyword, int num_upper_letters);
    std::string spec_characters(std::string keyword, int num_spec_char, const std::vector<std::string>& spec_chars_list);
    GenerateResult generatePassword(std::string site_name, int num_char, int num_number, int num_spec_char, const std::vector<std::string>& spec_chars_list);

    std::string getPassword();
};

#endif // KEYWORDCONTROLEUR_H
