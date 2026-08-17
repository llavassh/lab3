#include "Queue.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "Algorithms.h"

using namespace std;

int square(const int& x) { return x * x; }
int doubleVal(const int& x) { return x * 2; }
bool isEven(const int& x) { return x % 2 == 0; }
bool isOdd(const int& x) { return x % 2 != 0; }
bool isPositive(const int& x) { return x > 0; }
int sum(const int& a, const int& b) { return a + b; }
int multiply(const int& a, const int& b) { return a * b; }
int maxVal(const int& a, const int& b) { return a > b ? a : b; }
int minVal(const int& a, const int& b) { return a < b ? a : b; }
bool lessInt(const int& a, const int& b) { return a < b; }

//очистка потока ввода после ошибки
void ClearInput() {
    cin.clear();    //сбрасывает флаги ошибок
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // выкидывает символы из входного буфера
}

int* ReadArray(int n) {
    if (n <= 0) {
        return nullptr;
    }
    int* arr = new int[n];
    cout << "Enter " << n << "integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}

template <typename T>
void PrintSeq(Sequence<T>* seq, const string& name) {
    cout << name << "[" << seq->GetLength() << "]: ";
    for (int i = 0; i < seq->GetLength(); i++) {
        cout << seq->Get(i);
        if (i < seq->GetLength() - 1) cout << ", ";
    }
    cout << endl;
}

void DemoStack() {
    Stack<int> s;
    int choice;
    
    do {
        cout << "\n  --- STACK MENU ---\n";
        cout << " 1. Push\n";
        cout << " 2. Pop\n";
        cout << " 3. Peek\n";
        cout << " 4. Show\n";
        cout << " 5. Concat\n";
        cout << " 6. GetSubsequence\n";
        cout << " 7. FindSubsequence\n";
        cout << " 8. Split\n";
        cout << " 9. Map\n";
        cout << " 10. Where\n";
        cout << " 11. Reduce\n";
        cout << "  0. Back\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                s.Push(val);
                cout << "Stack: " << s << "\n";
                break;
            }
            case 2: {
                try {
                    int val = s.Pop();
                    cout << "Popped: " << val << "\n";
                    cout << "Stack: " << s << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                try {
                    cout << "Top: " << s.Peek() << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                cout << "Stack: " << s << "\n";
                break;
            }
            case 5: {
                cout << "Second stack size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Stack<int> s2(arr, n);
                delete[] arr;
                Stack<int> res = s.Concat(s2);
                cout << "Result: " << res << "\n";
                break;
            }
            case 6: {
                int start, end;
                cout << "Start and end index: ";
                cin >> start >> end;
                try {
                    Stack<int> sub = s.GetSubSequence(start, end);
                    cout << "Subsequence: " << sub << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 7: {
                cout << "Pattern size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Stack<int> pattern(arr, n);
                delete[] arr;
                int pos = s.FindSubSequence(pattern);
                if (pos != -1) cout << "Found at index: " << pos << "\n";
                else cout << "Not found\n";
                break;
            }
            case 8: {
                cout << "Split by: 1. even 2. odd 3. positive\n Choice: ";
                int opt;
                cin >> opt;
                
                Stack<int> s1, s2;
                if (opt == 1) s.Split(isEven, s1, s2);
                else if (opt == 2) s.Split(isOdd, s1, s2);
                else if (opt == 3) s.Split(isPositive, s1, s2);
                
                cout << "True stack:  " << s1 << "\n";
                cout << "False stack: " << s2 << "\n";
                break;
            }
            case 9: {
                cout << "1. square 2. double\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "Result: " << s.Map(square) << "\n";
                else if (opt == 2) cout << "Result: " << s.Map(doubleVal) << "\n";
                break;
            }
            case 10: {
                cout << "1. even 2. odd 3. positive\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "  Result: " << s.Where(isEven) << "\n";
                else if (opt == 2) cout << "Result: " << s.Where(isOdd) << "\n";
                else if (opt == 3) cout << "Result: " << s.Where(isPositive) << "\n";
                break;
            }
            case 11: {
                cout << "1. sum 2. product 3. max 4. min\n Choice: ";
                int opt;
                cin >> opt;
                int res = 0;
                if (opt == 1) res = s.Reduce(sum, 0);
                else if (opt == 2) res = s.Reduce(multiply, 1);
                else if (opt == 3) {
                    if (s.IsEmpty()) {
                        cout << "Stack is empty\n";
                        break;
                    }
                    res = s.Reduce(maxVal, s.Get(0));
                }
                else if (opt == 4) {
                    if (s.IsEmpty()) {
                        cout << "Stack is empty\n";
                        break;
                    }
                    res = s.Reduce(minVal, s.Get(0));
                }
                cout << "Result: " << res << "\n";
                break;
            }
        }
    } while (choice != 0);
}

void DemoQueue() {
    Queue<int> q;
    int choice;
    
    do {
        cout << "\n  --- QUEUE MENU ---\n";
        cout << " 1. Enqueue\n";
        cout << " 2. Dequeue\n";
        cout << " 3. Peek\n";
        cout << " 4. Show\n";
        cout << " 5. Concat\n";
        cout << " 6. GetSubsequence\n";
        cout << " 7. FindSubsequence\n";
        cout << " 8. Split\n";
        cout << " 9. Map\n";
        cout << " 10. Where\n";
        cout << " 11. Reduce\n";
        cout << "  0. Back\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "Value: ";
                cin >> val;
                q.Enqueue(val);
                cout << "Queue: " << q << "\n";
                break;
            }
            case 2: {
                try {
                    int val = q.Dequeue();
                    cout << "Dequeued: " << val << "\n";
                    cout << "Queue: " << q << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                try {
                    cout << "Front: " << q.Peek() << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                cout << "Queue: " << q << "\n";
                break;
            }
            case 5: {
                cout << "Second queue size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Queue<int> q2(arr, n);
                delete[] arr;
                Queue<int> res = q.Concat(q2);
                cout << "Result: " << res << "\n";
                break;
            }
            case 6: {
                int start, end;
                cout << "Start and end indices: ";
                cin >> start >> end;
                try {
                    Queue<int> sub = q.GetSubSequence(start, end);
                    cout << "Subsequence: " << sub << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 7: {
                cout << "Pattern size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Queue<int> pattern(arr, n);
                delete[] arr;
                int pos = q.FindSubSequence(pattern);
                if (pos != -1) cout << "Found at index: " << pos << "\n";
                else cout << "Not found\n";
                break;
            }
            case 8: {
                cout << "Split by: 1. even 2. odd 3. positive\n Choice: ";
                int opt;
                cin >> opt;
                
                Queue<int> q1, q2;
                if (opt == 1) q.Split(isEven, q1, q2);
                else if (opt == 2) q.Split(isOdd, q1, q2);
                else if (opt == 3) q.Split(isPositive, q1, q2);
                
                cout << "True queue:  " << q1 << "\n";
                cout << "False queue: " << q2 << "\n";
                break;
            }
            case 9: {
                cout << "1. square 2. double\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "Result: " << q.Map(square) << "\n";
                else if (opt == 2) cout << "Result: " << q.Map(doubleVal) << "\n";
                break;
            }
            case 10: {
                cout << "1. even 2. odd 3. positive\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "Result: " << q.Where(isEven) << "\n";
                else if (opt == 2) cout << "Result: " << q.Where(isOdd) << "\n";
                else if (opt == 3) cout << "Result: " << q.Where(isPositive) << "\n";
                break;
            }
            case 11: {
                cout << "1. sum 2. product 3. max 4. min\n Choice: ";
                int opt;
                cin >> opt;
                int res = 0;
                if (opt == 1) res = q.Reduce(sum, 0);
                else if (opt == 2) res = q.Reduce(multiply, 1);
                else if (opt == 3) {
                    if (q.IsEmpty()) {
                        cout << "Queue is empty\n";
                        break;
                    }
                    res = q.Reduce(maxVal, q.Get(0));
                }
                else if (opt == 4) {
                    if (q.IsEmpty()) {
                        cout << "Queue is empty\n";
                        break;
                    }
                    res = q.Reduce(minVal, q.Get(0));
                }
                cout << "Result: " << res << "\n";
                break;
            }
        }
    } while (choice != 0);
}

void DemoDeque() {
    Deque<int> d;
    int choice;
    
    do {
        cout << "\n  --- DEQUE MENU ---\n";
        cout << " 1. PushFront\n";
        cout << " 2. PushBack\n";
        cout << " 3. PopFront\n";
        cout << " 4. PopBack\n";
        cout << " 5. PeekFront/PeekBack\n";
        cout << " 6. Show\n";
        cout << " 7. Sort\n";
        cout << " 8. Merge\n";
        cout << " 9. Concat\n";
        cout << " 10. GetSubsequence\n";
        cout << " 11. FindSubsequence\n";
        cout << " 12. Map\n";
        cout << " 13. Where\n";
        cout << " 14. Reduce\n";
        cout << "  0. Back\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int val;
                cout << "  Value: ";
                cin >> val;
                d.PushFront(val);
                cout << "  Deque: " << d << "\n";
                break;
            }
            case 2: {
                int val;
                cout << "Value: ";
                cin >> val;
                d.PushBack(val);
                cout << "Deque: " << d << "\n";
                break;
            }
            case 3: {
                try {
                    int val = d.PopFront();
                    cout << "Popped front: " << val << "\n";
                    cout << "Deque: " << d << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                try {
                    int val = d.PopBack();
                    cout << "Popped back: " << val << "\n";
                    cout << "Deque: " << d << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                try {
                    cout << "Front: " << d.PeekFront() << "\n";
                    cout << "Back:  " << d.PeekBack() << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 6: {
                cout << "Deque: " << d << "\n";
                break;
            }
            case 7: {
                Deque<int> sorted = d.Sort(lessInt);
                cout << "Sorted: " << sorted << "\n";
                break;
            }
            case 8: {
                cout << "Second deque size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Deque<int> d2(arr, n);
                delete[] arr;
                Deque<int> merged = d.Merge(d2, lessInt);
                cout << "Merged: " << merged << "\n";
                break;
            }
            case 9: {
                cout << "Second deque size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Deque<int> d2(arr, n);
                delete[] arr;
                Deque<int> res = d.Concat(d2);
                cout << "Result: " << res << "\n";
                break;
            }
            case 10: {
                int start, end;
                cout << "Start and end indices: ";
                cin >> start >> end;
                try {
                    Deque<int> sub = d.GetSubSequence(start, end);
                    cout << "Subsequence: " << sub << "\n";
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 11: {
                cout << "Pattern size: ";
                int n;
                cin >> n;
                int* arr = ReadArray(n);
                Deque<int> pattern(arr, n);
                delete[] arr;
                int pos = d.FindSubSequence(pattern);
                if (pos != -1) cout << "Found at index: " << pos << "\n";
                else cout << "Not found\n";
                break;
            }
            case 12: {
                cout << " 1. square 2. double\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "  Result: " << d.Map(square) << "\n";
                else if (opt == 2) cout << "  Result: " << d.Map(doubleVal) << "\n";
                break;
            }
            case 13: {
                cout << "1. even 2. odd 3. positive\n Choice: ";
                int opt;
                cin >> opt;
                if (opt == 1) cout << "Result: " << d.Where(isEven) << "\n";
                else if (opt == 2) cout << "Result: " << d.Where(isOdd) << "\n";
                else if (opt == 3) cout << "Result: " << d.Where(isPositive) << "\n";
                break;
            }
            case 14: {
                cout << "1. sum 2. product 3. max 4. min\n Choice: ";
                int opt;
                cin >> opt;
                int res = 0;
                if (opt == 1) res = d.Reduce(sum, 0);
                else if (opt == 2) res = d.Reduce(multiply, 1);
                else if (opt == 3) {
                    if (d.IsEmpty()) {
                        cout << "Deque is empty\n";
                        break;
                    }
                    res = d.Reduce(maxVal, d.Get(0));
                }
                else if (opt == 4) {
                    if (d.IsEmpty()) {
                        cout << "Deque is empty\n";
                        break;
                    }
                    res = d.Reduce(minVal, d.Get(0));
                }
                cout << "Result: " << res << "\n";
                break;
            }
        }
    } while (choice != 0);
}

void DemoAlgorithms() {
    int choice;
    
    do {
        cout << "\n--- ALGORITHMS MENU ---\n";
        cout << "1. Prime numbers up to N\n";
        cout << "2. Count inversions\n";
        cout << "3. Fibonacci numbers\n";
        cout << "4. Factorial\n";
        cout << "5. Range\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                int n;
                cout << "N = ";
                cin >> n;
                auto* primes = Primes(n);
                PrintSeq(primes, "Primes");
                delete primes;
                break;
            }
            case 2: {
                int n;
                cout << "Size = ";
                cin >> n;
                int* arr = ReadArray(n);
                auto* seq = new MutableArraySequence<int>(arr, n);
                delete[] arr;
                cout << "Inversions: " << CountInversions<int>(seq) << "\n";
                delete seq;
                break;
            }
            case 3: {
                int n;
                cout << "Count = ";
                cin >> n;
                auto* fib = Fibonacci(n);
                PrintSeq(fib, "Fibonacci");
                delete fib;
                break;
            }
            case 4: {
                int n;
                cout << "n = ";
                cin >> n;
                auto* fact = Factorial(n);
                cout << "  " << n << "! = " << fact->GetLast() << "\n";
                delete fact;
                break;
            }
            case 5: {
                int l, h;
                cout << "l = ";
                cin >> l;
                cout << "h = ";
                cin >> h;
                try {
                    auto* range = Range(l, h);
                    PrintSeq(range, "Range");
                    delete range;
                } catch (exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;
            }
        }
    } while (choice != 0);
}

// ==================== MAIN ====================

int main() {
    cout << "\n========================================\n";
    cout << "  Laboratory Work #3\n";
    cout << "  Stack | Queue | Deque | Algorithms\n";
    cout << "========================================\n";
    
    int choice;
    do {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Stack (C-3)\n";
        cout << "2. Queue (C-1)\n";
        cout << "3. Deque (C-4)\n";
        cout << "4. Algorithms (A-1.2, A-2.1, A-2.2, A-3, A-3.2)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: DemoStack(); break;
            case 2: DemoQueue(); break;
            case 3: DemoDeque(); break;
            case 4: DemoAlgorithms(); break;
        }
    } while (choice != 0);
    
    return 0;
}