package com.example.SpringTraining.model;

import org.springframework.stereotype.Component;


public class Wheel {
    private static int i = 0;
    private final int id = i;
    public Wheel() {
        System.out.println("Creating wheel:" + i);
        i++;
    }

    public void getId() {
        System.out.println(id);
    }
}
