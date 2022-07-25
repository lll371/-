/*************************************************************************
    > File Name: test_1.cpp
    > Author: Alice
    > Mail: 2789828898@qq.com
    > Created Time: Tue Jun  7 15:26:42 2022
 ************************************************************************/

#include <cstdio>
#include<iostream>
using namespace std;

class Observable;
class Observer
{
public:
	virtual ~Observer(){}

public:
	virtual void Update(Observable* observable) = 0;
};

class Observable
{
private:
	int size;
	int capacity;
	Observer** observers;
	
public:
	Observable(Observer** observers = NULL , int size = 0 , int capacity = 0):observers(observers) , size(size) , capacity(capacity){}
    
		virtual ~Observable()
	{
		for(int i = 0; i < size; ++i)
		{
            delete observers[i];
		}
		delete observers;
	}

public:
	void AddObserver(Observer* observer)
	{
        if(size < capacity)
		{
            observers[size] = observer;
		    ++size;
		}
		else
		{
		    printf("Not enough sapce! ! !\n");		
		}
	}

	void RemoveObserver(Observer* observer)
	{
		if(size > 0)
		{
            delete observer;
			int flag = 0;
			for(int i = 0; i < size; ++i)
			{
				if(observers[i] == observer)
			    {
					flag = i;
					break;
				}
			}
				for(int i = flag; i < size-1; ++i)
			{
				observers[i] = observers[i+1];
			}
			--size;
	    }
		else
		{
			printf("No observer! ! !");
		}
	}
	
	void NotifyObservers(void)
	{
		for(int i = 0; i < size; ++i)
		{
			observers[i]->Update(this);
		}
	}
};

class WaterHeater : public Observable
{
private:
	int temperature;

public:
	WaterHeater(Observer** observers = NULL , int size = 0 , int capacity = 0 , int temperature = 25):Observable(observers , size , capacity) , temperature(temperature){}

	~WaterHeater(){}

public:
	int GetTemperature(void)
	{
		return temperature;
	}

	void SetTemperature(int temperature)
	{
		this->temperature = temperature;
	    printf("当前温度是：%d 摄氏度\n" , this->temperature);
		this->NotifyObservers();
	}
};

class WashingMode : public Observer
{


public:
	void Update(Observable* observable) override
	{
	
        if(((WaterHeater*)observable)->GetTemperature() >= 50 &&((WaterHeater*)observable)->GetTemperature() < 70)
		{
			printf("水的温度可以用来洗澡了.\n");
		}
	}
};
	
class DrinkingMode : public Observer
{
public:
	void Update(Observable* observable) override
	{
		if(((WaterHeater*)observable)->GetTemperature() >= 100)
		{
			printf("水的温度可以用来饮用了.\n");
		}
	}
};



int main(void)
{
	Observer** observers = new Observer* [10];
	WaterHeater* heater = new WaterHeater(observers , 0 , 10);
    Observer* washing_mode = new WashingMode;
	Observer* drinking_mode = new DrinkingMode;

	heater->AddObserver(washing_mode);
	heater->AddObserver(drinking_mode);

	heater->SetTemperature(40);
    heater->SetTemperature(60);
    heater->SetTemperature(100);

	delete heater;
	return 0;
}
