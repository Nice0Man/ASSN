#include <iostream> // Для работы с вводом/выводом
#include <string>
#include <map>      // Для использования контейнера map
#include <cctype>   // Для использования функций обработки символов

#include "i7188.h" // Подключение библиотеки от производителя
#include "include.h"

// Объявление переменных
int quit = 0;       // Переменная для остановки выполнения и выхода из программы
char data;          // Переменная для символа, введенного с клавиатуры
unsigned long time; // Переменная для работы с таймером

// Создание таблицы Морзе
std::map<char, std::string> morseCode;

void initMorseCode() {
    morseCode['A'] = ".-";   morseCode['B'] = "-..."; morseCode['C'] = "-.-."; morseCode['D'] = "-..";
    morseCode['E'] = ".";    morseCode['F'] = "..-."; morseCode['G'] = "--.";  morseCode['H'] = "....";
    morseCode['I'] = "..";   morseCode['J'] = ".---"; morseCode['K'] = "-.-";  morseCode['L'] = ".-..";
    morseCode['M'] = "--";   morseCode['N'] = "-.";   morseCode['O'] = "---";  morseCode['P'] = ".--.";
    morseCode['Q'] = "--.-"; morseCode['R'] = ".-.";  morseCode['S'] = "...";  morseCode['T'] = "-";
    morseCode['U'] = "..-";  morseCode['V'] = "...-"; morseCode['W'] = ".--";  morseCode['X'] = "-..-";
    morseCode['Y'] = "-.--"; morseCode['Z'] = "--..";
    morseCode['1'] = ".----"; morseCode['2'] = "..---"; morseCode['3'] = "...--"; morseCode['4'] = "....-";
    morseCode['5'] = "....."; morseCode['6'] = "-...."; morseCode['7'] = "--..."; morseCode['8'] = "---..";
    morseCode['9'] = "----."; morseCode['0'] = "-----";
    morseCode[' '] = " "; 
}

// Функция передачи символов азбуки Морзе
void sendMorseCode(char symbol) {
    symbol = std::toupper(symbol); // Приведение символа к верхнему регистру
    if (morseCode.find(symbol) != morseCode.end()) {
        std::string morse = morseCode[symbol];
        for (char ch : morse) {
            if (ch == '.') {
                LedOn();
                Delay(200); // Имитация короткого сигнала
                LedOff();
            } else if (ch == '-') {
                LedOn();
                Delay(600); // Имитация длинного сигнала
                LedOff();
            } 
            Delay(200); // Разделение между элементами кода
        }
        Delay(600); // Разделение между символами
    }
}

// Главная функция
int main(void) {
    TimerOpen();       // Инициализация таймера
    StopWatchStart(0); // Обнуление таймера
    LedOff();          // Выключение индикатора
    
    // Инициализация таблицы Морзе
    initMorseCode();

    // Начало цикла
    while (!quit) {
        if (Kbhit()) { // Если был произведен ввод с клавиатуры
            data = Getch(); // Считывание символа с клавиатуры в переменную data
            if (data == 'q' || data == 'Q')
                quit = 1; // Выход из программы
            else {
                // Отправка введенного символа в консоль
                Putch(data);

                // Если введен символ новой строки
                if (data == '\r'){
                    Putch('\n');
                } else {
                    sendMorseCode(data); // Передача символа в виде Морзе
                }
            }
        }
    }

    TimerClose(); // Прекращение использования таймера
}