#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "omp.h"

//3557 2579
using namespace std;

long int calculateE(long int t);

long int greatestCommonDivisor(long int e, long int t);

long int calculateD(long int e, long int t);

long int encrypt(long int i, long int e, long int n);

long int decrypt(long int i, long int d, long int n);

int main() {
    long int p, q, n, t, e, d;
    int thread, length;
    char sym[100000];
    long int encryptedText[100000];
    long int decryptedText[100000];
    string msg;

    memset(encryptedText, 0, sizeof(encryptedText));
    memset(decryptedText, 0, sizeof(decryptedText));

    cout << "Welcome to RCA program" << endl << endl;

//    cout << "Enter a Prime number  p :" << endl;
//    cin >> p;
    p = 3557;

//    cout << "Enter a Prime number  q :" << endl;
//    cin >> q;
    q = 2579;

    n = p * q;
    cout << "\nResult of computing n = p*q = " << n << endl;

    t = (p - 1) * (q - 1);
    cout << "Result of computing Euler's totient function:\t t = " << t << endl;

    e = calculateE(t);
    d = calculateD(e, t);

    cout << "\nRSA public key is (n = " << n << ", e = " << e << ")" << endl;
    cout << "RSA private key is (n = " << n << ", d = " << d << ")" << endl;


    cout << "\nWrite array length:" << endl;
    cin >> length;

    cout << "\nWrite thread:" << endl;
    cin >> thread;

    for (int i = 0; i < length; ++i) {
        char num = char(65 + rand() % 26);
        msg.push_back(num);
        printf("%c", sym[i]);
    }

    // encryption
    for (long int i = 0; i < msg.length(); i++) {
        encryptedText[i] = encrypt(msg[i], e, n);
    }

    //decryption
    double start_time = omp_get_wtime();
#pragma omp parallel for num_threads(thread)
    for (long int i = 0; i < msg.length(); i++) {
        decryptedText[i] = decrypt(encryptedText[i], d, n);
    }
    double end_time = omp_get_wtime();
    printf("\nTime %f \n", end_time - start_time);

    cout << endl << endl;

    return 0;
}

long int calculateE(long int t) {
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)

    long int e;

    for (e = 2; e < t; e++) {
        if (greatestCommonDivisor(e, t) == 1) {
            return e;
        }
    }

    return -1;
}

long int greatestCommonDivisor(long int e, long int t) {
    while (e > 0) {
        long int myTemp;

        myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int calculateD(long int e, long int t) {
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long int d;
    long int k = 1;

    while (1) {
        k = k + t;

        if (k % e == 0) {
            d = (k / e);
            return d;
        }
    }

}

long int encrypt(long int i, long int e, long int n) {
    long int current, result;

    current = i - 97;
    result = 1;

    for (long int j = 0; j < e; j++) {
        result = result * current;
        result = result % n;
    }

    return result;
}

long int decrypt(long int i, long int d, long int n) {
    long int current, result;

    current = i;
    result = 1;

    for (long int j = 0; j < d; j++) {
        result = result * current;
        result = result % n;
    }

    return result + 97;
}