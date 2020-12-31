
void removeOdds(vector<int>& v)
{
    // create an iterator:
    vector<int>::iterator it = v.begin();
    
    // delete odd items
    while (it != v.end())
    {
        if (*it%2 != 0)
        {
            v.erase(it);
            
            // iterator is no longer valid, so point it to the beginning
            it = v.begin();
        }
        else
            it++;
    }
}
