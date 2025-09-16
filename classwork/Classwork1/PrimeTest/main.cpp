/* PrimeTest Classwork
 * Jonah Shulske - COSC-2436 Fall 2025
 * September 9, 2025 + September 11, 2025
 * This program will check if a number is prime using various algorithms.
 * It will measure in seconds how long each algorithm takes to execute.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>   // Lets you measure high residual timing. Finer than milliseconds.
#include <bitset>   // Kinda like a vector. Each element is a single bit. Very compact container.
#include <fstream>
#include <stdexcept>
#include <cstdlib> // C standard library
#include <ctime>    // Gives actual clock time
using namespace std;
using namespace std::chrono;

// Constants
const int MAX_N = 100000000;    // 100,000,000
bitset<MAX_N> sieve;    // Don't do this

// Prototypes
bool IsPrimeBruteForce(long long N);
bool IsPrimeSkipEven(long long N);
bool IsPrimeSqrt(long long N);
bool MillerTest(long long D, long long N);
bool IsPrimeMillerRabin(long long N);
void GenerateSieve();
void GetTestPrimes(vector<long long>& primes, int numPrimes, string fileName);



int main()
{
    vector<long long> testPrimes;
    int primesToTest = 200;
    try 
    {
        GetTestPrimes(testPrimes, primesToTest, "primes.txt");
        /*for (auto N : testPrimes)     // Simple test for whether the program would print
            std::cout << N << endl;*/
    }
    catch (const exception& E)
    {
        cerr << E.what() << endl;
        return EXIT_FAILURE;
    }

    srand(time(0));     // Seeding rng with current computer clock time

    // Test Brute Force
    std::cout << "Starting Brute Force Test...\nWorking..." << endl;

    int count = 0;
    auto start = high_resolution_clock::now();        //std::chrono::high_resolution_clock::now();
    for (auto N : testPrimes)
        if (IsPrimeBruteForce(N))
            count++;

    auto end = high_resolution_clock::now();
    std::cout << "Brute Force Time: " << duration<double>(end - start).count() << "s\n" << endl;


    // Test Skip Even
    std::cout << "Starting Skip Even Test...\nWorking..." << endl;

    count = 0;
    start = high_resolution_clock::now();
    for (auto N : testPrimes)
        if (IsPrimeSkipEven(N))
            count++;

    end = high_resolution_clock::now();
    std::cout << "Skip Even Time: " << duration<double>(end - start).count() << "s\n" << endl;

    // Test Square Root
    std::cout << "Starting Square Root Test...\nWorking..." << endl;

    count = 0;
    start = high_resolution_clock::now();
    for (auto N : testPrimes)
        if (IsPrimeSqrt(N))
            count++;

    end = high_resolution_clock::now();
    std::cout << "Square Root Time: " << duration<double>(end - start).count() << "s\n" << endl;

    // Test Miller-Rabin
    std::cout << "Starting Miller-Rabin Test...\nWorking..." << endl;

    count = 0;
    start = high_resolution_clock::now();
    for (auto N : testPrimes)
        if (IsPrimeMillerRabin(N))
            count++;

    end = high_resolution_clock::now();
    std::cout << "Miller-Rabin Test Time: " << duration<double>(end - start).count() << "s\n" << endl;

    // Test Sieve
    std::cout << "Starting Sieve Test...\nWorking..." << endl;
    start = high_resolution_clock::now();
    GenerateSieve();
    end = high_resolution_clock::now();
    std::cout << "Sieve Creation Time: " << duration<double>(end - start).count() << "s\n" << endl;

    start = high_resolution_clock::now();
    count = 0;
    for (auto N : testPrimes)
        if (sieve[N])
            count++;
    end = high_resolution_clock::now();
    std::cout << "Sieve Look-Up Time: " << duration<double>(end - start).count() << "s\n" << endl;

    return 0;
}

bool IsPrimeBruteForce(long long N)
{
    if (N < 2) return false;

    for (long long index = 2; index < N; ++index)
        if (N % index == 0) return false;

    return true;
}

bool IsPrimeSkipEven(long long N)
{
    if (N < 2) return false;
    if (N == 2) return true;
    if (N % 2 == 0) return false;

    for (long long index = 3; index < N; index += 2)
        if (N % index == 0) return false;

    return true;
}

bool IsPrimeSqrt(long long N)
{
    if (N < 2) return false;
    if (N == 2) return true;
    if (N % 2 == 0) return false;
    long long sqrtN = ceil(sqrt(N));
    for (long long index = 3; index <= sqrtN; index += 2)
        if (N % index == 0) return false;

    return true;
}

bool MillerTest(long long D, long long N)
{
    long long A = 2 + rand() % (N - 4);     // A = between 3 and N - 1
    long long X = 1, base = A;

    long long power = D;
    while (power > 0)
    {
        if (power % 2 == 1)
            X = (X * base) % N;

        base = (base * base) % N;
        power /= 2;
    }

    if (X == 1 || X == N - 1)  return true;

    while (D != N - 1)
    {
        X = (X * X) % N;
        D *= 2;
        if (X == 1) return false;
        if (X == N - 1) return true;
    }
    return false;
}

bool IsPrimeMillerRabin(long long N)
{
    if (N < 2) return false;
    if (N != 2 && N % 2 == 0) return false;
    long long D = N - 1;

    while (D % 2 == 0) D /= 2;
    int K = 5;      // Number of Trials. Should probably be a parameter

    for (int index = 0; index < K; ++index)
        if (!MillerTest(D, N)) return false;

    return true;
}

// Generate the Sieve of Eratosthenes. Builds table of primes
void GenerateSieve()
{
    sieve.set();   // Sets all bits to true (1)
    sieve[0] = sieve[1] = 0;
    long long sqrtMAX_N = ceil(sqrt(MAX_N));

    for (long long index = 2; index * index < sqrtMAX_N; ++index)
        if (sieve[index])
            for (long long J = index * index; J < MAX_N; J += index)
                sieve[J] = 0;
}

void GetTestPrimes(vector<long long>&primes, int numPrimes, string fileName)
{
    if (numPrimes < 1 || numPrimes > 1000)
        throw runtime_error("Error: Can only get number of primes from 1 - 1,000");

    ifstream inFile(fileName);
    if (!inFile)
        throw runtime_error("Error: Cannot open file / File not found");
    
    primes.clear();
    primes.resize(numPrimes);
    for (size_t index = 0; index < numPrimes; ++index)
        inFile >> primes[index];
    inFile.close();

}
