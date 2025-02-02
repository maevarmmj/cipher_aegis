#include "passwordcontroleur.h"

PasswordControleur::PasswordControleur() {
    this->password = "";
}


std::string PasswordControleur::insert_into_string(std::string string, int position, char char_to_insert) {
    if (position < 0 || position > string.length()) {
        position = string.length(); // Insère à la fin si la position est invalide
    }
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
        std::uniform_int_distribution<> distrib_pos(0, password.length() - 1);
        std::uniform_int_distribution<> distrib_letter(65, 90); // Codes ASCII pour 'A' à 'Z'

        for (int i = 0; i < num_upper_letters; ++i) {
            int rd_upper_letter = distrib_pos(gen);
            password = insert_into_string(password, rd_upper_letter, static_cast<char>(distrib_letter(gen)));
        }
        return password;
    }

    // Fonction pour ajouter des caractères spéciaux (pas d'input dans cette version)
    std::string PasswordControleur::spec_characters(std::string password, int num_spec_char, const std::vector<std::string>& spec_chars_list) {
        if (spec_chars_list.empty()) {
            return password; // Rien à insérer, on retourne le mot de passe tel quel
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, password.length() - 1); // Correction de la limite

        for (int i = 0; i < num_spec_char; ++i) {
            std::uniform_int_distribution<> distrib_spec_chars_list(0, spec_chars_list.size() - 1);
            int spec_chars_list_index = distrib_spec_chars_list(gen);

            if (spec_chars_list[spec_chars_list_index].empty()) {
                continue; // Ignore les chaînes vides
            }
            char specialChar = spec_chars_list[spec_chars_list_index][0]; // Prendre le seul caractère de la chaîne

            int position = distrib_pos(gen);
            password = insert_into_string(password, position, specialChar); // Insérer proprement
        }

        qDebug() << "Mot de passe avant ajout des caractères spéciaux : " << QString::fromStdString(password);


        return password;
    }



    GenerateResult PasswordControleur::generatePassword(std::string site_name, int num_char, int num_number, int num_spec_char, const std::vector<std::string>& spec_chars_list)
    {
        if (num_number >= num_char) {
            return GenerateResult::Error;
        }
        if (num_spec_char >= num_char - num_number)
        {
            return GenerateResult::Error;
        }

        if (num_spec_char > 0 && spec_chars_list.size() != num_spec_char) {
            // Le nombre de chaînes dans spec_chars_list doit correspondre à num_spec_char
            return GenerateResult::Error; // Ou un code d'erreur plus spécifique
        }

        int num_upper_letters = num_char / 4;


        this->password = lower_case(this->password, num_char, num_upper_letters, num_spec_char);
        this->password = add_numbers(this->password, num_number);
        this->password = upper_case(this->password, num_upper_letters);
        this->password = spec_characters(this->password, num_spec_char, spec_chars_list);
        qDebug() << "Mot de passe après ajout des caractères spéciaux : " << QString::fromStdString(this->password);



        // Enregistrement dans le fichier CSV
        std::string csvDirPath = QDir::currentPath().toStdString() + "/../../CSV"; // Adapte le chemin si nécessaire
        std::string filePath = csvDirPath + "/Keyword.csv";

        // Création du dossier CSV s'il n'existe pas
        if (!std::filesystem::exists(csvDirPath)) {
            if (!std::filesystem::create_directory(csvDirPath)) {
                std::cerr << "Erreur : Impossible de créer le dossier " << csvDirPath << std::endl;
                return GenerateResult::Error;
            }
        }

        std::ofstream file(filePath, std::ios::app); // Ouvre en mode "append" pour ajouter à la fin

        if (file.is_open()) {
            // Si le fichier est vide, ajoute l'en-tête
            if (file.tellp() == 0) {
                file << "Site name,Keyword\n";
            }

            // Vérifie si le site_name existe déjà
            std::ifstream tempFile(filePath);
            std::string line;
            bool siteExists = false;
            if (tempFile.is_open()){
                while (std::getline(tempFile, line)) {
                    size_t pos = line.find(',');
                    if (pos != std::string::npos) {
                        std::string existingSiteName = line.substr(0, pos);
                        if (existingSiteName == site_name) {
                            siteExists = true;
                            break;
                        }
                    }
                }
                tempFile.close();
            }

            if(siteExists) {
                // Le site existe déjà, retourne une erreur
                return GenerateResult::Error;
            } else {
                // Ajoute la nouvelle ligne
                file << site_name << "," << this->password << "\n";
                std::cout << this->password << std::endl;
            }
            file.close();
            return GenerateResult::Success;
        } else {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
            return GenerateResult::Error;
        }
    }


    std::string PasswordControleur::getPassword(){
        return this->password;
    }
