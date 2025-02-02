#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QButtonGroup>
#include <QMessageBox>
#include <QComboBox>

#include "Controleur/passwordcontroleur.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QLabel *windowTitle;
    QLabel *windowDescr;
    QLabel *siteName;
    QLabel *numberOfChar;
    QLabel *numberOfNumbers;
    QLabel *specialCharQuestion;
    QLabel *numberOfSpecialChar;
    QLabel *description;
    QLabel *labelSpecChar;

    QComboBox *specCharComboBox;

    QLineEdit *siteNameLineEdit;

    QSpinBox *numberOfCharSpinBox;
    QSpinBox *numberOfNumbersSpinBox;
    QSpinBox *numberOfSpecCharSpinBox;

    QCheckBox *yes;
    QCheckBox *no;

    QPushButton *generateButton;
    QPushButton *generateButton2;
    QPushButton *enterButton;

    QWidget *centralWidget;

    QVBoxLayout *mainLayout;
    QVBoxLayout *specialCharsSelectionLayout;

    QHBoxLayout *siteNameLayout;
    QHBoxLayout *numberOfCharLayout;
    QHBoxLayout *numberOfNumbersLayout;
    QHBoxLayout *specialCharLayout;
    QHBoxLayout *numberOfSpecCharLayout;
    QHBoxLayout *bottomButtonsLayout;
    QHBoxLayout *topBarLayout;

    QList<QComboBox *> specCharComboBoxes;


private slots:
    void onClickedGenerate();
    void onClickedEnter();

public:
    MainWindow();
    ~MainWindow();
    void setUpUI();
    void handleYesCheckBox(int state);
    void handleNoCheckBox(int state);
    void clearData();
};

#endif // MAINWINDOW_H
