#include "keymatrixwindow.h"
#include "ui_keymatrixwindow.h"

//*******************************************************
//Constructor
//*******************************************************
KeyMatrixWindow::KeyMatrixWindow(Playfair *ptrPlayfair, QWidget *parent) : QDialog(parent), ui(new Ui::KeyMatrixWindow)
{
    try
    {
        ui->setupUi(this);

        //Guardamos los parámetros que recibimos
        mPlayfair = ptrPlayfair;

        //Conectamos las señales que emiten los controles del formulario
        connect(ui->btnPreview_S1, SIGNAL(clicked(bool)), this, SLOT(btnPreview_S1_Clicked()));
        connect(ui->btnPreview_S2, SIGNAL(clicked(bool)), this, SLOT(btnPreview_S2_Clicked()));
        connect(ui->btnPreview_S3, SIGNAL(clicked(bool)), this, SLOT(btnPreview_S3_Clicked()));
        connect(ui->btnPreview_S4, SIGNAL(clicked(bool)), this, SLOT(btnPreview_S4_Clicked()));
        connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(btnSave_Clicked()));
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::KeyMatrixWindow:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::KeyMatrixWindow:Error: Desconocido";
    }
}

//*******************************************************
//Destructor
//*******************************************************
KeyMatrixWindow::~KeyMatrixWindow()
{
    try
    {
        delete ui;
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::~KeyMatrixWindow:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::~KeyMatrixWindow:Error: Desconocido";
    }
}

//*******************************************************
//Muestra la previsualización de la contraseña en la matriz definida
//*******************************************************
bool KeyMatrixWindow::PreviewMatrix(const QString &pPassword)
{
    bool bResult = false;

    try
    {
        MatrixSizes mMatrixSize = (ui->rbMatrix_5x5->isChecked()) ? MatrixSizes::Size_5x5 : MatrixSizes::Size_6x6;
        ReplaceOptions mReplaceOption = (ui->rbReplace_J_I->isChecked()) ? ReplaceOptions::Replace_J_I : ReplaceOptions::Skip_Q;
        QString mMatrix = Playfair::GenerateMatrix(mMatrixSize, mReplaceOption, pPassword);
        qint32 mMaxColumnRow = (mMatrixSize == MatrixSizes::Size_5x5) ? 5 : 6;
        qint32 idxChar = 0;

        //Recorremos todas las filas
        for (qint32 y = 0; y < 6; y++)
        {
            //Recorremos todas las columnas
            for (qint32 x = 0; x < 6; x++)
            {
                QLineEdit *txt = ui->gbMatrixPreview->findChild<QLineEdit*>(QString("txtMatrix_%1%2").arg(QString::number(y), QString::number(x)));

                //Comprobamos que se haya obtenido el textbox asociado a las coordenadas "X" e "Y"
                if (txt != nullptr)
                {
                    //Borramos el contenido
                    txt->setText("");
                }
            }
        }

        //Recorremos todas las filas
        for (qint32 y = 0; y < mMaxColumnRow; y++)
        {
            //Recorremos todas las columnas
            for (qint32 x = 0; x < mMaxColumnRow; x++)
            {
                QLineEdit *txt = ui->gbMatrixPreview->findChild<QLineEdit*>(QString("txtMatrix_%1%2").arg(QString::number(y), QString::number(x)));

                //Comprobamos que se haya obtenido el textbox asociado a las coordenadas "X" e "Y"
                if (txt != nullptr)
                {
                    txt->setText(mMatrix.at(idxChar++));
                }
            }
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::PreviewMatrix:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::PreviewMatrix:Error: Desconocido";
    }

    return bResult;
}

//*******************************************************
//Slots para capturar las señales que emiten los controles del formulario
//*******************************************************
void KeyMatrixWindow::btnPreview_S1_Clicked()
{
    try
    {
        //Previsualizamos la matriz
        if (PreviewMatrix(ui->txtPassword_1->text()) == false)
        {
            qCritical() << "Ocurrió un error al previsualizar la matriz";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S1_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S1_Clicked:Error: Desconocido";
    }
}
void KeyMatrixWindow::btnPreview_S2_Clicked()
{
    try
    {
        //Previsualizamos la matriz
        if (PreviewMatrix(ui->txtPassword_2->text()) == false)
        {
            qCritical() << "Ocurrió un error al previsualizar la matriz";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S2_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S2_Clicked:Error: Desconocido";
    }
}
void KeyMatrixWindow::btnPreview_S3_Clicked()
{
    try
    {
        //Previsualizamos la matriz
        if (PreviewMatrix(ui->txtPassword_3->text()) == false)
        {
            qCritical() << "Ocurrió un error al previsualizar la matriz";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S3_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S3_Clicked:Error: Desconocido";
    }
}
void KeyMatrixWindow::btnPreview_S4_Clicked()
{
    try
    {
        //Previsualizamos la matriz
        if (PreviewMatrix(ui->txtPassword_4->text()) == false)
        {
            qCritical() << "Ocurrió un error al previsualizar la matriz";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S4_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::btnPreview_S4_Clicked:Error: Desconocido";
    }
}
void KeyMatrixWindow::btnSave_Clicked()
{
    try
    {
        //Comprobamos que la instancia a la clase codificadora no sea nula
        if (mPlayfair != nullptr)
        {
            MatrixSizes mMatrixSize = (ui->rbMatrix_5x5->isChecked()) ? MatrixSizes::Size_5x5 : MatrixSizes::Size_6x6;
            ReplaceOptions mReplaceOption = (ui->rbReplace_J_I->isChecked()) ? ReplaceOptions::Replace_J_I : ReplaceOptions::Skip_Q;
            bool bSetMatrixResult = false;

            //Comprobamos cuantos cuadrados hay
            if (ui->rbSquares_1->isChecked())
            {
                bSetMatrixResult = mPlayfair->SetMatrix(mMatrixSize, mReplaceOption, ui->txtPassword_1->text());
            }
            else if (ui->rbSquares_2->isChecked())
            {
                bSetMatrixResult = mPlayfair->SetMatrix(mMatrixSize, mReplaceOption, ui->txtPassword_1->text(), ui->txtPassword_2->text(), (ui->rbSquares_2_Horizontal->isChecked()) ? SquareAlignment::Horizontal : SquareAlignment::Vertical);
            }
            else
            {
                bSetMatrixResult = mPlayfair->SetMatrix(mMatrixSize, mReplaceOption, ui->txtPassword_1->text(), ui->txtPassword_2->text(), ui->txtPassword_3->text(), ui->txtPassword_4->text());
            }

            //Establecemos los nuevos parámetros de la nueva matriz de codificación que se tiene que crear
            if (bSetMatrixResult)
            {
                this->accept();
            }
            else
            {
                qCritical() << "Ocurrió un error al guardar la nueva matriz de codificación";
            }
        }
        else
        {
            qCritical() << "La instancia a la clase playfair no puede ser nula";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "KeyMatrixWindow::btnSave_Clicked:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "KeyMatrixWindow::btnSave_Clicked:Error: Desconocido";
    }
}
