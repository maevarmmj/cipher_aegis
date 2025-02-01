#include "keywordcontroleur.h"

KeywordControleur::KeywordControleur() {
    this->keyword = "";
}

KeywordControleur::~KeywordControleur() {
}

std::string KeywordControleur::insert_into_string(std::string string, int position, char char_to_insert) {
        string.insert(position, 1, char_to_insert);
        return string;
    }

    // Fonction pour ajouter des lettres minuscules aléatoires
std::string KeywordControleur::lower_case(std::string keyword, int num_char, int num_upper_letters, int num_spec_char) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(97, 122); // Codes ASCII for 'a' to 'z'

        for (int i = 0; i < num_char - num_upper_letters - num_spec_char; ++i) {
            keyword += static_cast<char>(distrib(gen));
        }
        return keyword;
    }

    // Fonction pour remplacer des caractères par des chiffres aléatoires
std::string KeywordControleur::add_numbers(std::string keyword, int num_number) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_char(0, keyword.length() - 1);
        std::uniform_int_distribution<> distrib_num(0, 9);

        for (int i = 0; i < num_number; ++i) {
            int rand_char_keyword = distrib_char(gen);
            while (isdigit(keyword[rand_char_keyword])) {
                rand_char_keyword = distrib_char(gen);
            }
            keyword[rand_char_keyword] = static_cast<char>(distrib_num(gen) + '0');
        }
        return keyword;
    }

    // Fonction pour ajouter des lettres majuscules aléatoires
std::string KeywordControleur::upper_case(std::string keyword, int num_upper_letters) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, keyword.length());
        std::uniform_int_distribution<> distrib_letter(65, 90); // Codes ASCII pour 'A' à 'Z'

        for (int i = 0; i < num_upper_letters; ++i) {
            int rd_upper_letter = distrib_pos(gen);
            keyword = insert_into_string(keyword, rd_upper_letter, static_cast<char>(distrib_letter(gen)));
        }
        return keyword;
    }

    // Fonction pour ajouter des caractères spéciaux (pas d'input dans cette version)
std::string KeywordControleur::spec_characters(std::string keyword, int num_spec_char, const std::string& spec_chars) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, keyword.length());
        std::uniform_int_distribution<> distrib_char(0, spec_chars.length() - 1);

        for (int i = 0; i < num_spec_char; ++i) {
            int position = distrib_pos(gen);
            keyword = insert_into_string(keyword, position, spec_chars[distrib_char(gen)]);
        }
        return keyword;
    }

    // Fonction pour générer le mot de passe (remplace la fonction main() du code Python)
GenerateResult KeywordControleur::generatePassword(int num_char, int num_number, int num_spec_char, const std::string& spec_chars)
    {
        if (num_number >= num_char) {
            return GenerateResult::Error;
        }
        if (num_spec_char >= num_char - num_number)
        {
            return GenerateResult::Error;
        }

        int num_upper_letters = num_char / 4;
        std::string keyword = "";

        this->keyword = lower_case(this->keyword, num_char, num_upper_letters, num_spec_char);
        this->keyword = add_numbers(this->keyword, num_number);
        this->keyword = upper_case(this->keyword, num_upper_letters);
        this->keyword = spec_characters(this->keyword, num_spec_char, spec_chars);

        return GenerateResult::Success;
 }


 std::string KeywordControleur::getKeyword(){
     return this->keyword;
 }


