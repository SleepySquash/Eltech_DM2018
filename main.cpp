#include <iostream>
#include <stdio.h>
#include <locale.h>
#ifndef __APPLE__
    #include <conio.h>
#endif
#include <string>
#ifndef __APPLE__
    #include <malloc.h>
#endif

using namespace std;

int __getch()
{
#ifdef __APPLE__
    return getchar();
#else
    return _getch();
#endif
}

template<typename... Args> int _scanf(Args... TArgs)
{
#ifndef __APPLE__
    return scanf_s(TArgs...);
#else
    return scanf(TArgs...);
#endif
}

//                                         Блок ЧАВО                                                     \\
// Проект выполнен на языке С/С++ в среде Microsoft Visual Studio 2013 студентами групп 7301, 7305 и 7307.
//
// _getch() читает вводимый символ с клавиатуры без вывода его на экран консоли.
// Коды для _getch():
// 72 - стрелка вверх.
// 80 - стрелка вниз.
// 13 - Enter.
// 27 - Esc.
// Коды для остальных кнопок можно получить из интернета или простейшим присвоением _getch() переменной типа int, а затем выводом этой самой переменной.
//
// Переменные, используемые мной в меню:
// index - счётчик-номер строки.
// tmp - временная переменная, хранящая в себе введённый символ.
// module - массивы с выводимыми строками (для каждой функции свой массив).
// prevIndex - счётчик-номер, который проверяет изменение индекса.
//
// Сдвиг курсора (знака >) во всех функциях производится с помощью одинакового использования _getch() и работы с результатом функции.
// Алгоритм сам по себе элементарный: если номер _getch() равен коду кнопки стрелки вверх, то уменьшение индекса, аналогично для стрелки вниз.
// Также проводятся проверки, что индексы не выйдут за границы массивов module.
//
// Выполнение программы строится по типу: функция, хранящая в себе функции, каждая из которых в себе хранит функции, которые, в свою очередь, также хранят в себе функции.
//
// Каждая новая версия программы несёт в себе малые (и не малые) изменения, которые значительно влияют и улучшают (а также дополняют) саму программу.
// То есть каждая новая программа по факту является улучшенной и оптимизированной версией каждой предыдущей.
// Первая цифра версии обозначает количество раз, сколько раз код был написан заново.
// Вторая цифра версии обозначает количество раз, когда уже в созданном коде были внесены значительные крупные изменения.
// Третья цифра версии обозначает количество раз, когда уже в созданном коде были внесены значительные малые изменения.
// Подробнее о каждой версии можно посмотреть в пункте меню I уровня под названием "Помощь".
//
// Список заданий можно увидеть по ссылке - http://pozdnkov.vm2-leti.spb.ru/ucebnye-gruppy-1/plany-lekcij/kollokvium-po-dm/kollokvium-po-dm-2
// Список распределений заданий по команде разработки - https://docs.google.com/spreadsheets/d/1X-aLv9Yl9oKm5RbzMNQT9eqwkyXjf6FtmMNYhdbeCRA/edit#gid=0
//
// По поводу уровней меню:
// I уровень - главное меню
// II уровень - модули
// III уровень - функции

bool inputSymbol(int &tmp, int &sign)
// Кезлинг Дмитрий, 7305
{
    bool result;
    if ((tmp >= 48) && (tmp <= 57))
        result = true;
    else if ((tmp == 45) && (sign != -1))
    {
        sign = 1;
        result = true;
    }
    else
        result = false;
    
    return result;
}

void inputDig(int &digit)
// Кезлинг Дмитрий, 7305
{
    bool flag = false;
    int tmp;
    digit = -1;
    do
    {
        tmp = __getch();
        if ((tmp >= 48) && (tmp <= 57) && (digit == -1))
        {
            digit = tmp - 48;
            cout << (char)tmp;
        }
        else if ((tmp == 13) && (digit != -1))
            flag = true;
    } while (!flag);
    cout << "\n";
}

void inputNumber(int &sign, int &size, int * &number)
// Кезлинг Дмитрий, 7305
{
    bool isMinusWritten = false, flag = false, isNotZeroInside = false;
    int tmp, result = 0;
    size = 0;
    number = NULL;
    
    if (sign != -1)
        sign = 0;
    
    do
    {
        tmp = __getch();
        if (inputSymbol(tmp, sign))
        {
            if ((tmp == 45) && (!isMinusWritten) && (sign != -1))
            {
                isMinusWritten = true;
                cout << (char)tmp;
            }
            else if ((tmp != 45) && (((tmp == 48) && (isNotZeroInside)) || (tmp != 48)))
            {
                if (tmp != 48)
                    isNotZeroInside = true;
                
                cout << (char)tmp;
                number = (int*)realloc(number, (size + 1) * sizeof(int));
                *(number + size) = tmp - 48;
                size++;
            }
            
            else if ((tmp == 48) && (!isNotZeroInside))
            {
                cout << (char)tmp;
                number = (int*)realloc(number, 1 * sizeof(int));
                *(number) = 0;
                size++;
                break;
            }
        }
        
        if (tmp == 13 || tmp == '\n')
        {
            if (size > 0)
                flag = true;
            else
                puts("Введите число!");
        }
        
    } while (!flag);
    cout << "\n";
}

void notZero(int &sign, int &size, int * &number)
// Кезлинг Дмитрий, 7305
{
    size = 0;
    number = NULL;
    inputNumber(sign, size, number);
    
    do
    {
        if (*(number) == 0)
        {
            cout << "Введите число, отличное от нуля: ";
            inputNumber(sign, size, number);
        }
    } while (*(number) == 0);
}

int COM_NN_D(int n1, int n2, int *A1, int *A2)
// сравнение чисел 2- если первое больше второго, 1 - если первое меньше второго, 0 - если числа равны.
// Диана Щебет, группа 7307
{
    int D = 0, i;
    
    if (n1 > n2)
        D = 2;
    else if (n1 < n2)
        D = 1;
    else if (n1 == n2)
        for (i = 0; i < n1; i++)
            if (A1[i] > A2[i])
            {
                D = 2;
                break;
            }
            else if (A1[i] < A2[i])
            {
                D = 1;
                break;
            }
    
    return D;
}

void MUL_Nk_N(int n, int *A1, int k, int **A10, int *n10)
///умножение числа на 10 в степени k
// Диана Щебет, группа 7307
{
    int i, m, *A2 = NULL;
    m = n + k;
    A2 = (int*)malloc(sizeof(int)*m);
    for (i = 0; i<n; i++) ///заполнение массива значащими цифрами данного массива
        A2[i] = A1[i];
    
    for (; n<m; n++) ///заполнение массива нулями после значащих цифр (собственно возведение в степень)
        A2[n] = 0;
    (*n10) = m;
    (*A10) = (int*)malloc(sizeof(int)*m);
    for (i = 0; i < m; i++) {
        (*A10)[i] = A2[i];
    }
    
    free(A2);
}

int *ABS_Z_N(int &b, int n, int *A)
// Стас Смирнов, группа 7301
{
    b = 0;
    return A;
}

int NZER_N_B(int n1, int * &A1)
//Евгений Сысенко, группа 7307
{
    int i, flag = 0, k = 0;
    for (i = 0; i<n1; i++)
    {
        if (A1[i] != 0)
        {
            flag = 1;
            break;
        }
    }
    
    return flag;
}

void MUL_ND_N(int n1, int dig, int *A1, int *n3, int **answer)
///Умножение натурального числа на цифру
// Евгений Сысенко, группа 7307
{
    int r = 0, p, q, i, k, z, *help_arr;
    help_arr = (int*)malloc((n1 + 1) * sizeof(int));
    for (i = n1 - 1; i >= 0; i--)
    {
        z = A1[i];
        q = z*dig + r;
        p = q % 10;
        help_arr[i + 1] = p;
        r = q / 10;
    }
    *n3 = n1;
    k = *n3;
    if (r != 0)
    {
        help_arr[0] = r;
        *n3 = n1 + 1;
        k = *n3;
    }
    else
    {
        for (i = 0; i<n1; i++)
        {
            help_arr[i] = help_arr[i + 1];
        }
    }
    
    (*answer) = (int*)malloc(sizeof(int)*(*n3));
    
    for (i = 0; i<k; i++)
    {
        (*answer)[i] = help_arr[i];
    }
    free(help_arr);
    
}

double LED_P_Q(int m, int *C)
// m – степень многочлена и массив C коэффициентов
// Старший коэффициент многочлена (Старший коэффициент - коэффициент при наибольшей степени неизвестного)
// Степенью многочлена  называют наибольшую из степеней входящих в него одночленов.
// Богряков Дмитрий, группа 7307
{
    printf("\nОтвет: %d", C[0]);
    puts("");
    return C[0]; //функция должна возвращать это значение или просто его выписывать в консольку?
}

void TRANS_Q_Z(int b, int n, int *A, int n1, int *A1)
// Рустам Аминов, группа 7307
{
    int i;
    if ((n1 == 1) && (A1[0] == 1))    //Провека: является ли знаменатель единицей?
    {
        printf("Число переведено в целое: ");
        if (b == 1)               //Данная функция всего лишь выводит на экран числитель, как вы поняли :)
            printf("-");       //Если вы хотите дальше работать с этим числом как целым, просто не берите знаменатель
        for (i = n; i >= 0; i--)
            printf("%d", A[i]);
    }
    else
        printf("Невозможен перевод в целое так как знаменатель не равен 1");//Если знаменатель  - не единица
    printf("\n");
}

void SUB_NN_N(int n1, int n2, int *A1, int *A2, int D, int *n6, int **A6)
// Диана Щебет, группа 7307
///"Вычитание из первого большего натурального числа второго меньшего или равного"
// Исаенко Никита - упростил
{
    int i, j, *A4;
    (*n6) = 0;
    
    A4 = (int*)malloc(n1 * sizeof(int));
    for (i = 0; i < n1; i++) { A4[i] = 0; }
    
    switch (D)
    {
            ///первое число больше второго
        case 2:
            for (i = n1 - 1; i >= 0; i--)
            {
                j = i - (n1 - n2);
                if (j >= 0) {
                    A4[i] += A1[i] - A2[j];
                    if (A4[i]<0) ///вычитание столбиком
                    {
                        A4[i] += 10;
                        A4[i - 1] -= 1;
                    }
                }
                else {
                    A4[i] += A1[i];
                    if (A4[i] < 0) { A4[i] += 10; A4[i - 1]--; }
                }
                (*n6)++;
            }
            
            while (A4[0] == 0 && (*n6) != 0) ///перестановка элементов массива с целью убрать 0 перед полученным результатом
            {
                for (i = 0; i < (*n6 - 1); i++)
                {
                    A4[i] = A4[i + 1];
                }
                *n6 = *n6 - 1;
            }
            
            (*A6) = (int*)malloc(sizeof(int) * (*n6));
            for (i = 0; i < (*n6); i++) ///заполнение массива данными
            {
                *((*A6) + i) = A4[i];
            }
            break;
            ///числа равны
        case 0:
            (*A6) = (int*)malloc(sizeof(int) * 1);
            (*A6)[0] = 0;
            
            break;
            ///первое меньше второго
        case 1:
            printf("\nОшибка! Неправильный ввод!\n");
            (*n6) = 0;
            break;
            
    }
    
}

void SUB_NDN_N(int *answer, int *A1, int n1, int n4, int D, int **A5, int *n5)
// Евгений Сысенко, группа 7307
///вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом.
{
    int *A6 = NULL, n6 = 1, i;
    if ((D == 2) || (D == 0))
    {
        SUB_NN_N(n1, n4, A1, answer, D, &n6, &A6);
        (*n5) = n6;
        (*A5) = (int*)malloc(sizeof(int)*(*n5));
        for (i = 0; i<n6; i++)
            (*A5)[i] = A6[i];
    }
    else
    {
        printf("Ошибка!");
        (*n5) = -1;
    }
    
    free(A6);
}

int POZ_Z_D(int sign, int sum, int *arr) {
    // Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)
    // sign - знак, sum = номер старшей позиции, arr - массив цифр числа
    // Александр Трифонов, группа 7301
    if (sign == 1) {//если изначально аргумент знака равен единицы то число отрицательное - возвращаем 1(число отрицательное)
        return 1;
    }
    else {
        if (arr[0] == 0) {//если изначально аргумент знака не равен единицы то число отрицательное или равно 0, если первое число в массиве равно 0  - возвращаем 0(число равно 0)
            return 0;
        }
        else {            //если первое число в массиве не равно 0  - возвращаем 2(число положительное)
            return 2;
        }
    }
}

void MUL_ZM_Z(int *sign, int sum, int *arr)
// Александр Трифонов, группа 7301
//в функцию передаються массив цифр числа через указатель, колличество цифр в числе минус 1, указател на знак числа(0 - положительное или ноль, 1 - отрицателное)
{
    if (*sign == 1) {//если изначально аргумент знака равен единицы то число отрицательное и при умножении получаем положительное число
        cout << "После умножения на (-1) числа получаем: ";
        for (int i = 0; i < sum; i++) {
            cout << arr[i];
        }
        *sign = 0;
        cout << "\n";
    }
    else {
        if (arr[0] == 0) {//если изначально аргумент знака не равен единицы то число gложительное или равно 0, если первое число в массиве равно 0  - число равно 0 и при умножении на (-1) получаем 0
            cout << "После умножения на (-1) получаем: ";
            for (int i = 0; i < sum; i++) {
                cout << arr[i];
            }
            cout << "\n";
        }
        else {            //если первое число в массиве не равно 0  - число положительное и при умножении на (-1) получаем отрицательное число
            cout << "После умножения на (-1) получаем: -";
            for (int i = 0; i < sum; i++) {
                cout << arr[i];
            }
            *sign = 1;
            cout << "\n";
        }
    }
}

int TRANS_N_Z(int b, int n, int *A) {
    //Стас Смирнов, группа 7301
    if ((b != 0) || (A[0] == 0)) {
        return 2;
    }
    else return b;
}

int TRANS_Z_N(int b, int n, int *A) {
    //Стас Смирнов, группа 7301
    if (b == 1)
        return -1;
    else if (A[0] == 0)
        return -2;
    else
        return *A;
}

int ADD_1N_N(int m, int * &A)
// Дмитрий Богряков, группа 7307
// возвращает номер старшей позиции (размер_массива-1)
// !эта функция может изменить размер массива (прибавить к размеру единицу)
{
    if (A == NULL)
    {
        A = (int*)malloc(sizeof(int));
        A[0] = 1;
        
        return 1;
    }
    
    if (m - 1 == 0)
        A[0]++;
    
    for (int i = m - 1; i > 0; i--) //для случая когда в числе есть хотя бы одна НЕ 9
    {
        if (A[i]<9)
        {
            A[i]++; //прибавление единицы
            i = -1;   //выход из цикла
        }
        else
        {
            A[i - 1]++;
            A[i] = 0;
            if (A[i - 1] != 10) { i = -1; }
        }
    }
    if (A[0] == 10) //случай, когда было введено значение, состоящее только из девяток
    {
        A = (int*)realloc(A, (m + 2) * sizeof(int));
        if (!A)  //проверка на выделение памяти
        {
            printf("Ошибка памяти.");
            exit(1);
        }
        A[0] = 1; //первый элемент единица, остальные-нули
        for (int i = 1; i<m + 2; i++) //заполнение остальных элементов нулями
        {
            A[i] = 0;
        }
        m++;
    }
    return m;
}

