#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#include "log_duration.h"

//-----Поиск простых чисел строго меньше n (n - натуральное число)

using namespace std;

vector<int> Eratosfen(int n) {
    LOG_DURATION("Eratosfen");

    vector<int> lp(n);
    for (int i = 0; i < n; ++i) {
        lp[i] = 0;
    }
    vector<int> result(0);

    for (int i = 2; i < n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            result.push_back(i);
        }

        for(int p : result) {
            if (p <= lp[i] && p*i <= n) {
                lp[p*i] = p;
            }
        }
    }
    return result;
}

bool IsPrime1(int p) {
    int sp = sqrt(p);
    for (int i = 2; i <= sp; ++i) {
        if (p % i == 0) {
            return false;
        }
    }
    return true;
}

bool IsPrime2(int p) {
    int sp = sqrt(p);
    for (int i = 3; i <= sp; i += 2) {
        if (p % i == 0 ) {
            return false;
        }
    }
    return true;
}

vector<int> Experimental_0(int n) {
    LOG_DURATION("Experimental_0");

    vector<int> result = {2, 3, 5, 7}; // Засчитываем цифру 2, 3, 5, 7

    for (int i = 12; i < n; i += 6) {
        if ( IsPrime1(i - 1) ) { result.push_back(i - 1); }
        if ( IsPrime1(i + 1) ) { result.push_back(i + 1); }
    }

    cout << endl << "Количество найденных простых чисел = " << result.size() << endl;
    cout << "Calculate PN --OK--" << endl;

    return result;
}

vector<int> Experimental_1(int n) {
    LOG_DURATION("Experimental_1");

    vector<int> result(0);

    for (int i = 2; i < n; ++i) {
        if (IsPrime1(i)) {
            result.push_back(i);
        }
    }
    return result;
}

vector<int> Experimental_2(int n) {
    LOG_DURATION("Experimental_2");

    vector<int> result(0);
    result.push_back(2);

    for (int i = 3; i < n; i += 2) {
        if (IsPrime2(i)) {
            result.push_back(i);
        }
    }
    return result;
}

vector<int> Experimental_3(int n) {
    LOG_DURATION("Experimental_3");

    vector<int> lp(n);
    for (int i = 0; i < n; ++i) {
        lp[i] = i;
    }
    lp[1] = 0;

    for (int i = 4; i <= n; i += 2) {
        lp[i] = 0;
    }

    for (int i = 3; i * i < n; ++i){
        if (lp[i] != 0) {
            for (int ii = i*i; ii < n; ii += i) {
                lp[+ii] = 0;
            }
        }
    }

    vector<int> result(0);
    for (int i = 0; i < n; ++i) {
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
//            cout << *(pointer + i) << " ";
//            ++j;
//        }
//    }
    cout << endl << "Количество найденных простых чисел = " << k << endl;
    //cout << endl << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << "Calculate PN --OK--" << endl;
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
//            cout << *(pointer + i) << " ";
//            ++j;
//        }
//    }
    cout << endl << "Количество найденных простых чисел = " << k << endl;
    //cout << endl << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << "Calculate PN --OK--" << endl;
}

vector<int> OptimizedEratosfen1(int n) {
    LOG_DURATION("OptimizedEratosfen1");

    vector<int> result(n/2 + 1);
    result[0] = 2;
    int k = 1;

    //for (int i = 3; i < n; i += 2) { lp[i] = 0; }

    for (int i = 3; i < n; i += 2) {
        result[(int)i/2] = i;
        ++k;
    }

    int maxFactor = (int)sqrt(n);

    for (int i = 3; i <= maxFactor; i += 2) {
        if (result[(int)i/2] != 0) {
            for (int ii = i*i; ii < n; ii += 2*i) {
                if (result[(int)ii/2] != 0) {
                    result[(int)ii/2] = 0;
                    --k;
                }
            }
        }
    }

    vector<int> res(k);

    int size = result.size();
    int j = 0;
    for (int i = 0; i < size; i += 1) {
        if (result[i] != 0) {
            res[j] = result[i];
            ++j;
        }
    }
    return res;
}

void OptimizedEratosfen2(int n) {
    LOG_DURATION("OptimizedEratosfen2");

    static bool result[500'000'000];

    int k = n/2;
    for (int i = 1; i < n/2 + 1; ++i) {
        result[i] = true;
    }

    int maxFactor = (int)sqrt(n);

    for (int i = 3; i <= maxFactor; i += 2) {
        if (result[i/2]) {
            for (int ii = i*i; ii < n; ii += 2*i) {
                if (result[ii/2]) {
                    result[ii/2] = false;
                    --k;
                }
            }
        }
    }

//    int j = 1;
//    for (int i = 1; i < n/2; i += 1) {
//        if (result[i]) {
//            ++j;
//        }
//    }

    cout << "Количество найденных простых чисел = " << k << endl;
    //cout << "Количество найденных простых чисел (повторно) = " << j << endl;
    cout << endl << "Calculate PN --OK--" << endl << endl;
}

void Print(const vector<int>& prime_numbers) {
    cout << "Количество найденных простых чисел = " << prime_numbers.size() << endl;
    //for (int i = 0; i < prime_numbers.size(); ++i) { cout << prime_numbers[i] << " "; }
    cout << endl << "Calculate PN --OK--" << endl << endl;
}

int main() {
    int n = 0;
    cin >> n;
    cout << endl << "Поиск простых чисел от 2 до " << n << " --->" << endl;

    //Print(Eratosfen(n));
//    Print(Experimental_0(n));
//    Print(Experimental_1(n));
//    Print(Experimental_2(n));
//    Print(Experimental_3(n));
//    Experimental_4(n);

    OptimizedEratosfen(n);
    Print(OptimizedEratosfen1(n));
    OptimizedEratosfen2(n);

    cout << endl;

    return 0;
}
