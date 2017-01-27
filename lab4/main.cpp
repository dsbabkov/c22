
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <iterator> 
#include <regex>
#include <cmath>
#include "Book.h"
#include <set>
#include "Human.h"

template <typename T>
void MyPrint(const T &value){
    std::cout << value << '\n';
}

template <typename T, typename... Args>
void MyPrint(const T &value, const Args &... args ){
    std::cout << value << ' ';
    MyPrint(args...);
}


int main()
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Задание 1. Регулярные выражения


	// 1a Обеспечить прием от пользователя целых значений в десятичной форме.
	// Необходимо учесть специфику пользователя, который должен ввести целое,
	//				а может ввести все, что угодно,
	//				число может предворяться знаком -/+,
	//				количество цифр может быть любым (в частности может превышать sizeof(int))
	//				
	//Подсказки:
	//			a) std::string может принять строчку с любым содержимым
	//			б) нужно проанализировать, соответствует ли введенное значение целому в допустимом диапазоне
	//			в) и, если соответствует, перевести из строкового представления в значение типа int
	//					(для преобразования удобно использовать С++11 - std::stoi())

	{
        const std::string userData = "-5349";
        std::regex re("(-|\\+)[[:digit:]]+");
        std::cout << std::regex_match(userData, re) << '\n';

	}
	// 1b ООбеспечить прием от пользователя целых значений в шестнадцатеричной форме.
	{
        const std::string userData = "0xFF20FF";
        std::regex re("(0x)?[[:digit:]A-Fa-f]+");
        std::cout << std::regex_match(userData, re) << '\n';
	}


	// 1с Обеспечить прием от пользователя плавающих значений в форматах
	//      -2.33 или +1.23e+06 или 0.245E10
	{
        const std::string userData = "+1.23e-2";
        std::regex re("(\\+|-)?[[:digit:]]+\\.?[[:digit:]]*((E|e)(\\+|-)?[[:digit:]]+)?"); //
        std::cout << std::regex_match(userData, re) << '\n';
	}

	// 1d Требуется узнать - есть ли хотя бы одна десятичная цифра в строке
	{
        const std::string userData = "some1 data";
        std::regex re(".*[[:digit:]].*");
        std::cout << std::regex_search(userData, re) << '\n';
    }

	
	//1e Требуется найти все десятичные цифры в строке
	{
        const std::string userData = "s1ome2 da3ta4";
        std::regex re("[[:digit:]]");
        std::transform(std::sregex_iterator (userData.cbegin(), userData.cend(), re),
                       std::sregex_iterator(),
                       std::ostream_iterator<std::string>(std::cout, "\n"),
                       [](const std::smatch &match){return match.str();});
	}
	////////////////////////////////////////////////////////////////////////////////
	//Задание 2 variadic template - функция
	//Реализуйте функцию, которая умеет печатать любое количество параметров любого типа,
	//Например: MyPrint(4,8.8, A(1),std::string("dfg") );


	{
        MyPrint(4,8.8,std::string("dfg"));
	}

	////////////////////////////////////////////////////////////////////////////////
	//Задание 3 function
	//3a Реализуйте "калькулятор", который будет выполнять простейшие действия: +,-,*,/,^
	//     над операндами типа double:
	// '+' - посредством шаблона глобальной функции
	// '-' - посредством шаблона std::minus 
	// '*' - посредством функционального объекта 
	// '/' - посредством лямбда-функции
	// '^' - посредством функции pow() (перегруженный вариант для double)
	// '%' - дробную часть от результата плавающего деления посредством std::bind()
	//* '?' - наибольшее из двух значений посредством std::bind() и метода Вашего класса  
	// 
	//Для хранения значка операции и соответствующего ему действия логично использовать
	//std::map<char, ???> 
	{
        struct Mult{
            constexpr double operator ()(double v1, double v2) const{
                return v1 * v2;
            }
        };

        using BinaryOperator = std::function<double(double, double)>;
        static const std::map<char, BinaryOperator> operators = {
            {'+', std::plus<double>()},
            {'-', std::minus<double>()},
            {'*', Mult()},
            {'/', [](double v1, double v2){return v1 / v2;}},
            {'^', pow}
        };
        std::cout << operators.at('^')(5, 3) << '\n';
	}


	//3б Рекурсивная лямбда функция. Посредством std::function и лямбда функции реализуйте
	//вычисление суммы натурального ряда (x+(x-1)+ (x-2)+...+1).
	//Подсказка: так как существование любой переменной начинается с момента определения, 
	//например: int x=x; - бессмысленно, но корректно
	// => переменную типа function можно использовать в списке захвата  - ... f = [&f]...
	{
        std::function<int (int)> f = [&f](int x){return x == 1 ? 1 : x + f(x-1);};

        std::cout << f(3) << '\n';
	}

	//////////////////////////////////////////////////////////////////////////////////
	//Задание 4 std::tuple
	//Создайте класс book (автор, заглавие, год издания...). 

    //Создайте библиотеку таким образом, чтобы книги хранились в упорядоченном виде.
	//Чтобы упорядочить совокупность книжек, нужно сформировать условие сравнения, то есть
	//перегрузить, например operator<. При реализации оператора хочется сформировать условие
	//с учетом всех данных!!! 
	
	//Подсказка: Для упорядочения удобно использовать шаблон std::tuple,
	//так как для std::tuple перегружены операторы ==,!=,<,<=,>,>=
	//,которые сравнивают два кортежа лексиграфически (в порядке следования членов).

    class Compare{
        std::tuple<std::string, std::string, unsigned> toTuple(const Book &book) const {
            return {book.author(), book.title(), book.year()};
        }

    public:
        bool operator() (const Book &b1, const Book &b2){
            return toTuple(b1) < toTuple(b2);
        }
    };

    static const std::multiset<Book, Compare> library = {
        {"asfga", "fff", 1900},
        {"asfga", "ads", 1900},
        {"ggg", "fff", 1900}
    };



	//Для проверки распечатайте библиотеку

	{


	}

/////////////////////////////////////////////////////////////////
	//Задание 5. shared_ptr и weak_ptr
	//Создаем генеалогическое дерево посредством класса human. В классе хранятся:
	//имя - string
	//возможно признак: жив или уже нет...
	//родители - shared_ptr (родители не всегда известны...)
	//дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

	//Методы класса human:
	//конструктор - для инициализации имени и признака
	//конструктор копирования, оператор присваивания, move ???
	//статический метод child() - 
	//				должен создать создать и вернуть обертку для родившегося человека
	//				+ сформировать все связи ребенка с родителями и наоборот

	//Ввести возможность распечатать генеалогическое дерево для указанного индивидума

	{
        auto Adam = Human::child("Adam");
        auto Eve = Human::child("Eve");

        auto Kain = Human::child("Kain", Eve, Adam);
        auto Avel = Human::child("Avel", Eve, Adam);

        decltype(Kain) children[] = {
            Human::child("Somebody1", Kain),
            Human::child("Somebody2", Kain),
            Human::child("Somebody3", Kain),
            Human::child("Somebody4", Kain),
            Human::child("Somebody5", Kain),
            Human::child("Somebody6", Avel),
            Human::child("Somebody7", Avel),
            Human::child("Somebody8", Avel),
            Human::child("Somebody9", Avel)
        };


        Adam->printTree();
        Eve->printTree();

        //История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
		//(то есть на самом деле два деда и две бабы):


		//std::shared_ptr<human> grandM1(new human("Eva"));
		//...
	
		//у них появились дети - child():


		//а у детей в свою очередь свои дети:


		//...

	}


}
