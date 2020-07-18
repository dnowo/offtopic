package com.example.SpringTraining.model;

import org.springframework.stereotype.Component;

@Component
public class Body {
    private String color;

    public Body() {
        this.color = "RED";
    }

    public String getColor() {
        return color;
    }
}
