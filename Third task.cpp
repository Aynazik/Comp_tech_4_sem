#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

struct Person 
{
    std::string Name;
    std::string Surname;
    int age;
    friend std::istream& operator>>(std::istream& stream, Person& obj);
};

nlohmann::json Struct_to_json(Person& obj)
{
    nlohmann::json result;
    result["Name"] = obj.Name;
    result["Surname"] = obj.Surname;
    result["age"] = obj.age;
    return result;
}

std::istream& operator>>(std::istream& stream, Person& obj)
{
    std::cout << "Input person's name, surname, age in correct order " << '\n';
    stream >> obj.Name >> obj.Surname >> obj.age;
    return stream;
}

int main()
{
    Person first, second;
    std::cin >> first >> second;
    nlohmann::json first_js = Struct_to_json(first);
    nlohmann::json second_js = Struct_to_json(second);
    // не уверен что достаточно нормально так делать
    std::filesystem::path p = std::filesystem::current_path();
    std::filesystem::create_directory(p /= "persons");
    {
        std::ofstream of("persons/first_person.json");
        of << first_js;
        of.close();
    }
    std::ofstream of("persons/second_person.json");
    of << second_js;
    of.close();
    return 0;
}
