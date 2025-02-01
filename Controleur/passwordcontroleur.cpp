#include "passwordcontroleur.h"

PasswordControleur::PasswordControleur() {
    this->password = "";
}


std::string PasswordControleur::insert_into_string(std::string string, int position, char char_to_insert) {
        string.insert(position, 1, char_to_insert);
        return string;
    }

    // Fonction pour ajouter des lettres minuscules aléatoires
std::string PasswordControleur::lower_case(std::string password, int num_char, int num_upper_letters, int num_spec_char) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(97, 122); // Codes ASCII for 'a' to 'z'

        for (int i = 0; i < num_char - num_upper_letters - num_spec_char; ++i) {
            password += static_cast<char>(distrib(gen));
        }
        return password;
    }

    // Fonction pour remplacer des caractères par des chiffres aléatoires
std::string PasswordControleur::add_numbers(std::string password, int num_number) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_char(0, password.length() - 1);
        std::uniform_int_distribution<> distrib_num(0, 9);

        for (int i = 0; i < num_number; ++i) {
            int rand_char_password = distrib_char(gen);
            while (isdigit(password[rand_char_password])) {
                rand_char_password = distrib_char(gen);
            }
            password[rand_char_password] = static_cast<char>(distrib_num(gen) + '0');
        }
        return password;
    }

    // Fonction pour ajouter des lettres majuscules aléatoires
std::string PasswordControleur::upper_case(std::string password, int num_upper_letters) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, password.length());
        std::uniform_int_distribution<> distrib_letter(65, 90); // Codes ASCII pour 'A' à 'Z'

        for (int i = 0; i < num_upper_letters; ++i) {
            int rd_upper_letter = distrib_pos(gen);
            password = insert_into_string(password, rd_upper_letter, static_cast<char>(distrib_letter(gen)));
        }
        return password;
    }

    // Fonction pour ajouter des caractères spéciaux (pas d'input dans cette version)
std::string PasswordControleur::spec_characters(std::string password, int num_spec_char, const std::string& spec_chars) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, password.length());
        std::uniform_int_distribution<> distrib_char(0, spec_chars.length() - 1);

        for (int i = 0; i < num_spec_char; ++i) {
            int position = distrib_pos(gen);
            password = insert_into_string(password, position, spec_chars[distrib_char(gen)]);
        }
        return password;
    }

    // Fonction pour générer le mot de passe (remplace la fonction main() du code Python)
GenerateResult PasswordControleur::generatePassword(int num_char, int num_number, int num_spec_char, const std::string& spec_chars)
    {
        if (num_number >= num_char) {
            return GenerateResult::Error;
        }
        if (num_spec_char >= num_char - num_number)
        {
            return GenerateResult::Error;
        }

        int num_upper_letters = num_char / 4;

        this->password = lower_case(this->password, num_char, num_upper_letters, num_spec_char);
        this->password = add_numbers(this->password, num_number);
        this->password = upper_case(this->password, num_upper_letters);
        this->password = spec_characters(this->password, num_spec_char, spec_chars);

        return GenerateResult::Success;
 }


 std::string PasswordControleur::getPassword(){
     return this->password;
 }


