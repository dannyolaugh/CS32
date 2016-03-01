bool anyTrue(const double a[], int n)
{
    if (n <= 0)
        return false;
    if(somePredicate(a[n-1]))
        return true;
    return anyTrue(a, n-1);
}


int countTrue(const double a[], int n)
{
    int counter = 0;
    if(n > 0)
    {
        if(somePredicate(a[n-1]))
            counter++;
        counter += countTrue(a, n-1);
    }
    return counter;
    
}


int firstTrue(const double a[], int n)
{
    int positionHolder = n-1;  //im returning the last negative number
    if(n > 0)
    {
        if(somePredicate(a[positionHolder]))
        {
            if(n == 1)
                return positionHolder;
            else if (firstTrue(a,n-1)== -1)
                return positionHolder;
            else
                return firstTrue(a, n-1);
        }
        else
            return firstTrue(a, n-1);
        
    }
    return -1;
}


int indexOfMin(const double a[], int n)
{
    if(n <= 0)
        return -1;
    if(n == 1)
        return n-1;
    if(a[n-1] < a[indexOfMin(a, n-1)])
    {
        return n-1;
    }
    else
    {
        return indexOfMin(a, n-1);
    }
}


bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if(n2 <= 0)   //what if n2 is negative
        return true;
    if(n1 <= 0)
        return false;
    if(a1[n1-1] == a2[n2-1])
    {
        return includes(a1, n1-1, a2, n2-1);
    }
    else
    {
        return includes(a1, n1-1, a2, n2);
    }
    
}
