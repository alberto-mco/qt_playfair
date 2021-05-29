#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QObject>
#include <QDebug>
#include <QReadWriteLock>
#include <QWriteLocker>
#include <QReadLocker>
#include <QRegularExpression>
#include <QMap>
#include <QPoint>

enum class MatrixSizes
{
    Size_5x5 = 0x00,
    Size_6x6 = 0x01
};

enum class ReplaceOptions
{
    Replace_J_I = 0x00,
    Skip_Q      = 0x01
};

enum class Squares
{
    One             = 0x00,
    Two_Vertical    = 0x01,
    Two_Horizontal  = 0x02,
    Four            = 0x03
};

enum class SquareAlignment
{
    Horizontal  = 0x00,
    Vertical    = 0x01
};

enum class CharsPositions
{
    Row     = 0x00,
    Column  = 0x01,
    Square  = 0x02
};

enum class Action
{
    Encode  = 0x00,
    Decode  = 0x01
};

class Playfair : public QObject
{
    Q_OBJECT

    private:
        QString mMatrix;
        MatrixSizes mMatrixSize;
        Squares mSquares;
        ReplaceOptions mReplaceOptions;
        QReadWriteLock mProperties_Mutex;
        QChar mNullChar;

        //Funciones privadas
        bool LoadSettings();
        bool GetChars(QChar pChar_1, QChar pChar_2, QChar &pNewChar_1, QChar &pNewChar_2, Action pAction);

        //Funciones estáticas
        static QList<QString> GetMatrixBySquares(QString pMatrix, MatrixSizes pMatrixSize, Squares pSquares);
        static QChar GetCharAt(QPoint pMatrixPosition, const QString &pMatrix, MatrixSizes pMatrixSize, bool *pOK = nullptr);
        static QPoint GetCharPosition(QChar pChr, const QString &pMatrix, MatrixSizes pMatrixSize, bool *pOK = nullptr);
        static qint32 CircularIndex(qint32 mNewIndex, MatrixSizes pMatrixSize);

    signals:
        void KeyMatrixChanged();

    public:
        explicit Playfair(QObject *parent = nullptr);

        //Funciones publicas para establecer la matrix de des/codificacion
        bool SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey);
        bool SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey_1, const QString &pKey_2, SquareAlignment pSquareAligment);
        bool SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey_1, const QString &pKey_2, const QString &pKey_3, const QString &pKey_4);

        //Funciones publicas para des/codificar
        QString Decode(const QString &pText, bool *pOK = nullptr);
        QString Encode(const QString &pText, bool *pOK = nullptr);

        //Funciones públicas para obtener las propiedades de la clase
        const QString &GetCurrentMatrix() const;
        MatrixSizes GetCurrentMatrixSize() const;

        //Funciones estaticas
        static QString GenerateMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey);
};

#endif // PLAYFAIR_H