void DIV_NN_Dk(int n1, int n2, int *A1, int *A2, int D, int **A11, int *n11)
///"Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10^k, где k - номер позиции этой цифры (номер считается с нуля)"
// Диана Щебет, группа 7307
{
    int *A6 = NULL, n6 = 1, i, k = 0, m = 0, *A10 = NULL, n10 = 1, F, *A3 = NULL, n3 = 1;
    A3 = (int*)malloc(n1 * sizeof(int));
    for (i = 0; i<n1; i++)
        A3[i] = A1[i];
    n3 = n1;
    if (D == 2)
    {
        F = COM_NN_D(n2, n2, A1, A2); ///сравнение цифр по длине 2 числа
        
        if ((F == 2) || (F == 0)) ///поиск разряда цифры
            k = n3 - n2;
        else
            k = n3 - n2 - 1;
        
        MUL_Nk_N(n2, A2, k, &A10, &n10); ///умножение цифры на 10^k
        
        F = COM_NN_D(n3, n10, A3, A10);
        
        
        while (F != 1) ///цикл со счетчиком искомой цифры
        {
            SUB_NN_N(n3, n10, A3, A10, F, &n6, &A6);
            m++;
            F = COM_NN_D(n6, n10, A6, A10);
            
            n3 = n6; ///необходимые перемещения массивов, чтобы функция вычитания работала в цикле
            A3 = (int*)realloc(A3, n3 * sizeof(int));
            for (i = 0; i<n3; i++)
                A3[i] = A6[i];
            n6 = 1;
            A6 = (int*)realloc(A6, n6 * sizeof(int));
            A6[0] = 0;
        }
        (*n11) = 1;
        (*A11) = (int*)malloc(sizeof(int)*(*n11));
        (*A11)[0] = m;
    }
    else
    {
        printf("\nОшибка!");
        
    }
    free(A10);
    free(A6);
    free(A3);
}

void ADD_NN_N(int n1, int n2, int &resultN, int *first, int *second, int * &result)
// Диана Щебет, группа 7307
{
    int sum, i;
    bool extraNum = false;
    
    if (n1 > n2)
        resultN = n1;
    else
        resultN = n2;
    
    n2--; // Так надо
    n1--;
    result = NULL;
    
    result = (int*)realloc(result, (resultN + 1) * sizeof(int));
    
    
    
    if (n1 > n2) // Заполнение нулями и остальными цифрами
    {
        for (int i = 0; i < (n1 - n2); i++)
            *(result + i) = *(first + i);
        
        for (int i = (n1 - n2); i <= n1; i++)
            *(result + i) = 0;
    }
    else
    {
        for (int i = 0; i < (n2 - n1); i++)
            *(result + i) = *(second + i);
        
        
        for (int i = (n2 - n1); i <= n2; i++)
            *(result + i) = 0;
        
    }
    
    if (n1 > n2) // Сам подсчёт
    {
        for (i = n1; i >= (n1 - n2); i--)
        {
            if (extraNum)
            {
                sum = 1;
                extraNum = false;
            }
            else
                sum = 0;
            
            sum += *(first + i) + *(second + i - (n1 - n2));
            if (sum > 9)
            {
                sum %= 10;
                extraNum = true;
            }
            
            *(result + i) = *(result + i) + sum;
        }
        if (extraNum && (i == -1))
        {
            for (int i = resultN; i >= 1; i--)
                *(result + i) = *(result + (i - 1));
            resultN++;
            *(result) = 1;
        }
        else if (extraNum)
        {
            *(result + i) = *(result + i) + 1;
        }
    }
    else
    {
        for (i = n2; i >= (n2 - n1); i--)
        {
            if (extraNum)
            {
                sum = 1;
                extraNum = false;
            }
            else
                sum = 0;
            
            sum += *(second + i) + *(first + i - (n2 - n1));
            if (sum > 9)
            {
                sum %= 10;
                extraNum = true;
            }
            
            *(result + i) = *(result + i) + sum;
        }
        if (extraNum && (i == -1))
        {
            for (int i = resultN; i >= 1; i--)
                *(result + i) = *(result + (i - 1));
            resultN++;
            *(result) = 1;
        }
        else if (extraNum)
        {
            *(result + i) = *(result + i) + 1;
        }
    }
}

int INT_Q_B(int b, int n, int *A, int n1, int *A1)
// Рустам Аминов, группа 7307
{
    int first = 0, second = 0;
    for (int i = 0; i < n; i++)
    {
        first *= 10;
        first += *(A + i);
    }
    for (int i = 0; i < n1; i++)
    {
        second *= 10;
        second += *(A1 + i);
    }
    
    if (first % second == 0)
        return 1;
    else
        return 0;
}

int TRANS_Z_Q(int b, int n, int *A, int n1, int *A1)
//Стас Смирнов, группа 7301
{
    A1[0] = 1;//знаменатель становится равным единице
    n1 = 1;
    return *A1;
}

void MUL_NN_N(int n0, int n1, int *A0, int *A1, int &nresult, int * &result)
//Максим Кортель, группа 7301
//Использование: MUL_NN_N(n0, n1, A0, A1, &nresult, &result)
//               n1 - количество цифр в первом числе
//               n2 - количество цифр во втором числе
//               A0 - массив цифр первого числа (где нулевой элемент - это высший разряд)
//               А1 - массив цифр второго числа (где нулевой элемент - это высший разряд)
//               nresult - сюда будет записано количество цифр числа-результата
//               result - это будет массив цифр числа-результата (где нулевой элемент - это высший разрдяд)
//Изначально значение nresult неважно, а result обязан иметь значение NULL или nullptr во избежание проблем с утечкой памяти.
{
    int i, j;
    int *tmp = NULL, ntmp = 0;
    int *add = NULL, nadd = 0;
    int ntemp = 1, *temp;
    int ntmpresult = 0, *tmpresult = NULL;
    
    temp = (int*)malloc(sizeof(int));
    temp[ntemp] = 0;
    
    for (i = 0; i<n1; i++)
    {
        MUL_ND_N(n0, A1[i], A0, &ntmp, &tmp);
        MUL_Nk_N(ntmp, tmp, n1 - i, &add, &nadd);
        ADD_NN_N(ntemp, nadd, ntmpresult, temp, add, tmpresult);
        ntemp = ntmpresult;
        temp = (int*)realloc(temp, (ntemp) * sizeof(int));
        for (j = 0; j<ntemp; j++)
            temp[j] = tmpresult[j];
        
        tmpresult = NULL; ntmpresult = 0;
        add = NULL; nadd = 0;
        ntmp = 0; tmp = NULL;
    }
    
    ntemp--;
    while ((*(temp) == 0) && (ntemp > 1))
    {
        *(temp) = *(temp + 1);
        ntemp--;
    }
    
    nresult = ntemp;
    result = (int*)malloc(sizeof(int)*(ntemp));
    for (i = 0; i < ntemp; i++)
        (result[i]) = temp[i];
    
    free(tmp);
    free(add);
    free(tmpresult);
}

void MUL_ZZ_Z(int sizeFirst, int sizeSecond, int *first, int *second, int markFirst, int markSecond, int &sizeResult, int * &result, int &markResult)
// Максим Кортель, группа 7301
{
    int isPositiveFirst, isPositiveSecond;
    markResult = 1;
    MUL_NN_N(sizeFirst, sizeSecond, first, second, sizeResult, result);
    
    isPositiveFirst = POZ_Z_D(markFirst, sizeFirst, first);
    isPositiveSecond = POZ_Z_D(markSecond, sizeSecond, second);
    
    if (isPositiveFirst == isPositiveSecond)
        ABS_Z_N(markResult, sizeResult, result);
}

void DER_PP_P(int m, int *C)
{
    int i, j = 0;
    for (i = 0; i <= 2 * m + 1; i = i + 2)
    {
        printf("Числитель: %d, знаменатель: %d", C[i] * j, C[i + 1]);
        j++;
    }
}

void ADD_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
    int D = 2;
    if (*sign1 == *sign2) {//если знаки у чисел одинаковые - складываем модули чисел и задаем знак нашей суммы равным знакам слагаемых
        ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
        *sign3 = *sign1;
        *sum3 = *sum3;
    }
    else {
        if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//если знаки не равны, то мы определяем какое из чисел по модулю больше, отрицательное или положительное, если отрицательное больше то мы вычитаем из отрицательного положительное по модулю и присваеваем нашей сумме знак минус
            if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//если положительное больше то вычитаем из положительного отрицательное и присваиваем нашей сцмме знак плюс
                *sign3 = 0;
                SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
                
            }
            else {
                *sign3 = 1;
                SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
            }
            
        }
        if (POZ_Z_D(*sign2, *sum2, arr2) == 2 || POZ_Z_D(*sign2, *sum2, arr2) == 0) {
            if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D(*sum2, *sum1, arr2, arr1) == 0) {
                *sign3 = 0;
                SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
                
            }
            else {
                *sign3 = 1;
                SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
            }
            
        }
    }
}

void SUB_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
    int D = 2;
    //if (COM_NN_D(*sum1, *sum2, arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//выясняем какой размер массива нам нужен для суммы чисел и выбираем максимальнуюиз них
    //    *sum3 = *sum1;
    //}
    //else {
    //    *sum3 = *sum2;
    //}
    //int *arr3 = new int[*sum3 + 2];//создаем массив
    if (*sign1 != *sign2) {//если знаки у чисел разные - складываем модули чисел и задаем знак нашей суммы равным знаку первого
        if (*sign2 == 1) {
            ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
            *sign3 = 0;
        }
        else {
            ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
            *sign3 = 1;
            
        }
        //ADD_NN_N( (*sum1), (*sum2), (*sum3), arr1,  arr2, *&arr3);
        //*sign3 = *sign1;
    }
    else {
        if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//если знаки равны то определяем какого знака числа, далее выясняем какое из них по модулю больше
            if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D((*sum1), (*sum2), arr1, arr2) == 0) {//и в зависимости от этого складываем или вычитаем модули чисел и задаем нужный знак
                *sign3 = 0;
                SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
                //первое больше нуля или равно 0, второе больше нуля
            }                                                    //первое больше - вычитаем из превого второе и задаем знак +
            else {                                                //и наоборот второе больше первого - вычитаем из второго первое и знак -
                *sign3 = 1;
                SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
            }
            
        }
        if (POZ_Z_D(*sign2, *sum2, arr2) == 1) {
            if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D((*sum2), (*sum1), arr2, arr1) == 0) {
                *sign3 = 0;
                SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
            }                                                    //первое и второе меньше нуля
            else {                                                //первое больше - вычитаем из превого второе и задаем знак -
                *sign3 = 1;                                        //и наоборот второе больше первого - вычитаем из второго первое и знак +
                SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
            }
            
        }
    }
}

void MUL_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b_result, int &n0_result, int &n1_result, int *&A0_result, int *&A1_result)
///выполнила Волкова Анна, гр.7307
//умножение дробей
// первая дробь: n0 -разряд числителя, n1 - разряд знаменателя, A0 - массив числителя, A1 - массив знаменателя;
//аналогично n0_1 и т.д. для второй дроби
//(_result) - аналогично - результат
{
    MUL_ZZ_Z(n0, n0_1, A0, A0_1, b, b_1, n0_result, A0_result, b_result);
    MUL_NN_N(n1, n1_1, A1, A1_1, n1_result, A1_result); //используем эту функцию, так как знаменатель - натуральное число
    //можно добавить функцию сокращения дроби
}

void DIV_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b0_result, int &b1_result, int &n0_result, int &n1_result, int * &A0_result, int * &A1_result)
///выполнила Волкова Анна, гр.7307
//умножение дробей
// первая дробь: n0 -разряд числителя, n1 - разряд знаменателя, A0 - массив числителя, A1 - массив знаменателя;
//аналогично n0_1 и т.д. для второй дроби
//(_result) - аналогично - результат
{
    MUL_ZZ_Z(n0, n1_1, A0, A1_1, b, 0, n0_result, A0_result, b0_result);
    MUL_ZZ_Z(n1, n0_1, A1, A0_1, 0, b_1, n1_result, A1_result, b1_result);//используем эту функцию, так как знаменатель - натуральное число
    //можно добавить функцию сокращения дроби
}

void DIV_NN_N(int n1, int *A1, int n2, int *A2, int &nRes, int * &ARes)
//Исаенко Никита 7305
{
    nRes = 0;
    ARes = NULL;
    int nFirst, nSecond, *AFirst, *ASecond;
    if (COM_NN_D(n1, n2, A1, A2) != 1)
    {
        nFirst = n1;
        AFirst = A1;
        
        nSecond = n2;
        ASecond = A2;
    }
    else
    {
        nFirst = n2;
        AFirst = A2;
        
        nSecond = n1;
        ASecond = A1;
    }
    
    nRes = 0;
    int nTemp = 0; int *ATemp = NULL;
    while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
    {
        SUB_NN_N(nFirst, nSecond, AFirst, ASecond, COM_NN_D(nFirst, nSecond, AFirst, ASecond), &nTemp, &ATemp);
        if (nRes != 0) { free(AFirst); } nFirst = nTemp; AFirst = ATemp;
        
        nRes = ADD_1N_N(nRes, ARes);
    }
}

void MOD_NN_N(int n1, int *A1, int n2, int *A2, int &nRes, int * &ARes)
//Исаенко Никита 7305
{
    nRes = 0;
    ARes = NULL;
    int nFirst, nSecond, *AFirst, *ASecond;
    if (COM_NN_D(n1, n2, A1, A2) != 1)
    {
        nFirst = n1;
        AFirst = A1;
        
        nSecond = n2;
        ASecond = A2;
    }
    else
    {
        nFirst = n2;
        AFirst = A2;
        
        nSecond = n1;
        ASecond = A1;
    }
    
    nRes = 0;
    int nTemp = 0; int *ATemp = NULL; bool First = true;
    while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
    {
        SUB_NN_N(nFirst, nSecond, AFirst, ASecond, COM_NN_D(nFirst, nSecond, AFirst, ASecond), &nTemp, &ATemp);
        if (!First) { free(AFirst); }
        else { First = false; }
        nFirst = nTemp; AFirst = ATemp;
    }
    nRes = nFirst; ARes = (int*)malloc(sizeof(int)*nFirst);
    if (nRes == 0)
    {
        nRes = 1;
        ARes = (int*)malloc(sizeof(int));
        ARes[0] = 0;
    }
    for (int i = 0; i < nFirst; i++)
        ARes[i] = AFirst[i];
}

void GCF_NN_N(int sizeFirst, int sizeSecond, int * first, int * second, int & nResult, int * &result)
// Дмитрий Кезлинг, группа 7305
{
    while ((NZER_N_B(sizeFirst, first) != 0) && (NZER_N_B(sizeSecond, second) != 0))
    {
        nResult = 0;
        result = NULL;
        
        MOD_NN_N(sizeFirst, first, sizeSecond, second, nResult, result);
        if (COM_NN_D(sizeFirst, sizeSecond, first, second) == 2)
        {
            first = NULL;
            first = (int*)malloc((nResult) * sizeof(int));
            sizeFirst = nResult;
            
            for (int i = 0; i < nResult; i++)
                *(first + i) = *(result + i);
            
        }
        else
        {
            second = NULL;
            second = (int*)malloc((nResult) * sizeof(int));
            sizeSecond = nResult;
            
            for (int i = 0; i < nResult; i++)
                *(second + i) = *(result + i);
        }
    }
    
    if (first[0] != 0) {
        nResult = sizeFirst;
        result = NULL;
        result = (int*)malloc((nResult) * sizeof(int));
        for (int i = 0; i < nResult; i++)
            *(result + i) = *(first + i);}
    else{
        nResult = sizeSecond;
        result = NULL;
        result = (int*)malloc((nResult) * sizeof(int));
        for (int i = 0; i < nResult; i++)
            *(result + i) = *(second + i);}
}

