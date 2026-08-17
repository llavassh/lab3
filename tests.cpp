#include <string>
#include <stdexcept>
#include <complex>
#include <cassert>

#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "Person.h"
#include "MutableArraySequence.h"
#include "Algorithms.h"

int sq(const int& x) { return x * x; }
int dbl(const int &x) { return x * 2; }
int three(const int &x) { return x * 3; }
bool even(const int& x) { return x % 2 == 0; }
bool odd(const int& x) { return x % 2 != 0; }
int add(const int& a, const int& b) { return a + b; }
int mul(const int& a, const int& b) { return a * b; }
bool lessint(const int &a, const int &b) { return a < b; }

void testStack() {
    Stack<int> stack1 = Stack<int>();
    assert(stack1.IsEmpty());
    bool thrown1 = false;
    try {
        stack1.Pop();
    } catch (const EmptyContainer&) {
        thrown1 = true;
    }
    assert(thrown1);

    stack1.Push(1);
    stack1.Push(2);
    stack1.Push(3);
    assert(!stack1.IsEmpty());
    assert(stack1.GetSize() == 3);

    assert(stack1.Peek() == 3);
    assert(stack1.GetSize() == 3);
    assert(stack1.Pop() == 3);
    assert(stack1.GetSize() == 2);
    assert(stack1.Get(stack1.GetSize() - 1) == 2);
    bool thrown2 = false;
    try {
        stack1.Get(100);
    } catch(const IndexOutOfRange&) {
        thrown2 = true;
    }
    assert(thrown2);

    //concat
    int arr[] = {1, 2, 3, 4, 5};
    Stack<int> stack2 = Stack<int>(arr, 5);
    assert(stack2.Get(3) == 4);
    Stack<int> concat = stack1.Concat(stack2);
    assert(concat.GetSize() == 7);
    assert(concat.Get(0) == 1); 
    assert(concat.Get(1) == 2); 
    assert(concat.Get(2) == 1); 
    assert(concat.Get(6) == 5);

    //getsubsequence
    Stack<int> sub = stack2.GetSubSequence(1, 3);
    assert(sub.GetSize() == 3);
    assert(sub.Get(0) == 2);
    assert(sub.Get(sub.GetSize() - 1) == 4);
    bool thrown3 = false;
    try {
        stack2.GetSubSequence(100, 200);
    }
    catch (const IndexOutOfRange &) {
        thrown3 = true;
    }
    assert(thrown3);

    //findsubsequence
    int arr2[] = {3, 4};
    Stack<int> pattern1 = Stack<int>(arr2, 2);
    assert(stack2.FindSubSequence(pattern1) == 2);
    int arr3[] = {8, 9};
    Stack<int> pattern2 = Stack<int>(arr3, 2);
    assert(stack2.FindSubSequence(pattern2) == -1);
    Stack<int> pattern3 = Stack<int>();
    assert(stack2.FindSubSequence(pattern3) == 0);

    //split
    Stack<int> trueStack = Stack<int>();
    Stack<int> falseStack = Stack<int>();
    stack2.Split(even, trueStack, falseStack);
    assert(trueStack.GetSize() == 2);
    assert(trueStack.Get(0) == 2);
    assert(trueStack.Get(1) == 4);
    assert(falseStack.GetSize() == 3);
    assert(falseStack.Get(0) == 1);
    assert(falseStack.Get(1) == 3);
    assert(falseStack.Get(2) == 5);

    //map
    Stack<int> map = stack2.Map(sq);
    assert(map.GetSize() == 5);
    assert(map.Get(0) == 1);
    assert(map.Get(1) == 4);
    assert(map.Get(2) == 9);
    assert(map.Get(3) == 16);
    assert(map.Get(4) == 25);
    assert(stack2.Get(3) == 4);

    //where
    Stack<int> where = stack2.Where(odd);
    assert(where.GetSize() == 3);
    assert(where.Get(0) == 1);
    assert(where.Get(1) == 3);
    assert(where.Get(2) == 5);
    assert(stack2.GetSize() == 5);

    //reduce
    assert(stack2.Reduce(add, 0) == 15);
    assert(stack2.Reduce(mul, 1) == 120);

    //copy
    Stack<int> copy = stack2;
    copy.Push(100);
    assert(copy.GetSize() == 6);
    assert(stack2.GetSize() == 5);

    //operators
    Stack<int> assigned;
    assigned = stack2;
    assigned.Pop();
    assert(assigned.GetSize() == 4);
    assert(stack2.GetSize() == 5);
    assert(stack2[2] == 3);
    Stack<int> same(stack2);
    assert(stack2 == same);
    same.Pop();
    assert(stack2 != same);
    Stack<int> plus = stack1 + stack2;
    assert(plus == concat);

    //tests for other types
    double arr4[] = {0.2, 3.4, 1.2};
    Stack<double> stack4 = Stack<double>(arr4, 3);
    assert(stack4.Pop() == 1.2);
    stack4.Push(2.5);
    assert(stack4.Get(2) == 2.5);

    std::string arr5[] = {"hello", "world", "!"};
    Stack<std::string> stack5 = Stack<std::string>(arr5, 3);
    assert(stack5.Pop() == "!");
    stack5.Push("name");
    assert(stack5.Get(2) == "name");

    std::complex<int> c1(1, 3);
    std::complex<int> c2(2, 1);
    std::complex<int> c3(5, 3);
    Stack<std::complex<int>> stack6 = Stack<std::complex<int>>();
    stack6.Push(c1);
    stack6.Push(c2);
    stack6.Push(c3);
    assert(stack6.Pop() == c3);
    assert(stack6.Get(1) == c2);

    Student stud1(123, "Harry", "Potter", 1985, 1, "Group1");
    Student stud2(115, "Donald", "Duck", 1976, 5, "Group2");
    Student stud3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Stack<Student> stack7 = Stack<Student>();
    stack7.Push(stud1);
    stack7.Push(stud2);
    stack7.Push(stud3);
    assert(stack7.Pop() == stud3);
    assert(stack7.Get(1) == stud2);

    Teacher teach1(123, "Harry", "Potter", 1985, 1, "Group1");
    Teacher teach2(115, "Donald", "Duck", 1976, 5, "Group2");
    Teacher teach3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Stack<Teacher> stack8 = Stack<Teacher>();
    stack8.Push(teach1);
    stack8.Push(teach2);
    stack8.Push(teach3);
    assert(stack8.Pop() == teach3);
    assert(stack8.Get(1) == teach2);

    using Func = int (*)(const int &);
    Stack<Func> stack9 = Stack<Func>();
    stack9.Push(sq);
    stack9.Push(dbl);
    stack9.Push(three);
    assert(stack9.Pop() == three);
    assert(stack9.Get(1) == dbl);
}

