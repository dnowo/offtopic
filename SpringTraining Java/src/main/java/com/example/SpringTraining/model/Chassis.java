package com.example.SpringTraining.model;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class Chassis {

    List<Wheel> wheels;
    Engine engine;

    @Autowired
    public Chassis(List<Wheel> wheels) {
        this.wheels = wheels;
        System.out.println("Creating Chassis");
        printWheels();
    }
    public void printWheels(){
        wheels.forEach(Wheel::getId);
    }

    /**
     * I know that it should be the other way, I mean: First create Engine then Chassis. It's only for learning 'lazy' injection.
     */

    @Autowired
    public void setEngine(Engine engine) {
        this.engine = engine;
        System.out.println("Engine injection!");
        checkEngine();
    }

    public void checkEngine(){
        System.out.println(this.engine.getModelName());
    }
}
