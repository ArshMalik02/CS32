
void listAll(string path, const Class* c)  // two-parameter overload
{
    cout << c->name() << endl;
    if (c->subclasses().empty())
        return;
    path+=c->name() + "=>";
    for (int i = 0; i!=c->subclasses().size(); i++)
    {
        cout << path;
        listAll(path, c->subclasses()[i]);
    }
}
