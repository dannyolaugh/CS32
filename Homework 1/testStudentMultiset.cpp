#include "StudentMultiset.h"

#include <iostream>

#include <cassert>

using namespace std;



int main()

{
    
    StudentMultiset h;
    
    StudentMultiset g;
    
    for (int i = 0; i < 4; i++)
        
    {
        
        h.add(i);
        
        g.add(i+1);
        
    }
    
    cout << "h size: " << h.size() << endl;
    
    cout << "g size: " << g.size() << endl;
    
    h.print();
    
    g.print();
    
    //StudentMultiset test(h);    // COMPILER-GENERATED CONSTRUCTOR WORKS 21
    
    StudentMultiset test;
    
    test = h;            // COMPILER-GENERATED ASSIGNMENT OPERATOR WORKS 23
    
    cout << "test size: " << test.size() << endl;
    
    test.print();
    
    
    
}
