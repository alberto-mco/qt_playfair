#ifndef KEYMATRIXWINDOW_H
#define KEYMATRIXWINDOW_H

#include <QDialog>
#include <QDebug>

#include "playfair.h"

namespace Ui
{
    class KeyMatrixWindow;
}

class KeyMatrixWindow : public QDialog
{
    Q_OBJECT

    private:
        Ui::KeyMatrixWindow *ui;

        //Variables privadas
        Playfair *mPlayfair;

        //Funciones privadas
        bool PreviewMatrix(const QString &pPassword);

    private slots:
        void btnPreview_S1_Clicked();
        void btnPreview_S2_Clicked();
        void btnPreview_S3_Clicked();
        void btnPreview_S4_Clicked();
        void btnSave_Clicked();

    public:
        explicit KeyMatrixWindow(Playfair *ptrPlayfair, QWidget *parent = nullptr);
        ~KeyMatrixWindow();
};

#endif // KEYMATRIXWINDOW_H
