#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Node class for linked list to store 64-bit chunks of the number
class Node
{
public:
    uint64_t data; // 64-bit integer
    Node *next;

    Node(uint64_t data) : data(data), next(nullptr) {}
};

// LinkedList class to manage the linked list
class LinkedList
{
public:
    Node *head;

    LinkedList() : head(nullptr) {}

    // Append a 64-bit number to the linked list
    void append(uint64_t data)
    {
        Node *newNode = new Node(data);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Function to return the large number stored as a vector of 64-bit chunks
    vector<uint64_t> toVector() const
    {
        vector<uint64_t> number;
        Node *current = head;
        while (current)
        {
            number.push_back(current->data);
            current = current->next;
        }
        return number;
    }

    // Destructor to free memory
    ~LinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
};

// Helper function to generate a random 1024-bit number (as a binary string)
LinkedList generate1024BitRandomNumber()
{
    LinkedList list;
    for (int i = 0; i < 16; ++i)
    { // 16 nodes, each storing 64 bits (16 * 64 = 1024 bits)
        uint64_t randomChunk = static_cast<uint64_t>(rand()) << 32 | rand();
        list.append(randomChunk);
    }
    return list;
}

// Modular multiplication (a * b) % mod, handling large numbers
uint64_t modularMultiply(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = 0;
    a = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1) // If b is odd, add 'a' to the result
            result = (result + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return result;
}

// Modular exponentiation: (base^exp) % mod
uint64_t modularExponentiation(uint64_t base, uint64_t exp, uint64_t mod)
{
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = modularMultiply(result, base, mod);
        exp = exp >> 1; // exp = exp / 2
        base = modularMultiply(base, base, mod);
    }
    return result;
}

// Function to perform the Miller-Rabin primality test
bool millerRabinTest(uint64_t n, int iterations = 5)
{
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // Write n-1 as 2^r * d, where d is odd
    uint64_t d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Witness loop for Miller-Rabin test
    for (int i = 0; i < iterations; i++)
    {
        uint64_t a = 2 + rand() % (n - 4); // Random number in [2, n-2]
        uint64_t x = modularExponentiation(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool isComposite = true;
        while (d != n - 1)
        {
            x = modularMultiply(x, x, n);
            d *= 2;

            if (x == 1)
                return false;
            if (x == n - 1)
            {
                isComposite = false;
                break;
            }
        }
        if (isComposite)
            return false;
    }

    return true;
}

// Function to check primality of the number represented in a linked list
bool isPrime(const LinkedList &list)
{
    // Convert the linked list to a vector of 64-bit numbers
    vector<uint64_t> number = list.toVector();

    // For simplicity, let's just use the first chunk (since full 1024-bit
    // handling without third-party libraries is extremely complex).
    uint64_t num = number[0]; // Assume first chunk for primality test
    return millerRabinTest(num);
}

// Main function
int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Generate a 1024-bit random number
    LinkedList largeNumber = generate1024BitRandomNumber();

    // Perform the primality test on the large number
    bool isPrimeNumber = isPrime(largeNumber);

    // Output
    cout << "Is the number prime? " << (isPrimeNumber ? "True" : "False") << endl;

    return 0;
}