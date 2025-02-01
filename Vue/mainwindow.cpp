#include "mainwindow.h"
#include <QDir>

MainWindow::MainWindow() {

    QString file(QDir::currentPath() + "/../../Ressources/planning.ico");
    QIcon icon(file);
    setWindowIcon(icon);
    this->setFixedSize(400, 400);
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

    windowTitle = new QLabel("Cipher Aegis");
    windowTitle->setMaximumHeight(40);
    windowDescr = new QLabel("Your Ultimate Guardian");
    windowDescr->setMaximumHeight(40);
    siteName = new QLabel("Site name of the keyword:", this);
    numberOfChar = new QLabel("Number of total characters:", this);
    numberOfNumbers = new QLabel("Number of numbers:", this);
    specialCharQuestion = new QLabel("Some special characters?", this);
    numberOfSpecialChar = new QLabel("Number of special characters:",this);

    generateButton = new QPushButton("Generate", this);

    siteNameLineEdit = new QLineEdit();

    numberOfCharSpinBox = new QSpinBox();
    numberOfCharSpinBox->setRange(0, 50);
    numberOfNumbersSpinBox = new QSpinBox();
    numberOfNumbersSpinBox->setRange(0, 50);
    numberOfSpecCharSpinBox = new QSpinBox();
    numberOfSpecCharSpinBox->setRange(0, 50);

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
    bottomButtonsLayout->addWidget(generateButton, 0, Qt::AlignHCenter);
    mainLayout->addLayout(bottomButtonsLayout);

    setCentralWidget(centralWidget);

    // Connexions des CheckBox
    connect(yes, &QCheckBox::checkStateChanged, this, &MainWindow::handleYesCheckBox);
    connect(no, &QCheckBox::checkStateChanged, this, &MainWindow::handleNoCheckBox);
}

void MainWindow::handleYesCheckBox(int state)
{
    if (state == Qt::Checked) {
        numberOfSpecialChar->show();
        numberOfSpecCharSpinBox->show();
    } else {
        numberOfSpecialChar->hide();
        numberOfSpecCharSpinBox->hide();
    }
}

void MainWindow::handleNoCheckBox(int state)
{
    if (state == Qt::Checked) {
        generateButton->show();
        numberOfSpecialChar->hide();
        numberOfSpecCharSpinBox->hide();
    }
}
