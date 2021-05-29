#include "playfair.h"

//*******************************************************
//Constructor
//*******************************************************
Playfair::Playfair(QObject *parent) : QObject(parent)
{
    try
    {
        //Inicializamos las variables
        mMatrix = "";
        mMatrixSize = MatrixSizes::Size_5x5;
        mReplaceOptions = ReplaceOptions::Replace_J_I;
        mNullChar = 'X';
        mSquares = Squares::One;

        //Cargamos la configuración inicial de la clase
        if (LoadSettings() == false)
        {
            qCritical() << "Ocurrió un error al cargar la configuración de la clase";
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::Playfair:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::Playfair:Error: Desconocido";
    }
}

//*******************************************************
//Carga la configuración inicial de la clase
//*******************************************************
bool Playfair::LoadSettings()
{
    bool bResult = false;

    try
    {
        //Generamos una matriz aleatoriamente
        SetMatrix(mMatrixSize, ReplaceOptions::Replace_J_I, "");

        //Establecemos el resultado de la operación
        bResult = true;
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::LoadSettings:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::LoadSettings:Error: Desconocido";
    }

    return bResult;
}

//*******************************************************
//Obtiene los carácteres asociados a los carácteres que recibe en el parámetro
//*******************************************************
bool Playfair::GetChars(QChar pChar_1, QChar pChar_2, QChar &pNewChar_1, QChar &pNewChar_2, Action pAction)
{
    bool bResult = false;

    try
    {
        QList<QString> mMatrixArray = Playfair::GetMatrixBySquares(mMatrix, mMatrixSize, mSquares);

        //Comprobamos cuantos cuadrados hay
        switch (mSquares)
        {
            case Squares::One:
            {
                QPoint mChar_1_Position = Playfair::GetCharPosition(pChar_1, mMatrixArray[0], mMatrixSize);
                QPoint mChar_2_Position = Playfair::GetCharPosition(pChar_2, mMatrixArray[0], mMatrixSize);

                //Comprobamos si los carácteres están en la misma fila
                if (mChar_1_Position.y() == mChar_2_Position.y()) //Row
                {
                    //Comprobamos que tipo de acción es, para determinar la dirección de lectura del carácter a decodificar
                    if (pAction == Action::Encode)
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_1_Position.x() + 1, mMatrixSize), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_2_Position.x() + 1, mMatrixSize), mChar_2_Position.y()), mMatrixArray[0], mMatrixSize);
                    }
                    else
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_1_Position.x() - 1, mMatrixSize), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_2_Position.x() - 1, mMatrixSize), mChar_2_Position.y()), mMatrixArray[0], mMatrixSize);
                    }
                }
                else if (mChar_1_Position.x() == mChar_2_Position.x()) //Column
                {
                    //Comprobamos que tipo de acción es, para determinar la dirección de lectura del carácter a decodificar
                    if (pAction == Action::Encode)
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), CircularIndex(mChar_1_Position.y() + 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), CircularIndex(mChar_2_Position.y() + 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                    }
                    else
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), CircularIndex(mChar_1_Position.y() - 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), CircularIndex(mChar_2_Position.y() - 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                    }
                }
                else //Square
                {
                    //Obtenemos los carácteres que hay en las diagonales opuestas dentro del cuadrado que conforman
                    pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                    pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), mChar_2_Position.y()), mMatrixArray[0], mMatrixSize);
                }

                //Establecemos el resultado de la operación
                bResult = true;
                break;
            }
            case Squares::Two_Horizontal:
            {
                QPoint mChar_1_Position = Playfair::GetCharPosition(pChar_1, mMatrixArray[0], mMatrixSize);
                QPoint mChar_2_Position = Playfair::GetCharPosition(pChar_2, mMatrixArray[1], mMatrixSize);

                //Comprobamos si los carácteres están en la misma fila
                if (mChar_1_Position.y() == mChar_2_Position.y()) //Row
                {
                    //Comprobamos que tipo de acción es, para determinar la dirección de lectura del carácter a decodificar
                    if (pAction == Action::Encode)
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_1_Position.x() + 1, mMatrixSize), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_2_Position.x() + 1, mMatrixSize), mChar_2_Position.y()), mMatrixArray[1], mMatrixSize);
                    }
                    else
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_1_Position.x() - 1, mMatrixSize), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(CircularIndex(mChar_2_Position.x() - 1, mMatrixSize), mChar_2_Position.y()), mMatrixArray[1], mMatrixSize);
                    }
                }
                else //Square
                {
                    //Obtenemos los carácteres que hay en las diagonales opuestas dentro del cuadrado que conforman
                    pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), mChar_2_Position.y()), mMatrixArray[0], mMatrixSize);
                    pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), mChar_1_Position.y()), mMatrixArray[1], mMatrixSize);
                }

                //Establecemos el resultado de la operación
                bResult = true;
                break;
            }
            case Squares::Two_Vertical:
            {
                QPoint mChar_1_Position = Playfair::GetCharPosition(pChar_1, mMatrixArray[0], mMatrixSize);
                QPoint mChar_2_Position = Playfair::GetCharPosition(pChar_2, mMatrixArray[1], mMatrixSize);

                //Comprobamos si los carácteres están en la misma columna
                if (mChar_1_Position.x() == mChar_2_Position.x())
                {
                    //Comprobamos que tipo de acción es, para determinar la dirección de lectura del carácter a decodificar
                    if (pAction == Action::Encode)
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), CircularIndex(mChar_1_Position.y() + 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), CircularIndex(mChar_2_Position.y() + 1, mMatrixSize)), mMatrixArray[1], mMatrixSize);
                    }
                    else
                    {
                        pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), CircularIndex(mChar_1_Position.y() - 1, mMatrixSize)), mMatrixArray[0], mMatrixSize);
                        pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), CircularIndex(mChar_2_Position.y() - 1, mMatrixSize)), mMatrixArray[1], mMatrixSize);
                    }
                }
                else //Square
                {
                    //Obtenemos los carácteres que hay en las diagonales opuestas dentro del cuadrado que conforman
                    pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), mChar_1_Position.y()), mMatrixArray[0], mMatrixSize);
                    pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), mChar_2_Position.y()), mMatrixArray[1], mMatrixSize);
                }

                //Establecemos el resultado de la operación
                bResult = true;
                break;
            }
            case Squares::Four:
            {
                QPoint mChar_1_Position = Playfair::GetCharPosition(pChar_1, (pAction == Action::Encode) ? mMatrixArray[0] : mMatrixArray[1], mMatrixSize);
                QPoint mChar_2_Position = Playfair::GetCharPosition(pChar_2, (pAction == Action::Encode) ? mMatrixArray[3] : mMatrixArray[2], mMatrixSize);

                //Obtenemos los carácteres que hay en las diagonales opuestas dentro del cuadrado que conforman
                pNewChar_1 = Playfair::GetCharAt(QPoint(mChar_2_Position.x(), mChar_1_Position.y()), (pAction == Action::Encode) ? mMatrixArray[1] : mMatrixArray[0], mMatrixSize);
                pNewChar_2 = Playfair::GetCharAt(QPoint(mChar_1_Position.x(), mChar_2_Position.y()), (pAction == Action::Encode) ? mMatrixArray[2] : mMatrixArray[3], mMatrixSize);

                //Establecemos el resultado de la operación
                bResult = true;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::GetChars:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::GetChars:Error: Desconocido";
    }

    return bResult;
}