void testQueue() {
    Queue<int> queue1 = Queue<int>();
    assert(queue1.IsEmpty());
    bool thrown1 = false;
    try {
        queue1.Dequeue();
    } catch(const EmptyContainer&) {
        thrown1 = true;
    }
    assert(thrown1);
    queue1.Enqueue(1);
    queue1.Enqueue(2);
    queue1.Enqueue(3);
    assert(!queue1.IsEmpty());
    assert(queue1.GetSize() == 3);
    assert(queue1.Peek() == 1);
    assert(queue1.Dequeue() == 1);
    assert(queue1.GetSize() == 2);
    assert(queue1.Get(0) == 2);
    bool thrown2 = false;
    try {
        queue1.Get(100);
    } catch(const IndexOutOfRange&) {
        thrown2 = true;
    }
    assert(thrown2);

    //concat
    int arr[] = {1, 2, 3, 4, 5};
    Queue<int> queue2 = Queue<int>(arr, 5);
    assert(queue2.Get(3) == 4);
    Queue<int> concat = queue1.Concat(queue2);
    assert(concat.GetSize() == 7);
    assert(concat.Get(0) == 2); 
    assert(concat.Get(1) == 3); 
    assert(concat.Get(2) == 1); 
    assert(concat.Get(6) == 5);

    //getsubsequence
    Queue<int> sub = queue2.GetSubSequence(1, 3);
    assert(sub.GetSize() == 3);
    assert(sub.Get(0) == 2);
    assert(sub.Get(sub.GetSize() - 1) == 4);
    bool thrown3 = false;
    try {
        queue2.GetSubSequence(100, 200);
    }
    catch (const IndexOutOfRange &) {
        thrown3 = true;
    }
    assert(thrown3);

    //findsubsequence
    int arr2[] = {3, 4};
    Queue<int> pattern1 = Queue<int>(arr2, 2);
    assert(queue2.FindSubSequence(pattern1) == 2);
    int arr3[] = {8, 9};
    Queue<int> pattern2 = Queue<int>(arr3, 2);
    assert(queue2.FindSubSequence(pattern2) == -1);
    Queue<int> pattern3 = Queue<int>();
    assert(queue2.FindSubSequence(pattern3) == 0);

    //split
    Queue<int> trueQueue = Queue<int>();
    Queue<int> falseQueue = Queue<int>();
    queue2.Split(even, trueQueue, falseQueue);
    assert(trueQueue.GetSize() == 2);
    assert(trueQueue.Get(0) == 2);
    assert(trueQueue.Get(1) == 4);
    assert(falseQueue.GetSize() == 3);
    assert(falseQueue.Get(0) == 1);
    assert(falseQueue.Get(1) == 3);
    assert(falseQueue.Get(2) == 5);

    //map
    Queue<int> map = queue2.Map(sq);
    assert(map.GetSize() == 5);
    assert(map.Get(0) == 1);
    assert(map.Get(1) == 4);
    assert(map.Get(2) == 9);
    assert(map.Get(3) == 16);
    assert(map.Get(4) == 25);
    assert(queue2.Get(3) == 4);

    //where
    Queue<int> where = queue2.Where(odd);
    assert(where.GetSize() == 3);
    assert(where.Get(0) == 1);
    assert(where.Get(1) == 3);
    assert(where.Get(2) == 5);
    assert(queue2.GetSize() == 5);

    //reduce
    assert(queue2.Reduce(add, 0) == 15);
    assert(queue2.Reduce(mul, 1) == 120);

    //zip
    auto zip = queue1.Zip(queue2);
    assert(zip.GetSize() == 2);
    assert(zip.Get(0).first == 2);
    assert(zip.Get(0).second == 1);
    assert(zip.Get(1).first == 3);
    assert(zip.Get(1).second == 2);

    //copy
    Queue<int> copy = queue2;
    copy.Enqueue(100);
    assert(copy.GetSize() == 6);
    assert(queue2.GetSize() == 5);

    //operators
    Queue<int> assigned;
    assigned = queue2;
    assigned.Dequeue();
    assert(assigned.GetSize() == 4);
    assert(queue2.GetSize() == 5);
    assert(queue2[2] == 3);
    Queue<int> same(queue2);
    assert(queue2 == same);
    same.Dequeue();
    assert(queue2 != same);
    Queue<int> plus = queue1 + queue2;
    assert(plus == concat);

    //tests for other types
    double arr4[] = {0.2, 3.4, 1.2};
    Queue<double> queue4 = Queue<double>(arr4, 3);
    assert(queue4.Dequeue() == 0.2);
    queue4.Enqueue(2.5);
    assert(queue4.Get(2) == 2.5);

    std::string arr5[] = {"hello", "world", "!"};
    Queue<std::string> queue5 = Queue<std::string>(arr5, 3);
    assert(queue5.Dequeue() == "hello");
    queue5.Enqueue("name");
    assert(queue5.Get(2) == "name");

    std::complex<int> c1(1, 3);
    std::complex<int> c2(2, 1);
    std::complex<int> c3(5, 3);
    Queue<std::complex<int>> queue6 = Queue<std::complex<int>>();
    queue6.Enqueue(c1);
    queue6.Enqueue(c2);
    queue6.Enqueue(c3);
    assert(queue6.Dequeue() == c1);
    assert(queue6.Get(1) == c3);

    Student stud1(123, "Harry", "Potter", 1985, 1, "Group1");
    Student stud2(115, "Donald", "Duck", 1976, 5, "Group2");
    Student stud3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Queue<Student> queue7 = Queue<Student>();
    queue7.Enqueue(stud1);
    queue7.Enqueue(stud2);
    queue7.Enqueue(stud3);
    assert(queue7.Dequeue() == stud1);
    assert(queue7.Get(1) == stud3);

    Teacher teach1(123, "Harry", "Potter", 1985, 1, "Group1");
    Teacher teach2(115, "Donald", "Duck", 1976, 5, "Group2");
    Teacher teach3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Queue<Teacher> queue8 = Queue<Teacher>();
    queue8.Enqueue(teach1);
    queue8.Enqueue(teach2);
    queue8.Enqueue(teach3);
    assert(queue8.Dequeue() == teach1);
    assert(queue8.Get(1) == teach3);

    using Func = int (*)(const int &);
    Queue<Func> queue9 = Queue<Func>();
    queue9.Enqueue(sq);
    queue9.Enqueue(dbl);
    queue9.Enqueue(three);
    assert(queue9.Dequeue() == sq);
    assert(queue9.Get(1) == three);
}

