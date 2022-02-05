#include <iostream>
#include <string>
using namespace std;

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
    virtual bool isOutdoor() const = 0;
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
    : Sport(name), m_isOutdoorSport(true), m_icon("a descending snowboarder")
    {}
    virtual bool isOutdoor() const {return m_isOutdoorSport;}
    virtual string icon() const {return m_icon;}
    virtual ~Snowboarding()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
private:
    string m_name;
    bool m_isOutdoorSport;
    string m_icon;
};

class Biathlon
: public Sport
{
public:
    Biathlon(string name, double distance)
    : Sport(name), m_distance(distance), m_isOutdoorSport(true), m_icon("a skier with a rifle")
    {}
    virtual bool isOutdoor() const {return m_isOutdoorSport;}
    virtual string icon() const {return m_icon;}
    virtual ~Biathlon()
    {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << endl;
    }
private:
    bool m_isOutdoorSport;
    string m_icon;
    double m_distance;
};

class FigureSkating
: public Sport
{
public:
    FigureSkating(string name)
    : Sport(name), m_isOutdoorSport(false), m_icon("a skater in the Biellmann position")
    {}
    virtual bool isOutdoor() const {return m_isOutdoorSport;}
    virtual string icon() const {return m_icon;}
    virtual ~FigureSkating()
    {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }
private:
    string m_name;
    bool m_isOutdoorSport;
    string m_icon;
};
void display(const Sport* sp)
{
    cout << sp->name() << " is ";
    if (sp->isOutdoor())
        cout << "an outdoor sport ";
    else
        cout << "an indoor sport ";
    cout << "with an icon showing " << sp->icon() << "." << endl;
}

int main()
{
    Sport* sports[4];
    sports[0] = new Snowboarding("Women's halfpipe");
    // Biathlon events have a distance in kilometers
    sports[1] = new Biathlon("Men's pursuit", 12.5);
    sports[2] = new Biathlon("Women's sprint", 7.5);
    sports[3] = new FigureSkating("Pair skating free");
    
    cout << "Here are the sports." << endl;
    for (int k = 0; k < 4; k++)
        display(sports[k]);
    
    // Clean up the sports before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete sports[k];
}
