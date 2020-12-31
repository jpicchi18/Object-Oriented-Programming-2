
void listAll(const Domain* d, string path) // two-parameter overload
{
    // if it's a leaf node, print the path
    if (d->subdomains().empty())
        cout << path << endl;
    
    // add a dot before the path, if necessary
    if (path != "")
        path = "." + path;
    
    // loop through the vector
    for (int i = 0; i < d->subdomains().size(); i++)
    {
        // recursively call until a leaf is reached
        Domain* next = d->subdomains()[i];
        listAll(next, next->label() + path);
    }
}