void testDeque() {
    Deque<int> deque1 = Deque<int>();
    assert(deque1.IsEmpty());
    bool thrown1 = false;
    try {
        deque1.PopBack();
    } catch(const EmptyContainer&) {
        thrown1 = true;
    }
    assert(thrown1);
    bool thrown2 = false;
    try {
        deque1.PopFront();
    } catch(const EmptyContainer&) {
        thrown2 = true;
    }
    assert(thrown2);
    deque1.PushBack(2);
    deque1.PushBack(3);
    deque1.PushFront(1);
    assert(!deque1.IsEmpty());
    assert(deque1.GetSize() == 3);
    assert(deque1.PeekBack() == 3);
    assert(deque1.PopBack() == 3);
    assert(deque1.GetSize() == 2);
    assert(deque1.PopFront() == 1);
    assert(deque1.GetSize() == 1);
    deque1.PushFront(1);
    assert(deque1.Get(deque1.GetSize() - 1) == 2);
    bool thrown3 = false;
    try {
        deque1.Get(100);
    } catch(const IndexOutOfRange&) {
        thrown3 = true;
    }
    assert(thrown3);

    //concat
    int arr[] = {1, 2, 3, 4, 5};
    Deque<int> deque2 = Deque<int>(arr, 5);
    assert(deque2.Get(3) == 4);
    Deque<int> concat = deque1.Concat(deque2);
    assert(concat.GetSize() == 7);
    assert(concat.Get(0) == 1); 
    assert(concat.Get(1) == 2); 
    assert(concat.Get(2) == 1); 
    assert(concat.Get(6) == 5);

    //getsubsequence
    Deque<int> sub = deque2.GetSubSequence(1, 3);
    assert(sub.GetSize() == 3);
    assert(sub.Get(0) == 2);
    assert(sub.Get(sub.GetSize() - 1) == 4);
    bool thrown4 = false;
    try {
        deque2.GetSubSequence(100, 200);
    }
    catch (const IndexOutOfRange &) {
        thrown4 = true;
    }
    assert(thrown4);

    //findsubsequence
    int arr2[] = {3, 4};
    Deque<int> pattern1 = Deque<int>(arr2, 2);
    assert(deque2.FindSubSequence(pattern1) == 2);
    int arr3[] = {8, 9};
    Deque<int> pattern2 = Deque<int>(arr3, 2);
    assert(deque2.FindSubSequence(pattern2) == -1);
    Deque<int> pattern3 = Deque<int>();
    assert(deque2.FindSubSequence(pattern3) == 0);

    //split
    Deque<int> trueDeque = Deque<int>();
    Deque<int> falseDeque = Deque<int>();
    deque2.Split(even, trueDeque, falseDeque);
    assert(trueDeque.GetSize() == 2);
    assert(trueDeque.Get(0) == 2);
    assert(trueDeque.Get(1) == 4);
    assert(falseDeque.GetSize() == 3);
    assert(falseDeque.Get(0) == 1);
    assert(falseDeque.Get(1) == 3);
    assert(falseDeque.Get(2) == 5);

    //map
    Deque<int> map = deque2.Map(sq);
    assert(map.GetSize() == 5);
    assert(map.Get(0) == 1);
    assert(map.Get(1) == 4);
    assert(map.Get(2) == 9);
    assert(map.Get(3) == 16);
    assert(map.Get(4) == 25);
    assert(deque2.Get(3) == 4);

    //where
    Deque<int> where = deque2.Where(odd);
    assert(where.GetSize() == 3);
    assert(where.Get(0) == 1);
    assert(where.Get(1) == 3);
    assert(where.Get(2) == 5);
    assert(deque2.GetSize() == 5);

    //reduce
    assert(deque2.Reduce(add, 0) == 15);
    assert(deque2.Reduce(mul, 1) == 120);
    
    //sort
    int arr4[] = {5, 4, 3, 2, 1};
    Deque<int> deque3 = Deque<int>(arr4, 5);
    auto sort = deque3.Sort(lessint);
    assert(sort.GetSize() == 5);
    assert(sort.Get(0) == 1);
    assert(sort.Get(1) == 2);
    assert(sort.Get(2) == 3);
    assert(sort.Get(3) == 4);
    assert(sort.Get(4) == 5);

    //merge
    int arr5[] = {3, 5, 8};
    int arr6[] = {2, 6, 10, 12};
    Deque<int> deque4 = Deque<int>(arr5, 3);
    Deque<int> deque5 = Deque<int>(arr6, 4);
    auto merge = deque4.Merge(deque5, lessint);
    assert(merge.GetSize() == 7);
    assert(merge.Get(0) == 2);
    assert(merge.Get(1) == 3);
    assert(merge.Get(2) == 5);
    assert(merge.Get(3) == 6);
    assert(merge.Get(4) == 8);
    assert(merge.Get(5) == 10);
    assert(merge.Get(6) == 12);

    //copy
    Deque<int> copy = deque2;
    copy.PushBack(100);
    assert(copy.GetSize() == 6);
    assert(deque2.GetSize() == 5);

    //operators
    Deque<int> assigned;
    assigned = deque2;
    assigned.PopBack();
    assert(assigned.GetSize() == 4);
    assert(deque2.GetSize() == 5);
    assert(deque2[2] == 3);
    Deque<int> same(deque2);
    assert(deque2 == same);
    same.PopBack();
    assert(deque2 != same);
    Deque<int> plus = deque1 + deque2;
    assert(plus == concat);

    //tests for other types
    double arr7[] = {0.2, 3.4, 1.2};
    Deque<double> deque6 = Deque<double>(arr7, 3);
    assert(deque6.PopBack() == 1.2);
    deque6.PushBack(2.5);
    assert(deque6.Get(2) == 2.5);

    std::string arr8[] = {"hello", "world", "!"};
    Deque<std::string> deque7 = Deque<std::string>(arr8, 3);
    assert(deque7.PopFront() == "hello");
    deque7.PushBack("name");
    assert(deque7.Get(2) == "name");

    std::complex<int> c1(1, 3);
    std::complex<int> c2(2, 1);
    std::complex<int> c3(5, 3);
    Deque<std::complex<int>> deque8 = Deque<std::complex<int>>();
    deque8.PushBack(c1);
    deque8.PushBack(c2);
    deque8.PushFront(c3);
    assert(deque8.PopBack() == c2);
    assert(deque8.Get(1) == c1);

    Student stud1(123, "Harry", "Potter", 1985, 1, "Group1");
    Student stud2(115, "Donald", "Duck", 1976, 5, "Group2");
    Student stud3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Deque<Student> deque9 = Deque<Student>();
    deque9.PushBack(stud1);
    deque9.PushBack(stud2);
    deque9.PushFront(stud3);
    assert(deque9.PopBack() == stud2);
    assert(deque9.Get(1) == stud1);

    Teacher teach1(123, "Harry", "Potter", 1985, 1, "Group1");
    Teacher teach2(115, "Donald", "Duck", 1976, 5, "Group2");
    Teacher teach3(122, "Ronald", "Weasly", 1985, 8, "Group1");
    Deque<Teacher> deque10 = Deque<Teacher>();
    deque10.PushBack(teach1);
    deque10.PushBack(teach2);
    deque10.PushFront(teach3);
    assert(deque10.PopBack() == teach2);
    assert(deque10.Get(1) == teach1);

    using Func = int (*)(const int &);
    Deque<Func> deque11 = Deque<Func>();
    deque11.PushBack(sq);
    deque11.PushBack(dbl);
    deque11.PushFront(three);
    assert(deque11.PopBack() == dbl);
    assert(deque11.Get(1) == sq);
}

