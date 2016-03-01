#include "StudentMultiset.h"
#include "Multiset.h"

StudentMultiset::StudentMultiset()
: mStudents()
{
    //call multisets constructor
    //mStudents;  //you dont need to call the constructor it does it automatically
    //cout << mStudents.empty() << endl;
}

bool StudentMultiset:: add(unsigned long id)
{
    return mStudents.insert(id);
}
// Add a student id to the StudentMultiset.  Return true if and only
// if the id was actually added.
int StudentMultiset:: size() const
{
    return mStudents.size();
}

void StudentMultiset:: print() const
{
    ItemType holder;
    for(int i = 0; i < mStudents.uniqueSize(); i++)
    {
        for(int j = 0; j < mStudents.get(i,holder); j++)
        {
            cout << holder << endl;
        }
    }
}