void LCM_NN_N(int sizeFirst, int sizeSecond, int * first, int * second, int & nResult, int * &result)
// Дмитрий Кезлинг, группа 7305
{
    int _nResult1, *_result1 = NULL,
    _nResult2, *_result2 = NULL;
    nResult = 0;
    result = NULL;
    GCF_NN_N(sizeFirst, sizeSecond, first, second, _nResult1, _result1);
    MUL_NN_N(sizeFirst, sizeSecond, first, second, _nResult2, _result2);
    DIV_NN_N(_nResult2, _result2, _nResult1, _result1, nResult, result);
}

void DIV_ZZ_Z(int markFirst, int markSecond, int sizeFirst, int sizeSecond, int * first, int * second, int & markResult, int & sizeResult, int * &result)
// Дмитрий Кезлинг, группа 7305
{
    if (POZ_Z_D(markFirst, sizeFirst, first) == POZ_Z_D(markSecond, sizeSecond, second))
        markResult = 0;
    else
        markResult = 1;
    
    sizeResult = 0;
    result = NULL;
    
    /*cout << "sizeFirst: " << sizeFirst << " first: ";
     for (int i = 0; i < sizeFirst; i++)
     cout << first[i];
     cout << endl;
     cout << "sizeSecond: " << sizeSecond << " second: ";
     for (int i = 0; i < sizeSecond; i++)
     cout << second[i];
     cout << endl;*/
    
    DIV_NN_N(sizeFirst, first, sizeSecond, second, sizeResult, result);
    
    /*cout << "nResult: " << sizeResult << " result: ";
    for (int i = 0; i < sizeResult; i++)
        cout << result[i];
    cout << endl;*/
}

void MOD_ZZ_Z(int markFirst, int markSecond, int sizeFirst, int sizeSecond, int * first, int * second, int & markResult, int & sizeResult, int * &result)
// Дмитрий Кезлинг, группа 7305
{
    sizeResult = 0;
    result = NULL;
    
    int nFirst, nSecond, *AFirst, *ASecond,
    nTemp = 0, markSkip = 0;
    int *ATemp = NULL;
    bool First = true;
    markResult = 0;
    
    if (COM_NN_D(sizeFirst, sizeSecond, first, second) != 1)
    {
        nFirst = sizeFirst;
        AFirst = first;
        
        nSecond = sizeSecond;
        ASecond = second;
    }
    else
    {
        nFirst = sizeSecond;
        AFirst = second;
        
        nSecond = sizeFirst;
        ASecond = first;
    }
    
    while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
    {
        SUB_ZZ_Z(&nFirst, AFirst, &markSkip, &nSecond, ASecond, &markSkip, &nTemp, ATemp, &markResult);
        if (!First) { free(AFirst); }
        else { First = false; }
        nFirst = nTemp; AFirst = ATemp;
    }
    
    if (markFirst == 1)
        ADD_ZZ_Z(&nFirst, AFirst, &markFirst, &sizeSecond, second, &markSecond, &sizeResult, result, &markResult);
    else
    {
        if (nFirst == 0)
        {
            sizeResult = 1;
            result = (int*)malloc(sizeof(int)*nFirst);
            *(result) = 0;
        }
        else
        {
            sizeResult = nFirst;
            result = (int*)malloc(sizeof(int)*nFirst);
            for (int i = 0; i < nFirst; i++)
                result[i] = AFirst[i];
        }
    }
}


void RED_QQ_Q(int markFirst, int markSecond, int sizeNumer, int sizeDeno, int * numer, int * deno, int & markResult, int & sizeResultNumer, int & sizeResultDeno, int * & numerResult, int * &denoResult)
// Дмитрий Кезлинг, группа 7305
{
    sizeResultDeno = 0;
    sizeResultNumer = 0;
    numerResult = NULL;
    denoResult = NULL;
    
    if (markFirst == markSecond)
        markResult = 0;
    else
        markResult = 1;
    
    int *tmpResult = NULL, sizeTmpResult = 0, markSkip = 0;
    GCF_NN_N(sizeNumer, sizeDeno, numer, deno, sizeTmpResult, tmpResult);
    if (!(tmpResult[0] == 1 && sizeTmpResult == 1))
    {
        DIV_ZZ_Z(markSkip, markSkip, sizeNumer, sizeTmpResult, numer, tmpResult, markResult, sizeResultNumer, numerResult);
        DIV_ZZ_Z(markSkip, markSkip, sizeDeno, sizeTmpResult, deno, tmpResult, markResult, sizeResultDeno, denoResult);
    }
    else
    {
        sizeResultNumer = sizeNumer;
        sizeResultDeno = sizeDeno;
        numerResult = numer;
        denoResult = deno;
    }
    
    if (markFirst == markSecond)
        markResult = 0;
    else
        markResult = 1;
}

void ADD_QQ_Q(int markFirstNumer, int markFirstDeno, int markSecondNumer, int markSecondDeno,
              int sizeNumer1, int sizeDeno1, int * numer1, int * deno1, int sizeNumer2, int sizeDeno2, int * numer2, int * deno2,
              int & markResultNumer, int & markResultDeno, int & sizeResultNumer, int & sizeResultDeno, int * & numerResult, int * &denoResult)
// Дмитрий Кезлинг, группа 7305
{
    sizeResultDeno = 0;
    sizeResultNumer = 0;
    numerResult = NULL;
    denoResult = NULL;
    
    int * tmpFirst = NULL, sizeTmpFirst = 0, markTmpFirst = 0,
    *tmpSecond = NULL, sizeTmpSecond = 0, markTmpSecond = 0;
    
    MUL_ZZ_Z(sizeNumer1, sizeDeno2, numer1, deno2, markFirstNumer, markSecondDeno, sizeTmpFirst, tmpFirst, markTmpSecond);
    MUL_ZZ_Z(sizeNumer2, sizeDeno1, numer2, deno1, markSecondNumer, markFirstNumer, sizeTmpSecond, tmpSecond, markTmpSecond);
    
    ADD_ZZ_Z(&sizeTmpFirst, tmpFirst, &markTmpFirst, &sizeTmpSecond, tmpSecond, &markTmpSecond, &sizeResultNumer, numerResult, &markResultNumer);
    
    MUL_ZZ_Z(sizeDeno1, sizeDeno2, deno1, deno2, markFirstDeno, markSecondDeno, sizeResultDeno, denoResult, markResultDeno);

    if (sizeResultNumer == 0 || sizeResultDeno == 0)
    {
        markResultNumer = 0;
        sizeResultNumer = 1;
        sizeResultDeno = 1;
        numerResult = (int*)malloc(sizeof(int)*sizeResultNumer);
        denoResult = (int*)malloc(sizeof(int)*sizeResultDeno);
        numerResult[0] = 0;
        denoResult[0] = 1;
    }
    else
    {
        RED_QQ_Q(markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult, markTmpFirst, sizeTmpFirst, sizeTmpSecond, tmpFirst, tmpSecond);
        markResultNumer = markTmpFirst;
        sizeResultNumer = sizeTmpFirst;
        sizeResultDeno = sizeTmpSecond;
        numerResult = (int*)malloc(sizeof(int)*sizeResultNumer);
        denoResult = (int*)malloc(sizeof(int)*sizeResultDeno);
        for (int i = 0; i < sizeResultNumer; i++)
            numerResult[i] = tmpFirst[i];
        for (int i = 0; i < sizeResultDeno; i++)
            denoResult[i] = tmpSecond[i];
    }
}

void SUB_QQ_Q (int markFirstNumer, int markFirstDeno, int markSecondNumer, int markSecondDeno,
               int sizeNumer1, int sizeDeno1, int * numer1, int * deno1, int sizeNumer2, int sizeDeno2, int * numer2, int * deno2,
               int & markResultNumer, int & markResultDeno, int & sizeResultNumer, int & sizeResultDeno, int * & numerResult, int * &denoResult)
// Дмитрий Кезлинг, группа 7305
{
    sizeResultDeno = 0;
    sizeResultNumer = 0;
    numerResult = NULL;
    denoResult = NULL;
    
    int * tmpFirst = NULL, sizeTmpFirst = 0, markTmpFirst = 0,
    *tmpSecond = NULL, sizeTmpSecond = 0, markTmpSecond = 0;
    
    MUL_ZZ_Z(sizeNumer1, sizeDeno2, numer1, deno2, markFirstNumer, markSecondDeno, sizeTmpFirst, tmpFirst, markTmpSecond);
    MUL_ZZ_Z(sizeNumer2, sizeDeno1, numer2, deno1, markSecondNumer, markFirstNumer, sizeTmpSecond, tmpSecond, markTmpSecond);
    
    SUB_ZZ_Z(&sizeTmpFirst, tmpFirst, &markTmpFirst, &sizeTmpSecond, tmpSecond, &markTmpSecond, &sizeResultNumer, numerResult, &markResultNumer);
    
    MUL_ZZ_Z(sizeDeno1, sizeDeno2, deno1, deno2, markFirstDeno, markSecondDeno, sizeResultDeno, denoResult, markResultDeno);
    
    if (sizeResultNumer == 0 || sizeResultDeno == 0)
    {
        markResultNumer = 0;
        sizeResultNumer = 1;
        sizeResultDeno = 1;
        numerResult = (int*)malloc(sizeof(int)*sizeResultNumer);
        denoResult = (int*)malloc(sizeof(int)*sizeResultDeno);
        numerResult[0] = 0;
        denoResult[0] = 1;
    }
    else
    {
        RED_QQ_Q(markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult, markTmpFirst, sizeTmpFirst, sizeTmpSecond, tmpFirst, tmpSecond);
        markResultNumer = markTmpFirst;
        sizeResultNumer = sizeTmpFirst;
        sizeResultDeno = sizeTmpSecond;
        numerResult = (int*)malloc(sizeof(int)*sizeResultNumer);
        denoResult = (int*)malloc(sizeof(int)*sizeResultDeno);
        for (int i = 0; i < sizeResultNumer; i++)
            numerResult[i] = tmpFirst[i];
        for (int i = 0; i < sizeResultDeno; i++)
            denoResult[i] = tmpSecond[i];
    }
}

int DEG_P_N(int &n)
{
    return n;
}

int power10(int power)
{
    int result = 1;
    for (int i = 0; i < power; i++)
        result *= 10;
    return result;
}

char *InputString()
{
    char *str{ nullptr };
    char wc;
    int strLen{ 0 };
    
    bool MemError{ false };
    
    while ((wc = getchar()) != '\n' && !MemError)
    {
        char *temp = (char*)realloc(str, (strLen + 2) * sizeof(char));
        if (temp != nullptr)
        {
            str = temp;
            str[strLen] = wc;
            strLen++;
        }
        else
        {
            free(str); str = nullptr;
            MemError = true;
            cout << "Ошибка выделения памяти. Попробуйте снова." << endl;
        }
    }
    
    if (!MemError)
    {
        if (strLen == 0)
        {
            str = (char*)malloc(sizeof(char));
        }
        str[strLen] = '\0';
    }
    
    fflush(stdin); cin.clear();
    return str;
}

//Допускается:
//  1/2, 6, -12 - всё это свободные члены
//  x, -x, 1/2x, -1/2x, 6x, -12x^2, 51x10, 10*x^12 - всё это ввод коэффициентов и степеней икс
//Не допускается:
//  x+12x^2-12 - ввод коэффициентов без пробелов между ними
//Предполагается:
//  int m = -1;
//  int *C = NULL;
void InputPolynom(int &m, int *&C)
{
    char *parse = InputString();
    
    int lettersCounted = 0;
    bool signInput = false;
    for (int i = 0; (i != 0 && parse[i-1] != '\0') || (i == 0 && parse[0] != '\0'); i++) {
        if (parse[i] == 'x')
        {
            int toSkipAhead = 1;
            int xDegree = -1;
            //DEGREE ANALTSIS
            int j = i;
            for (; parse[j] != ' ' && parse[j] != '\0'; j++) {
                //parse dergee from [i + j]
            } toSkipAhead = j - i - 1;
            if (j == i || (j-1 == i && (parse[j] == '\0')))
            {
                //degree = 1
                xDegree = 1;
                if (m < 1) {
                    C = (int*)realloc(C, sizeof(int)*4);
                    for (int k = (m+1)*2; k < (xDegree+1)*2; k++)
                        C[k] = NULL;
                    m = 1;
                }
            }
            else
            {
                bool atLeastOne = false;
                int resultInt = 0;
                int numberDegree = 0;
                for (int k = j-1; k > i; k--)
                {
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        resultInt += (parse[k] - 48) * power10(numberDegree);
                        numberDegree++;
                    }
                }
                if (!atLeastOne) {atLeastOne = true; resultInt = 1;}
                if (atLeastOne)
                {
                    xDegree = resultInt;
                    if (xDegree > m)
                    {
                        C = (int*)realloc(C, sizeof(int)*(xDegree+1)*2);
                        for (int k = (m+1)*2; k < (xDegree+1)*2; k++)
                            C[k] = NULL;
                        m = xDegree;
                    }
                    C[xDegree*2] = NULL;
                    C[xDegree*2 + 1] = NULL;
                }
            }
            //DEGREE ANALYSIS
            
            //COEFF ANALYSIS
            int slashPosition = -1;
            j = i;
            for (; parse[j] != ' ' && j >= 0 && parse[j] != '+' && parse[j] != '-'; j--) {
                //parse coeff from [j-i to j] [...]x
                if (parse[j] == '\\' || parse[j] == '/') {slashPosition = j;}
            }
            if (j == i || (j+1 == i))
            {
                //coeff = 1
                C[xDegree*2] = !signInput ? 1 : -1;
                C[xDegree*2 + 1] = 1;
            }
            else
            {
                if (slashPosition != -1)
                {
                    //coeff = x/y
                    bool atLeastOne = false;
                    int resultInt = 0;
                    int numberDegree = 0;
                    for (int k = i-1; k > slashPosition; k--)
                    {
                        if (parse[k] == 43)
                            signInput = false;
                        if (parse[k] == 45)
                            signInput = true;
                        
                        if (parse[k] >= 48 && parse[k] <= 57)
                        {
                            atLeastOne = true;
                            resultInt += (parse[k] - 48) * power10(numberDegree);
                            numberDegree++;
                        }
                    }
                    
                    if (atLeastOne)
                    {
                        C[xDegree*2] = 1;
                        C[xDegree*2 + 1] = resultInt;
                        
                        atLeastOne = false;
                        resultInt = 0;
                        numberDegree = 0;
                        for (int k = slashPosition-1; k > j; k--)
                        {
                            if (parse[k] == 43)
                                signInput = false;
                            if (parse[k] == 45)
                                signInput = true;
                            
                            if (parse[k] >= 48 && parse[k] <= 57)
                            {
                                atLeastOne = true;
                                resultInt += (parse[k] - 48) * power10(numberDegree);
                                numberDegree++;
                            }
                        }
                        
                        if (atLeastOne)
                        {
                            if (signInput)
                                resultInt = -resultInt;
                            C[xDegree*2] = resultInt;
                        }
                    }
                }
                else
                {
                    //coeff = x
                    bool atLeastOne = false;
                    int resultInt = 0;
                    int numberDegree = 0;
                    for (int k = i-1; k > j; k--)
                    {
                        if (parse[k] == 43)
                            signInput = false;
                        if (parse[k] == 45)
                            signInput = true;
                        
                        if (parse[k] >= 48 && parse[k] <= 57)
                        {
                            atLeastOne = true;
                            resultInt += (parse[k] - 48) * power10(numberDegree);
                            numberDegree++;
                        }
                    }
                    
                    if (atLeastOne)
                    {
                        if (signInput)
                            resultInt = -resultInt;
                        C[xDegree*2] = resultInt;
                        C[xDegree*2 + 1] = 1;
                    }
                }
            }
            //COEFF ANALYSIS
            
            //now skipping the whole a/b*x^d fragment
            lettersCounted = 0;
            i += toSkipAhead;
        }
        else if ((parse[i] == ' ' || parse[i] == '\0') && lettersCounted > 0)
        {
            //we've done parsing a word
            //it's a number
            
            int slashPosition = -1;
            int j = i-1;
            for (; parse[j] != ' ' && j >= 0 && parse[j] != '+' && parse[j] != '-'; j--) {
                //parse coeff from [j-i to j] [...]x
                if (parse[j] == '\\' || parse[j] == '/') {slashPosition = j;}
            }
            if (slashPosition != -1)
            {
                bool atLeastOne = false;
                int resultInt = 0;
                int numberDegree = 0;
                for (int k = i-1; k > slashPosition; k--)
                {
                    if (parse[k] == 43)
                        signInput = false;
                    if (parse[k] == 45)
                        signInput = true;
                    
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        resultInt += (parse[k] - 48) * power10(numberDegree);
                        numberDegree++;
                    }
                }
                
                if (atLeastOne)
                {
                    if (m < 0) {m = 0;
                        C = (int*)malloc(sizeof(int)*2);}
                    C[0] = 1;
                    C[1] = resultInt;
                    
                    atLeastOne = false;
                    resultInt = 0;
                    numberDegree = 0;
                    for (int k = slashPosition-1; k > j; k--)
                    {
                        if (parse[k] == 43)
                            signInput = false;
                        if (parse[k] == 45)
                            signInput = true;
                        
                        if (parse[k] >= 48 && parse[k] <= 57)
                        {
                            atLeastOne = true;
                            resultInt += (parse[k] - 48) * power10(numberDegree);
                            numberDegree++;
                        }
                    }
                    
                    if (atLeastOne)
                    {
                        if (signInput)
                            resultInt = -resultInt;
                        C[0] = resultInt;
                    }
                }
            }
            else
            {
                bool atLeastOne = false;
                int resultInt = 0;
                int numberDegree = 0;
                for (int k = i-1; k > j; k--)
                {
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        resultInt += (parse[k] - 48) * power10(numberDegree);
                        numberDegree++;
                    }
                }
                
                if (atLeastOne)
                {
                    if (m < 0) {m = 0;
                        C = (int*)malloc(sizeof(int)*2);}
                    C[0] = resultInt;
                    C[1] = 1;
                }
            }
            lettersCounted = 0;
        }
        else
        {
            if (parse[i] == 43)
                signInput = false;
            if (parse[i] == 45)
                signInput = true;
            
            //we're parsing a word
            lettersCounted++;
        }
    }
}

