package com.example.SpringTraining.model;


import org.junit.Assert;
import org.junit.Test;

public class BodyTest {
    Body body = new Body();

    @Test
    public void colorTest(){
        Assert.assertEquals("RED" ,body.getColor());
    }
}
