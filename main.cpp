#include <iostream>
#include <stdexcept>
#include <cmath>

class GeomProgErr : public std::invalid_argument {
public:
    double first;
    double prog;
    double* invptr;
    int size;

    GeomProgErr(const std::string& notification, double first, double prog, double* invptr, int size)
        : std::invalid_argument(notification),first(first), prog(prog), invptr(invptr), size(size) {}


    void printMessage() const {
        std::cout<<"_____________________________________________________________Данные Исключения_____________________________________________________________"<<std::endl;
        std::cout<<"Уведомление об ошибке: "<<what()<<std::endl;
        std::cout<<"Первый элемент: "<<first<<std::endl;
        std::cout<<"Знаменатель (?): "<<prog<<std::endl;
        std::cout<<"Размер массива: "<<size<<std::endl;
        std::cout<<"Сам массив: [";
        for (int i = 0; i < size; ++i) {
            std::cout<<" "<<invptr[i];
        }
        std::cout<<"]"<<std::endl;
    }

};


class GeomProg {
private:
    double fel;
    double div;
    double* ptr;
    int size;
    bool valid(double* data, int sz, double one, double step) const {
        double espect = 1e-6;
        for (int i = 0; i < sz; ++i) {
            double test = one * std::pow(step, i);
            if (std::fabs(test - data[i]) > espect) {
                return false;
            }
        }
        return true;
    }

public:
    GeomProg(double one, double step,double* input, int sz) {
        if (sz <= 0) {
            throw std::invalid_argument("Размер массива должен быть больше 0");
        }
        if (!valid(input, sz, one, step)) {
            throw GeomProgErr(
                "Массив не является геом прогрессией с заданными условиями.",
                one,step,input,sz
                );
        }
        fel = one;
        div = step;
        size = sz;

        ptr = new double[size];
        for (int i = 0; i < size; ++i) {
            ptr[i] = input[i];
        }
    }
    ~GeomProg() {
        delete[] ptr;
    }

    void print() const {
        std::cout<<"Вывод Массива:"<<std::endl;
        std::cout<<"Первый элемент: "<<fel<<std::endl;
        std::cout<<"Знаменатель: "<<div<<std::endl;
        std::cout<<"Элементы: [";
        for (int i = 0; i < size; ++i) {
            std::cout<<" "<<ptr[i];
        }
        std::cout<<"]"<<std::endl;
    }
};





int main() {
    std::cout<<"_________________________ТЕСТ 1 Без исключения ____________________________"<<std::endl;
    try {
        double work_mass[] = {2.0, 6.0, 18.0, 54.0, 162.0};
        GeomProg test(2.0,3.0,work_mass,5);
        test.print();
    }catch (const std::exception& err) {
        std::cout<<"Непреднамеренное исключение: "<<err.what()<<std::endl;
    }
    std::cout<<"_________________________ТЕСТ 2 С исключением ____________________________"<<std::endl;
    try {
        double wrong_mass[] = {2.0, 6.0, 20.0, 54.0, 162.0};
        GeomProg test1(2.0,3.0,wrong_mass,5);
        test1.print();
    }catch (const GeomProgErr& err) {
        err.printMessage();
        std::cout<<"Поймано нестандартное исключение!"<<std::endl;
    }catch (const std::exception& err) {
        std::cout<<"Поймано стандартное исключение: "<<err.what()<<std::endl;
    }
    return 0;
}