void testAlgorithms() {
    //inversions
    int arr1[] = {5, 4, 3, 2, 1};
    MutableArraySequence<int> seq1(arr1, 5);
    assert(CountInversions(&seq1) == 10);
    int arr2[] = {0, 1, 5};
    MutableArraySequence<int> seq2(arr2, 3);
    assert(CountInversions(&seq2) == 0);
    MutableArraySequence<int> seq0;
    assert(CountInversions(&seq0) == 0);

    //factorial
    auto* seq3 = Factorial(5);
    assert(seq3->GetLength() == 6);
    assert(seq3->Get(0) == 1);
    assert(seq3->Get(1) == 1);
    assert(seq3->Get(2) == 2);
    assert(seq3->Get(3) == 6);
    assert(seq3->Get(4) == 24);
    assert(seq3->Get(5) == 120);
    bool thrown1 = false;
    try {
        Factorial(-2);
    } catch (std::invalid_argument&) {
        thrown1 = true;
    }
    assert(thrown1);

    //fibonacci
    auto *seq4 = Fibonacci(5);
    assert(seq4->GetLength() == 5);
    assert(seq4->Get(0) == 0LL);
    assert(seq4->Get(1) == 1LL);
    assert(seq4->Get(2) == 1LL);
    assert(seq4->Get(3) == 2LL);
    assert(seq4->Get(4) == 3LL);
    bool thrown2 = false;
    try {
        Fibonacci(-2);
    } catch (std::invalid_argument&) {
        thrown2 = true;
    }
    assert(thrown2);

    //range
    auto *seq5 = Range(3, 8);
    assert(seq5->GetLength() == 6);
    assert(seq5->Get(0) == 3);
    assert(seq5->Get(1) == 4);
    assert(seq5->Get(2) == 5);
    assert(seq5->Get(3) == 6);
    assert(seq5->Get(4) == 7);
    assert(seq5->Get(5) == 8);
    bool thrown3 = false;
    try {
        Range(5, 1);
    } catch (std::invalid_argument&) {
        thrown3 = true;
    }
    assert(thrown3);

    //primes
    auto *seq6 = Primes(10);
    assert(seq6->GetLength() == 4);
    assert(seq6->Get(0) == 2);
    assert(seq6->Get(1) == 3);
    assert(seq6->Get(2) == 5);
    assert(seq6->Get(3) == 7);

    delete seq3;
    delete seq4;
    delete seq5;
    delete seq6;
}

int main() {
    testStack();
    testQueue();
    testDeque();
    testAlgorithms();
    return 0;
}