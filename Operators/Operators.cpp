#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CPlant
{

private:
    string name;
    int dAge;
    int cmHeigh;
    bool isBlooming;
    int growingSpeedADay;
    int oxygenGeneratingAnHour;
    int hBloomingTime;
    int oxygenGenerated = 0;
    int timeSlept = 0;

public:
    CPlant(string name)
    {
        this->name = name;
        dAge = 0;
        cmHeigh = 0;
        isBlooming = false;
        growingSpeedADay = 0;
        oxygenGeneratingAnHour = 0;
        hBloomingTime = 0;
    }

    CPlant(string name, int dAge, int cmHeigh, bool isBlooming, int growingSpeedADay, int oxygenGeneratingAnHour, int hBloomingTime)
    {
        this->name = name;
        this->dAge = dAge;
        this->cmHeigh = cmHeigh;
        this->isBlooming = isBlooming;
        this->growingSpeedADay = growingSpeedADay;
        this->oxygenGeneratingAnHour = oxygenGeneratingAnHour;
        this->hBloomingTime = hBloomingTime;
    }

    CPlant& operator ++()
    {
        this->dAge++;
        this->cmHeigh += this->growingSpeedADay;
        this->oxygenGenerated += (this->oxygenGeneratingAnHour * this->hBloomingTime);
        return *this;
    }



    CPlant& operator ++(int x)
    {
        CPlant postfix(*this);

        this->dAge++;
        this->cmHeigh += this->growingSpeedADay;
        this->oxygenGenerated += (this->oxygenGeneratingAnHour * this->hBloomingTime);
        return postfix;
    }



    CPlant& operator =(const CPlant& other)
    {
        this->dAge = other.dAge;
        this->cmHeigh = other.cmHeigh;
        this->isBlooming = other.isBlooming;
        this->oxygenGenerated = other.oxygenGenerated;
        return *this;
    }

    CPlant& operator =(const int x)
    {
        this->cmHeigh = x;
        this->oxygenGenerated = x;
        return *this;
    }

    CPlant& operator +=(const CPlant& other)
    {
        this->oxygenGenerated += other.oxygenGenerated;
        return *this;
    }

    bool operator ||(const CPlant& other)
    {
        return this->isBlooming || other.isBlooming;
    }

    bool operator !()
    {
        return this->cmHeigh == NULL && this->oxygenGenerated == NULL;
    }

    void SetAge(int day)
    {
        for (int i = 0; i < day; i++)
        {
            dAge++;
        }
    }

    void SetHeigh(int day)
    {
        for (int i = 0; i < day; i++)
        {
            cmHeigh += growingSpeedADay;
        }
    }

    int SetIsBloomingGetTimeSlept(int time)
    {
        int i = 0;
        while (time >= 25)
        {
            time -= 25;
        }
        for (i; i < hBloomingTime; i++)
        {
            isBlooming = true;
            if (i == time)
                goto endOfSetter;
        }
        timeSlept = NULL;
        for (i; i < 24; i++)
        {
            isBlooming = false;
            if (i == time)
                goto endOfSetter;
            timeSlept++;
        }
    endOfSetter:
        return timeSlept;
    }

    int GetOxygen()
    {
        return oxygenGenerated;
    }

    void SetOxygenGenerated(int time)
    {
        oxygenGenerated = oxygenGeneratingAnHour * time;
    }

    int GetBloomingTime()
    {
        return hBloomingTime;
    }

    string printIsBlooming()
    {
        if (isBlooming)
        {
            return "Blooms";
        }
        else
        {
            return "Sleeps";
        }
    }

    void printClass()
    {
        cout << "Name: " << name << "\t\tAge: " << dAge << "\t\tHeigh: " << cmHeigh << "\tCondition:" << printIsBlooming() << "\tOxygen generated: " << oxygenGenerated << endl;
    }

    friend ostream& operator <<(ostream& os, const CPlant& plant);
};


ostream& operator <<(ostream& os, const CPlant& plant)
{
    os << plant.name << " " << plant.dAge << " " << plant.cmHeigh << " " << plant.isBlooming << " " << plant.oxygenGenerated << endl;
    return os;
}

//istream& operator >>(istream& is, const CPlant& plant)
//{
//    is >> plant;
//    return is;
//}

int main()
{
    int plusTime = 0, timeNow = 0, timeSlept[2] = { 0, 0 }, controlDay = 0, dayNow = 0;

    CPlant sunflower("Sunflower", 29, 40, true, 3, 25, 8);
    CPlant tulip("Tulip", 16, 13, true, 1, 12, 11);
    CPlant sunflowerCopy("Second sunflower");
    CPlant tulipCopy("Second tulip");
    CPlant sum("All oxygen");

    string filePlace = "Plants.txt";
    fstream fs;
    fs.open(filePlace, fstream::app);

    if (!fs.is_open())
    {
        cout << "ERROR!!!\n";
    }
    else
    {
        do
        {
            if (plusTime < 0)
            {
                cout << "ERROR!!!";
                break;
            }
            else
            {

                fs << sunflower;
                fs << tulip;
                fs << sunflowerCopy;
                fs << tulipCopy;
                cout << "Your plants for now:\n";
                sunflower.printClass();
                tulip.printClass();
                sunflowerCopy = sunflower;
                sunflowerCopy.printClass();
                tulipCopy = tulip;
                tulipCopy.printClass();

                sum += sunflowerCopy;
                sum += tulipCopy;
                cout << "The sum of generated oxygen is " << sum.GetOxygen() << endl;
                sum = NULL;

                if (!sum)
                    cout << "Sum data were erased\n";
                else
                    break;

                if (sunflower || tulip)
                {
                    cout << "At least one plant isn't sleeping\n";
                }
                else
                {
                    cout << "All plants are sleeping\n";
                }

                cout << "How many hours want you to wait (enter 0 to quit)?" << endl;
                cin >> plusTime;

                timeNow += plusTime;
                dayNow = timeNow / 24;

                sunflower.SetAge(dayNow - controlDay);
                tulip.SetAge(dayNow - controlDay);
                sunflower.SetHeigh(dayNow - controlDay);
                tulip.SetHeigh(dayNow - controlDay);
                timeSlept[0] = sunflower.SetIsBloomingGetTimeSlept(timeNow);
                timeSlept[1] = tulip.SetIsBloomingGetTimeSlept(timeNow);
                sunflower.SetOxygenGenerated(timeNow - timeSlept[0]);
                tulip.SetOxygenGenerated(timeNow - timeSlept[1]);
                if (dayNow > controlDay)
                {
                    ++sunflowerCopy;
                    tulipCopy++;
                }

                controlDay = dayNow;
            }

        } while (plusTime != 0);
    }

    return 0;
}