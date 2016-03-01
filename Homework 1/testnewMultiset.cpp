#include "newMultiset.h"
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
    
    ms.insert("yellow");
    
    ms.insert("yellow");
    
    ms.insert("yellow");
    
    
    
    assert(ms.erase("yellow") );
    
    assert(ms.eraseAll("yellow") == 2);
    
    assert(ms.empty());
    
    
    
    ms.insert("yellow");
    
    ms.insert("yellow");
    
    ms.insert("yellow");
    
    ms.insert("sister");
    
    ms.insert("sister");
    
    ms.insert("happy");
    
    
    
    assert(ms.uniqueSize() == 3 && ms.size() == 6);
    
    assert(ms.contains("yellow") && ms.contains("happy"));
    
    assert(ms.count("sister") == 2);
    
    
    
    ms2.insert("knew");
    
    ms2.insert("bappy");
    
    ms2.insert("knew");
    
    ms2.insert("knew");
    
    ms.swap(ms2);
    
    
    
    assert(!ms.contains("sister") && ms2.contains("happy") && ms.contains("knew") && !ms2.contains("bappy"));
    
    cout << "Passed all tests" << endl;
    
}