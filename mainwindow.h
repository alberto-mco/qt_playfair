#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "keymatrixwindow.h"

#include "playfair.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        Playfair *mPlayfair;

        //Funciones privadas
        bool InitializeControls();

    private slots:
        //Slots para capturar las señales que emiten los controles del formulario
        void btnChangeMatrix_Clicked();
        void btnEncode_Clicked();
        void btnDecode_Clicked();

        //Slots para capturar las señales que emite la clase playfair
        void Playfair_KeyMatrixChanged();

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};
#endif // MAINWINDOW_H
