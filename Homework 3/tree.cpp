
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    int count = 0;
    if(n2 <= 0)
        return 1;
    if(n1 <= 0)
        return 0;
    if(a1[n1-1] == a2[n2-1])
    {
        count += countIncludes(a1, n1-1, a2, n2-1);
        count += countIncludes(a1, n1-1, a2, n2);
        
    }
    else
    {
        count += countIncludes(a1, n1-1, a2, n2);
        
    }
    return count;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}


void order(double a[], int n)
{
    int firstNotGreater = 0;
    int firstLess = 0;
    
    if(n <= 1)
        return;
    separate(a, n, a[n-1], firstNotGreater, firstLess);
    if(firstLess == n)
    {
        order(a, n-1);
    }
    else
    {
        order(a, n);
    }
    
    return;
}

