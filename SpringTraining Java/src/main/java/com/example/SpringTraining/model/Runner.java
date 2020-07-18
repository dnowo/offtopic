package com.example.SpringTraining.model;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.stereotype.Component;

@Component
public class Runner implements ApplicationRunner {
    Car car;
    @Autowired
    public Runner(Car car) {
        this.car = car;
    }

    @Override
    public void run(ApplicationArguments args) throws Exception {
        System.out.println(car.getBrand());
        System.out.println(car.getType());
        System.out.println(car.getClass());
    }
}