//Вывод в формате -12x^6 + 3/2x^3 + -x^1 + 1/2
//  (+ всегда между слагаемыми, а если слагамаемое отрицательно, то будет "... + -12/5x^2 + ..."
void PrintPolynom(int m, int *C)
{
    if (m >= 0)
    {
        for (int i = m*2; i >= 0; i -= 2)
        {
            if (C[i] != 0)
            {
                if (i != m*2)
                    cout << " + ";
                
                if (i != 0)
                {
                    if (C[i + 1] == 1 && C[i] == 1)
                        cout << "x^" << i/2;
                    else if (C[i + 1] == 1 && C[i] == -1)
                        cout << "-x^" << i/2;
                    else
                    {
                        if (C[i+1] != 0 && C[i+1] != 1)
                            cout << C[i] << "/" << C[i+1] << "x^" << i/2;
                        else
                            cout << C[i] << "x^" << i/2;
                    }
                }
                else
                {
                    if (C[i+1] != 0 && C[i+1] != 1)
                        cout << C[i] << "/" << C[i+1];
                    else
                        cout << C[i];
                }
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Данный многочлен не существует, поэтому вывод на экран коэффициентов невозможен." << endl;
    }
}

//Вывод в формате -12x^6 + 3/2x^3 - x^1 + 1/2
//  (+ меняется на -, если слагамаемое отрицательно
void PrintPolynomSigned(int m, int *C)
{
    if (m >= 0)
    {
        for (int i = m*2; i >= 0; i -= 2)
        {
            if (C[i] != 0)
            {
                if (i != m*2)
                {
                    if (C[i] > 0)
                        cout << " + ";
                    else
                        cout << " - ";
                }
                if (i == m*2)
                {
                    if (C[i] < 0)
                        cout << "-";
                }
                
                if (i != 0)
                {
                    if (C[i + 1] == 1 && C[i] == 1)
                        cout << "x^" << i/2;
                    else if (C[i + 1] == 1 && C[i] == -1)
                        cout << "x^" << i/2;
                    else
                    {
                        int Temp = C[i];
                        if (Temp < 0) Temp = -Temp;
                        if (C[i+1] != 0 && C[i+1] != 1)
                        {
                            cout << Temp << "/" << C[i+1] << "x^" << i/2;
                        }
                        else
                            cout << Temp << "x^" << i/2;
                    }
                }
                else
                {
                    int Temp = C[i];
                    if (Temp < 0) Temp = -Temp;
                    if (C[i+1] != 0 && C[i+1] != 1)
                        cout << Temp << "/" << C[i+1];
                    else
                        cout << Temp;
                }
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Данный многочлен не существует, поэтому вывод на экран коэффициентов невозможен." << endl;
    }
}

struct Q
{
    int sign = 0;
    
    int nNom = -1;
    int *ANom = NULL;
    
    int nDeno = -1;
    int *ADeno = NULL;
};

//Допускается:
//  1/2, 6, -12 - всё это свободные члены
//  x, -x, 1/2x, -1/2x, 6x, -12x^2, 51x10, 10*x^12 - всё это ввод коэффициентов и степеней икс
//Не допускается:
//  x+12x^2-12 - ввод коэффициентов без пробелов между ними
//Предполагается:
//  int m = -1;
//  int *C = NULL;
void InputPolynom(int &m, Q *&C)
{
    char *parse = InputString();
    
    int lettersCounted = 0;
    bool signInput = false;
    for (int i = 0; (i != 0 && parse[i-1] != '\0') || (i == 0 && parse[0] != '\0'); i++) {
        if (parse[i] == 'x')
        {
            int toSkipAhead = 1;
            int xDegree = -1;
            //DEGREE ANALTSIS
            int j = i;
            for (; parse[j] != ' ' && parse[j] != '\0'; j++) {
                //parse dergee from [i + j]
            } toSkipAhead = j - i - 1;
            if (j == i || (j-1 == i && (parse[j] == '\0')))
            {
                //degree = 1
                xDegree = 1;
                if (m < 1) {
                    C = (Q*)realloc(C, sizeof(Q)*2);
                    //for (int k = (m+1)*2; k < (xDegree+1)*2; k++)
                    //    C[k] = NULL;
                    for (int k = m+1; k < (xDegree+1); k++)
                    {
                        C[k].nNom = 0;
                        C[k].ANom = (int*)malloc(sizeof(int));
                        C[k].ANom[0] = 0;
                        
                        C[k].nDeno = 0;
                        C[k].ADeno = (int*)malloc(sizeof(int));
                        C[k].ADeno[0] = 0;
                    }
                    m = 1;
                }
            }
            else
            {
                bool atLeastOne = false;
                int resultInt = 0;
                int numberDegree = 0;
                for (int k = j-1; k > i; k--)
                {
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        resultInt += (parse[k] - 48) * power10(numberDegree);
                        numberDegree++;
                    }
                }
                if (!atLeastOne) {atLeastOne = true; resultInt = 1;}
                if (atLeastOne)
                {
                    xDegree = resultInt;
                    if (xDegree > m)
                    {
                        C = (Q*)realloc(C, sizeof(Q)*(xDegree+1));
                        //for (int k = (m+1)*2; k < (xDegree+1)*2; k++)
                        //    C[k] = NULL;
                        for (int k = (m+1); k < (xDegree+1); k++)
                        {
                            C[k].nNom = 0;
                            C[k].ANom = (int*)malloc(sizeof(int));
                            C[k].ANom[0] = 0;
                            
                            C[k].nDeno = 0;
                            C[k].ADeno = (int*)malloc(sizeof(int));
                            C[k].ADeno[0] = 0;
                        }
                        m = xDegree;
                    }
                    //C[xDegree*2] = NULL;
                    //C[xDegree*2 + 1] = NULL;
                    if (C[xDegree].nNom != 0)
                    {
                        C[xDegree].nNom = 0;
                        C[xDegree].ANom = (int*)malloc(sizeof(int));
                        C[xDegree].ANom[0] = 0;
                    }
                    if (C[xDegree].nDeno != 0)
                    {
                        C[xDegree].nDeno = 0;
                        C[xDegree].ADeno = (int*)malloc(sizeof(int));
                        C[xDegree].ADeno[0] = 0;
                    }
                }
            }
            //DEGREE ANALYSIS
            
            //COEFF ANALYSIS
            int slashPosition = -1;
            j = i;
            for (; parse[j] != ' ' && j >= 0 && parse[j] != '+' && parse[j] != '-'; j--) {
                //parse coeff from [j-i to j] [...]x
                if (parse[j] == '\\' || parse[j] == '/') {slashPosition = j;}
            }
            if (j == i || (j+1 == i))
            {
                //coeff = 1
                //C[xDegree*2] = !signInput ? 1 : -1;
                //C[xDegree*2 + 1] = 1;
                
                C[xDegree].sign = !signInput ? 0 : 1;
                
                C[xDegree].nNom = 0;
                if (C[xDegree].ANom == NULL)
                    C[xDegree].ANom = (int*)malloc(sizeof(int));
                C[xDegree].ANom[0] = 1;
                C[xDegree].nDeno = 0;
                if (C[xDegree].ADeno == NULL)
                    C[xDegree].ADeno = (int*)malloc(sizeof(int));
                C[xDegree].ADeno[0] = 1;
            }
            else
            {
                if (slashPosition != -1)
                {
                    //coeff = x/y
                    bool atLeastOne = false;
                    int numberDegree = 0;
                    int *resultA = NULL;
                    for (int k = slashPosition+1; k < i; k++)
                    {
                        if (parse[k] == 43)
                            signInput = false;
                        if (parse[k] == 45)
                            signInput = true;
                        
                        if (parse[k] >= 48 && parse[k] <= 57)
                        {
                            atLeastOne = true;
                            //resultInt += (parse[k] - 48) * power10(numberDegree);
                            resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                            resultA[numberDegree] = parse[k] - 48;
                            numberDegree++;
                        }
                    }
                    
                    if (atLeastOne)
                    {
                        if (!(numberDegree == 1 && resultA[0] == 0))
                        {
                            //C[xDegree*2] = 1;
                            //C[xDegree*2 + 1] = resultInt;
                            C[xDegree].nDeno = numberDegree-1;
                            C[xDegree].ADeno = resultA;
                            
                            atLeastOne = false;
                            numberDegree = 0;
                            resultA = NULL;
                            for (int k = j+1; k < slashPosition; k++)
                            {
                                if (parse[k] == 43)
                                    signInput = false;
                                if (parse[k] == 45)
                                    signInput = true;
                                
                                if (parse[k] >= 48 && parse[k] <= 57)
                                {
                                    atLeastOne = true;
                                    //resultInt += (parse[k] - 48) * power10(numberDegree);
                                    resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                                    resultA[numberDegree] = parse[k] - 48;
                                    numberDegree++;
                                }
                            }
                            
                            if (atLeastOne)
                            {
                                //if (signInput)
                                //    resultInt = -resultInt;
                                //C[xDegree*2] = resultInt;
                                C[xDegree].nNom = numberDegree-1;
                                C[xDegree].ANom = resultA;
                                C[xDegree].sign = signInput ? 1 : 0;
                            }
                        }
                    }
                }
                else
                {
                    //coeff = x
                    bool atLeastOne = false;
                    int numberDegree = 0;
                    int *resultA = NULL;
                    for (int k = j+1; k < i; k++)
                    {
                        if (parse[k] == 43)
                            signInput = false;
                        if (parse[k] == 45)
                            signInput = true;
                        
                        if (parse[k] >= 48 && parse[k] <= 57)
                        {
                            atLeastOne = true;
                            //resultInt += (parse[k] - 48) * power10(numberDegree);
                            resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                            resultA[numberDegree] = parse[k] - 48;
                            numberDegree++;
                        }
                    }
                    
                    if (atLeastOne)
                    {
                        //if (signInput)
                        //    resultInt = -resultInt;
                        //C[xDegree*2] = resultInt;
                        //C[xDegree*2 + 1] = 1;
                        C[xDegree].nNom = numberDegree-1;
                        C[xDegree].ANom = resultA;
                        C[xDegree].sign = signInput ? 1 : 0;
                        C[xDegree].nDeno = 0;
                        C[xDegree].ADeno[0] = 1;
                    }
                }
            }
            //COEFF ANALYSIS
            
            //now skipping the whole a/b*x^d fragment
            lettersCounted = 0;
            i += toSkipAhead;
        }
        else if ((parse[i] == ' ' || parse[i] == '\0') && lettersCounted > 0)
        {
            //we've done parsing a word
            //it's a number
            
            int slashPosition = -1;
            int j = i-1;
            for (; parse[j] != ' ' && j >= 0 && parse[j] != '+' && parse[j] != '-'; j--) {
                //parse coeff from [j-i to j] [...]x
                if (parse[j] == '\\' || parse[j] == '/') {slashPosition = j;}
            }
            if (slashPosition != -1)
            {
                bool atLeastOne = false;
                int numberDegree = 0;
                int *resultA = NULL;
                for (int k = slashPosition + 1; k < i; k++)
                {
                    if (parse[k] == 43)
                        signInput = false;
                    if (parse[k] == 45)
                        signInput = true;
                    
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        //resultInt += (parse[k] - 48) * power10(numberDegree);
                        resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                        resultA[numberDegree] = parse[k] - 48;
                        numberDegree++;
                    }
                }
                
                if (atLeastOne)
                {
                    if (!(numberDegree == 1 && resultA[0] == 0))
                    {
                        if (m < 0) {m = 0;
                            C = (Q*)malloc(sizeof(Q));}
                        C[0].nNom = 0;
                        C[0].ANom = (int*)malloc(sizeof(int));
                        C[0].ANom[0] = 1;
                        C[0].nDeno = numberDegree - 1;
                        C[0].ADeno = resultA;
                        //C[0] = 1;
                        //C[1] = resultInt;
                        
                        atLeastOne = false;
                        resultA = NULL;
                        numberDegree = 0;
                        for (int k = j + 1; k < slashPosition; k++)
                        {
                            if (parse[k] == 43)
                                signInput = false;
                            if (parse[k] == 45)
                                signInput = true;
                            
                            if (parse[k] >= 48 && parse[k] <= 57)
                            {
                                atLeastOne = true;
                                //resultInt += (parse[k] - 48) * power10(numberDegree);
                                resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                                resultA[numberDegree] = parse[k] - 48;
                                numberDegree++;
                            }
                        }
                        
                        if (atLeastOne)
                        {
                            //if (signInput)
                            //    resultInt = -resultInt;
                            //C[0] = resultInt;
                            C[0].sign = signInput ? 1 : 0;
                            if (C[0].ANom != NULL)
                                free(C[0].ANom);
                            C[0].nNom = numberDegree - 1;
                            C[0].ANom = resultA;
                        }
                    }
                }
            }
            else
            {
                bool atLeastOne = false;
                int *resultA = NULL;
                int numberDegree = 0;
                for (int k = j+1; k < i; k++)
                {
                    if (parse[k] >= 48 && parse[k] <= 57)
                    {
                        atLeastOne = true;
                        //resultInt += (parse[k] - 48) * power10(numberDegree);
                        resultA = (int*)realloc(resultA, sizeof(int)*(numberDegree+1));
                        resultA[numberDegree] = parse[k] - 48;
                        numberDegree++;
                    }
                }
                
                if (atLeastOne)
                {
                    if (m < 0) {m = 0;
                        C = (Q*)malloc(sizeof(Q));}
                    //if (m < 0) {m = 0;
                    //    C = (int*)malloc(sizeof(int)*2);}
                    //C[0] = resultInt;
                    //C[1] = 1;
                    C[0].sign = signInput ? 1 : 0;
                    //if (C[0].ANom != NULL)
                    //    free(C[0].ANom);
                    C[0].nNom = numberDegree - 1;
                    C[0].ANom = resultA;
                    C[0].nDeno = 0;
                    C[0].ADeno = (int*)malloc(sizeof(int));
                    C[0].ADeno[0] = 1;
                }
            }
            lettersCounted = 0;
        }
        else
        {
            if (parse[i] == 43)
                signInput = false;
            if (parse[i] == 45)
                signInput = true;
            
            //we're parsing a word
            lettersCounted++;
        }
    }
}

//Вывод в формате -12x^6 + 3/2x^3 + -x^1 + 1/2
//  (+ всегда между слагаемыми, а если слагамаемое отрицательно, то будет "... + -12/5x^2 + ..."
void PrintPolynom(int m, Q *C)
{
    if (m >= 0)
    {
        for (int i = m; i >= 0; i --)
        {
            //cout << "_____ " << i << " ____ " << C[i].nNom << " ____ " << C[i].ANom[0] << endl;
            if (!(C[i].nNom == 0 && C[i].ANom[0] == 0))
            {
                if (i != m)
                    cout << " + ";
                
                if (i != 0)
                {
                    if (C[i].nNom == 0 && C[i].ANom[0] == 1 && C[i].nDeno == 0 && C[i].ADeno[0] == 1 && C[i].sign == 0)
                    {
                        if (i != 1)
                            cout << "x^" << i;
                        else
                            cout << "x";
                    }
                    else if (C[i].nNom == 0 && C[i].ANom[0] == 1 && C[i].nDeno == 0 && C[i].ADeno[0] == 1 && C[i].sign == 1)
                    {
                        if (i != 1)
                            cout << "-x^" << i;
                        else
                            cout << "-x";
                    }
                    else
                    {
                        if (!(C[i].nDeno == 0 && (C[i].ADeno[0] == 1 || C[i].ADeno[0] == 0)))
                        {
                            if (C[i].sign == 1)
                                cout << "-";
                            for (int j = 0; j <= C[i].nNom; j++) {cout << C[i].ANom[j];}
                            cout << "/";
                            for (int j = 0; j <= C[i].nDeno; j++) {cout << C[i].ADeno[j];}
                            if (i != 1)
                                cout << "x^" << i;
                            else
                                cout << "x";
                        }
                        else
                        {
                            if (C[i].sign == 1)
                                cout << "-";
                            for (int j = 0; j <= C[i].nNom; j++) {cout << C[i].ANom[j];}
                            if (i != 1)
                                cout << "x^" << i;
                            else
                                cout << "x";
                        }
                    }
                }
                else
                {
                    if (!(C[i].nDeno == 0 && (C[i].ADeno[0] == 1 || C[i].ADeno[0] == 0)))
                    {
                        if (C[i].sign == 1)
                            cout << "-";
                        for (int j = 0; j <= C[i].nNom; j++) {cout << C[i].ANom[j];}
                        cout << "/";
                        for (int j = 0; j <= C[i].nDeno; j++) {cout << C[i].ADeno[j];}
                    }
                    else
                    {
                        if (C[i].sign == 1)
                            cout << "-";
                        for (int j = 0; j <= C[i].nNom; j++) {cout << C[i].ANom[j];}
                    }
                }
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Данный многочлен не существует, поэтому вывод на экран коэффициентов невозможен." << endl;
    }
}

void ADD_PP_P(int m1, Q *C1, int m2, Q *C2, int &mRes, Q *&CRes)
{
    mRes = -1;
    CRes = NULL;
    for (int i = 0; i <= m1 && i <= m2; i++)
    {
        if (C1[i].nNom >= 0 || C2[i].nNom >= 0)
        {
            if (!((C1[i].nNom == 0 && C1[i].ANom[0] == 0) || (C2[i].nNom == 0 && C2[i].ANom[0] == 0)))
            {
                int markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, *numerResult, *denoResult;
                
                ADD_QQ_Q(C1[i].sign, 0, C2[i].sign, 0, C1[i].nNom+1, C1[i].nDeno+1, C1[i].ANom, C1[i].ADeno, C2[i].nNom+1, C2[i].nDeno+1, C2[i].ANom, C2[i].ADeno,
                         markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult);
                
                /*puts("Получилась следующая дробь:");
                 cout << "Числитель:   ";
                 if (markResultNumer)
                 cout << "-";
                 
                 for (int i = 0; i < sizeResultNumer; i++)
                 cout << *(numerResult + i);
                 
                 cout << "\nЗнаменатель: ";
                 for (int i = 0; i < sizeResultDeno; i++)
                 cout << *(denoResult + i);
                 cout << endl;*/
                
                if (!(sizeResultNumer == 1 && numerResult[0] == 0))
                {
                    if (sizeResultNumer <= 0 || sizeResultDeno <= 0)
                    {
                        CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                        for (int j = mRes+1; j <= i; j++)
                        {
                            CRes[j].sign = 0;
                            CRes[j].nNom = 0;
                            CRes[j].ANom = (int*)malloc(sizeof(int));
                            CRes[j].ANom[0] = 0;
                            
                            CRes[j].nDeno = 0;
                            CRes[j].ADeno = (int*)malloc(sizeof(int));
                            CRes[j].ADeno[0] = 0;
                        }
                        mRes = i;
                    }
                    else
                    {
                        CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                        for (int j = mRes+1; j < i; j++)
                        {
                            CRes[j].sign = 0;
                            CRes[j].nNom = 0;
                            CRes[j].ANom = (int*)malloc(sizeof(int));
                            CRes[j].ANom[0] = 0;
                            
                            CRes[j].nDeno = 0;
                            CRes[j].ADeno = (int*)malloc(sizeof(int));
                            CRes[j].ADeno[0] = 0;
                        }
                        mRes = i;
                        
                        CRes[mRes].sign = markResultNumer;
                        CRes[mRes].nNom = sizeResultNumer-1;
                        CRes[mRes].ANom = numerResult;
                        CRes[mRes].nDeno = sizeResultDeno-1;
                        CRes[mRes].ADeno = denoResult;
                    }
                }
                else
                {
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                    for (int j = mRes+1; j <= i; j++)
                    {
                        CRes[j].sign = 0;
                        CRes[j].nNom = 0;
                        CRes[j].ANom = (int*)malloc(sizeof(int));
                        CRes[j].ANom[0] = 0;
                        
                        CRes[j].nDeno = 0;
                        CRes[j].ADeno = (int*)malloc(sizeof(int));
                        CRes[j].ADeno[0] = 0;
                    }
                    mRes = i;
                }
            }
            else
            {
                if (C1[i].nNom == 0 && C1[i].ANom[0] == 0)
                {
                    mRes = i;
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                    
                    CRes[mRes].sign = C2[mRes].sign;
                    CRes[mRes].nNom = C2[mRes].nNom;
                    CRes[mRes].ANom = (int*)malloc(sizeof(int)*CRes[mRes].nNom);
                    memcpy(CRes[mRes].ANom, C2[mRes].ANom, sizeof(int)*CRes[mRes].nNom);
                    
                    CRes[mRes].nDeno = C2[mRes].nDeno;
                    CRes[mRes].ADeno = (int*)malloc(sizeof(int)*CRes[mRes].nDeno);
                    memcpy(CRes[mRes].ADeno, C2[mRes].ADeno, sizeof(int)*CRes[mRes].nDeno);
                }
                else
                {
                    mRes = i;
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                    
                    CRes[mRes].sign = C1[mRes].sign;
                    CRes[mRes].nNom = C1[mRes].nNom;
                    CRes[mRes].ANom = (int*)malloc(sizeof(int)*CRes[mRes].nNom);
                    memcpy(CRes[mRes].ANom, C1[mRes].ANom, sizeof(int)*CRes[mRes].nNom);
                    
                    CRes[mRes].nDeno = C1[mRes].nDeno;
                    CRes[mRes].ADeno = (int*)malloc(sizeof(int)*CRes[mRes].nDeno);
                    memcpy(CRes[mRes].ADeno, C1[mRes].ADeno, sizeof(int)*CRes[mRes].nDeno);
                }
            }
        }
    }
    
    if (m1 > m2)
    {
        for (int i = m2+1; i <= m1; i++)
        {
            if (C1[i].nNom >= 0)
            {
                mRes = i;
                CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                
                CRes[mRes].sign = C1[mRes].sign;
                CRes[mRes].nNom = C1[mRes].nNom;
                CRes[mRes].ANom = C1[mRes].ANom;
                CRes[mRes].nDeno = C1[mRes].nDeno;
                CRes[mRes].ADeno = C1[mRes].ADeno;
            }
        }
    }
    else if (m2 > m1)
    {
        for (int i = m1+1; i <= m2; i++)
        {
            if (C2[i].nNom >= 0)
            {
                mRes = i;
                CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                
                CRes[mRes].sign = C2[mRes].sign;
                CRes[mRes].nNom = C2[mRes].nNom;
                CRes[mRes].ANom = C2[mRes].ANom;
                CRes[mRes].nDeno = C2[mRes].nDeno;
                CRes[mRes].ADeno = C2[mRes].ADeno;
            }
        }
    }
    
    //Удаляем нули из высших степеней, понижая её
    bool triggered = false;
    for (int i = mRes; i >= 0 && !triggered; i--)
    {
        triggered = !(CRes[i].nNom == 0 && CRes[i].ANom[0] == 0);
        if (!triggered)
        {
            free(CRes[i].ANom);
            free(CRes[i].ADeno);
            mRes--;
        }
    }
}

void SUB_PP_P(int m1, Q *C1, int m2, Q *C2, int &mRes, Q *&CRes)
{
    mRes = -1;
    CRes = NULL;
    for (int i = 0; i <= m1 && i <= m2; i++)
    {
        if (C1[i].nNom >= 0 || C2[i].nNom >= 0)
        {
            if (!((C1[i].nNom == 0 && C1[i].ANom[0] == 0) || (C2[i].nNom == 0 && C2[i].ANom[0] == 0)))
            {
                int markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, *numerResult, *denoResult;
                
                SUB_QQ_Q(C1[i].sign, 0, C2[i].sign, 0, C1[i].nNom+1, C1[i].nDeno+1, C1[i].ANom, C1[i].ADeno, C2[i].nNom+1, C2[i].nDeno+1, C2[i].ANom, C2[i].ADeno,
                         markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult);
                
                /*puts("Получилась следующая дробь:");
                 cout << "Числитель:   ";
                 if (markResultNumer)
                 cout << "-";
                 
                 for (int i = 0; i < sizeResultNumer; i++)
                 cout << *(numerResult + i);
                 
                 cout << "\nЗнаменатель: ";
                 for (int i = 0; i < sizeResultDeno; i++)
                 cout << *(denoResult + i);
                 cout << endl;*/
                
                if (!(sizeResultNumer == 1 && numerResult[0] == 0))
                {
                    if (sizeResultNumer <= 0 || sizeResultDeno <= 0)
                    {
                        CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                        for (int j = mRes+1; j <= i; j++)
                        {
                            CRes[j].sign = 0;
                            CRes[j].nNom = 0;
                            CRes[j].ANom = (int*)malloc(sizeof(int));
                            CRes[j].ANom[0] = 0;
                            
                            CRes[j].nDeno = 0;
                            CRes[j].ADeno = (int*)malloc(sizeof(int));
                            CRes[j].ADeno[0] = 0;
                        }
                        mRes = i;
                    }
                    else
                    {
                        CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                        for (int j = mRes+1; j < i; j++)
                        {
                            CRes[j].sign = 0;
                            CRes[j].nNom = 0;
                            CRes[j].ANom = (int*)malloc(sizeof(int));
                            CRes[j].ANom[0] = 0;
                            
                            CRes[j].nDeno = 0;
                            CRes[j].ADeno = (int*)malloc(sizeof(int));
                            CRes[j].ADeno[0] = 0;
                        }
                        mRes = i;
                        
                        CRes[mRes].sign = markResultNumer;
                        CRes[mRes].nNom = sizeResultNumer-1;
                        CRes[mRes].ANom = numerResult;
                        CRes[mRes].nDeno = sizeResultDeno-1;
                        CRes[mRes].ADeno = denoResult;
                    }
                }
                else
                {
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(i+1));
                    for (int j = mRes+1; j <= i; j++)
                    {
                        CRes[j].sign = 0;
                        CRes[j].nNom = 0;
                        CRes[j].ANom = (int*)malloc(sizeof(int));
                        CRes[j].ANom[0] = 0;
                        
                        CRes[j].nDeno = 0;
                        CRes[j].ADeno = (int*)malloc(sizeof(int));
                        CRes[j].ADeno[0] = 0;
                    }
                    mRes = i;
                }
            }
            else
            {
                if (C1[i].nNom == 0 && C1[i].ANom[0] == 0)
                {
                    mRes = i;
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                    
                    CRes[mRes].sign = C2[mRes].sign;
                    CRes[mRes].nNom = C2[mRes].nNom;
                    CRes[mRes].ANom = (int*)malloc(sizeof(int)*CRes[mRes].nNom);
                    memcpy(CRes[mRes].ANom, C2[mRes].ANom, sizeof(int)*CRes[mRes].nNom);
                    
                    CRes[mRes].nDeno = C2[mRes].nDeno;
                    CRes[mRes].ADeno = (int*)malloc(sizeof(int)*CRes[mRes].nDeno);
                    memcpy(CRes[mRes].ADeno, C2[mRes].ADeno, sizeof(int)*CRes[mRes].nDeno);
                }
                else
                {
                    mRes = i;
                    CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                    
                    CRes[mRes].sign = C1[mRes].sign;
                    CRes[mRes].nNom = C1[mRes].nNom;
                    CRes[mRes].ANom = (int*)malloc(sizeof(int)*CRes[mRes].nNom);
                    memcpy(CRes[mRes].ANom, C1[mRes].ANom, sizeof(int)*CRes[mRes].nNom);
                    
                    CRes[mRes].nDeno = C1[mRes].nDeno;
                    CRes[mRes].ADeno = (int*)malloc(sizeof(int)*CRes[mRes].nDeno);
                    memcpy(CRes[mRes].ADeno, C1[mRes].ADeno, sizeof(int)*CRes[mRes].nDeno);
                }
            }
        }
    }
    
    if (m1 > m2)
    {
        for (int i = m2+1; i <= m1; i++)
        {
            if (C1[i].nNom >= 0)
            {
                mRes = i;
                CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                
                CRes[mRes].sign = C1[mRes].sign;
                CRes[mRes].nNom = C1[mRes].nNom;
                CRes[mRes].ANom = C1[mRes].ANom;
                CRes[mRes].nDeno = C1[mRes].nDeno;
                CRes[mRes].ADeno = C1[mRes].ADeno;
            }
        }
    }
    else if (m2 > m1)
    {
        for (int i = m1+1; i <= m2; i++)
        {
            if (C2[i].nNom >= 0)
            {
                mRes = i;
                CRes = (Q*)realloc(CRes, sizeof(Q)*(mRes+1));
                
                CRes[mRes].sign = C2[mRes].sign;
                CRes[mRes].nNom = C2[mRes].nNom;
                CRes[mRes].ANom = C2[mRes].ANom;
                CRes[mRes].nDeno = C2[mRes].nDeno;
                CRes[mRes].ADeno = C2[mRes].ADeno;
            }
        }
    }
    
    //Удаляем нули из высших степеней, понижая её
    bool triggered = false;
    for (int i = mRes; i >= 0 && !triggered; i--)
    {
        triggered = !(CRes[i].nNom == 0 && CRes[i].ANom[0] == 0);
        if (!triggered)
        {
            free(CRes[i].ANom);
            free(CRes[i].ADeno);
            mRes--;
        }
    }
}

void naturalNum() // Модуль, в котором идут операции с натуральными числами
{
    string module[14] = { "1. Сравнение натуральных чисел ",
        "2. Проверка на ноль",
        "3. Добавление 1",
        "4. Сложение натуральных чисел",
        "5. Вычитание из первого большего натурального...",
        "6. Умножение натурального числа на цифру",
        "7. Умножение натурального числа на 10^k",
        "8. Умножение натуральных чисел",
        "9. Вычитание из натурального другого натурального...",
        "10. Вычисление первой цифры деления большего...",
        "11. Частное от деления большего натурального числа...",
        "12. Остаток от деления большего натурального числа...",
        "13. НОД натуральных чисел",
        "14. НОК натуральных чисел" };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    // Переменные для кейсов
    int n0, n1, n2, n4, n5, n6, n10, n11, k, D, dig, m, nresult, sign = -1,
    *A = NULL,
    *A0 = NULL,
    *A1 = NULL,
    *A2 = NULL,
    *A3 = NULL,
    *A5 = NULL,
    *A6 = NULL,
    *A10 = NULL,
    *A11 = NULL,
    *answer = NULL,
    *result = NULL,
    n3 = 0;
    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Внимание! Троеточие означает, что полный текст задания не поместился.\n"
                 "Для прочтения полного текста выберите соответствующий пункт меню.\n"
                 "Выберите функцию, которую хотите запустить:\n");
            
            for (int i = 0; i < 14; i++)
            {
                if (i != index)
                    cout << " " << module[i] << "\n";
                else
                    cout << ">" << module[i] << "\n";
            }
            
            puts("\nДля возврата в прошлое меню нажмите Esc.");
        }
        
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 13)
                    index++;
                break;
                
#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 53:
                index = 4;
                break;
            case 54:
                index = 5;
                break;
            case 55:
                index = 6;
                break;
            case 56:
                index = 7;
                break;
            case 57:
                index = 8;
                break;
            case 65:
                index = 9;
                break;
            case 66:
                index = 10;
                break;
            case 67:
                index = 11;
                break;
            case 68:
                index = 12;
                break;
            case 69:
                index = 13;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                system("cls");
                switch (index)
            {
                case 0:
                    // Диана Щебет, группа 7307
                    //ввод количества цифр в числах
                    puts("Сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе.");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    D = COM_NN_D(n1, n2, A1, A2);
                    printf("\nРезультат сравнения = %d\n", D);
                    system("pause");
                    break;
                    
                case 1:
                    // Евгений Сысенко, группа 7307
                    //ввод количества цифр в числах
                    puts("Проверка на ноль: если число не равно нулю, то «да» иначе «нет»");
                    
                    printf("Введите число: ");
                    inputNumber(sign, n1, A1);
                    
                    D = NZER_N_B(n1, A1);
                    
                    if (D)
                        cout << "Результат: число не равно нулю";
                    else
                        cout << "Результат: число равно нулю";
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 2:
                    // Дмитрий Богряков, группа 7301
                    // m - номер старшей позиции (размер_массива)
                    // *A - указатель на начало массива цифр
                    // i -переменная для цикла
                    puts("Добавление 1 к натуральному числу");
                    
                    printf("Введите число: ");
                    inputNumber(sign, m, A);
                    
                    m = ADD_1N_N(m, A);
                    
                    printf("Полученное число: ");
                    for (int i = 0; i < m; i++)
                    {
                        printf("%d", A[i]);
                    }
                    printf("\n");
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 3:
                    // Диана Щебет, группа 7307
                    //ввод количества цифр в числах
                    puts("Сложение натуральных чисел");
                    
                    n5 = 1;
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    ADD_NN_N(n1, n2, n5, A1, A2, A5);
                    
                    printf("\nОтвет: ");
                    for (int i = 0; i<n5; i++)
                        printf("%d", A5[i]);
                    
                    free(A1);
                    free(A2);
                    free(A5);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 4:
                    // Диана Щебет, группа 7307
                    // ввод количества цифр в числах
                    n3 = 1;
                    puts("Вычитание из первого большего натурального числа второго меньшего или равного");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    D = COM_NN_D(n1, n2, A1, A2);
                    //  printf("Comparison result= %d\n", D);
                    SUB_NN_N(n1, n2, A1, A2, D, &n3, &A3);
                    printf("\nОтвет: ");
                    for (int i = 0; i<n3; i++)
                    {
                        printf("%d", A3[i]);
                        // printf("%d\n",n3);
                    }
                    puts("");
                    free(A1);
                    free(A2);
                    free(A3);
                    system("pause");
                    break;
                    
                case 5:
                    // Евгений Сысенко, группа 7307
                    //ввод количества цифр в числах
                    puts("Умножение натурального числа на цифру");
                    
                    printf("Введите число: ");
                    inputNumber(sign, n1, A1);
                    
                    printf("Введите цифру: ");
                    _scanf("%d", &dig);
                    
                    MUL_ND_N(n1, dig, A1, &n3, &answer);
                    printf("Ответ: ");
                    for (int i = 0; i<n3; i++)
                        printf("%d", answer[i]);
                    puts("");
                    free(A1);
                    free(answer);
                    system("pause");
                    break;
                    
                case 6:
                    // Диана Щебет, группа 7307
                    //ввод количества цифр в числах
                    puts("Умножение натурального числа на 10^k");
                    
                    printf("Введите число: ");
                    inputNumber(sign, n1, A1);
                    
                    cout << "Введите степень k: ";
                    inputDig(k);
                    
                    n10 = 1;
                    MUL_Nk_N(n1, A1, k, &A10, &n10);
                    puts("");
                    cout << "Ответ: ";
                    for (int i = 0; i < n10; i++)
                        cout << *(A10 + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 7:
                    // Максим кортель, группа 7301
                    puts("Умножение натуральных чисел");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n0, A0);
                    printf("Введите второе число: ");
                    inputNumber(sign, n1, A1);
                    
                    MUL_NN_N(n0, n1, A0, A1, nresult, result);
                    
                    cout << "Ответ: ";
                    for (int i = 0; i < nresult; i++)
                        cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 8:
                    // Евгений Сысенко, группа 7307
                    //ввод количества цифр в числах
                    n3 = 1;
                    n4 = 0;
                    n5 = 1;
                    puts("Вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    printf("Введите цифру: ");
                    inputDig(dig);
                    
                    D = COM_NN_D(n1, n2, A1, A2);
                    MUL_ND_N(n2, dig, A2, &n4, &answer);
                    SUB_NDN_N(answer, A1, n1, n4, D, &A5, &n5);
                    
                    printf("Ответ: ");
                    
                    for (int i = 0; i<n5; i++)
                    {
                        printf("%d", A5[i]);
                    }
                    
                    free(A1);
                    free(A2);
                    free(answer);
                    free(A5);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 9:
                    // Диана Щебет, группа 7307
                    n6 = 1;
                    n11 = 1;
                    puts("Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10 ^ k, \n"
                         "где k - номер позиции этой цифры(номер считается с нуля)");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    D = COM_NN_D(n1, n2, A1, A2);
                    
                    DIV_NN_Dk(n1, n2, A1, A2, D, &A11, &n11);
                    if (A11 != NULL)
                    {
                        printf("\nОтвет = ");
                        printf("%d", A11[0]);
                    }
                    else
                    {
                        printf("Ошибка!");
                    }
                    
                    free(A1);
                    free(A2);
                    free(A6);
                    free(A11);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 10:
                    // Никита Исаенко, группа 7305
                    puts("Частное от деления большего натурального числа на меньшее или равное натуральное с остатком(делитель отличен от нуля)");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    notZero(sign, n2, A2);
                    
                    DIV_NN_N(n1, A1, n2, A2, nresult, result);
                    
                    cout << "Ответ: ";
                    for (int i = 0; i < nresult; i++)
                        cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 11:
                    // Никита Исаенко, группа 7305
                    puts("Остаток от деления большего натурального числа на меньшее или равное натуральное с остатком(делитель отличен от нуля))");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    notZero(sign, n2, A2);
                    
                    MOD_NN_N(n1, A1, n2, A2, nresult, result);
                    
                    cout << "Ответ: ";
                    if (nresult == 0)
                        cout << 0;
                    else
                        for (int i = 0; i < nresult; i++)
                            cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 12:
                    // Дмитрий Кезлинг, группа 7305
                    puts("НОД натуральных чисел");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    GCF_NN_N(n1, n2, A1, A2, nresult, result);
                    
                    cout << "Ответ: ";
                    for (int i = 0; i < nresult; i++)
                        cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 13:
                    // Дмитрий Кезлинг, группа 7305
                    puts("НОК натуральных чисел");
                    
                    printf("Введите первое число: ");
                    inputNumber(sign, n1, A1);
                    printf("Введите второе число: ");
                    inputNumber(sign, n2, A2);
                    
                    LCM_NN_N(n1, n2, A1, A2, nresult, result);
                    
                    cout << "Ответ: ";
                    for (int i = 0; i < nresult; i++)
                        cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
}

void totalNum() // Модуль, в котором идёт работа с целыми числами
{
    string module[10] = { "1. Абсолютная величина числа",
        "2. Определение положительности числа...",
        "3. Умножение целого на (-1)",
        "4. Преобразование натурального в целое",
        "5. Преобразование целого неотрицательного в натуральное",
        "6. Сложение целых чисел",
        "7. Вычитание целых чисел",
        "8. Умножение целых чисел",
        "9. Частное от деления большего целого числа на меньшее...",
        "10. Остаток от деления большего целого числа на меньшее..." };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    // Переменные для кейсов
    int *A = NULL, *arr = NULL, *first = NULL, *second = NULL, *result = NULL, *sum1 = NULL, *sum2 = NULL, *sum3 = NULL, *arr1 = NULL, *arr2 = NULL, *arr3 = NULL, *sign1, *sign2, *sign3,
    b = 0, n = 0,
    sign = 0, sum, sign11, tmpCase, sizeFirst, sizeSecond, markFisrt, markSecond, sizeResult, markResult;
    
    
    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Звёздочка, идущая после цифры, обозначает недоступность данной функции.");
            puts("Внимание! Троеточие означает, что полный текст задания не поместился.\n"
                 "Для прочтения полного текста выберите соответствующий пункт меню.\n"
                 "Выберите функцию, которую хотите запустить:\n");
            
            for (int i = 0; i < 10; i++)
            {
                if (i != index)
                    cout << " " << module[i] << "\n";
                else
                    cout << ">" << module[i] << "\n";
            }
            
            puts("\nДля возврата в прошлое меню нажмите Esc.");
        }
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 9)
                    index++;
                break;
               
#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 53:
                index = 4;
                break;
            case 54:
                index = 5;
                break;
            case 55:
                index = 6;
                break;
            case 56:
                index = 7;
                break;
            case 57:
                index = 8;
                break;
            case 65:
                index = 9;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                system("cls");
                switch (index)
            {
                case 0:
                    // Стас Смирнов, группа 7301
                    puts("Абсолютная величина числа, результат - натуральное");
                    
                    printf("Введите число: ");
                    inputNumber(b, n, A);
                    
                    ABS_Z_N(b, n, A);
                    
                    cout << "Полученное число: ";
                    for (int i = 0; i < n; i++)
                        cout << *(A + i);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 1:
                    // Алекандр Трифонов, группа 7301
                    puts("Определение положительности числа (2 - положительное, 0 — равное нулю, 1 - отрицательное)");
                    
                    printf("Введите число: ");
                    inputNumber(sign, sum, arr);
                    
                    sign11 = POZ_Z_D(sign, sum, arr);
                    cout << "\n";
                    cout << "Знак числа: " << sign11 << "\n";
                    
                    free(arr);
                    system("pause");
                    break;
                    
                case 2:
                    // Александр Трифонов, группа 7301
                    puts("Умножение целого на (-1)");
                    
                    cout << "Введите целое число: ";
                    inputNumber(sign, sum, arr);
                    
                    MUL_ZM_Z(&sign, sum, arr);
                    
                    free(arr);
                    system("pause");
                    break;
                    
                case 3:
                    // Стас Смирнов, группа 7301
                    puts("Перевод из натурального числа в целое, результат - знак числа");
                    
                    cout << "Введите целое число: ";
                    inputNumber(b, n, A);
                    
                    if (TRANS_N_Z(b, n, A) == 2)
                        cout << "Число введено некорректно, т.к. оно должно быть натуральным";
                    else
                    {
                        cout << "Результат - знак числа: " << TRANS_N_Z(b, n, A);
                        puts(" ");
                        cout << "Число: ";
                        for (int i = 0; i < n; i++)
                            cout << A[i];
                        cout << endl;
                    }
                    
                    puts("");
                    free(A);
                    
                    system("pause");
                    break;
                    
                case 4:
                    // Стас Смирнов, группа 7301
                    puts("Перевод из целого неотрицательного числа в натуральное, результат - натуральное число");
                    
                    cout << "Введите целое число: ";
                    inputNumber(b, n, A);
                    
                    tmpCase = TRANS_Z_N(b, n, A);
                    if (tmpCase == -1)
                        cout << "Число введено некорректно, т.к. оно должно быть натуральным";
                    if (tmpCase == -2)
                        cout << "Число введено некорректно, т.к. число 0 нельзя перевести в натуральное";
                    if ((tmpCase != -1) && (tmpCase != -2))
                    {
                        cout << "Результат - массив с цифрами и старшая степень: ";
                        for (int i = 0; i < n; i++)
                            cout << A[i];
                        cout << endl;
                        cout << "Степень числа - " << n << endl;
                    }
                    
                    free(A);
                    puts("");
                    system("pause");
                    break;
                    
                case 5:
                    // Александр Трифонов, группа 7301
                    sum1 = (int*)malloc(1 * sizeof(int));
                    sum2 = (int*)malloc(sizeof(int) * 1);
                    sum3 = (int*)malloc(sizeof(int) * 1);
                    sign1 = (int*)malloc(sizeof(int) * 1);
                    sign2 = (int*)malloc(sizeof(int) * 1);
                    sign3 = (int*)malloc(sizeof(int) * 1);
                    *sum1 = 0;
                    *sum2 = 0;
                    *sum3 = 0;
                    
                    puts("Сложение целых чисел");
                    cout << "Введите первое целое число: ";
                    inputNumber(*sign1, *sum1, arr1);
                    cout << "Введите второе целое число: ";
                    inputNumber(*sign2, *sum2, arr2);
                    
                    ADD_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
                    cout << "Результат: ";
                    
                    if (*sign3 == 1) {
                        cout << "-";
                    }
                    for (int i = 0; i < (*sum3); i++) {
                        cout << arr3[i];
                    }
                    
                    cout << "\n\n";
                    system("pause");
                    break;
                    
                case 6:
                    // Александр Трифонов, группа 7301
                    sum1 = (int*)malloc(1 * sizeof(int));
                    sum2 = (int*)malloc(sizeof(int) * 1);
                    sum3 = (int*)malloc(sizeof(int) * 1);
                    sign1 = (int*)malloc(sizeof(int) * 1);
                    sign2 = (int*)malloc(sizeof(int) * 1);
                    sign3 = (int*)malloc(sizeof(int) * 1);
                    *sum1 = 0;
                    *sum2 = 0;
                    *sum3 = 0;
                    
                    cout << "Введите первое целое число: ";
                    inputNumber(*sign1, *sum1, arr1);
                    cout << "Введите второе целое число: ";
                    inputNumber(*sign2, *sum2, arr2);
                    
                    SUB_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
                    cout << "Результат: ";
                    
                    if (*sign3 == 1) {
                        cout << "-";
                    }
                    for (int i = 0; i < (*sum3); i++) {
                        cout << arr3[i];
                    }
                    
                    cout << "\n\n";
                    system("pause");
                    break;
                    
                case 7:
                    // Максим Кортель, группа 7301
                    puts("Умножение целых чисел");
                    
                    cout << "Введите первое целое число: ";
                    inputNumber(markFisrt, sizeFirst, first);
                    cout << "Введите второе целое число: ";
                    inputNumber(markSecond, sizeSecond, second);
                    
                    sizeResult = 0;
                    result = NULL;
                    MUL_ZZ_Z(sizeFirst, sizeSecond, first, second, markFisrt, markSecond, sizeResult, result, markResult);
                    
                    cout << "Ответ: ";
                    if (markResult)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResult; i++)
                        cout << *(result + i);
                    
                    free(result);
                    free(first);
                    free(second);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 8:
                    // Дмитрий Кезлинг, группа 7305
                    puts("Частное от деления большего целого числа на меньшее или равное натуральное с остатком (делитель отличен от нуля)");
                    
                    cout << "Введите первое целое число: ";
                    inputNumber(markFisrt, sizeFirst, first);
                    cout << "Введите второе целое число: ";
                    markSecond = -1;
                    notZero(markSecond, sizeSecond, second);
                    markSecond = 0;
                    
                    DIV_ZZ_Z(markFisrt, markSecond, sizeFirst, sizeSecond, first, second, markResult, sizeResult, result);
                    
                    cout << "Ответ: ";
                    if (markResult)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResult; i++)
                        cout << *(result + i);
                    
                    free(result);
                    free(first);
                    free(second);
                    
                    puts("");
                    system("pause");
                    
                    break;
                    
                case 9:
                    // Дмитрий Кезлинг, группа 7305
                    puts("Остаток от деления большего целого числа на меньшее или равное натуральное с остатком (делитель отличен от нуля)");
                    
                    cout << "Введите первое целое число: ";
                    inputNumber(markFisrt, sizeFirst, first);
                    cout << "Введите второе целое число: ";
                    markSecond = -1;
                    notZero(markSecond, sizeSecond, second);
                    markSecond = 0;
                    
                    MOD_ZZ_Z(markFisrt, markSecond, sizeFirst, sizeSecond, first, second, markResult, sizeResult, result);
                    
                    cout << "Ответ: ";
                    if (markResult)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResult; i++)
                        cout << *(result + i);
                    
                    puts("");
                    system("pause");
                    break;
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
}

