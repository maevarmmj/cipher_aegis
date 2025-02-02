#include "mainwindow.h"
#include <QDir>

MainWindow::MainWindow() {

    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    this->setFixedSize(410, 400);
    this->setWindowTitle("Cipher Aegis");
    setUpUI();
}

MainWindow::~MainWindow(){}

void MainWindow::setUpUI(){

    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);
    bottomButtonsLayout = new QHBoxLayout();
    siteNameLayout = new QHBoxLayout();
    numberOfCharLayout = new QHBoxLayout();
    numberOfNumbersLayout = new QHBoxLayout();
    specialCharLayout = new QHBoxLayout();
    numberOfSpecCharLayout = new QHBoxLayout();
    bottomButtonsLayout = new QHBoxLayout();
    specialCharsSelectionLayout = new QVBoxLayout();


    windowTitle = new QLabel("Cipher Aegis", this);
    windowTitle->setMaximumHeight(40);
    windowDescr = new QLabel("Your Ultimate Guardian", this);
    windowDescr->setMaximumHeight(40);
    siteName = new QLabel("Site name of the keyword:", this);
    numberOfChar = new QLabel("Number of total characters:", this);
    numberOfNumbers = new QLabel("Number of numbers:", this);
    specialCharQuestion = new QLabel("Some special characters?", this);
    numberOfSpecialChar = new QLabel("Number of special characters:",this);
    description = new QLabel("(If the site already exists in the CSV file, your password will be overwritten)");
    description->setMaximumHeight(30);

    generateButton = new QPushButton("Generate", this);
    generateButton2 = new QPushButton("Generate", this);
    enterButton = new QPushButton("Enter", this);


    siteNameLineEdit = new QLineEdit();

    numberOfCharSpinBox = new QSpinBox();
    numberOfCharSpinBox->setRange(1, 50);
    numberOfNumbersSpinBox = new QSpinBox();
    numberOfNumbersSpinBox->setRange(0, 50);
    numberOfSpecCharSpinBox = new QSpinBox();
    numberOfSpecCharSpinBox->setRange(1, 50);

    yes = new QCheckBox("Yes");
    no = new QCheckBox("No");

    // Groupe les cases à cocher dans un QButtonGroup pour un comportement exclusif
    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(yes);
    group->addButton(no);

    mainLayout->addWidget(windowTitle, 0, Qt::AlignHCenter);
    mainLayout->addWidget(windowDescr, 0, Qt::AlignHCenter);

    siteNameLayout->addWidget(siteName);
    siteNameLayout->addWidget(siteNameLineEdit);
    mainLayout->addLayout(siteNameLayout);
    mainLayout->addWidget(description);

    numberOfCharLayout->addWidget(numberOfChar);
    numberOfCharLayout->addWidget(numberOfCharSpinBox);
    mainLayout->addLayout(numberOfCharLayout);

    numberOfNumbersLayout->addWidget(numberOfNumbers);
    numberOfNumbersLayout->addWidget(numberOfNumbersSpinBox);
    mainLayout->addLayout(numberOfNumbersLayout);

    specialCharLayout->addWidget(specialCharQuestion);
    specialCharLayout->addWidget(yes);
    specialCharLayout->addWidget(no);
    mainLayout->addLayout(specialCharLayout);

    numberOfSpecialChar->hide();
    numberOfSpecCharSpinBox->hide();
    numberOfSpecCharLayout->addWidget(numberOfSpecialChar);
    numberOfSpecCharLayout->addWidget(numberOfSpecCharSpinBox);
    mainLayout->addLayout(numberOfSpecCharLayout);

    generateButton->hide();
    generateButton2->hide();
    enterButton->hide();
    bottomButtonsLayout->addWidget(generateButton, 0, Qt::AlignHCenter);
    bottomButtonsLayout->addWidget(enterButton, 0, Qt::AlignHCenter);
    mainLayout->addLayout(bottomButtonsLayout);

    mainLayout->addLayout(specialCharsSelectionLayout);


    setCentralWidget(centralWidget);

    connect(yes, &QCheckBox::checkStateChanged, this, &MainWindow::handleYesCheckBox);
    connect(no, &QCheckBox::checkStateChanged, this, &MainWindow::handleNoCheckBox);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onClickedGenerate);
    connect(generateButton2, &QPushButton::clicked, this, &MainWindow::onClickedGenerate);
    connect(enterButton, &QPushButton::clicked, this, &MainWindow::onClickedEnter);


}

