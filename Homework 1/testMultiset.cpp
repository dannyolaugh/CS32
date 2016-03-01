#include "StudentMultiset.h"

#include <iostream>

#include <cassert>

using namespace std;


void test()

{
    
    Multiset sms;
    
    assert(sms.insert("cumin"));
    
    assert(sms.insert("turmeric"));
    
    assert(sms.insert("cumin"));
    
    assert(sms.insert("coriander"));
    
    assert(sms.insert("cumin"));
    
    assert(sms.insert("turmeric"));
    
    assert(sms.size() == 6  &&  sms.uniqueSize() == 3);
    
    assert(sms.count("turmeric") == 2);
    
    assert(sms.count("cumin") == 3);
    
    assert(sms.count("coriander") == 1);
    
    assert(sms.count("cardamom") == 0);
    
}

//void test2()

//{

//    Multiset ulms;

//    assert(ulms.insert(20));

//    assert(ulms.insert(10));

//    assert(ulms.insert(20));

//    assert(ulms.insert(30));

//    assert(ulms.insert(20));

//    assert(ulms.insert(10));

//    assert(ulms.size() == 6  &&  ulms.uniqueSize() == 3);

//    assert(ulms.count(10) == 2);

//    assert(ulms.count(20) == 3);

//    assert(ulms.count(30) == 1);

//    assert(ulms.count(40) == 0);

//}

//int main()

//{

//    //test();

//    test2();

//    Multiset ms;

//    Multiset ms2;

//    assert(ms.empty());

//    ms.insert(15);

//    ms.insert(15);

//    ms.insert(15);

//

//    assert(ms.erase(15) && ms.count(15)==2);

//    assert(ms.eraseAll(15)==2);

//    assert(ms.empty());

//

//    ms.insert(15);

//    ms.insert(15);

//    ms.insert(15);

//    ms.insert(26);

//    ms.insert(26);

//    ms.insert(1);

//

//    assert(ms.uniqueSize() == 3 && ms.size() == 6);

//    assert(ms.contains(15) && ms.contains(1));

//    assert(ms.count(26) == 2);

//

//    ms2.insert(14);

//    ms2.insert(20);

//    ms2.insert(14);

//    ms2.insert(14);

//    ms.swap(ms2);

//

//    assert(!ms.contains(26) && ms2.contains(1));

//    cout << "Passed all tests" << endl;

//}



int main()

{
    
    test();
    
    Multiset ms;
    
    Multiset ms2;
    
    assert(ms.empty());
    
    ms.insert("oop");
    
    ms.insert("oop");
    
    ms.insert("oop");
    
    
    
    assert(ms.erase("oop") );
    
    assert(ms.eraseAll("oop") == 2);
    
    assert(ms.empty());
    
    
    
    ms.insert("oop");
    
    ms.insert("oop");
    
    ms.insert("oop");
    
    ms.insert("dud");
    
    ms.insert("dud");
    
    ms.insert("aaa");
    
    
    
    assert(ms.uniqueSize() == 3 && ms.size() == 6);
    
    assert(ms.contains("oop") && ms.contains("aaa"));
    
    assert(ms.count("dud") == 2);
    
    
    
    ms2.insert("yyya");
    
    ms2.insert("whet");
    
    ms2.insert("yyya");
    
    ms2.insert("yyya");
    
    ms.swap(ms2);
    
    
    
    assert(!ms.contains("dud") && ms2.contains("aaa") && ms.contains("yyya") && !ms2.contains("whet"));
    
    cout << "Passed all tests" << endl;
    
}

