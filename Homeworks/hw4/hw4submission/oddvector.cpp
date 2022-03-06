
void removeOdd(vector<int>& v)
{
    vector<int>::iterator it;
    for (it = v.begin(); it!=v.end();)
    {
        if ((*it)%2!=0)
            v.erase(it);
        else
            it++;
    }
}
