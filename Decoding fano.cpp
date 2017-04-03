#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    list<string> symb, code;
    list<string>::iterator i, n;
    int answer;
    bool error = false;
    string element, code_el, message, message_try, result, code_try, test, code_try2;

    cout << "Введите правила декодирования" << endl;
    do{
        cout << "Введите элемент" << endl;
        cin >> element;
        symb.push_back(element);

        cout << "Введите код этого элемента" << endl;
        // Запускаем цикл - ввод, пока введено неправильное значение
        do{
            cin >> code_el;
            // Перебираем все символы, введенного кода
            for (int k = 0; k < code_el.length(); k++){
                code_try += code_el[k];
                // Пробегаем по уже созданному списку кодов
                for (i = code.begin(); i != code.end(); ++i){
                    // Сравниваем, если нашли код, который является началом введенного кода ошибка
                    //(сначала ввели 0, затем 00 - ошибка, так как 0 - начало кода 00)
                    if (code_try.compare(*i) == 0){
                        error = true;
                        code_try = "";
                        break;
                    }
                    else
                       error = false;
                }
            }


            //Проверяем является ли введенный код началом кода из списка
            for (i = code.begin(); i != code.end(); ++i){
                for (int k = 0; k < (*i).length(); k++){
                    code_try2 += (*i)[k];
                    if (code_el.compare(code_try2) == 0){
                        error = true;
                        code_try2 = "";
                        break;
                    }
                    else
                        error = false;
                }
            }

             // Если не нашли ошибку, добавляем код.
            if (!error){
                    code.push_back(code_el);
                    code_try = "";
                    code_try2 = "";
            }
            else
                cout << "Вы вели код, не удовлетворяющий условию Фано, повторите ввод:" << endl;
        }while (error);

        cout << endl << "Продолжить ввод? (1 - да, 0 - нет)" << endl;
        cin >> answer;
    }while(answer);

    cout << "Введите сообщение, которое необходимо декодировать" << endl;
    cin >> message;



    //Запускаем цикл, по всем элементам сообщения
    for (int k = 0; k < message.length(); k++){
        message_try += message[k];
        //Проходим по всем введенным кодам.
        for (i = code.begin(), n = symb.begin(); i != code.end(); ++i, ++n)

            //Если нашли код, дописываем элемент с этим кодом, в результирующую строку.
            if (message_try.compare(*i) == 0){
                result += *n;
                message_try = "";
            }
    }


    ofstream fout("output.xls");
    fout << "Введенные правила:" << endl;
    for (i = code.begin(), n = symb.begin(); i != code.end(); ++i, ++n)
        fout << *n << "\t" << *i << ";" << endl;

    fout << "Введенное закодированное сообщение:" << endl;
    fout << message << ";" << endl;

    fout << "Декодированное сообщение:" << endl;
    fout << result << endl;
    fout.close();

    cout << result << endl;
    return 0;
}