void fractionNum() // Модуль, в котором идёт работа с дробями
{
    string module[8] = { "1. Сокращение дроби",
        "2. Проверка на целое",
        "3. Преобразование целого в дробное",
        "4. Преобразование дробного в целое",
        "5. Сложение дробей",
        "6. Вычитание дробей",
        "7. Умножение дробей",
        "8. Деление дробей (делитель отличен от нуля)" };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    // Переменные для кейсов
    int *A0_1, *A1_1, *A0_result, *A1_result, *A = NULL, *A0 = NULL, *A1 = NULL, **result = NULL,
    b = 0, b1, b2, b_1, n0, n0_1, n1_1, n0_result, n1_result, b_result, b0_result, b1_result, n = -1, n1 = -1, skipSign = -1;
    int markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, *numerResult, *denoResult, markResult;

    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Звёздочка, идущая после цифры, обозначает недоступность данной функции.");
            puts("Выберите функцию, которую хотите запустить:\n");
            
            for (int i = 0; i < 8; i++)
            {
                if (i != index)
                    cout << " " << module[i] << "\n";
                else
                    cout << ">" << module[i] << "\n";
            }
            
            puts("\nДля возврата в прошлое меню нажмите Esc.");
        }
        
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 7)
                    index++;
                break;
                
