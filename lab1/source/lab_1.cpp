//Практика 1:
// enum class
// initializer_list и универсальные списки инициализации
// auto
// decltype
// lambda functions

#include <string>
#include <vector>
#include <list>
#include <deque>

int main()
{


	//Задание 1. 
	{
		enum months { January, February, March/*...*/ };
		enum weekDays { Monday, Tuesday /*...*/ };

		months m = January;
		//а) уберите проблемы
		if (m == Monday) { /*...*/ }
		//б) оптимизируйте использование памяти
		months year[] = { January, February, March };
		size_t n = sizeof(year); //???

	}


	//////////////////////////////////////////////////////////////////////////////////
	//Задание 2. Создайте и с помощью списка инициализации заполните значениями вектор с
	//элементами - string
	//С помощью range-based for преобразуйте все буквы в верхний регистр
	//а остальные символы должны остаться неизменными
	{


	}

	/////////////////////////////////////////////////////////////////////
	///Задание 3. Создайте и с помощью списка инициализации заполните значениями
	//map таким образом, чтобы он содержал в качестве ключа букву, а в качестве значения 
	//отсортированную по алфавиту совокупность слов (string), начинающихся с этой буквы
	
	//С помощью range-based for распечатайте содержимое, например: A: any, apple, away
	{

	}

    /////////////////////////////////////////////////////////////////////
	///Задание 4. создать функцию для вывода на печать элементов последовательностей, заданных ниже

	{
		std::vector<double> vd = { 1.1,2.2,3.3 };
		//PrintAnyCont(vd);

		std::string s("abc");
		//PrintAnyCont(s);

		int ar[] = { 1, 2, 3 };
		//PrintAnyCont(ar);

		std::initializer_list<int> il{ 3,4,5 };
		//PrintAnyCont(il);

		
	}

	/////////////////////////////////////////////////////////////////////
	///Задание 5. 	
	//создать функцию для "отрицания" значений, например:
	// было: {1, -2, 5}, стало: {-1, 2, -5})
	// изменение объектов типа std::string может выглядеть "aBc1" -> "AbC1"
	//элементов последовательностей, заданных ниже:

	{
		std::vector<double> vd{ 1.1,2.2,3.3 };
		//NegateAll(vd);

		std::list<std::string> ls{ "aBc", "Qwerty", "n12" };
		//NegateAll(ls);

		int ar[]{ 1, 2, 3 };
		//NegateAll(ar);
		

	}




	///Задание 4а. создать функцию для инкремента элементов последовательностей, заданных ниже

	{
		std::vector<double> vd = { 1.1, 2.2, 3.3 };
		//IncAnyCont(vd);


		int ar[] = { 1, 2, 3 };
		//IncAnyCont(ar);

		std::string s("123");
		//IncAnyCont(s);


	}

	//////////////////////////////////////////////////////////////////////////////////
	//Задание 5. Реализовать функцию сортировки по модулю элементов последовательностей, заданных ниже
	//Собственно для сортировки можно использовать обобщенный алгоритм sort(), 
	//а для задания условия - лямбда-функцию
	{
		std::vector<double> vd = { -3.3,  2.2, -1.1 };
		//absSort(vd);


		int ar[] = { -3, 2, -1 };
		//absSort(ar);

	}

	//////////////////////////////////////////////////////////////////////////////////
	//Задание 6.
	//напишите функцию, которая будет формировать и возвращать вектор, каждый элемент 
	//которого является суммой элементов двух последовательностей 
	//РАЗНОЙ длины и с элементами РАЗНОГО типа.

	//Подсказка 1: так как последовательности могут быть разной длины, логично
	//сделать размер результирующего вектора максимальным из двух
	 
	//Подсказка 2: подумайте о возможности использования алгоритма transform(), 
	//в котором трансформирующее действие удобно в свою очередь задавать лямбда-функцией

	//например:
	{
		std::vector<int> v{ 1,2,3,4 };
		std::list<double> l{ 1.1, 2.2, 3.3, 4.4, 5.5 };

		//??? = SumCont(v, l);
		

		std::list<int> ll{ 1, 2, 3, 4, 5, 6, 7, 8 };
		double ar[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		//??? = SumContT(ar, ll);
		
	}


	
	//////////////////////////////////////////////////////////////////////////////////
	//Задание 7. Реализуйте функцию, которая принимает следующие парметры:	
	//сформированную последовательность любого типа с элементами любого типа, 
	//два (пустых) контейнера любого типа из vector, list, deque, set с элементами того же 
	//типа, что и у сформированной последовательности 

	//Функция должна "разложить" значения заданной последовательности в два пустых контейнера 
	//согласно заданному условию. Условие задать лябда-функцией
	//Исходная последовательность при этом не меняется
	{
		//Например:
		std::vector<int> v{ 1,2,3,4,5 };
		std::list<int> l; //сюда четные
		std::deque<int> d; //а сюда нечетные
		//Separate(v, l, d, <условие>);
		
	}


	//////////////////////////////////////////////////////////////////////////////////
	//Задание 8. C помощью алгоритма for_each()!!! (а не count_if()) посчитать сколько 
	//букв в верхнем регистре
	//  Использовать лямбда функцию
	{
		char s[] = "Hello World!";


	}


	//////////////////////////////////////////////////////////////////////////////////
	//Задание 9a. Создайте класс, который должен быть "оберткой" для вектора с УНИКАЛЬНЫМИ значениями
	//любого типа. 
	//Для хранения элементов используйте std::vector

	//Реализуйте конструктор, который может принимать любое количество значений (значения могут повторяться)
	//Реализуйте метод добавления любого количества значений (значения могут повторяться)
	//Реализуйте метод удаления любого количества значений (значения могут повторяться)
	//Реализуйте метод сортировки, который будет принимать в качестве параметра признак по возрастанию / по убыванию

	


	
	//Задание 9b. Модифицируйте класс из предыдущего задания (или создайте новый) таким образом,
	//чтобы значения не только были бы уникальными, но и находились в заданном диапазоне.
	//Замечание: такой класс в общем виде (для любых данных) смысла, наверно, не имеет, но его можно
	//использовать для таких типов данных, как целых, плавающих и тех пользовательских, для которых
	//имеют смысл операции сравнения (больше, меньше)
	//Подумайте: какие данные нужно добавить в класс и какие методы нужно модифицировать 
 

	//////////////////////////////////////////////////////////////////////////////////
	//Задание 10*. Реализовать конвертацию enum в строковое представление  - enumToString
	// и наоборот - stringToEnum

	//Подсказки: 
	//***********
	//1. Соответствующие именованным константам строки все равно нужно где-то хранить =>
	//1.1 Именованные константы в перечислении должны быть уникальными => соответствующие строки
	//тоже должны быть уникальными, => уникальные строки могут быть использованы в качестве
	//ключа в std::map
	
	//1.2 а вот значения (соответствующие именованым константам)
	//могут быть любыми и даже могут повторяться (упрощаем задачу, считая, что значения НЕ повторяются) 
	//=> подходит контейнер std::map<string,<значение> >
	
	//1.3 Согласно стандарту С++11 переменные перечислимого типа могут быть разного размера и типа,
	//а хотелось бы обеспечить универсальную конвертацию 
	
	//***********
	//2. Так как типы перечислений разные, то enumToString и stringToEnum должны быть шаблонными
	//2.1 Пользователь может ошибиться или злонамеренно передать в функции значения, которым
	//   ничего не соответствует => защита!
	//2.2 В функциях enumToString и stringToEnum (в зависимости от типа перечисления) нужно будет
	//   анализировать соответствующий используемому типу перечисления контейнер
	
	

	{
	//Например:
/*
		COLORS c1;
		try {
			c1 = stringToEnum<COLORS>("blue");
		}
		catch (...)
		{
		//...
		}

	
		auto Str = enumToString(c1);
*/
	}
}
