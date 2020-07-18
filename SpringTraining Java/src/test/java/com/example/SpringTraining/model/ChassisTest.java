package com.example.SpringTraining.model;

import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class ChassisTest {
    List<Wheel> wheelList = new ArrayList<Wheel>();
    Chassis chassis = new Chassis(wheelList);
    @Test
    public void numberOfWheelsTest(){
        for (int i = 0; i < 4; i++) {
            wheelList.add(new Wheel());
        }
        Assert.assertEquals(4, chassis.wheels.size());
    }

}
