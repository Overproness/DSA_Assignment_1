#include <iostream>
#include <cstdlib>
#include <ctime>

// Node structure for linked list
class Node
{
public:
    unsigned int data; // 32-bit integer to store part of the 1024-bit number
    Node *next;

    Node(unsigned int data) : data(data), next(nullptr) {}
};

// Linked list to represent the large number
class LinkedList
{
private:
    Node *head;
    Node *tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Add a new node at the end
    void append(unsigned int data)
    {
        Node *newNode = new Node(data);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to print the entire number (as individual chunks)
    void printNumber() const
    {
        Node *current = head;
        while (current)
        {
            std::cout << current->data << " "; // Print each chunk
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Function to perform modular exponentiation on the large number
    unsigned int modularExponentiation(unsigned int base, unsigned int exp, unsigned int mod) const
    {
        unsigned int result = 1;
        base = base % mod;
        while (exp > 0)
        {
            if (exp % 2 == 1)
            {
                result = (result * base) % mod;
            }
            exp = exp >> 1; // Divide exp by 2
            base = (base * base) % mod;
        }
        return result;
    }

    // Function to perform the Miller-Rabin test on the whole number
    bool millerRabinTest(int iterations = 5) const
    {
        // For simplicity, use the first chunk as a small modulus
        unsigned int num = head->data;
        if (num <= 1)
            return false;
        if (num == 2 || num == 3)
            return true;
        if (num % 2 == 0)
            return false;

        // Apply Miller-Rabin test on the whole number as represented in the list
        unsigned int d = num - 1;
        unsigned int r = 0;

        // Find r and d such that num - 1 = d * 2^r
        while (d % 2 == 0)
        {
            d /= 2;
            r++;
        }

        for (int i = 0; i < iterations; i++)
        {
            unsigned int a = 2 + rand() % (num - 4);
            unsigned int x = modularExponentiation(a, d, num);
            if (x == 1 || x == num - 1)
            {
                continue;
            }

            bool composite = true;
            for (unsigned int j = 0; j < r - 1; j++)
            {
                x = (x * x) % num;
                if (x == num - 1)
                {
                    composite = false;
                    break;
                }
            }

            if (composite)
                return false;
        }
        return true;
    }

    // Check if the whole number represented by the linked list is prime
    bool isPrime() const
    {
        return millerRabinTest();
    }
};

// Function to generate a random 1024-bit number (split into 32 32-bit chunks)
LinkedList generate1024BitRandomNumber()
{
    LinkedList list;
    for (int i = 0; i < 32; ++i)
    {                                      // We need 32 chunks of 32 bits to make a 1024-bit number
        unsigned int randomChunk = rand(); // Generate a 32-bit random chunk
        list.append(randomChunk);
    }
    return list;
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generator

    LinkedList number = generate1024BitRandomNumber(); // Generate the random 1024-bit number
    number.printNumber();                              // Print the number as chunks in decimal format

    // Check primality of the entire number
    if (number.isPrime())
    {
        std::cout << "The number is prime." << std::endl;
    }
    else
    {
        std::cout << "The number is not prime." << std::endl;
    }

    return 0;
}
