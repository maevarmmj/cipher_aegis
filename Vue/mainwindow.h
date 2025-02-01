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

    QLineEdit *siteNameLineEdit;

    QSpinBox *numberOfCharSpinBox;
    QSpinBox *numberOfNumbersSpinBox;
    QSpinBox *numberOfSpecCharSpinBox;

    QCheckBox *yes;
    QCheckBox *no;

    QPushButton *generateButton;

    QWidget *centralWidget;

    QVBoxLayout *mainLayout;

    QHBoxLayout *siteNameLayout;
    QHBoxLayout *numberOfCharLayout;
    QHBoxLayout *numberOfNumbersLayout;
    QHBoxLayout *specialCharLayout;
    QHBoxLayout *numberOfSpecCharLayout;
    QHBoxLayout *bottomButtonsLayout;
    QHBoxLayout *topBarLayout;


public:
    MainWindow();
    ~MainWindow();
    void setUpUI();
    void handleYesCheckBox(int state);
    void handleNoCheckBox(int state);
};

#endif // MAINWINDOW_H