//*******************************************************
//Obtiene las matriz que se utiliza en cada cuadrado
//*******************************************************
QList<QString> Playfair::GetMatrixBySquares(QString pMatrix, MatrixSizes pMatrixSize, Squares pSquares)
{
    QList<QString> mResult;

    try
    {
        //Comprobamos si solo hay una matrix
        if (pSquares == Squares::One)
        {
            mResult.push_back(pMatrix);
        }
        else
        {
            //Obtenemos cuantas columnas tiene la matriz
            quint8 mColumnsRows = (pMatrixSize == MatrixSizes::Size_5x5) ? 5 : 6;

            while (pMatrix.size() > 0)
            {
                mResult.push_back(pMatrix.mid(0, mColumnsRows * mColumnsRows));
                pMatrix.remove(0, mColumnsRows * mColumnsRows);
            }
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::GetMatrixBySquares:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::GetMatrixBySquares:Error: Desconocido";
    }

    return mResult;
}

//*******************************************************
//Obtiene el carácter que hay en la matriz en las coordenadas especificadas en el parámetro
//*******************************************************
QChar Playfair::GetCharAt(QPoint pMatrixPosition, const QString &pMatrix, MatrixSizes pMatrixSize, bool *pOK)
{
    QChar mChr = '\0';
    bool bOK = false;

    try
    {
        //Obtenemos cuantas columnas tiene la matriz
        quint8 mColumns = (pMatrixSize == MatrixSizes::Size_5x5) ? 5 : 6;

        //Calculamos el índice teórico
        qint32 idx = (pMatrixPosition.y() * mColumns) + pMatrixPosition.x();

        //Comprobamos que el carácter exista
        if (pMatrix.size() > idx)
        {
            //Obtenemos el carácter
            mChr = pMatrix.at(idx);

            //Establecemos el resultado de la operación
            bOK = true;
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::GetCharAt:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::GetCharAt:Error: Desconocido";
    }

    //Comprobamos si hemos de retornar el resultado de la operación
    if (pOK != nullptr)
    {
        //Guardamos el resultado de la operación en la variable de retorno
        *pOK = bOK;
    }

    return mChr;
}

//*******************************************************
//Obtiene las coordenadas del carácter dentro de la matriz
//*******************************************************
QPoint Playfair::GetCharPosition(QChar pChr, const QString &pMatrix, MatrixSizes pMatrixSize, bool *pOK)
{
    QPoint mPos;
    bool bOK = false;

    try
    {
        qint32 idx = -1;

        //Recorremos todos los carácteres de la matriz, para buscar el carácter
        for (qint32 i = 0; i < pMatrix.size(); i++)
        {
            //Comprobamos si es el carácter que estamos buscando
            if (pMatrix.at(i) == pChr)
            {
                //Guardamos la posición que ocupa dentro de la cadena de texto de la matriz
                idx = i;
            }
        }

        //Comprobamos si hemos encontrado el carácter
        if (idx > -1)
        {
            //Obtenemos cuantas columnas tiene la matriz
            quint8 mColumns = (pMatrixSize == MatrixSizes::Size_5x5) ? 5 : 6;

            //Buscamos el número de línea dentro de la matriz (posición Y)
            while (idx >= mColumns)
            {
                //Incrementamos la posición Y
                mPos.setY(mPos.y() + 1);

                //Restamos una línea
                idx -= mColumns;
            }

            //Establecemos la posición X, con el restante del idx (ya que al restarle las lineas, solo queda la posición de la columna en la variable idx)
            mPos.setX(idx);

            //Establecemos el resultado de la operación
            bOK = true;
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::GetCharPosition:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::GetCharPosition:Error: Desconocido";
    }

    //Comprobamos si hemos de retornar el resultado de la operación
    if (pOK != nullptr)
    {
        //Guardamos el resultado de la operación en la variable de retorno
        *pOK = bOK;
    }

    return mPos;
}

//*******************************************************
//Obtiene el indice asegurado rotativo dentro de la matriz
//*******************************************************
qint32 Playfair::CircularIndex(qint32 mNewIndex, MatrixSizes pMatrixSize)
{
    qint32 iResult = 0;

    try
    {
        //Obtenemos cuantas columnas tiene la matriz
        quint8 mRowsColumns = (pMatrixSize == MatrixSizes::Size_5x5) ? 5 : 6;

        if (mNewIndex >= mRowsColumns)
        {
            iResult = mNewIndex - mRowsColumns;
        }
        else if (mNewIndex < 0)
        {
            iResult = mNewIndex + mRowsColumns;
        }
        else
        {
            iResult = mNewIndex;
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::CircularIndex:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::CircularIndex:Error: Desconocido";
    }

    return iResult;
}

//*******************************************************
//Establece la matriz de des/codificación que se va a utilizar
//*******************************************************
bool Playfair::SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey)
{
    bool bResult = false;

    try
    {
        //Bloqueamos el acceso a las propiedades de la clase
        QWriteLocker mLocker(&mProperties_Mutex);

        //Generamos la nueva matriz
        mMatrix = Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey);

        //Guardamos el tamaño de la matriz
        mMatrixSize = pMatrixSize;

        //Guardamos la opción de reemplazo seleccionada
        mReplaceOptions = pReplaceOptions;

        //Indicamos que se trata de una matriz simple
        mSquares = Squares::One;

        //Liberamos el mutex
        mLocker.unlock();

        //Establecemos el resultado de la operación
        bResult = true;

        //Emitimos una señal para indicar que la matriz ha cambiado
        emit KeyMatrixChanged();
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::SetMatrix:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::SetMatrix:Error: Desconocido";
    }

    return bResult;
}
bool Playfair::SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey_1, const QString &pKey_2, SquareAlignment pSquareAligment)
{
    bool bResult = false;

    try
    {
        //Bloqueamos el acceso a las propiedades de la clase
        QWriteLocker mLocker(&mProperties_Mutex);

        //Generamos la nueva matriz
        mMatrix = Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_1);
        mMatrix += Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_2);

        //Guardamos el tamaño de la matriz
        mMatrixSize = pMatrixSize;

        //Guardamos la opción de reemplazo seleccionada
        mReplaceOptions = pReplaceOptions;

        //Indicamos que se trata de una matriz simple
        if (pSquareAligment == SquareAlignment::Horizontal)
        {
            mSquares = Squares::Two_Horizontal;
        }
        else
        {
            mSquares = Squares::Two_Vertical;
        }

        //Liberamos el mutex
        mLocker.unlock();

        //Establecemos el resultado de la operación
        bResult = true;

        //Emitimos una señal para indicar que la matriz ha cambiado
        emit KeyMatrixChanged();
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::SetMatrix:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::SetMatrix:Error: Desconocido";
    }

    return bResult;
}
bool Playfair::SetMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey_1, const QString &pKey_2, const QString &pKey_3, const QString &pKey_4)
{
    bool bResult = false;

    try
    {
        //Bloqueamos el acceso a las propiedades de la clase
        QWriteLocker mLocker(&mProperties_Mutex);

        //Generamos la nueva matriz
        mMatrix = Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_1);
        mMatrix += Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_2);
        mMatrix += Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_3);
        mMatrix += Playfair::GenerateMatrix(pMatrixSize, pReplaceOptions, pKey_4);

        //Guardamos el tamaño de la matriz
        mMatrixSize = pMatrixSize;

        //Guardamos la opción de reemplazo seleccionada
        mReplaceOptions = pReplaceOptions;

        //Indicamos que se trata de una matriz simple
        mSquares = Squares::Four;

        //Liberamos el mutex
        mLocker.unlock();

        //Establecemos el resultado de la operación
        bResult = true;

        //Emitimos una señal para indicar que la matriz ha cambiado
        emit KeyMatrixChanged();
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::SetMatrix:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::SetMatrix:Error: Desconocido";
    }

    return bResult;
}

