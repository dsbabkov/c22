#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <list>
#include "literals.h"
#include "Range.h"
#include "ConstBit.h"
#include <functional>
#include <cstdio>

using namespace std;

constexpr unsigned factorial(unsigned n){
    return n ? n * factorial(n - 1) : 1;
}

int main()
{
	
    {
        //Задание 1. Сырые строковые литералы (Raw String Literals)
        //Выведите строку, например: my name is "Marina"
        //а) без использования Raw String Literals
        std::string a = "my name is \"Marina\"";
        //б) посредством Raw String Literals
        std::string b = R"(my name is "Marina")";
        //в) добавьте разделители (Delimeter)
        std::string c = R"GG(my name is "Marina")GG";
    }



	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 2. Реализуйте вычисление факториала с помощью constexpr-функции.
	//
	//Подсказки/напоминания: 
	//		- constexpr – функция должна состоять из единственной инструкции return <выражение>; (пока!)
	//		- но это выражение может включать вызов другой constexpr – функции, в частности рекурсивный
	//			вызов 
	//		- если параметр рекурсивной constexpr- функции - это константа, компилятор вычислит результат
	//			на этапе компиляции

	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции (если в качестве
	//				параметра используется константа, известная компилятору на этапе компиляции).
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-функции:

	{//Например:
		//int ar[factorial(3)];

		//или
        constexpr int n = factorial(5);
        int ar1[n];

		//попробуйте:
        int m = 7;
		//constexpr int n1 = factorial(m);
		//int ar1[n1];
		
		//а так?
        int n2 = factorial(m);
	}



	
	//////////////////////////////////////////////////////////////////////////////////////////////


	//Задание 3a. Перевод с помощью пользовательского литерала из двоичного представления строкового
	//в значение, например: строку "100000000" -> в значение 256
	//Проверить результат посредством префикса 0b
	//Чтобы вызов пользовательского литерала выглядел просто и читаемо, например: 100000000_b
	//логично использовать пользовательский литерал с единственным параметром - const char*
    {
        constexpr int a = "100000000"_b;
        constexpr int a2 = 100000000_b;
        std::cout << (a == 0b100000000) << '\n';
    }

	//Так как речь идет о литералах, логично вычислять значения на этапе компиляции
	// => реализуйте пользовательский литерал посредством constexpr - функций
	//Подсказка/напоминание: 
    //		- constexpr – функция должна состоять из единственной инструкции return <выражение>;
	//		- но это выражение может включать вызов другой constexpr – функции,
	//		- которая может быть рекурсивной (если параметр такой функции - это константа,
	//					компилятор вычислит результат вызова рекурсивной функции на этапе компиляции)



	//Задание 3b. Перевод в строковое двоичное представление, например: 256 -> "0b100000000"
	//Так как строка может быть любой длины, логичнее и проще возвращать объект std::string
	//=> возвращаемое значение не может быть constexpr!
	//Подсказка: манипулятора std::bin пока нет => преобразование в двоичную строку
	//придется делать вручную
	//Подсказка: количество разрядов в байте определяет константа CHAR_BIT - <cstdint>
    {
        std::string sBin= 256_toBinStr;
        std::cout << sBin << '\n';
    }



	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 4а. constexpr - объекты 
	//Создать класс (шаблон класса?) для хранения и манипулирования диапазоном значений.
	//В классе должны быть:
	//	переменные для хранения минимального и максимального значений,
	//	методы для получения каждого из значений
	//	метод для проверки - попадает ли указанное значение в диапазон
	//	метод, который получает любое значение данного типа и формирует результирующее значение:
	//							если принадлежит диапазону, то его и возвращаем
	//							если меньше минимального значения, возвращаем минимальное
	//							если больше максимального значения, возвращаем максимальное



	//Проверьте тот факт, что компилятор вычисляет значение на этапе компиляции. 
	//				Для проверки достаточно создать встроенный массив с размерностью, вычисляемой
	//				посредством constexpr-метода:
	{
        int test[makeRange(9).validate(36)];
        test[0] = 1;
	}


		//Задание 4b. constexpr класс с битовыми полями
		//Часто в задачах требуется получать разные наборы констант в зависимости от
		//разных условий. Причем диапазон значений констант может быть существенно меньше
		//диапазона значений, предоставляемых типом char или unsigned char

		//Посредством constexpr класса и битовых полей реализуйте получение и 
		//использование констант на этапе компиляции

	{
        int test[ConstBit(0b10).bit(1) + 1];
        int test2[ConstBit(0b10).bit(0) + 1];
        int test3[ConstBit(0b10).bit(3) + 1];
        test[0] = test2[0] = test3[0] = 0;
        std::cout << sizeof(test) << ' '
                  << sizeof(test2) << ' '
                  << sizeof(test3) << '\n';
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 5. unique_ptr
	{

		//5.а - обеспечьте корректное выполнение фрагмента
		{
			std::vector<std::string*> v = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
			//Распечатайте все строки
            for (const string *str: v){
                std::cout << *str << ' ';
            }
            std::cout << '\n';

            for_each(v.begin(), v.end(), [](string *s){delete s;});

			//???
		} //???

		//5.b - модифицируйте задание 1.а:
		 //обеспечьте посредством std::unique_ptr: 
		 //эффективное заполнение (вспомните про разные способы формирования std::unique_ptr), 
		 //безопасное хранение указателей на динамически создаваемые объекты std::string, 
		 //манипулирование,
		 //и освобождение ресурсов
		 //
			
		{
            using StringPtr = std::unique_ptr<const std::string>;
            std::vector<StringPtr> v;
            for (const char *str: {"aa", "bb", "cc"}){
                v.emplace_back(new std::string(str));
            }
		 //Распечатайте все строки

            for_each(v.cbegin(), v.cend(), [](const StringPtr &str){cout << *str << ' ';});
            std::cout << '\n';

		 //??? Уничтожение динамически созданных объектов?
		} //???

		{//5.c - дополните задание 5.b добавьте возможность изменять хранящиеся строки
		 //следующим образом (например, добавить указанный суффикс: "AAA" -> "AAA_1")  
            using StringPtr = std::unique_ptr<std::string>;
            std::vector<StringPtr> v;
            for (const char *str: {"aa", "bb", "cc"}){
                v.emplace_back(new std::string(str));
            }

            std::for_each(v.begin(), v.end(), [](StringPtr &str){*str += "_1";});

            for_each(v.cbegin(), v.cend(), [](const StringPtr &str){cout << *str << ' ';});
            std::cout << '\n';


		}

		{//5.d - динамический массив объектов	

		 //Создайте unique_ptr, который является оберткой для динамического массива
		 //с элементами std::string
		 //С помощью unique_ptr::operator[] заполните обернутый массив значениями
		 //Когда происходит освобождения памяти?

            constexpr size_t arrSize = 9;
            std::unique_ptr<int[]> ptr(new int[arrSize]);
            for (size_t i = 0; i < arrSize; ++i){
                ptr[i] = i;
            }
		}


        std::string *outStrs[3]={};
		{//5.e - массивы динамических объектов и пользовательская delete-функция (функтор)
		 //Задан стековый массив указателей на динамически созданные объекты
		 //Создайте unique_ptr для такого массива
		 //Реализуйте пользовательскую delete-функцию (функтор) для корректного 
		 //освобождения памяти

			std::string* arStrPtr[] = { new std::string("aa"), new std::string("bb"), new std::string("cc") };
            std::copy(std::cbegin(arStrPtr), std::cend(arStrPtr), outStrs);
            constexpr size_t arrSize = std::cend(arStrPtr) - std::cbegin(arStrPtr); // std::size

            auto delStr = [](std::string *ptr){delete ptr;};
            auto delAll = [arrSize, delStr](std::string **arr){std::for_each(arr, arr + arrSize, delStr);};
            std::unique_ptr<std::string* [], decltype(delAll)> ptr(arStrPtr, delAll);
		}

		{//5.f Создайте и заполните вектор, содержащий unique_ptr для указателей на std::string
			//Посредством алгоритмя copy() скопируйте элементы вектора в пустой список с элементами 
			//того же типа
			//Подсказка: перемещающие итераторы и шаблон std::make_move_iterator
            using StrPtr = std::unique_ptr<std::string>;
            std::vector<StrPtr> v;
            for (const char *str: {"my", "unique", "strings"}){
                v.emplace_back(std::make_unique<std::string>(str));
            }
            std::list<StrPtr> l;
            std::copy(make_move_iterator(v.begin()), make_move_iterator(v.end()), back_inserter(l));
            std::cout << l.size();
		}


	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 6.shared_ptr + пользовательская delete-функция 

	//Реализовать возможность записи в файл данных (строчек) из разных источников 
	//(для упрощения пусть источниками являются два массива)
	//Так как все "писатели" будут по очереди записывать свои данные в один и тот же файл,
	//логично предоставить им возможность пользоваться одним и тем же указателем FILE* =>
	//безопасной оберткой для такого указателя является shared_ptr
	//а. Первый владелец должен открыть/создать файл для записи
	//б. Все остальные писатели должны присоединиться к использованию
	//в. Последний владелец указателя должен закрыть файл

	//Подсказка: имитировать порядок записи можно с помощью функции rand()

	{
	//"писатели":
	//Создать writer1, writer2

        class Writter{
            std::shared_ptr<FILE> file_;
            const char *data_ = nullptr;
        public:
            Writter(std::shared_ptr<FILE> file, const char *data)
                : file_{file}, data_{data}
            {}
            void write(){
                if (!data_){return;}
                if (!file_){
                    file_.reset(fopen("shared_ptr_file", "w"));
                    if (!(file_)){return;}
                }
                fputs(data_, file_.get());
            }
        };

	//например, источники данных:
        auto fileDeleter = [](FILE *file){if(file){fclose(file);}};
        std::shared_ptr<FILE> file(0, fileDeleter);

	char ar1[] = "Writer1";
	char ar2[] = "Writer2";

    Writter writters[] = {{file, ar1}, {file, ar2}};

    for (int i = 0; i < 10; ++i){
//        writters[rand() & 1].write();
    }

    std::shared_ptr<FILE> writter1(fopen("shared_ptr_file", "w"), fileDeleter);
    std::shared_ptr<FILE> writter2(writter1);

    fputs(ar2, writter2.get());
    fputs(ar1, writter1.get());

	//заданное число итераций случайным образом позволяем одному из "писателей" записать в файл
	//свою строчку
	//Подсказка: строчки удобно записывать в файл посредством функции fputs()



    std::cout << "before close\n";
	}//закрытие файла???	
    std::cout << "after close\n";
}
