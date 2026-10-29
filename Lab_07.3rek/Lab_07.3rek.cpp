#include <iostream>
#include <iomanip>

using namespace std;

// рекурсивне введення з клавіатури елементів рядка rowNo
void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

// рекурсивне введення всіх рядків матриці
void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

// рекурсивно виводить рядок rowNo
void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(5) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

// рекурсивно виводить усі рядки матриці
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

// рекурсивно перевіряє, чи стовпчик colNo містить нульовий елемент
// (переглядаються рядки rowNo, rowNo+1, ..., rowCount-1)
bool ColHasZero(int** a, const int rowCount, const int colNo, int rowNo)
{
    if (rowNo == rowCount)
        return false;
    if (a[rowNo][colNo] == 0)
        return true;
    return ColHasZero(a, rowCount, colNo, rowNo + 1);
}

// 1. int-функція: рекурсивно обчислює кількість стовпців (починаючи з colNo),
// що не містять жодного нульового елементу
int CountColsWithoutZero(int** a, const int rowCount, const int colCount, int colNo)
{
    if (colNo == colCount)
        return 0;
    return (ColHasZero(a, rowCount, colNo, 0) ? 0 : 1)
        + CountColsWithoutZero(a, rowCount, colCount, colNo + 1);
}

// рекурсивно обчислює характеристику рядка rowNo -
// суму його додатних парних елементів (починаючи зі стовпчика colNo)
int RowCharacteristic(int** a, const int rowNo, const int colCount, int colNo)
{
    if (colNo == colCount)
        return 0;
    int x = a[rowNo][colNo];
    return (x > 0 && x % 2 == 0 ? x : 0)
        + RowCharacteristic(a, rowNo, colCount, colNo + 1);
}

// міняє місцями рядки row1 та row2 (обмін вказівниками на рядки)
void ChangeRows(int** a, const int row1, const int row2)
{
    int* tmp = a[row1];
    a[row1] = a[row2];
    a[row2] = tmp;
}

// один прохід "бульбашки": порівнює сусідні рядки i1 та i1+1, поки i1 < last
void SortPass(int** a, const int colCount, const int last, int i1)
{
    if (i1 < last)
    {
        if (RowCharacteristic(a, i1, colCount, 0) >
            RowCharacteristic(a, i1 + 1, colCount, 0))
            ChangeRows(a, i1, i1 + 1);
        SortPass(a, colCount, last, i1 + 1);
    }
}

// 2. void-функція: рекурсивно переставляє рядки матриці відповідно до
// зростання характеристик; i0 - номер проходу
void SortRowsByCharacteristic(int** a, const int rowCount, const int colCount, int i0)
{
    if (i0 < rowCount - 1)
    {
        SortPass(a, colCount, rowCount - i0 - 1, 0);
        SortRowsByCharacteristic(a, rowCount, colCount, i0 + 1);
    }
}

// рекурсивно виводить характеристики рядків (для контролю результату)
void PrintCharacteristics(int** a, const int rowCount, const int colCount, int rowNo)
{
    cout << RowCharacteristic(a, rowNo, colCount, 0) << " ";
    if (rowNo < rowCount - 1)
        PrintCharacteristics(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

int main()
{
    int rowCount, colCount;     // розмірності матриці (k x n)
    cout << "k = "; cin >> rowCount;
    cout << "n = "; cin >> colCount;
    cout << endl;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);
    cout << endl;
    PrintRows(a, rowCount, colCount, 0);

    cout << "1.): "
        << CountColsWithoutZero(a, rowCount, colCount, 0) << endl;

    cout << "   Row characteristics: ";
    PrintCharacteristics(a, rowCount, colCount, 0);

    SortRowsByCharacteristic(a, rowCount, colCount, 0);
    cout << "2.):" << endl;
    PrintRows(a, rowCount, colCount, 0);

    cout << "   Row characteristics: ";
    PrintCharacteristics(a, rowCount, colCount, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
