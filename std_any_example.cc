/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <any>
#include <map>
#include <iostream>

#if 0
int main(){
 void* _value;

  // set the value as int
 int a =30;
 _value=&a;
 
  // we can read it as int
 std::cout << "int: "<<*((int*)_value)<<'\n';

  // set the value as bool 
  bool b =true;
 _value=&b;
 
 // read the value as bool 
 std::cout <<"bool: " <<*((bool*)_value)<<'\n';
 return 0;   
}
#else 

struct MyType
{
    int a, b;

    MyType(int x, int y) : a(x), b(y) { }

    void Print() { std::cout << a << ", " << b << "\n"; }
};

int main()
{
    
/*    Creation  */ 
    // default initialization:
    std::any b;
    std::cout << "Default initialization: "<< b.has_value()<<'\n';

    // initialization with an object
    std::any a(12);
    std::cout << "Initialization with an object: "<< a.has_value()<<'\n';
    
    // make_any
    std::any a6 = std::make_any<std::string>("Hello World");
    std::cout << "Initialization of an object using make_any: "<< a6.has_value()<<'\n';
    
    /* Changing the Value */
    // set any value:
    a = std::string("Hello!");
    a = 16;

   // we can read it as int
   std::cout << std::any_cast<int>(a) << '\n'; 
   // using emplace public function 
   a.emplace<float>(100.5f);
   // we can read it as float
   std::cout << std::any_cast<float>(a) << '\n'; 
   
// but not as string:
try 
{
    std::cout << std::any_cast<std::string>(a) << '\n';
}
catch(const std::bad_any_cast& e) 
{
    std::cout << e.what() << '\n';
}

// reset and check if it contains any value:
a.reset();
if (!a.has_value())
{
    std::cout << "a is empty!" << "\n";
}

// you can use it in a container:
std::map<std::string, std::any> m;
m["integer"] = 10;
m["string"] = std::string("Hello World");
m["float"] = 1.0f;

for (auto &[key, val] : m)
{
    if (val.type() == typeid(int))
        std::cout << "int: " << std::any_cast<int>(val) << "\n";
    else if (val.type() == typeid(std::string))
        std::cout << "string: " << std::any_cast<std::string>(val) << "\n";
    else if (val.type() == typeid(float))
        std::cout << "float: " << std::any_cast<float>(val) << "\n";
}
 
    std::any var = std::make_any<MyType>(10, 10);
    try
    {
        std::any_cast<MyType&>(var).Print(); // to return a copy of the value, and throw std::bad_any_cast when it fails
        std::any_cast<MyType&>(var).a = 11; // read/write  return a reference (also writable), and throw std::bad_any_cast when it fails
        std::any_cast<MyType&>(var).Print(); 
        std::any_cast<int>(var); // throw!
    }
    catch(const std::bad_any_cast& e) 
    {
        std::cout << e.what() << '\n';
    }
    // to return a pointer to the value (const or not) or nullptr on failure
    int* p = std::any_cast<int>(&var);
    std::cout << (p ? "contains int... \n" : "doesn't contain an int...\n");

    MyType* pt = std::any_cast<MyType>(&var);
    if (pt)
    {
        pt->a = 12;
        std::any_cast<MyType&>(var).Print();
    }

    return 0;
}
#endif
