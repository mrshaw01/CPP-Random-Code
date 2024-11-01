#include <iostream>
#include <optional>
#include <variant>
#include <string>
#include <tuple>
#include <map>
#include <any>

// Function that returns a structured binding from a tuple
std::tuple<int, std::string, double> getData() {
    return {42, "example", 3.14};
}

// Function demonstrating std::optional
std::optional<std::string> findWord(const std::string& word) {
    std::map<std::string, std::string> dictionary = {
        {"hello", "greeting"},
        {"world", "earth"},
    };

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        return it->second;
    } else {
        return std::nullopt;
    }
}

// Function demonstrating std::variant
std::variant<int, double, std::string> getVariant(int choice) {
    if (choice == 1) return 42;
    if (choice == 2) return 3.14;
    return "variant";
}

int main() {
    // Structured bindings
    auto [id, name, value] = getData();
    std::cout << "ID: " << id << ", Name: " << name << ", Value: " << value << std::endl;

    // If with initialization
    if (auto opt = findWord("hello"); opt.has_value()) {
        std::cout << "Found word: " << *opt << std::endl;
    } else {
        std::cout << "Word not found!" << std::endl;
    }

    // Using std::variant with std::visit
    std::variant<int, double, std::string> v = getVariant(3);
    std::visit([](auto&& arg) { std::cout << "Variant holds: " << arg << std::endl; }, v);

    // Using std::any
    std::any anyValue = 10;
    std::cout << "std::any holds an int: " << std::any_cast<int>(anyValue) << std::endl;

    return 0;
}
