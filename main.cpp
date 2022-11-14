#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#include "log_duration.h"

//-----Количество простых чисел строго меньше n (n - натуральное число)

using namespace std;

bool IsPrime1(size_t p) {
    size_t sp = sqrt(p);
    for (size_t i = 2; i <= sp; ++i) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}

bool IsPrime2(size_t p) {
    size_t sp = sqrt(p);

    for (size_t i = 3; i <= sp; i += 2) {
        if (p % i == 0 ) {
            return false;
        }

    }
    return true;
}


vector<size_t> Experimental_1(size_t n) {
    LOG_DURATION("Experimental_1");

    vector<size_t> result(0);

    for (size_t i = 2; i < n; ++i) {
        if (IsPrime1(i)) {
            result.push_back(i);
        }
    }
    return result;
}

vector<size_t> Experimental_2(size_t n) {
    LOG_DURATION("Experimental_2");

    vector<size_t> result(0);
    result.push_back(2);

    for (size_t i = 3; i < n; i += 2) {
        if (IsPrime2(i)) {
            result.push_back(i);
        }
    }
    return result;
}

vector<size_t> Experimental_3(size_t n) {
    LOG_DURATION("Experimental_3");

    vector<size_t> lp(n);
    for (size_t i = 0; i < n; ++i) {
        lp[i] = i;
    }
    lp[1] = 0;

    for (size_t i = 4; i <= n; i += 2) {
        lp[i] = 0;
    }

    for (size_t i = 3; i * i < n; ++i){
        if (lp[i] != 0) {
            for (size_t ii = i*i; ii < n; ii += i) {
                lp[+ii] = 0;
            }
        }
    }

    vector<size_t> result(0);
    for (size_t i = 0; i < n; ++i) {
        if (lp[i] != 0) {
            result.push_back(lp[i]);
        }
    }
    return result;
}

void Experimental_4(int n) {
    LOG_DURATION("Experimental_4");

    int* pointer = (int*) malloc(n * sizeof(int));
    int k = 0;

    for (int i = 0; i < n; ++i) {
        *(pointer + i) = i;
        ++k;
    }

    *(pointer + 1) = 0;
    k -= 2; // Вычитаем места цифр 0 и 1

    for (int i = 4; i < n; i += 2) {
        *(pointer + i) = 0;
        --k;
    }

    for (int i = 3; i*i < n; ++i) {
        if (*(pointer + i) != 0) {
            for (int ii = i*i; ii < n; ii += i) {
                if (*(pointer + ii) != 0) {
                    *(pointer + ii) = 0;
                    --k;
                }

            }
        }
    }

//    cout << endl;
//    //int* result[n];
//    int j = 0;
//    for (int i = 0; i < n; i += 1) {
//        if (*(pointer + i) != 0) {
//            //result[j] = (pointer + i);
//            //cout << *(pointer + i) << " ";
//            ++j;
//        }
//    }
    cout << endl << "Количество найденных простых чисел = " << k << endl;
    //cout << endl << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << "Calculate PN --OK--" << endl;
}

void Experimental_5(int n) {
    LOG_DURATION("Experimental_5");

    int* pointer = (int*) malloc(n * sizeof(int));
    int k = 0;

    for (int i = 0; i < n; ++i) {
        *(pointer + i) = i;
        ++k;
    }

    *(pointer + 1) = 0;
    k -= 2; // Вычитаем места цифр 0 и 1

    for (int i = 4; i < n; i += 2) {
        *(pointer + i) = 0;
        --k;
    }

    for (int i = 3; i*i < n; ++i) {
        if (*(pointer + i) != 0) {
            for (int ii = i*i; ii < n; ii += i) {
                if (*(pointer + ii) != 0) {
                    *(pointer + ii) = 0;
                    --k;
                }
            }
        }
    }

//    cout << endl;
//    //int* result[n];
//    int j = 0;
//    for (int i = 0; i < n; i += 1) {
//        if (*(pointer + i) != 0) {
//            //result[j] = (pointer + i);
//            //cout << *(pointer + i) << " ";
//            ++j;
//        }
//    }
    cout << endl << "Количество найденных простых чисел = " << k << endl;
    //cout << endl << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << "Calculate PN --OK--" << endl;
}

vector<size_t> Eratosfen(size_t n) {
    LOG_DURATION("Eratosfen");

    vector<size_t> lp(n);
    for (size_t i = 0; i < n; ++i) {
        lp[i] = 0;
    }
    vector<size_t> result(0);

    for (size_t i = 2; i < n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            result.push_back(i);
        }

        for(size_t p : result) {
            if (p <= lp[i] && p*i <= n) {
                lp[p*i] = p;
            }
        }
    }
    return result;
}

void OptimizedEratosfen(int n) {
    LOG_DURATION("OptimizedEratosfen");

    int* pointer = (int*) malloc((n/2 + 1) * sizeof(int));
    *pointer = 2;
    int k = 1;  // Засчитываем цифру 2

    for (int i = 3; i < n; i += 2) {
        *(pointer + (int)i/2) = i;
        ++k;
    }

    int maxFactor = (int)sqrt(n);

    for (int i = 3; i <= maxFactor; i += 2) {
        if (*(pointer + (int)i/2) != 0) {
            for (int ii = i*i; ii < n; ii += 2*i) {
                if (*(pointer + (int)ii/2) != 0) {
                    *(pointer + (int)ii/2) = 0;
                    --k;
                }
            }
        }
    }

//    cout << endl;
//    int j = 0;
//    for (int i = 0; i < n/2; i += 1) {
//        if (*(pointer + i) != 0) {
//            //cout << *(pointer + i) << " ";
//            ++j;
//        }
//    }
    cout << endl << "Количество найденных простых чисел = " << k << endl;
    //cout << endl << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << "Calculate PN --OK--" << endl;
}

void Print(const vector<size_t>& prime_numbers) {
    cout << "Количество найденных простых чисел = " << prime_numbers.size() << endl;
    //for (size_t i = 0; i < prime_numbers.size(); ++i) { cout << prime_numbers[i] << " "; }
    cout << endl << "Calculate PN --OK--" << endl << endl;
}

int main() {
    int n;
    cin >> n;
    cout << endl << "Поиск простых чисел от 2 до " << n << " --->" << endl;

    Print(Eratosfen(n));
    Print(Experimental_1(n));
    Print(Experimental_2(n));
    Print(Experimental_3(n));
    Experimental_4(n);
    OptimizedEratosfen(n);

    cout << endl;

    return 0;
}