void MainWindow::handleYesCheckBox(int state)
{
    if (state == Qt::Checked) {
        numberOfSpecialChar->show();
        numberOfSpecCharSpinBox->show();
        generateButton->hide();
        enterButton->show();
    } else {
        numberOfSpecialChar->hide();
        numberOfSpecCharSpinBox->hide();
    }
}

void MainWindow::handleNoCheckBox(int state)
{
    if (state == Qt::Checked) {
        generateButton->show();
        enterButton->hide();
        numberOfSpecialChar->hide();
        numberOfSpecCharSpinBox->hide();
    }
}


void MainWindow::onClickedGenerate() {
    std::string site_name = siteNameLineEdit->text().toStdString();
    int num_char = numberOfCharSpinBox->value();
    int num_number = numberOfNumbersSpinBox->value();
    int num_spec_char = 0;
    PasswordControleur password = *new PasswordControleur();

    std::vector<std::string> selectedSpecialChars;

    if (yes->isChecked()) {
        num_spec_char = numberOfSpecCharSpinBox->value();

        // Récupérer les valeurs sélectionnées des QComboBox stockées
        for (int i = 0; i < num_spec_char && i < specCharComboBoxes.size(); ++i) {
            QComboBox *comboBox = specCharComboBoxes[i];
            selectedSpecialChars.push_back(comboBox->currentText().toStdString());
        }



    } else if (no->isChecked()) {
        num_spec_char = 0;
        selectedSpecialChars.clear();
    }


    if (num_char == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez spécifier le nombre de caractères.");
        return;
    }
    if (num_number >= num_char) {
        QMessageBox::warning(this, "Erreur", "Le nombre de chiffres ne peut pas être supérieur ou égal au nombre total de caractères.");
        return;
    }

    // Appel de generatePassword
    GenerateResult result = password.generatePassword(site_name, num_char, num_number, num_spec_char, selectedSpecialChars);

    // Gestion du résultat
    if (result == GenerateResult::Success) {
        QMessageBox::information(this, "Succès", "Le mot de passe a été généré et enregistré avec succès.");
        clearData();
    } else if (result == GenerateResult::Error) {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la génération du mot de passe.");
    } else if (result == GenerateResult::MissingInfo) {
        QMessageBox::warning(this, "Erreur", "Des informations sont manquantes.");
    }
}



void MainWindow::onClickedEnter() {
    // Nettoyer la liste avant d'ajouter de nouveaux éléments
    specCharComboBoxes.clear();

    int numberOfSpecChar = numberOfSpecCharSpinBox->value();
    QStringList specialCharsList = {"!", "@", "#", "$", "%", "^", "&", "*",
                                    "-", "_", "+", "=", "[", "]",
                                    "\"", "?", "/", "|"};

    for (int i = 0; i < numberOfSpecChar; i++) {
        QLabel *labelSpecChar = new QLabel(QString("Character n° %1").arg(i + 1), this);
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItems(specialCharsList);

        // Stocker la QComboBox créée
        specCharComboBoxes.append(comboBox);

        QHBoxLayout *specCharHLayout = new QHBoxLayout();
        specCharHLayout->addWidget(labelSpecChar);
        specCharHLayout->addWidget(comboBox);

        specialCharsSelectionLayout->addLayout(specCharHLayout);
    }

    specialCharsSelectionLayout->addWidget(generateButton2, 0, Qt::AlignCenter);
    generateButton2->show();
}


void MainWindow::clearData(){
    // REINITIALISATION DE TOUT

    siteNameLineEdit->clear();
    numberOfCharSpinBox->setValue(1);
    numberOfNumbersSpinBox->setValue(0);
    numberOfSpecCharSpinBox->setValue(0);

    specCharComboBoxes.clear();

    yes->setChecked(false);
    no->setChecked(false);

}