#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 53:
                index = 4;
                break;
            case 54:
                index = 5;
                break;
            case 55:
                index = 6;
                break;
            case 56:
                index = 87;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                system("cls");
                switch (index)
            {
                case 0:
                    // Дмитрий Кезлинг, группа 7305
                    puts("Сокращение дроби");
                    
                    printf("Пожалуйста, введите числитель: ");
                    inputNumber(b1, n, A);
                    printf("Пожалуйста, введите знаменатель: ");
                    notZero(b2, n1, A1);
                    
                    RED_QQ_Q(b1, b2, n, n1, A, A1, markResult, sizeResultNumer, sizeResultDeno, numerResult, denoResult);
                    
                    puts("Получилась следующая дробь:");
                    cout << "Числитель:   ";
                    
                    if (markResult)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResultNumer; i++)
                        cout << *(numerResult + i);
                    
                    cout << "\nЗнаменатель: ";
                    for (int i = 0; i < sizeResultDeno; i++)
                        cout << *(denoResult + i);
                    
                    puts("");
                    system("pause");
                    
                    free(A);
                    free(A1);
                    break;
                    
                case 1:
                    // Рустам Аминов, группа 7307
                    puts("Проверка на целое, если рациональное число является целым, то «да», иначе «нет»");
                    printf("Введите числитель: ");
                    inputNumber(b1, n, A);
                    
                    do
                    {
                        printf("Введите знаменатель: ");
                        inputNumber(b2, n1, A1);
                        if (*(A1) == 0)
                            puts("Введите знаменатель, отличный от нуля!");
                    } while (*(A1) == 0);
                    
                    if (b1 == b2)
                        b = 0;
                    else
                        b = 1;
                    
                    if (INT_Q_B(b, n, A, n1, A1) == 1)//То ради чего все это делалось
                        puts("Да, число целое");
                    else
                        puts("Нет, число не целое");
                    
                    free(A); //Освобождение памяти
                    free(A1);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 2:
                    // Стас Смирнов, группа 7301
                    puts("Преобразование целого в дробное");
                    
                    cout << "Введите число:";
                    inputNumber(b, n, A);
                    
                    A1 = (int*)malloc((n + 1) * sizeof(int));
                    
                    cout << "Результат - число: " << endl;
                    cout << "Числитель : ";
                    if (b == 1) cout << "-";
                    for (int i = 0; i < n; i++)
                        cout << A[i];
                    cout << endl;
                    cout << "Знаменатель : ";
                    cout << TRANS_Z_Q(b, n, A, n1, A1);
                    free(A);
                    free(A1);
                    
                    puts("\n");
                    system("pause");
                    break;
                    
                case 3:
                    // Рустам Аминов, группа 7307
                    puts("Преобразование дробного в целое (если знаменатель равен 1)");
                    
                    printf("Пожалуйста, введите числитель: ");
                    inputNumber(b, n, A);
                    printf("Пожалуйста, введите знаменатель: ");
                    notZero(b, n1, A1);
                    
                    TRANS_Q_Z(b, n, A, n1, A1);//То ради чего все это делалось
                    free(A); //Освобождение памяти
                    free(A1);
                    
                    system("pause");
                    break;
                    
                case 4:
                    // Дмитрий Кезлинг, 7305
                    puts("Сложение дробей");
                    printf("Пожалуйста, введите числитель первой дроби: ");
                    inputNumber(b1, n0, A0);
                    printf("Пожалуйста, введите знаменатель первой дроби: ");
                    notZero(b2, n0_1, A0_1);
                    
                    
                    printf("Пожалуйста, введите числитель второй дроби: ");
                    inputNumber(b, n1, A1);
                    printf("Пожалуйста, введите знаменатель второй дроби: ");
                    notZero(b_1, n1_1, A1_1);
                    
                    ADD_QQ_Q(b1, b2, b, b_1, n0, n0_1, A0, A0_1, n1, n1_1, A1, A1_1, markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult);
                    
                    puts("Получилась следующая дробь:");
                    cout << "Числитель:   ";
                    if (markResultNumer)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResultNumer; i++)
                        cout << *(numerResult + i);
                    
                    cout << "\nЗнаменатель: ";
                    for (int i = 0; i < sizeResultDeno; i++)
                        cout << *(denoResult + i);
                    
                    puts("");
                    system("pause");
                    
                    free(A0);
                    free(A1);
                    free(A0_1);
                    free(A1_1);
                    break;
                case 5:
                    // Дмитрий Кезлинг, 7305
                    puts("Вычитание дробей");
                    printf("Пожалуйста, введите числитель первой дроби: ");
                    inputNumber(b1, n0, A0);
                    printf("Пожалуйста, введите знаменатель первой дроби: ");
                    notZero(b2, n0_1, A0_1);
                    
                    
                    printf("Пожалуйста, введите числитель второй дроби: ");
                    inputNumber(b, n1, A1);
                    printf("Пожалуйста, введите знаменатель второй дроби: ");
                    notZero(b_1, n1_1, A1_1);
                    
                    SUB_QQ_Q(b1, b2, b, b_1, n0, n0_1, A0, A0_1, n1, n1_1, A1, A1_1, markResultNumer, markResultDeno, sizeResultNumer, sizeResultDeno, numerResult, denoResult);
                    
                    puts("Получилась следующая дробь:");
                    cout << "Числитель:   ";
                    if (markResultNumer)
                        cout << "-";
                    
                    for (int i = 0; i < sizeResultNumer; i++)
                        cout << *(numerResult + i);
                    
                    if (markResultDeno)
                        cout << "-";
                    cout << "\nЗнаменатель: ";
                    for (int i = 0; i < sizeResultDeno; i++)
                        cout << *(denoResult + i);
                    
                    puts("");
                    system("pause");
                    
                    free(A0);
                    free(A1);
                    free(A0_1);
                    free(A1_1);
                    break;
                    
                case 6:
                    // Анна Волкова, группа 7307
                    puts("Умножение дробей");
                    
                    printf("Введите числитель первой дроби: ");
                    inputNumber(b, n0, A0);
                    printf("Введите знаменатель первой дроби: ");
                    notZero(skipSign, n1, A1);
                    
                    printf("\nВведите числитель второй дроби: ");
                    inputNumber(b_1, n0_1, A0_1);
                    printf("Введите знаменатель второй дроби: ");
                    notZero(skipSign, n1_1, A1_1);
                    
                    MUL_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b_result, n0_result, n1_result, A0_result, A1_result); //умножение дробей
                    
                    printf("\nРезультат: ");
                    
                    if (b != b_1)
                        cout << "-";
                    
                    for (int i = 0; i<n0_result; i++)
                        printf("%d", A0_result[i]);
                    printf("/");
                    for (int i = 0; i<n1_result; i++)
                        printf("%d", A1_result[i]);
                    
                    free(A0);
                    free(A1);
                    free(A0_result);
                    free(A1_result);
                    free(A1_1);
                    free(A0_1);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 7:
                    // Анна Волкова, группа 7307
                    puts("Деление дробей");
                    printf("Введите числитель первой дроби: ");
                    notZero(b, n0, A0);
                    printf("Введите знаменатель первой дроби: ");
                    inputNumber(skipSign, n1, A1);
                    
                    printf("\nВведите числитель второй дроби: ");
                    inputNumber(b_1, n0_1, A0_1);
                    printf("Введите знаменатель второй дроби: ");
                    notZero(skipSign, n1_1, A1_1);
                    
                    DIV_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b0_result, b1_result, n0_result, n1_result, A0_result, A1_result);  //Деление дробей
                    
                    printf("\nРезультат: ");
                    if (b0_result != b1_result)
                        printf("-");
                    
                    for (int i = 0; i<n0_result; i++)
                        printf("%d", A0_result[i]);
                    printf("/");
                    for (int i = 0; i<n1_result; i++)
                        printf("%d", A1_result[i]);
                    
                    free(A0);
                    free(A1);
                    free(A0_result);
                    free(A1_result);
                    free(A1_1);
                    free(A0_1);
                    
                    puts("");
                    system("pause");
                    break;
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
    
}

