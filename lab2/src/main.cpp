#include "../include/headers.hpp"

int main() {
    std::cout << "\n--- Constructors ---\n";

    Twelve def;
    std::cout << "Default: ";
    def.print();
    std::cout << "\n";

    Twelve fromStr("00A0B");
    std::cout << "From string (\"00A0B\"): ";
    fromStr.print();
    std::cout << "\n";

    Twelve fromList{'B', 0, 5}; 
    std::cout << "From list {B,0,5}: ";
    fromList.print();
    std::cout << "\n";

    Twelve copy(fromStr);
    std::cout << "Copy fromStr: ";
    copy.print();
    std::cout << "\n";

    Twelve moved(std::move(copy));
    std::cout << "Moved (copy -> moved): ";
    moved.print();
    std::cout << "\n";

    std::cout << "Old copy (after move): ";
    copy.print();
    std::cout << "\n";

    std::cout << "\n--- Arithmetic: add / minus ---\n";

    Twelve a("1A3"); 
    Twelve b("B0"); 

    std::cout << "a = "; a.print(); std::cout << "\n";
    std::cout << "b = "; b.print(); std::cout << "\n";

    Twelve sum = a.add(b);
    std::cout << "a + b = ";
    sum.print();
    std::cout << "\n";

    Twelve diff = a.minus(Twelve("10")); 
    std::cout << "a - 10 = ";
    diff.print();
    std::cout << "\n";

    std::cout << "\n--- Comparison ---\n";
    std::cout << "a == b ? " << (a.isEqual(b) ? "Yes" : "No") << "\n";
    std::cout << "a > b  ? " << (a.isGreater(b) ? "Yes" : "No") << "\n";
    std::cout << "a < b  ? " << (a.isLess(b) ? "Yes" : "No") << "\n";

    std::cout << "\n--- Exception test (minus underflow) ---\n";
    try {
        Twelve x("10"); 
        Twelve y("B");  
        std::cout << "x = "; x.print();
        std::cout << ", y = "; y.print();
        std::cout << "\n";

        Twelve res1 = x.minus(y);
        std::cout << "x - y = ";
        res1.print();
        std::cout << "\n";

        Twelve z("11");
        std::cout << "Trying x - z (12 - 13)...\n";
        Twelve res2 = x.minus(z); 
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "\n--- Assignment ---\n";

    Twelve c("A0");
    Twelve d("B");
    std::cout << "c = "; c.print();
    std::cout << ", d = "; d.print();
    std::cout << "\n";

    Twelve e = c.add(d);
    std::cout << "e = c + d = ";
    e.print();
    std::cout << "\n";

    Twelve f;
    f = e; // копирование
    std::cout << "f = e (copy): ";
    f.print();
    std::cout << "\n";

    Twelve g;
    g = std::move(e); 
    std::cout << "g = move(e): ";
    g.print();
    std::cout << "\n";
    std::cout << "e after move: ";
    e.print();
    std::cout << "\n";

    Twelve t(4, '0');
    t.print();

    std::cout << "\n--- End of program ---\n";
    std::cout << "All destructors will be called now.\n";
    std::cout << "\n=== End ===\n\n";

    return 0;
}
