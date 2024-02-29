#include <iostream>
#include <memory>

// Step 1: Define the base Callable interface
class CallableBase {
public:
    virtual ~CallableBase() = default;
    virtual void call() = 0;
};

// Step 2: Implement the derived template class for callable types
template<typename F>
class Callable : public CallableBase {
private:
    F f; // The callable object

public:
    Callable(F f) : f(f) {}

    void call() override {
        f();
    }
};

// Step 3: Create the custom Function class
class Function {
private:
    std::unique_ptr<CallableBase> callable;

public:
    // Constructor template for any callable matching the signature
    template<typename F>
    Function(F f) : callable(new Callable<F>(f)) {}

    // Invocation of the stored callable
    void operator()() {
        if (callable) {
            callable->call();
        }
    }
};

// Example usage
int main() {
    // Store a lambda
    Function f([]() { std::cout << "Hello from lambda!" << std::endl; });

    // Call the stored lambda
    f();

    // Store a regular function
    Function g([]() { std::cout << "Hello from another lambda!" << std::endl; });

    // Call the stored regular function
    g();

    return 0;
}