//*******************************************************
//Decodifica el texto
//*******************************************************
QString Playfair::Decode(const QString &pText, bool *pOK)
{
    QString mDecodedText = "";
    QString mInputText = "";
    bool bOK = false;

    try
    {
        //Bloqueamos las propiedades para que no se pueda modiciar la matriz ni otras propiedades hasta que no terminemos de descodificar el texto
        QReadLocker mLocker(&mProperties_Mutex);

        //Copiamos el texto a decodificar y nos aseguramos que está en mayúsculas
        mInputText = pText.toUpper();

        //Eliminamos todos los caracteres que no están contemplados en la matriz
        mInputText.remove(QRegularExpression(QString("[^%1]").arg(mMatrix)));

        //Comprobamos que la cadena no este vacía
        if (mInputText.size() > 0)
        {
            //Comprobamos si la cadena tiene un número impar de carácteres
            if ((mInputText.size() % 2) != 0)
            {
                //Insertamos un carácter nulo
                mInputText.push_back(mNullChar);
            }

            //Recorremos la cadena en pares de 2
            for (qint32 i = 0; i < mInputText.size(); i += 2)
            {
                //Obtenemos los caracteres que forman el par
                QChar mChr_1 = mInputText.at(i);
                QChar mChr_2 = mInputText.at(i + 1);
                QChar mNew_Chr_1 = '\0';
                QChar mNew_Chr_2 = '\0';

                //Comprobamos si se han decodificado correctamente los carácteres
                if (GetChars(mChr_1, mChr_2, mNew_Chr_1, mNew_Chr_2, Action::Decode))
                {
                    //Insertamos el par de carácteres decodificados
                    mDecodedText.append(mNew_Chr_1);
                    mDecodedText.append(mNew_Chr_2);
                }
                else
                {
                    qCritical() << QString("Ocurrió un error al decodificar los pares de caracteres '%1' y '%2'").arg(QString(mChr_1), QString(mChr_2));
                }
            }
        }

        //Liberamos el mutex para que se pueda acceder a las propiedades
        mLocker.unlock();

        //Establecemos el resultado de la operacion
        bOK = true;
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::Decode:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::Decode:Error: Desconocido";
    }

    //Comprobamos si hemos de retornar el resultado de la operación
    if (pOK != nullptr)
    {
        //Guardamos el resultado de la operación en la variable de retorno
        *pOK = bOK;
    }

    return mDecodedText;
}