void polyNum() // Модуль, в котором идёт работа с многочленами
{
    string module[13] = { "1. Сложение многочленов",
        "2. Вычитание многочленов",
        "3*. Умножение многочлена на рациональное число",
        "4. Умножение многочлена на x^k",
        "5. Старший коэффициент многочлена",
        "6*. Степень многочлена",
        "7*. Вынесение из многочлена НОК знаменателей...",
        "8*. Умножение многочленов",
        "9*. Частное от деления многочлена на многочлен...",
        "10*. ВОстаток от деления многочлена на многочлен ...",
        "11*. НОД многочленов",
        "12. Производная многочлена",
        "13*. Преобразование многочлена — кратные корни в простые" };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    // Переменные для case
    int m,
        *C = NULL;
    
    int m1 = -1, m2 = -1, mRes = -1;
    Q *C1 = NULL, *C2 = NULL, *CRes = NULL;
    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Звёздочка, идущая после цифры, обозначает недоступность данной функции.");
            puts("Внимание! Троеточие означает, что полный текст задания не поместился.\n"
                 "Для прочтения полного текста выберите соответствующий пункт меню.\n"
                 "Выберите функцию, которую хотите запустить:\n");
            
            for (int i = 0; i < 13; i++)
            {
                if (i != index)
                    cout << " " << module[i] << "\n";
                else
                    cout << ">" << module[i] << "\n";
            }
            
            puts("\nДля возврата в прошлое меню нажмите Esc.");
        }
        
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 12)
                    index++;
                break;
                
