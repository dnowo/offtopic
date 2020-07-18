package com.example.SpringTraining.model;

import org.springframework.stereotype.Component;

@Component
public class Engine {
    private String modelName;

    public Engine() {
        modelName = "1.9 TDI, 132km, Diesel";
    }

    public String getModelName() {
        return modelName;
    }
}