//*******************************************************
//Codifica el texto
//*******************************************************
QString Playfair::Encode(const QString &pText, bool *pOK)
{
    QString mEncodedText = "";
    QString mInputText = "";
    bool bOK = false;

    try
    {
        //Bloqueamos las propiedades para que no se pueda modiciar la matriz ni otras propiedades hasta que no terminemos de descodificar el texto
        QReadLocker mLocker(&mProperties_Mutex);

        //Copiamos el texto a decodificar y nos aseguramos que está en mayúsculas
        mInputText = pText.toUpper();

        //Eliminamos todos los caracteres que no están contemplados en la matriz
        mInputText.remove(QRegularExpression(QString("[^%1]").arg(mMatrix)));

        //Comprobamos que la cadena no este vacía
        if (mInputText.size() > 0)
        {
            //Comprobamos si la cadena tiene un número impar de carácteres
            if ((mInputText.size() % 2) != 0)
            {
                //Insertamos un carácter nulo
                mInputText.push_back(mNullChar);
            }

            //Recorremos la cadena en pares de 2
            for (qint32 i = 0; i < mInputText.size(); i += 2)
            {
                //Obtenemos los caracteres que forman el par
                QChar mChr_1 = mInputText.at(i);
                QChar mChr_2 = mInputText.at(i + 1);
                QChar mNew_Chr_1 = '\0';
                QChar mNew_Chr_2 = '\0';

                //Comprobamos si se han codificado correctamente los carácteres
                if (GetChars(mChr_1, mChr_2, mNew_Chr_1, mNew_Chr_2, Action::Encode))
                {
                    //Insertamos el par de carácteres codificados
                    mEncodedText.append(mNew_Chr_1);
                    mEncodedText.append(mNew_Chr_2);
                }
                else
                {
                    qCritical() << QString("Ocurrió un error al decodificar los pares de caracteres '%1' y '%2'").arg(QString(mChr_1), QString(mChr_2));
                }
            }
        }

        //Liberamos el mutex para que se pueda acceder a las propiedades
        mLocker.unlock();

        //Establecemos el resultado de la operación
        bOK = true;
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::Encode:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::Encode:Error: Desconocido";
    }

    //Comprobamos si hemos de retornar el resultado de la operación
    if (pOK != nullptr)
    {
        //Guardamos el resultado de la operación en la variable de retorno
        *pOK = bOK;
    }

    return mEncodedText;
}