#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 53:
                index = 4;
                break;
            case 54:
                index = 5;
                break;
            case 55:
                index = 6;
                break;
            case 56:
                index = 7;
                break;
            case 57:
                index = 8;
                break;
            case 65:
                index = 9;
                break;
            case 66:
                index = 10;
                break;
            case 67:
                index = 11;
                break;
            case 68:
                index = 12;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                system("cls");
                switch (index)
            {
                case 0:
                    cout << "Сложение многочленов." << endl << endl;
                    
                    m1 = -1;
                    m2 = -1;
                    mRes = -1;
                    C1 = NULL;
                    C2 = NULL;
                    CRes = NULL;
                    
                    cin.ignore();
                    //  5/6x^5 + 3x^4 - x + 12
                    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
                    InputPolynom(m1, C1);
                    cout << "   +" << endl;
                    //  5/6x^5 - 3x^4 + x + 12
                    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
                    InputPolynom(m2, C2);
                    ADD_PP_P(m1, C1, m2, C2, mRes, CRes);
                    
                    cout << "   =" << endl;
                    cout << "Результат: " << endl;
                    PrintPolynom(mRes, CRes);
                    
                    system("pause");
                    break;
                    
                case 1:
                    cout << "Вычитание многочленов." << endl << endl;
                    
                    m1 = -1;
                    m2 = -1;
                    mRes = -1;
                    C1 = NULL;
                    C2 = NULL;
                    CRes = NULL;
                    
                    cin.ignore();
                    //  5/6x^5 + 3x^4 - x + 12
                    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
                    InputPolynom(m1, C1);
                    cout << "   -" << endl;
                    //  5/6x^5 - 3x^4 + x + 12
                    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
                    InputPolynom(m2, C2);
                    SUB_PP_P(m1, C1, m2, C2, mRes, CRes);
                    
                    cout << "   =" << endl;
                    cout << "Результат: " << endl;
                    PrintPolynom(mRes, CRes);
                    
                    system("pause");
                    break;
                    
                case 2:
                    cout << "Умножение многочлена на рациональное число." << endl << endl;
                    break;
                    
                case 3:
                    cout << "Умножение многочлена на x^k." << endl << endl;
                    break;
                    
                case 4:
                    cout << "Старший коэффициент многочлена." << endl << endl;
                    
                    // Дмитрий Богряков, группа 7307
                    puts("Старший коэффициент многочлена");
                    cout << "Введите степень многочлена: ";
                    cin >> m;
                    cout << "Введите коэффициенты: \n";
                    C = (int*)realloc(C, (m + 1) * sizeof(int));
                    for (int i = 0; i<m; i++)
                    {
                        cout << "c[" << i + 1 << "] = ";
                        cin >> *(C + i);
                    }
                    LED_P_Q(m, C);
                    system("pause");
                    break;
                    
                case 5:
                    cout << "Степень многочлена." << endl << endl;
                    
                    puts("Степень многочлена");
                    
                    cout << "Введите степень многочлена: ";
                    cin >> m;
                    cout << "Введите коэффициенты: \n";
                    C = (int*)realloc(C, (m + 1) * sizeof(int));
                    for (int i = 0; i<m; i++)
                    {
                        cout << "c[" << i + 1 << "] = ";
                        cin >> *(C + i);
                    }
                    cout << "Ответ: " << DEG_P_N(m);
                    puts("");
                    system("pause");
                    break;
                    
                case 6:
                    cout << "Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей." << endl << endl;
                    break;
                    
                case 7:
                    cout << "Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей." << endl << endl;
                    break;
                    
                case 8:
                    cout << "Частное от деления многочлена на многочлен при делении с остатком." << endl << endl;
                    break;
                    
                case 9:
                    cout << "Остаток от деления многочлена на многочлен при делении с остатком." << endl << endl;
                    break;
                    
                case 10:
                    cout << "НОД многочленов." << endl << endl;
                    break;
                    
                case 11:
                    cout << "Производная многочлена." << endl << endl;
                    
                    // Алина Белоусова, группа 7307
                    printf("Введите старшую степень многочлена: ");
                    _scanf("%d", &m);
                    
                    C = (int*)realloc(C, (2 * m + 2) * sizeof(int));
                    
                    printf("Введите коэффициенты многочлена:\n");
                    
                    for (int i = 2 * m + 1; i >= 0; i = i - 2) // Ввод числителей и знаменателей первого многочлена
                    {
                        printf("Числитель: %");
                        _scanf("%d", &C[i - 1]);
                        printf("Знаменатель: ");
                        do
                        {
                            _scanf("%d", &C[i]);
                            if (&C[i] == 0)
                                cout << "Число должно быть не равно нулю!";
                        } while (&C[i] == 0);
                        
                        _scanf("%d", &C[i]);
                    }
                    DER_PP_P(m, C);
                    
                    puts("");
                    system("pause");
                    break;
                    
                case 12:
                    cout << "Преобразование многочлена — кратные корни в простые." << endl << endl;
                    break;
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
}

void modulePick() // Выбор модуля
{
    string module[4] = { "1. Натуральные числа с нулем",
        "2. Целые числа",
        "3. Рациональная числа (дроби)",
        "4. Многочлен с рациональными коэффициентами" };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Выберите модуль, в котором Вы хотите произвести вычисления:\n");
            
            for (int i = 0; i < 4; i++)
            {
                if (i != index)
                    cout << " " << module[i] << "\n";
                else
                    cout << ">" << module[i] << "\n";
            }
            
            puts("\nДля возврата в прошлое меню нажмите Esc.");
        }
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 3)
                    index++;
                break;
                
#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                switch (index)
            {
                case 0:
                    naturalNum();
                    break;
                    
                case 1:
                    totalNum();
                    break;
                    
                case 2:
                    fractionNum();
                    break;
                    
                case 3:
                    polyNum();
                    break;
                    
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
}

void devTeam() // Команда разработчиков
{
    system("cls");
    puts("Список людей, разрабатывавших этот проект:\n"
         "Архитектор:                      Программисты:\n"
         "Дмитрий Кезлинг, группа 7305     Диана Щебет, группа 7307\n"
         "                                 Евгений Сысенко, группа 7307\n"
         "                                 Дмитрий Богряков, группа 7307\n"
         "                                 Рустам Аминов, группа 7307\n"
         "Ответственный по качеству:       Анна Волкова, группа 7307\n"
         "Никита Исаенко, группа 7305      Владислав Лагерев, группа 7307\n"
         "                                 Алина Белоусова, группа 7307\n"
         "                                 Алексаднр Трифонов, группа 7301\n"
         "                                 Максим Кортель, группа 7301\n"
         "                                 Станислав Смирнов, группа 7301\n\n"
         "Для возврата в прошлое меню нажмите Esc.");
    do
    {
#ifdef __APPLE__
    } while (__getch() != 'q');
#else
    } while (__getch() != 27);
#endif
}

void fixJournal() // Журнал всех исправлений
{
    system("cls");
    puts("Версия 1.0 BETA - Список изменений: \n"
         "1. Начало разработки проекта\n"
         "2. Внесены данные о разработчиках\n"
         "3. Введён лог обновлений программы\n"
         "4. Введены функции:\n"
         "I  уровня (меню) - выбор меню, команда разработчиков, журнал исправлений\n"
         "II уровня (модули) - натуральные числа, целые числа, рациональные числа, многочлены \n"
         "Отчёт обновлён 30.03.2018 в 15:15 \n\n"
         
         "Версия 1.0.1 - Список изменений: \n"
         "1. Введена функция I уровня 'Помощь'\n"
         "2. Исправление мелких ошибок\n"
         "3. Оптимизация программы \n"
         "4. Введены первые комментарии \n"
         "5. Произведена оптимизация места для удобности чтения(убраны или добавлены пробелы) \n"
         "Отчёт обновлён 30.03.2018 в 17:20 \n\n"
         
         "Версия 1.1.0 - Список изменений: \n"
         "1. Добавлен блок ЧАВО, отвечающий на основные вопросы \n"
         "2. Добавлена функция N - 1 (III уровень) \n"
         "3. Добавлена функция N - 2 (III уровень) \n"
         "4. Добавлена функция N - 7 (III уровень) \n"
         "5. Добавлена функция Z - 1 (III уровень) \n"
         "6. Добавлена функция Q - 4 (III уровень) \n"
         "Отчёт обновлён 30.03.2018 в 23:30 \n\n"
         
         "Версия 1.2.0 - Список изменений: \n"
         "1. Добавлено множество комментариев в блоке ЧАВО \n"
         "2. Добавлены комментарии по всей программе"
         "3. Добавлена функция N - 6 (III уровень) \n"
         "4. Добавлена функция P - 5 (III уровень) \n"
         "5. Значительная оптимизация всего кода \n"
         "Отчёт обновлён 03.04.2018 в 00:30 \n\n"
         
         "Версия 1.2.1 - Список изменений: \n"
         "1. Добавлена функция N - 5 (III уровень) \n"
         "2. Исправление мелких ошибок \n"
         "Отчёт обновлён 03.04.2018 в 13:30 \n\n"
         
         "Версия 1.2.2 - Список изменений: \n"
         "1. Добавлена функция N - 9 (III уровень) \n"
         "2. Уменьшение мерцания при выборе пункта меню \n"
         "2.1 Обновление надписей на экране производится только при измении пунктов меню, поэтому мерцания меньше \n"
         "3. Исправление мелких ошибок \n"
         "Отчёт обновлён 03.04.2018 в 16:30 \n\n"
         
         "Версия 1.2.3 - Список изменений: \n"
         "1. Добавлена функция Z - 2 (III уровень) \n"
         "2. Добавлена функция Z - 3 (III уровень) \n"
         "3. Исправление мелких ошибок \n"
         "Отчёт обновлён 04.04.2018 в 20:00 \n\n"
         
         "Версия 1.2.4 - Список изменений: \n"
         "1. Добавлена функция N - 3 (III уровень) \n"
         "2. Добавлена функция Z - 4 (III уровень) \n"
         "3. Добавлена функция Z - 5 (III уровень) \n"
         "4. Исправление мелких ошибок \n"
         "Отчёт обновлён 05.04.2018 в 12:30 \n\n"
         
         "Версия 1.2.5 - Список изменений: \n"
         "1. Обновлена функция N - 7 (III уровень) \n"
         "2. Добавлена функция N - 10 (III уровень) \n"
         "3. Исправление мелких ошибок \n"
         "Отчёт обновлён 05.04.2018 в 20:30 \n\n"
         
         "Версия 1.2.6 - Список изменений: \n"
         "1. Добавлена функция N - 4 (III уровень) \n"
         "2. Добавлена функция Q - 2 (III уровень) \n"
         "3. Исправление мелких ошибок \n"
         "Отчёт обновлён 06.04.2018 в 19:00 \n\n"
         
         "Версия 1.2.7 - Список изменений: \n"
         "1. Переписана функция N - 4 (III уровень) \n"
         "2. Добавлена функция Q - 3 (III уровень) \n"
         "3. Исправление мелких ошибок \n"
         "Отчёт обновлён 08.04.2018 в 02:00 \n\n"
         
         "Версия 1.2.8 - Список изменений: \n"
         "1. Добавлена функция N - 8 (III уровень) \n"
         "2. Переписана функция Z - 1 (III уровень) \n"
         "3. Добавлена функция Z - 8 (III уровень) \n"
         "4. Исправление мелких ошибок \n"
         "Отчёт обновлён 08.04.2018 в 17:30 \n\n"
         
         "Версия 1.2.9 RELEASE - Список изменений: \n"
         "1. Обновлена функция N - 4 (III уровень) \n"
         "2. Обновлена функция N - 10 (III уровень) \n"
         "3. Добавлена функция P - 12 (III уровень) \n"
         "4. Исправление мелких ошибок \n"
         "Отчёт обновлён 10.04.2018 в 22:30 \n\n"
         
         "Версия 1.2.10 RELEASE - Список изменений: \n"
         "1. Добавлена функция Z - 6 (III уровень) \n"
         "2. Добавлена функция Z - 7 (III уровень) \n"
         "3. Обновлена функция N - 5 (III уровень) \n"
         "4. Добавлена функция Q - 7 (III уровень) \n"
         "5. Добавлена функция Q - 8 (III уровень) \n"
         "6. Исправление мелких ошибок \n"
         "Отчёт обновлён 11.04.2018 в 17:00 \n\n"
         
         "(Актуальная) Версия 1.3.0 RELEASE - Список изменений: \n"
         "1. Значительно изменён ввод чисел во всех функциях \n"
         "1.1 Ввод стал значительно удобнее \n"
         "1.2 Теперь ввести можно только цифры или знак минус \n"
         "2. Обновлена функция N - 3 (III уровень) \n"
         "3. Обновлена функция N - 5 (III уровень) \n"
         "4. Добавлена функция N - 11 (III уровень) \n"
         "5. Добавлена функция N - 12 (III уровень) \n"
         "6. Добавлена функция N - 13 (III уровень) \n"
         "7. Добавлена функция N - 14 (III уровень) \n"
         "9. Добавлена функция Z - 9 (III уровень) \n"
         "10. Добавлена функция Z - 10 (III уровень) \n"
         "11. Добавлена функция Q - 1 (III уровень) \n"
         "12. Добавлена функция Q - 2 (III уровень) \n"
         "13. Добавлены второстепенные функции, значительно укорачивающие код \n"
         "14. Исправление мелких ошибок \n"
         "15. Исправление серьёзных ошибок \n"
         "Отчёт обновлён 13.04.2018 в 00:00 \n\n"
         
         "Список будущих нововведений (без хронологического порядка):\n"
         "1. Заполнение всех функций во всех модулях (III уровень) \n"
         "2. Оптимизация программы\n"
         "3. Введение новых комментариев\n"
         "4. (Возможное) Введение 'админ-панели', вызываемой по секретной кнопке\n"
         "4.1 (Возможное) Введение возможности редактирования всех текстовых выводимых данных\n"
         "5. (Возможное) Улучшение графического интерфейса программы \n"
         "Отчёт обновлён 30.03.2018 в 16:30 \n\n"
         
         "Для возврата в прошлое меню нажмите Esc.");
    do
    {
#ifdef __APPLE__
    } while (__getch() != 'q');
#else
    } while (__getch() != 27);
#endif
}

void help() // Помощь
{
    system("cls");
    puts("При возникновении вопросов, жалоб и предложений - обращаться на почту:\n"
         "dimon@kezling.ru\n\n"
         "Для возврата в прошлое меню нажмите Esc.");
    do
    {
#ifdef __APPLE__
    } while (__getch() != 'q');
#else
    } while (__getch() != 27);
#endif
}

void menuPick() // Выбор меню
{
    string mainMenu[4] = { "1. Переход к основной части программы",
        "2. Команда разработчиков",
        "3. Журнал обновлений",
        "4. Помощь" };
    
    // Переменные для выбора пункта
    int index = 0, tmp, prevIndex = -1;
    
    do
    {
        if (prevIndex != index)
        {
            prevIndex = index;
            system("cls");
            puts("Версия программы: 1.3.2 RELEASE \n\n"
                 "Здравствуйте!\n"
                 "Для управления программой используйте стрелки вверх/вниз на клавиатуре\n"
                 "Для входа в пункт меню используйте Enter, для выхода - Esc.\n"
                 "Приятного использования!\n");
            
            for (int i = 0; i < 4; i++)
            {
                if (i != index)
                    cout << " " << mainMenu[i] << "\n";
                else
                    cout << ">" << mainMenu[i] << "\n";
            }
            
            puts("\nДля выхода из программы нажмите Esc.");
        }
        
        tmp = __getch();
        switch (tmp)
        {
            case 72:
                if (index > 0)
                    index--;
                break;
                
            case 80:
                if (index < 3)
                    index++;
                break;

#ifdef __APPLE__
            case 49:
                index = 0;
                break;
            case 50:
                index = 1;
                break;
            case 51:
                index = 2;
                break;
            case 52:
                index = 3;
                break;
            case 'f':
#endif
            case 13:
                prevIndex = -1;
                
                switch (index)
            {
                case 0:
                    modulePick();
                    break;
                    
                case 1:
                    devTeam();
                    break;
                    
                case 2:
                    fixJournal();
                    break;
                    
                case 3:
                    help();
                    break;
            }
                break;
        }
#ifdef __APPLE__
    } while (tmp != 'q');
#else
    } while (tmp != 27);
#endif
}

int main() // Основная функция
{
    setlocale(LC_ALL, "RUS"); // Подключение русской локализации
    
    /*int b = 0;
     do
     {
     b = _getch();
     cout << (int)b << "\n";
     } while ((char)b != 'j'); */
    
    /*int m = -1;
    int *C = NULL;
    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
    InputPolynom(m, C);
    PrintPolynomSigned(m, C);*/
    
    /*int m = -1;
    Q *C = NULL;
    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
    InputPolynom(m, C);
    PrintPolynom(m, C);*/
    
    int m1 = -1, m2 = -1, mRes = -1;
    Q *C1 = NULL, *C2 = NULL, *CRes = NULL;
    //  5/6x^5 + 3x^4 - x + 12
    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
    InputPolynom(m1, C1);
    PrintPolynom(m1, C1);
    //  5/6x^5 - 3x^4 + x + 12
    cout << "Введите многочлен в формате: 1/2 - x + 3/2x^3 - 12*x^6 + ..." << endl;
    InputPolynom(m2, C2);
    PrintPolynom(m2, C2);
    ADD_PP_P(m1, C1, m2, C2, mRes, CRes);
    PrintPolynom(mRes, CRes);
    
    menuPick();
    
    system("cls");
    puts("Команда разработчиков благодарит Вас за использование нашей программмы! \n"
         "Надеемся увидеть вас снова! \n"
         "До свидания!");
    system("pause");
    return 0;
}
