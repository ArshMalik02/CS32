class Sport
{
public:
    Sport(string nm)
    : m_name(nm)
    {}
    string name() const
    {
        return m_name;
    }
    virtual bool isOutdoor() const {return true;}
    virtual string icon() const = 0;
    virtual ~Sport(){};
private:
    string m_name;
};

class Snowboarding
: public Sport
{
public:
    Snowboarding(string name)
    : Sport(name)
    {}
    virtual string icon() const {return "a descending snowboarder";}
    virtual ~Snowboarding()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
};

class Biathlon
: public Sport
{
public:
    Biathlon(string name, double distance)
    : Sport(name), m_distance(distance)
    {}
    virtual string icon() const {return "a skier with a rifle";}
    virtual ~Biathlon()
    {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << endl;
    }
private:
    double m_distance;
};

class FigureSkating
: public Sport
{
public:
    FigureSkating(string name)
    : Sport(name)
    {}
    virtual bool isOutdoor() const {return false;}
    virtual string icon() const {return "a skater in the Biellmann position";}
    virtual ~FigureSkating()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
};

