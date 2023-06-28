#include "mainwindow.h"
#include "./ui_mainwindow.h"

extern "C" {
    #include "smartcalc.h"
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_op, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_cp, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_and_funcs_clicked()));
    connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC_clicked()));
    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equal_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_and_funcs_clicked()
{
    QPushButton *button = (QPushButton*)sender();
    ui->lineEdit->setText(ui->lineEdit->text() + button->text());
}

void MainWindow::AC_clicked()
{
    ui->lineEdit->setText("");
}


void MainWindow::equal_clicked()
{
    QString str = ui->lineEdit->text();
    int status = 0;
    Stack_t stack = {NULL, NULL};
    Stack_t rpn_stack = {NULL, NULL};
    status = check_data((char*)str.data());
    if (!status) status = parse_str((char*)str.data(), &stack);
    if (status) {
        ui->lineEdit->setText("Wrong expression!");
    } else {
        rpn_stack = convert_to_rpn(&stack);
        ui->lineEdit->setText(QString::number(calculate(&rpn_stack)));
    }
}

