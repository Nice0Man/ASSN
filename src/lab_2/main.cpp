#include "i7188.h"
#include <iostream>

// Объявление переменных
int quit = 0;
int LedMode = 0;
int data;
long baud = 9600;
int i = 0;
float q;
char temp[80];
unsigned long time;

// Начало главной функции
int main(void) {
    TimerOpen();
    StopWatchStart(0);
    // Инициализация COM соединения
    InstallCom2(baud, 8, 0, 1);
    // Запуск цикла
    while (!quit){
        // Обнуление таймера
        StopWatchReadValue(0, &time);
        // На отметке таймера в 1700мс выполняется запрос к ПНК
        if (time >= 1700){
            StopWatchStart(0);
            ToCom2('#');
            ToCom2('0');
            ToCom2('1');
            ToCom2('\r');
            ClearCom2();
        } // Конец команды запроса
        // Проверка, если на вход контроллера поступили данные
        if (IsCom2())        {
            // Если данные длиной 8 бит то считываем. В противном случае ждем
            if (DataSizeInCom2() == 8)            {
                ReadCom2();
                for (i = 0; i < 7; i++)                {
                    temp[i] = ReadCom2();
                }
                // Очищаем буфер порта
                ClearCom2();
                // Преобразовываем температуру в float формат в переменной q
                q = atof(temp);
                /* Примечание: в данном коде программы, команда Print выводит переменную по COM порту в ПК(если он подключен). Это стоит делать для того, чтобы было возможно наблюдать за текущей температурой на мониторе компьютера.*/
                Print("$%.1f;\n", q);
                // Сравнение температуры с границами диапазона
                if (q > 30.6){
                    ToCom2('#');
                    ToCom2('0');
                    ToCom2('2');
                    ToCom2('0');
                    ToCom2('A');
                    ToCom2('0');
                    ToCom2('0');
                    ToCom2('\r');
                    ClearCom2();
                    LedOn();
                }

                if (q < 27.0){
                    ToCom2('#');
                    ToCom2('0');
                    ToCom2('2');
                    ToCom2('0');
                    ToCom2('A');
                    ToCom2('0');
                    ToCom2('1');
                    ToCom2('\r');
                    ClearCom2();
                    LedOff();
                }
            }
        }
    }
}