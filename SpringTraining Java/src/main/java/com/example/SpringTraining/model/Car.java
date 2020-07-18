package com.example.SpringTraining.model;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class Car {
    private Body body;
    private Chassis chassis;
    private String type;
    private String brand;

    @Autowired
    public Car(Body body, Chassis chassis) {
        this.body = body;
        this.chassis = chassis;
        this.brand = "VolksWagen";
        this.type = "Sedan";
        System.out.println("Car created!");
    }

    public String getType() {
        return type;
    }

    public String getBrand() {
        return brand;
    }
}
