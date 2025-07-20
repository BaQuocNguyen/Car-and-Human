#include <iostream>
#include<string>
 
// Car
class Car {
protected:  
    const std::string serialNumber;
    const int enginePower;
    float engineSpeed;
    static int serialCreate;
public:
    Car(int power, float speed)
        : serialNumber("VN" + std::to_string(++serialCreate)), enginePower(power), engineSpeed(speed){}
    virtual ~Car() = default;
 
    std::string GetSerialNumber() const {
        return serialNumber;
    }
    int GetEnginePower() const {
        return enginePower;
    }
    virtual float GetEngineSpeed() const{
        return engineSpeed;
    }
    virtual void Drive() const {
        std::cout <<"Driving at " << engineSpeed << "km/h\n";
    }
};
 
//Normal Car
class NormalCar : public Car {
public:
    NormalCar(int power, float speed) : Car(power, speed){}
};
 
//Performance Car
class PerformanceCar : public Car {
private:
    float turbo;
    float longitude;
    float latitude;
public:
    PerformanceCar(int power, float speed)
                : Car(power, speed), turbo(10.0f), longitude(0.0), latitude(0.0){}
    void ActiveTurbo(){
        engineSpeed *= (1 + turbo/100);
    }
    void SetNavigation(float lon, float lat) {
        longitude = lon;
        latitude = lat;
    }
    void GetNavigation() const {
        std::cout <<"Location system is " << longitude << ", " << latitude << "\n";
    }
    float GetEngineSpeed() const override {
        return Car::GetEngineSpeed();
    }
};
 
//Person
class Person {
public:
    virtual void DriveCar(Car* car) const {
          car->Drive();
    }
    virtual void ReadEngineSpeed(Car* car) const {
        std::cout << "Engine speed: " << car->GetEngineSpeed() << " km/h\n";
    }
    virtual void ReadEnginePower(Car* car) const {
        std::cout << "Engine power: " << car->GetEnginePower() << " hp\n";
    }
    virtual ~Person() = default;
};

class Engineer : public Person {
public:
    void ProgramNavigation(PerformanceCar* car, float lon, float lat) const {
        car->SetNavigation(lon, lat);
        car->GetNavigation();
    }
    void ReadSerialNumber(Car* car) const {
        std::cout << "Serial Number: " << car->GetSerialNumber() << "\n";
    }
};
class User : public Person {
public:
    void PositionCar(PerformanceCar* car, float lon, float lat) const {
        car->SetNavigation(lon, lat);
        car->GetNavigation();
    }
};
int Car::serialCreate = 0;
int main() {
// Create Car object pointer
    Car* normalCar = new NormalCar(300, 90.0f);
    Car* perfCar = new PerformanceCar(500, 120.0f);

// Create Person object pointer
    Person* engineer = new Engineer();
    Person* user = new User();
    PerformanceCar* realPerfCar = dynamic_cast<PerformanceCar*>(perfCar);

    std::cout << "\n******** Engineer Actions ***********\n";
// Cast to the correct Engineer class to call the private function
    Engineer* engPtr = dynamic_cast<Engineer*>(engineer);
    if (engPtr) {
    //Engineer actions Normal Car
        std::cout << "--- Engineer Actions Normal Car ---\n";
        engineer->DriveCar(normalCar);
        engineer->ReadEngineSpeed(normalCar);
        engineer->ReadEnginePower(normalCar);
        engPtr->ReadSerialNumber(normalCar);

    //Engineer actions performance Car
        std::cout << "\n--- Engineer Actions Performance Car ---\n";
        engineer->DriveCar(perfCar);
        engineer->ReadEngineSpeed(perfCar);
        if (realPerfCar) {
           realPerfCar->ActiveTurbo();
           std::cout << "Turbo Activated boost ";
           engineer->ReadEngineSpeed(realPerfCar);
    }
        engineer->ReadEnginePower(perfCar);
        engPtr->ReadSerialNumber(perfCar);
        engPtr->ProgramNavigation(dynamic_cast<PerformanceCar*>(perfCar), 45.76f, -73.57f);
    }

    std::cout << "\n******** User Actions ***********\n";
// Cast to the correct User class to call the private function
    User* userPtr = dynamic_cast<User*>(user);
    if (userPtr) {
        std::cout << "--- User Actions Normal Car ---\n";
        user->DriveCar(normalCar);
        user->ReadEngineSpeed(normalCar);  
        user->ReadEnginePower(normalCar);

        std::cout << "\n--- User Actions Performance Car---\n";
        user->DriveCar(perfCar);
        user->ReadEngineSpeed(perfCar);  
        user->ReadEnginePower(perfCar);
        userPtr->PositionCar(dynamic_cast<PerformanceCar*>(perfCar), 48.85f, 2.35f);
    }

    delete normalCar;
    delete perfCar;
    delete engineer;
    delete user;

    return 0;
}