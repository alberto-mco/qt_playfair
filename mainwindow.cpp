#include "mainwindow.h"
#include "ui_mainwindow.h"

//*******************************************************
//Constructor
//*******************************************************
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    try
    {
        ui->setupUi(this);

        //Inicializamos las variables
        mPlayfair = new Playfair(this);

        //Conectamos las señales que emiten los controles del formulario
        connect(ui->btnChangeMatrix, SIGNAL(clicked(bool)), this, SLOT(btnChangeMatrix_Clicked()));
        connect(ui->btnEncode, SIGNAL(clicked(bool)), this, SLOT(btnEncode_Clicked()));
        connect(ui->btnDecode, SIGNAL(clicked(bool)), this, SLOT(btnDecode_Clicked()));

        //Conectamos las señales que emite la clase playfair
        connect(mPlayfair, SIGNAL(KeyMatrixChanged()), this, SLOT(Playfair_KeyMatrixChanged()));

        //Inicializamos los controles del formulario
        if (InitializeControls() == false)
        {
            qCritical() << "Ocurrió un error al inicializar los controles del formulario";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::MainWindow:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::MainWindow:Error: Desconocido";
    }
}

//*******************************************************
//Destructor
//*******************************************************
MainWindow::~MainWindow()
{
    try
    {
        //Eliminamos la instancia
        mPlayfair->deleteLater();

        delete ui;
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::~MainWindow:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::~MainWindow:Error: Desconocido";
    }
}

//*******************************************************
//Inicializa los controles del formulario
//*******************************************************
bool MainWindow::InitializeControls()
{
    bool bResult = false;

    try
    {
        //Mostramos la configuración actual del codificador de playfair
        Playfair_KeyMatrixChanged();

        //Establecemos el resultado de la operación
        bResult = true;
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::InitializeControls:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::InitializeControls:Error: Desconocido";
    }

    return bResult;
}

//*******************************************************
//Slots para capturar las señales que emiten los controles del formulario
//*******************************************************
void MainWindow::btnChangeMatrix_Clicked()
{
    try
    {
        KeyMatrixWindow *frm = new KeyMatrixWindow(mPlayfair, this);
        frm->setAttribute(Qt::WA_DeleteOnClose);
        frm->show();
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::btnChangeMatrix_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::btnChangeMatrix_Clicked:Error: Desconocido";
    }
}
void MainWindow::btnEncode_Clicked()
{
    try
    {
        ui->TabEncode_txtOutputText->setPlainText(mPlayfair->Encode(ui->TabEncode_txtInputText->document()->toPlainText()));
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::btnEncode_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::btnEncode_Clicked:Error: Desconocido";
    }
}
void MainWindow::btnDecode_Clicked()
{
    try
    {
        ui->TabDecode_txtOutputText->setPlainText(mPlayfair->Decode(ui->TabDecode_txtInputText->document()->toPlainText()));
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::btnDecode_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::btnDecode_Clicked:Error: Desconocido";
    }
}

//*******************************************************
//Slots para capturar las señales que emite la clase playfair
//*******************************************************
void MainWindow::Playfair_KeyMatrixChanged()
{
    try
    {
        //Mostramos la configuración actual del codificador de playfair
        ui->txtCurrentMatrix->setText(mPlayfair->GetCurrentMatrix());
        ui->txtMatrixSize->setText((mPlayfair->GetCurrentMatrixSize() == MatrixSizes::Size_5x5) ? QString("5x5") : QString("6x6"));
    }
    catch (std::exception &e)
    {
        qCritical() << "MainWindow::Playfair_KeyMatrixChanged:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "MainWindow::Playfair_KeyMatrixChanged:Error: Desconocido";
    }
}
