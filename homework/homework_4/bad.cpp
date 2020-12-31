
void removeBad(list<Movie*>& li)
{
    // loop through and delete
    for (list<Movie*>::iterator it = li.begin(); it != li.end(); it++)
    {
        if ((*it)->rating() < 55)
        {
            // make temps so we can handle the items after the item is removed
            Movie* killMe = *it;
            list<Movie*>::iterator placeHolder = it;
            
            // erase everything
            it--;
            li.erase(placeHolder);
            delete killMe;
        }
    }
}