//*******************************************************
//Obtiene la matriz actual de des/codificación
//*******************************************************
const QString &Playfair::GetCurrentMatrix() const
{
    return mMatrix;
}

//*******************************************************
//Obtiene el tamaño actual de la matriz
//*******************************************************
MatrixSizes Playfair::GetCurrentMatrixSize() const
{
    return mMatrixSize;
}

//*******************************************************
//Genera una matrix de codificacion
//*******************************************************
QString Playfair::GenerateMatrix(MatrixSizes pMatrixSize, ReplaceOptions pReplaceOptions, const QString &pKey)
{
    QString mMatrix = "";

    try
    {
        QString mKey = pKey.toUpper();
        QString mCharset = "";

        //Comprobamos de que tamaño se requiere la matrix
        switch (pMatrixSize)
        {
            case MatrixSizes::Size_5x5:
            {
                //Comprobamos que teclas hay que reemplazar
                if (pReplaceOptions == ReplaceOptions::Replace_J_I)
                {
                    //Reemplazamos todos los carácteres no válidos
                    mKey.replace('J', 'I');

                    //Incluimos los carácteres normales de la matriz
                    mCharset = QString("ABCDEFGHIKLMNOPQRSTUVWXYZ");
                }
                else
                {
                    //Reemplazamos todos los carácteres no válidos
                    mKey.replace('Q', 'O');

                    //Incluimos los carácteres normales de la matriz
                    mCharset = QString("ABCDEFGHIJKLMNOPRSTUVWXYZ");
                }

                break;
            }
            case MatrixSizes::Size_6x6:
            {
                mCharset = QString("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                break;
            }
        }

        //Eliminamos los carácteres no válidos de la clave (todos aquellos que no están en el charset original)
        mKey.remove(QRegularExpression(QString("[^%1]").arg(mCharset)));

        //Insertamos la clave en el charset, para generar la matriz
        mCharset.push_front(mKey);

        //Recorremos todo el conjunto de carácteres para generar la matriz de des/codificación
        for (qint32 i = 0; i < mCharset.size(); i++)
        {
            //Obtenemos el carácter
            QChar mChar = mCharset.at(i);

            //Comprobamos que el carácter no exista ya en la matrix
            if (mMatrix.contains(mChar) == false)
            {
                mMatrix.push_back(mChar);
            }
        }
    }
    catch (std::exception &e)
    {
        qCritical() << "Playfair::GenerateMatrix:Error:" << e.what();
    }
    catch (...)
    {
        qCritical() << "Playfair::GenerateMatrix:Error: Desconocido";
    }

    return mMatrix;
}
